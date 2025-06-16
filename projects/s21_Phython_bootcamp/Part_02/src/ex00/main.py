from multiprocessing import Queue, Lock, Process
from modules.class_examiner import Examiner
from modules.class_student import Student
from modules.class_exam_information_board import ExamInformationBoard  
import os
import time


def read_data_from_files(data_dir="exam_data"):
    try:
        with open(os.path.join(data_dir, "students.txt"), 'r', encoding='utf-8') as f:
            students = [line.strip() for line in f if line.strip()]
        with open(os.path.join(data_dir, "examiners.txt"), 'r', encoding='utf-8') as f:
            examiners = [line.strip() for line in f if line.strip()]
        with open(os.path.join(data_dir, "questions.txt"), 'r', encoding='utf-8') as f:
            questions = [line.strip() for line in f if line.strip()]
        return students, examiners, questions
    except Exception as e:
        print(f"Ошибка при чтении файлов: {e}")
        raise

def create_students_queue(students_list):
    queue = Queue()
    for student_name in students_list:
        queue.put(Student(student_name))
    return queue

def run_examiner(examiner):
    examiner._examine_students()

def run_exam_information_board(info_board):
    info_board.start_the_board()

def main():
    """Общая схема работы следующая:
    - экзаменаторы запускаются в отдельных процессах
    - забирают студентов из очереди и помещают в соответствующее поле класса
    - после помещают в очередь для результатов экзамена сообщение о начале экзаменации данного студента (для обновления табло с данными)
    - далее, допрашивают жертву, общаясь через callback-функцию для ответа студента
    - ставят оценку и записывают результаты в очередь результатов
    - табло фильтрует сообщения из очереди по имени класса-контейнера, используемого для передачи данных"""
    try:
        os.system('cls' if os.name == 'nt' else 'clear')
        # Загружаем данные
        students, examiners, questions = read_data_from_files()
        # Создаем межпроцессорные очереди и замки
        students_queue = create_students_queue(students)
        exam_results_queue = Queue()
        student_lock = Lock()
        results_lock = Lock()
        # Создаем табло
        info_board = ExamInformationBoard(
            results_queue=exam_results_queue,
            all_students=students,
            examiners=examiners
        )
        # Запускаем в отдельном процессе
        board_process = Process(target=run_exam_information_board, args=(info_board,))
        board_process.start()

        # Стартуем экзаменаторов
        examiners_processes = []
        for examiner_name in examiners:
            examiner = Examiner(
                name=examiner_name,
                students_queue=students_queue,
                student_queue_lock=student_lock,
                exam_results_queue=exam_results_queue,
                exam_results_queue_lock=results_lock,
                questions=questions
            )
            p = Process(target=run_examiner, args=(examiner,))
            p.start()
            examiners_processes.append(p)

        # Завершаем экзамены
        for p in examiners_processes:
            p.join()
        board_process.join()
    except Exception as e:
        print(f"Ошибка: {e}")
        return 1

if __name__ == "__main__":
    main()