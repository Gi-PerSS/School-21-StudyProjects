def scalar_product_1(x_input:str, y_input:str)->float:
    """ - Разбиваем на строки-числа
        - применяем к каждому функцию конверсии во float
        - превращаем итератор в кортеж
        - сливаем 2 кортежа в пары и умножаем их члены друг на друга
        - суммируем полученный кортеж
    """
    xf : tuple[float] = tuple(map(float, x_input.split())) 
    yf : tuple[float] = tuple(map(float, y_input.split()))
    # zip соединяет в пары элементы данных списков, возвращая кортеж из пар
    t = tuple(map(lambda t: t[0]*t[1], zip(xf, yf)))
    r = sum(t)
    return r

def scalar_product_2(x_input:str, y_input:str)->float:
    """ Разбиваем списки на подстроки и обрабатываем в цикле """
    xs: list[str] = x_input.split()
    ys: list[str] = y_input.split()
    r : float = 0
    for i in range(3):
        r+=float(xs[i])*float(ys[i])
    return r

def scalar_product_3(x_input: str, y_input: str) -> float:
    """Вычисляет скалярное произведение двух векторов, заданных строками."""
    x_values = map(float, x_input.split())
    y_values = map(float, y_input.split())
    return sum(x * y for x, y in zip(x_values, y_values))

def main():
    x : str = input("Enter a vector of 3 real numbers. Use a dot as a separator for the fractional part: ")
    y : str= input("Enter a second vector of 3 real numbers. Use a dot as a separator for the fractional part: ")
    print(f'x = {x}, and y = {y}')
    print("Method 1 result = ", scalar_product_1(x,y))
    print("Method 2 result = ", scalar_product_2(x,y))
    print("Method 2 result = ", scalar_product_3(x,y))

if __name__ == "__main__":
    main()