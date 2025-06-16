import random
import time
import threading
from multiprocessing import Process, Value
from multiprocessing import Lock
from typing import List, Dict, Union
from dataclasses import dataclass
from .class_student import Student
from .data_classes import ExamResult, ExamStartEvent

class Examiner:
    _remaining_students = None
    _exam_results_queue = None  
    _student_queue_lock = None
    _exam_results_queue_lock = None
    _current_student = None
    _students_answer = None
    _exam_time = None
    _time_before_lunch = 30
    _lunch_time_range = 12, 18
    _actual_lunch_time = None
    _mood_variants = ["good", "bad", "neutral"]
    _mood_probabilities = [1/4, 1/8, 5/8]
    _actual_mood = None
    _next_question_probability = 1/3
    _isLunchFinished = False
    _total_students: int = 0
    _failed_students: int = 0
    _work_time: float = 0.0

    def _calculate_lunch_delay(self):
        return random.randint(*self._lunch_time_range)
    
    def _calculate_mood(self):
        return random.choices(self._mood_variants, weights=self._mood_probabilities, k=1)[0] 

    def _calculate_exam_time(self):
        return random.randint(len(self._name)-1, len(self._name)+1)

    def __init__(self, name, students_queue, student_queue_lock, exam_results_queue, exam_results_queue_lock, questions):
        self._dbg_is_running = True
        self._name = name        
        self._questions = questions
        self._remaining_students = students_queue
        self._student_queue_lock = student_queue_lock
        self._exam_results_queue_lock = exam_results_queue_lock
        self._exam_results_queue = exam_results_queue
        self._exam_time = self._calculate_exam_time()
        self._actual_lunch_time = self._calculate_lunch_delay()
        self._actual_mood = self._calculate_mood()

    def _set_student(self):
        """Загружаем студента из очереди на экзамен"""
        with self._student_queue_lock:
            if not self._remaining_students.empty():
                # Загружаем студента из очереди на расправу
                self._current_student = self._remaining_students.get()
                # отправляем координаты функции для звонка обратно внутрь класса студента
                self._current_student.set_answers_callback(self.students_answer)
                return True
        return False
    
    def students_answer(self, students_answer: str):
        """callback-метод передаваемый студенту для возможности ответа"""
        self._students_answer = students_answer

    def _start_lunch(self):
        """Метод для осуществления обеда"""
        time.sleep(self._actual_lunch_time)
        self._isLunchFinished = True

    def _generate_correct_answers(self, question: str) -> List[str]:
        """Генерирует список правильных ответов на основе вопроса"""
        question_by_words = question.split()
        correct_answers = set()
        correct_answers.add(random.choice(question_by_words))
        
        while True:
            remaining_words = [word for word in question_by_words if word not in correct_answers]
            if not remaining_words:
                break
            if random.random() < self._next_question_probability:
                correct_answers.add(random.choice(remaining_words))
            else:
                break
                
        return list(correct_answers)

    def _evaluate_answers(self, questions_and_answers: List[Dict[str, Union[str, List[str]]]]):
        """Ставим оценку"""
        correct_answers_count = 0
        incorrect_answers_count = 0

        for item in questions_and_answers:
            student_answer = item["student_answer"]
            correct_answers = item["correct_answers"]

            if student_answer in correct_answers:
                correct_answers_count += 1
            else:
                incorrect_answers_count += 1

        # Ставим оценку
        if self._actual_mood == "good":
            return True  
        elif self._actual_mood == "bad":
            return False  
        else:
            # neutral                
            return correct_answers_count > incorrect_answers_count  

    def _examine_students(self):
        """Экзаменуем студентов"""
        exam_start = time.perf_counter()
        while True:
            # Проверяем, не кончились ли студенты
            if not self._set_student():
                break 
            # Фиксируем начало экзаменации студента для информационного табло
            start_event = ExamStartEvent(
                examiner_name=self._name,
                student_name=self._current_student._name
            )
            with self._exam_results_queue_lock:
                self._exam_results_queue.put(start_event)
            # Экзаменуем и фиксируем вопросы и ответы
            questions_and_answers : List[Dict[str, Union[str, List[str]]]] = []
            for _ in range(3):
                question = random.choice(self._questions)
                self._current_student.set_question(question)
                self._current_student.get_answer()

                correct_answers = self._generate_correct_answers(question)

                questions_and_answers.append({
                    "question": question,
                    "correct_answers": correct_answers,
                    "student_answer": self._students_answer
                })
            # Ставим оценку
            isPassed = self._evaluate_answers(questions_and_answers)
            self._current_student.set_exam_result(isPassed)
            # Обновляем статистику
            self._total_students += 1
            if not isPassed:
                self._failed_students += 1
            self._work_time += self._exam_time
            # Ждем время до конца экзамена
            time.sleep(self._exam_time)    
            # Отправляем результаты экзамена на табло
            result = ExamResult(
                student_name=self._current_student._name,
                is_passed=isPassed,
                examiner_name=self._name,
                total_students=self._total_students,
                failed_students=self._failed_students,
                work_time=self._work_time,
                questions_and_answers=questions_and_answers
            )
            with self._exam_results_queue_lock:
                self._exam_results_queue.put(result)
            # Если экзаменатор еще не обедал, проверяем, не пора ли?
            if not self._isLunchFinished and \
            (time.perf_counter() - exam_start) >= self._time_before_lunch:            
                if self._current_student: 
                    time.sleep(self._exam_time)
                self._start_lunch()     
            self._current_student = None