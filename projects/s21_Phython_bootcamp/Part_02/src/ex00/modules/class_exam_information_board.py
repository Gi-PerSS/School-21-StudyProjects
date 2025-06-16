import time
from prettytable import PrettyTable
from multiprocessing import Queue
from collections import defaultdict
from .data_classes import ExamResult, ExamStartEvent
import os
import queue

class ExamInformationBoard:
    """Табло отрисовки результатов экзаменов"""
    def __init__(self, results_queue: Queue, all_students: list, examiners: list):
        self.results_queue = results_queue
        self.all_students = all_students
        self.start_time = time.time()
        # создаем словарь с данными по каждому из экзаменаторов
        self.examiners = {name: {'current': '-', 'total': 0, 'failed': 0, 'time': 0.0} for name in examiners}
        # создаем словарь статуса сдачи для каждого из студентов
        self.students_status = {name: "Очередь" for name in self.all_students}
        self.final_results = []
        # Создаем словарь для хранения статистики по вопросам. Дефолтный словарь вызывает указанную лямбда-функцию при попытке добавления нового значения, здесь - списка из двух интов-нолей.
        self.questions_stats = defaultdict(lambda: [0, 0])  # [correct, total]
        self.best_students = []
        self.exam_duration = 0.0
        self.total_students = len(all_students)
        self.processed_students = 0
    

    def update_data(self):
        """Обновляем данные"""
        while not self.is_exam_finished():
            try:
                event = self.results_queue.get_nowait()
                # сигнал о начале экзаменации студента
                if isinstance(event, ExamStartEvent):
                    examiner_name = event.examiner_name
                    student_name = event.student_name
                    if examiner_name in self.examiners:
                        self.examiners[examiner_name]["current"] = student_name
                # результаты законченного экзамена
                elif isinstance(event, ExamResult):
                    self._process_result(event)
                    self.final_results.append(event)
                    self.processed_students += 1
            except queue.Empty:
                break

    def _process_result(self, result):
        """
        Обрабатываем результаты экзамена:
        - Статус студента
        - Статистику экзаменатора
        - Статистику по вопросам
        """
        # Тернарный оператор
        self.students_status[result.student_name] = "Сдал" if result.is_passed else "Провалил"
        # извлекаем имя экзаменатора и обновляем данные
        examiner = self.examiners[result.examiner_name]
        examiner['total'] = result.total_students
        examiner['failed'] = result.failed_students
        examiner['time'] = result.work_time
        examiner['current'] = '-' 
        # считаем статистику по качеству вопросов
        for item in result.questions_and_answers:
            question = item["question"]
            student_answer = item["student_answer"]
            # Всего ответов на данный вопрос
            self.questions_stats[question][1] += 1
            # Число правильных ответов
            if student_answer in item["correct_answers"]:
                self.questions_stats[question][0] += 1

    def is_exam_finished(self):
        return self.processed_students == len(self.all_students)

    def start_the_board(self):
        """Запускаем табло и общий отчет"""
        while True:
            self.display_real_time_stats()
            time.sleep(0.01)
            if self.is_exam_finished():
                break
        self.display_final_report()

    def display_real_time_stats(self):
        """Диспетчер отрисовки"""
        self._clear_console()
        self.update_data()
        self._display_students_table()
        self._display_examiners_table()
        self._display_progress_info()

    def _clear_console(self):
        os.system('cls' if os.name == 'nt' else 'clear')

    def _sort_students_by_status(self):
        """Сортировка по статусу: Очередь -> Сдал -> Провалил
        """
        # Словарь приоритета сортировки по статусу
        status_order = {"Очередь": 0, "Сдал": 1, "Провалил": 2}
        
        # Сортируем словарь статусов студентов, используя приоритет из status_order
        return sorted(
            self.students_status.items(),
            key=lambda x: status_order.get(x[1])
        )

    def _display_students_table(self):
        """Выводит таблицу со статусами студентов в реальном времени"""
        table = PrettyTable()
        table.field_names = ["Студент", "Статус"]
        table.align = "l"

        # Получаем отсортированный список студентов
        sorted_students = self._sort_students_by_status()

        for student, status in sorted_students:
            table.add_row([student, status])
        
        print(table)

    def _display_examiners_table(self):
        """Экзаменаторы"""
        table = PrettyTable()
        table.field_names = ["Экзаменатор", "Текущий студент", "Всего", "Завалил", "Время работы"]
        table.align = "l"
        
        # Тип данных self.examiners:
        #  Dict[str, Dict[str, Union[str, int, float]]]
        # Извлекаем данные из словаря в таблицу
        for name, data in self.examiners.items():
            table.add_row([
                name,
                data['current'],
                data['total'],
                data['failed'],
                f"{data['time']:.1f} сек"
            ])
        
        print("\n" + str(table))

    def _display_progress_info(self):
        """Прогресс"""
        # создаем список из единиц и суммируем, по числу статуса "Очередь"
        remaining = sum(1 for s in self.students_status.values() if s == "Очередь")
        elapsed = time.time() - self.start_time
        
        print(f"\nОсталось в очереди: {remaining} из {len(self.all_students)}")
        print(f"Прошло времени: {elapsed:.1f} сек")

    def display_final_report(self):
        """Общий отчет"""
        self.exam_duration = time.time() - self.start_time
        
        self._calculate_best_students()
        best_examiners = self._calculate_best_examiners()
        best_questions = self._calculate_best_questions()
        exam_success = self._calculate_exam_success()
        expelled = self._generate_expelled_list()

        print("\n=== ФИНАЛЬНЫЙ ОТЧЕТ ===")
        self._display_students_final_table()
        self._display_examiners_final_table()

        self._display_time_summary()
        self._display_top_metrics(best_examiners, best_questions)
        self._display_expelled(expelled)
        self._display_exam_verdict(exam_success)

    def _calculate_best_students(self):
        """Лучший студент тот, кто попал к самому быстрому экзаменатору"""
        # поля класса смотри в data_classes
        # фильтруем успешно сдавших и формируем список кортежей из имен и времени экзамена
        passed_students = [(r.student_name, r.work_time) for r in self.final_results if r.is_passed]
        # Находим минимальное время сдачи и все имена с этим временем
        if passed_students:
            min_time = min(t for _, t in passed_students)
            self.best_students = [name for name, t in passed_students if t == min_time]

    def _calculate_best_examiners(self):
        """Рассчитывает рейтинг экзаменаторов по проценту провалов"""
        examiner_stats = []
        # создаем список кортежей из имени и словаря с данными
        for name, data in self.examiners.items():
        # делим количество проэкзаменованных на количество завалов
            if data['total'] > 0:
                fail_rate = data['failed'] / data['total']
                examiner_stats.append((name, fail_rate))

        # Извлекаем минимальный рейтинг завалов и возвращаем имена всех, кто соответствует 
        best_examiners = []
        min_fail_rate = min(r for _, r in examiner_stats)
        best_examiners = [name for name, r in examiner_stats if r == min_fail_rate]
        return best_examiners

    def _calculate_best_questions(self):
        """Вычисляем лучшие вопросы"""
        # словарь - {question: [correct_answers, total_answers]}
        max_correct = max(stats[0] for stats in self.questions_stats.values())
        # Извлекаем все вопросы с максимальным числом правильных ответов
        return [q for q, stats in self.questions_stats.items() if stats[0] == max_correct]

    def _generate_expelled_list(self):
        """Список отчисляемых"""
        failed_with_time = [(r.student_name, r.work_time) for r in self.final_results if not r.is_passed]
        if not failed_with_time:
            return []
            
        min_fail_time = min(t for _, t in failed_with_time)
        return [name for name, t in failed_with_time if t == min_fail_time]

    def _calculate_exam_success(self):
        """успешный экзамен > 85% сдавших"""
        total_passed = sum(1 for r in self.final_results if r.is_passed)
        return total_passed / len(self.all_students) > 0.85

    def _display_students_final_table(self):
        """Результаты"""
        table = PrettyTable()
        table.field_names = ["Студент", "Результат"]
        table.align = "l"

        sorted_students = self._sort_students_by_status()

        for student, status in sorted_students:
            table.add_row([student, status])
        print(table)

    def _display_examiners_final_table(self):
        """Экзаменаторы"""
        table = PrettyTable()
        table.field_names = ["Экзаменатор", "Всего", "Завалил", "Время работы"]
        table.align = "l"

        for name, data in self.examiners.items():
            table.add_row([
                name,
                data['total'],
                data['failed'],
                f"{data['time']:.1f} сек"
            ])
        print("\n" + str(table))

    def _display_time_summary(self):
        """Время"""
        print(f"\nВремя экзамена: {self.exam_duration:.1f} сек")

    def _display_top_metrics(self, best_examiners, best_questions):
        """ Лучшие: студенты, экзаменаторы, вопросы"""
        print(f"Лучшие студенты: {', '.join(self.best_students)}")
        print(f"Лучшие экзаменаторы: {', '.join(best_examiners)}")
        print(f"Лучшие вопросы: {', '.join(best_questions)}")

    def _display_expelled(self, expelled):
        print(f"Отчисляемые: {', '.join(expelled)}")

    def _display_exam_verdict(self, exam_success):
        print(f"Вывод: {'экзамен удался' if exam_success else 'экзамен не удался'}")