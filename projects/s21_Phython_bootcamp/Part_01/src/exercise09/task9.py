class Polynomial: 
    """ коэфициенты расположены как в уравнении - в порядке убывания степени """
    def __init__(self, highest_degree:int, coefficients:list[float]):
        self.__coefficients = coefficients
        self.__highest_degree = highest_degree
        self.__set_polynomial_string()
        self.__set_derivative_string()

    def derivative_at(self, point:float)->float:
        """ Производная в точке. Формула производной для x^(n): nx^(n−1), производная константы равна 0. Производная многочлена равна сумме производных членов. """
        derivative_at_point = 0.0
        for actual_degree in range(self.__highest_degree, 0, -1):
            actual_coefficient = self.__coefficients[-actual_degree-1]
            derivative_at_point += actual_degree * actual_coefficient * point**(actual_degree-1) 
        return derivative_at_point

    @property
    def polynomial(self):
        return self.__polynomial_string
    
    @property
    def derivative(self):
        return self.__derivative_string

    def __set_polynomial_string(self):
        self.__polynomial_string = ""
        if self.__highest_degree == 0:
            self.__polynomial_string = '0'
            return
        # обратный ряд, коэфициенты считаются сзади.
        for d in range(self.__highest_degree, 0, -1): 
            self.__polynomial_string += str(self.__coefficients[-d-1]) + ' * ' + 'x^' + str(d) + ' + '
        self.__polynomial_string += str(self.__coefficients[-1])
    
    def __set_derivative_string(self):
        self.__derivative_string = ""
        if self.__highest_degree == 0:
            self.__derivative_string = '0'
            return
        for d in range(self.__highest_degree, 1, -1):
            self.__derivative_string += str(d) + ' * ' + str(self.__coefficients[-d-1]) + ' * ' + 'x^' + str(d - 1) + ' + '
        self.__derivative_string = self.__derivative_string + str(self.__coefficients[-2])

def get_data_from_user():
    try:
        hd = int(input("Enter the highest degree of polynomial: "))
        if hd < 0:
            print("Dont't play with me!! EXIT!!")
            exit()
        derivative_point = float(input("Enter the point of calculating the derivative: "))
        coefficients = []
        for i in reversed(range(hd+1)):
            c = float(input(f"Enter the coefficient for x^{i}: "))
            coefficients.append(c)
        print(f"\nВерхняя степень: {hd}\nКоофициенты: {coefficients}\nТочка вычисления производной: {derivative_point}")
    except ValueError:
        print("Dont't play with me!! EXIT!!")
        exit()
    else:
        return Polynomial(hd, coefficients), derivative_point

def main():
    polynomial, derivative_point = get_data_from_user()
    # polynomial = Polynomial(2, [5, 1.2, -3])
    print(f"\nПолином: {polynomial.polynomial}")
    print(f"Производная: {polynomial.derivative}")
    d = polynomial.derivative_at(derivative_point)
    print(f"\nПравильный ответ... => {d:.3f}")    

if __name__ == "__main__":
    main()