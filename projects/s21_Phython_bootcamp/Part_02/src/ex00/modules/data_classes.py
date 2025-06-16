from dataclasses import dataclass
from typing import List, Dict, Union
from multiprocessing import Queue

@dataclass
class ExamResult:
    """Класс-контейнер для передачи данных в информационное табло от экзаменатора"""
    student_name: str
    is_passed: bool
    examiner_name: str
    total_students: int
    failed_students: int
    work_time: float
    questions_and_answers: List[Dict[str, Union[str, List[str]]]]


@dataclass
class ExamStartEvent:
    """Класс-контейнер для передачи сообщения на табло о начале экзаменации конкретного студента"""
    examiner_name: str
    student_name: str