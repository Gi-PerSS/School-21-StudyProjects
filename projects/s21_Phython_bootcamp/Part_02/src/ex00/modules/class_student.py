import random

class Student:
    def __init__(self, name):
        self._name = name
        self._sex = name[-1]
        self._question_by_words = None
        self._question = None
        self._answer_weights = None
        self._isPassed = None
        self._current_question = None
        self._answers_callback = None

    def set_exam_result(self, is_pass: bool):
        self._isPassed = is_pass

    def get_exam_result(self):
        return self._isPassed

    def _calculate_answer_weights(self):
        """Вычисляем веса вероятности выбора для слов вопроса"""
        self.f = 1.618 # правильное значение золотого сечения       
        question_lenght = len(self._question_by_words)
        _answer_weights = []
        remaining_weight = 1.0     
        # экпоненциально убывающая вероятность для каждого последующего слова вопроса быть выбранным правильным ответом
        for i in range(question_lenght - 1):
            current_weight = remaining_weight / self.f
            _answer_weights.append(current_weight)
            remaining_weight -= current_weight
        _answer_weights.append(remaining_weight)
         # для девочек переворачиваем порядок весов
        if self._sex == "Ж":
            _answer_weights = _answer_weights[::-1]
        self._answer_weights = _answer_weights
    
    def set_answers_callback(self, callback_method):
        """Устанавливаем метод для возврата ответа экзаменатору"""
        self._answers_callback = callback_method

    def set_question(self, question: str):
        """Делим вопрос на отдельные слова"""
        self._question = question
        self._question_by_words = self._question.split()        
    
    def get_answer(self):
        """Создаем ответ и отправляем экзаменатору"""
        self._calculate_answer_weights()       
        result = random.choices(self._question_by_words, weights=self._answer_weights, k=1)[0]
        self._answers_callback(result)