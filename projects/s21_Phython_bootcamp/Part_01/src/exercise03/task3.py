import os

def load_matrix(file_path):
    """ Извлекаем цифры, преобразуем в int, генерируем список """
    with open(file_path, "r" ) as data_file:
        field_matrix = [list(map(int, line.split())) for line in data_file]
    return field_matrix

def CheckIfSquare(field_matrix:list[list[int]], figure_coords:list[tuple[int, int]])->bool:
    """ Проверяем на квадратность. По условию задания, если фигура не правильный квадрат, то она круг, поэтому просто проверяем левый верхний угол."""
    y, x = figure_coords[0]
    rows, cols = GetMatrixDimension(field_matrix)
    # Если первая точка фигуры на краю поля, это квадрат
    # Если точка вниз по диагонали на 1 позицию от первой не относится к фигуре, то фигура имеет угол, значит квадрат.
    if (x == 0 or y == rows-1 or field_matrix[y+1][x-1]==0):
        return True
    else:
        return False

def GetMatrixDimension(field_matrix: list[list[int]])->tuple[int, int]:
    return (len(field_matrix), len(field_matrix[0]))

def ExtractFigureCoords(field_matrix, visited_matrix, y,x, figure_coords):
    """ Находим координаты облака точек фигуры, через проверку на смежность. Метод связных компонент."""
    rows, cols = GetMatrixDimension(field_matrix)
    
    # проверка на предмет выхода за пределы поля матрицы в процессе рекурсии
    if (y<0 or y>= rows or x<0 or x>= cols):
        return
    
    # если вне фигуры или клетка посещена, то скип.
    if (field_matrix[y][x]==0 or visited_matrix[y][x]):
        return
    
    # добавляем координаты точки в текущую фигуру
    figure_coords.append((y,x))
    visited_matrix[y][x]=True

    # проверяем окружение точки через рекурсивный вызов
    for i in range(y-1, y+1+1): # правое число range не входит в диапазон
        for j in range(x-1, x+2):
            ExtractFigureCoords(field_matrix, visited_matrix, i, j, figure_coords)
            

def FindAFigures(field_matrix: list[list[int]]):
    """ Проходим матрицу, извлекая фигуры"""
    squares = 0
    circles = 0
    rows, cols = GetMatrixDimension(field_matrix)
    actual_figure = []

    # Генерируем пустую матрицу посещений
    visited = [[False for element in line] for line in field_matrix]
    
    for i in range(rows):
        for j in range(cols):
            if(field_matrix[i][j] == 1 and not visited[i][j]):
                actual_figure = []
                ExtractFigureCoords(field_matrix, visited, i, j, actual_figure)                
                if(CheckIfSquare(field_matrix, actual_figure)):
                    squares+=1
                else:
                    circles+=1
    return (squares, circles)

def main():
    # test_dir = os.path.join(os.path.dirname(__file__), "test_files")
    test_dir = input("Enter the path to the directory with the test files. (test_files or '.' for example) ")
    
    for filename in os.listdir(test_dir):
        os.system('clear')
        if filename.endswith(".txt"): 
            file_path = os.path.join(test_dir, filename)
            field_matrix = load_matrix(file_path)
            print(f'{filename}:\n')
            for row in field_matrix:
                print(' '.join(map(str, row)))
            s, c = FindAFigures(field_matrix)
            print(f'\nSquares = {s}, Circles = {c}\n')
            t=input("Only 'Enter' lead to the next slide... ")
            if(t != ""):
                print("Hmmm... :)")
                break

if __name__ == "__main__":
    main()