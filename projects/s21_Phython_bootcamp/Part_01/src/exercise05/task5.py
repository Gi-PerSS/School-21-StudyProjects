import string
from functools import reduce

class s21_float:
    # конструктор класса, как класса
    def __new__(cls, string_float):
        if not isinstance(string_float, str):
            raise TypeError("Input must be a string")
        normalized_number = cls.normalize_number(string_float) 
        if cls.check_entered_data(normalized_number): 
            return cls.make_float_from_string(normalized_number) 
        else:
            raise ValueError("could not convert string to float")
            
    @classmethod
    def check_entered_data(cls, number: str) -> bool:
        """ Проверяем:
        - присутствуют только допустимые символы
        - в приемлемых количествах
        - в правильном порядке
        """
        if len(number) == 1 and not number.isdigit():
            return False
        
        if number == "":
            return False

        acceptable_characters = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '.', 'e'}

        if any(char not in acceptable_characters for char in number):
            return False
        
        if number.count('.') > 1 or number.count('e') > 1:
            return False
        
        if number.count('+') + number.count('-') > 2:  
            return False  # Больше двух знаков быть не может
        
        signs = set("+-")
        e_position = number.find('e')

        for i, char in enumerate(number):
            if char in signs:
                # знак допустим в начале строки или после 'e'
                if not (i == 0 or (e_position != -1 and i == e_position + 1)):
                    return False
                # Проверяем, что после знака есть цифра
                if i == len(number) - 1 or not number[i + 1].isdigit():
                    return False
        
        # до и после E должна быть цифра, после может быть предваряющий знак и после E не должно быть точек
        if e_position != -1:
            if e_position == len(number) - 1 or e_position == 0:
                return False  # если E в конце или в начале
            before_e_digit: bool = number[e_position - 1].isdigit()
            after_e_sign: bool = number[e_position + 1] == '-' or number[e_position + 1] == '+'

            if after_e_sign:
                digit_after_e_position = 2
            else:
                digit_after_e_position = 1

            after_e_digit: bool = number[e_position + digit_after_e_position].isdigit() 
            dot_after_e: bool = number[e_position:].find('.') != -1

            if not before_e_digit or not after_e_digit or dot_after_e:
                return False
            
        return True
    
    @classmethod
    def normalize_number(cls, str_number: str) -> str:
        nd_str_number = str_number.replace(',', '.')
        if nd_str_number == ".":
            nd_str_number = ""  # исключаем превращение точки в 0.0
        nd_str_number = nd_str_number.lower()
        nd_str_number = nd_str_number.strip()
        # добавляем 0 для чисел типа .99 или 99.
        if nd_str_number.startswith('.'):
            nd_str_number = '0' + nd_str_number
        if nd_str_number.endswith('.'):
            nd_str_number = nd_str_number + '0'
        # добавляем 0 для чисел типа 99.e и -.99
        dot_position = nd_str_number.find('.')
        if dot_position != -1:
            for sign in ['+', '-']: 
                if nd_str_number.startswith(sign) and nd_str_number[1] == '.':
                    nd_str_number = nd_str_number[0] + '0' + nd_str_number[1:]
            if nd_str_number[dot_position + 1] == 'e':
                nd_str_number = nd_str_number[:dot_position] + '0' + nd_str_number[dot_position:]
        return nd_str_number
            
    @classmethod
    def make_int_from_string(cls, string_number: str) -> int:
        # вычленяем знак числа и делаем модуль для последующей обработки
        if not string_number[0].isdigit():
            abs_string_number = string_number[1:]
            if string_number[0] == '-':
                sign = -1
            if string_number[0] == '+':
                sign = 1
        else:
            abs_string_number = string_number
            sign = 1
        # делаем словарь сопоставлений строковых цифр с реальными
        int_digits = dict(zip(string.digits, range(10)))
        # функция reduce использует лямбду с 2-мя аргументами, чтобы через эту функцию свести ряд к одному значению, последний аргумент - инициализация аккумулятора.
        r = reduce(lambda result, char: result * 10 + int_digits[char], abs_string_number, 0)
        return r * sign

    @classmethod
    def get_fractional_part(cls, fractional_part_s: str) -> float:
        """Вычисляем дробную часть числа из строкового представления"""
        fractional_int = cls.make_int_from_string(fractional_part_s)
        return fractional_int / 10 ** len(fractional_part_s)

    @classmethod
    def make_float_from_string(cls, string_number: str) -> float:
        # извлекаем число
        float_number = 0.0
        # вычленяем знак числа и делаем модуль для последующей обработки
        if not string_number[0].isdigit():
            abs_string_number = string_number[1:]
            if string_number[0] == '-':
                sign = -1
            if string_number[0] == '+':
                sign = 1
        else:
            abs_string_number = string_number
            sign = 1
        
        # определяем экспоненту, если есть
        if (e_position := abs_string_number.find('e')) != -1:
            e_str = abs_string_number[e_position + 1:]
            e = 10 ** cls.make_int_from_string(e_str)        
            string_number_wt_e = abs_string_number[:e_position]
        else:
            e = 1
            string_number_wt_e = abs_string_number

        # выделяем целую и дробную части
        if (dot_position := string_number_wt_e.find('.')) != -1:
            int_part = cls.make_int_from_string(string_number_wt_e[:dot_position])
            fractional_part = cls.get_fractional_part(string_number_wt_e[dot_position + 1:])
            before_e = int_part + fractional_part
        else:
            before_e = cls.make_int_from_string(string_number_wt_e)

        float_number += before_e * e * sign
        return round(float_number, 15)

def main():
    
    while True:
        str_number = input("Enter the float-number (or q for exit): ")
        if str_number.lower() == 'q' or str_number.lower() == 'e':
            exit()
        try:
            float_number = s21_float(str_number)
        except:
            print("Are you kidding me? It's not a real number!!")
        else:
            result = 2 * float_number
            print(f"2 * {float_number} = {result: .3f}")

if __name__ == "__main__":
    main()