import random

def DBG_print_the_money_field(money_field):
    # Определяем максимальную длину числа в матрице
    max_length = max(len(str(num)) for row in money_field for num in row)    
    # Выводим матрицу с выравниванием по ширине
    for row in money_field:
        formatted_row = " ".join(f"{num:>{max_length}d}" for num in row)
        print(formatted_row)

def DBG_create_robot_path_table(money_field: list[list[int]], dp: list[list[int]]) -> list[list[str]]:
    """Создает таблицу dbg_path_table, содержащую значения money_field только для клеток маршрута."""
    rows = len(dp)  # Количество строк
    cols = len(dp[0])  # Количество столбцов

    # Создаем таблицу dbg_path_table, заполненную символами '-' (или нулями)
    dbg_path_table = [[0] * cols for _ in range(rows)]

    # Начинаем с правой нижней клетки (последняя строка, последний столбец)
    y, x = rows - 1, cols - 1

    # Добавляем значение из money_field для конечной клетки
    dbg_path_table[y][x] = money_field[y][x]

    # Восстанавливаем маршрут
    while y > 0 or x > 0:
        if y == 0:  # Если мы в первой строке, можем двигаться только влево
            x -= 1
        elif x == 0:  # Если мы в первом столбце, можем двигаться только вверх
            y -= 1
        else:
            # Выбираем, откуда пришли: сверху или слева
            if dp[y - 1][x] >= dp[y][x - 1]:  # Пришли сверху
                y -= 1
            else:  # Пришли слева
                x -= 1

        # Добавляем значение из money_field для текущей клетки
        dbg_path_table[y][x] = money_field[y][x]

    return dbg_path_table

def make_max_values_table(money_field:list[list[int]])->list[list[int]]:
    """ Размечаем сколько монет может принести достижение каждой из клеток таблицы """
    rows = len(money_field)
    cols = len(money_field[0])
    max_values_table = [[0] * cols for _ in range(rows)]

    # первая клетка
    max_values_table[0][0] = money_field[0][0]

    # первый ряд достижим только при движении вправо
    for x in range(1, cols):
        max_values_table[0][x] = max_values_table[0][x - 1] + money_field[0][x]

    # первый столбец достижим только при движении вниз
    for y in range(1, rows):
        max_values_table[y][0] = max_values_table[y-1][0] + money_field[y][0]

    # выбираем клетку слева или сверху от текущей, в зависимости от того, где больше денег
    for y in range(1, rows):
        for x in range(1, cols):
            max_values_table[y][x]=max(max_values_table[y-1][x], max_values_table[y][x-1]) + money_field[y][x]
    return max_values_table

def sow_the_field_with_money(rows: int, cols: int)->list[list[int]]:
    money_field = [[random.randint(0, 10) for _ in range(cols)] for _ in range(rows)]
    return money_field

def get_matrix_dimensions():
    while True:
        rows_input = input("Enter the number of rows (or 'q' to exit): ")
        if rows_input.lower() == 'q':
            exit()
        cols_input = input("Enter the number of columns (or 'q' to exit): ")
        if cols_input.lower() == 'q':
            exit()
        
        try:
            rows = int(rows_input)
            cols = int(cols_input)
            
            if rows <= 0 or cols <= 0:
                print("Dimensions must be positive integers!")
                continue
                
        except ValueError:
            print("You couldn't overcome the task. But you can try again.")
        else:
            return rows, cols

def money_manual_input(rows: int, cols: int) -> list[list[int]]:
    money_field = []    
    for y in range(rows):
        while True:
            try:                
                row_input = input(f"Enter {cols} values for row {y} separated by spaces: ")    
                row = list(map(int, row_input.split()))                
                money_field.append(row)
                break
            except ValueError:
                print("Something went wrong... Try again may be...")    
    return money_field

def main():
    rows, cols = get_matrix_dimensions()
    # rows, cols = 5, 7

    t = input("Дальше есть два варианта: 1) автоматическое заполнение ячеек случайными значениями, 2) ручной ввод количества денег для каждой ячейки. Какой выберешь ты?: ")

    if t == '1':
        money_field = sow_the_field_with_money(rows, cols)
    else:
        money_field = money_manual_input(rows, cols)

    print("\nMoney in cells:")
    DBG_print_the_money_field(money_field)
    
    max_values_table = make_max_values_table(money_field)
    # DBG_print_the_money_field(max_values_table)
    r = max_values_table[rows-1][cols-1]
    print(f"\nmax money value = {r}")

    # путь робота
    print(f"\nПуть робота: ")
    dbg_path_table = DBG_create_robot_path_table(money_field, max_values_table)
    DBG_print_the_money_field(dbg_path_table)

if __name__ == "__main__":
    main()