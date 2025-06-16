        
def create_Pascal_triangle(lines_remain:int, triangle:list[list[int]])->list[list[int]]:
    if (lines_remain > 0):
        """ вычисляем"""
        last_triangle_line = triangle[-1]
        new_line:list[int] = [1]
        for i in range(len(last_triangle_line)-1):
            actual_number = last_triangle_line[i]+last_triangle_line[i+1]
            new_line.append(actual_number)
        new_line.append(1)
        lines_remain-=1
        triangle.append(new_line)
        return create_Pascal_triangle(lines_remain, triangle)
    else:
        return triangle

def paskal_triangle(lines_in_triangle):  
    """ Строим треугольник Паскаля """  
    if(lines_in_triangle == 1):
        print(lines_in_triangle)
    elif(lines_in_triangle == 2):
        print("1\n1, 1")
    else:
        triangle:list[list[int]] = [[1], [1, 1]]
        Pascal_triangle = create_Pascal_triangle(lines_in_triangle-2, triangle)
        for line in Pascal_triangle:
            print(str(line)[1:-1]) # приводим к строковому виду и выбрасываем скобки спереди и сзади

def main():
    while(True):
        try:
            t = input("Enter the number of lines to create a Pascal Triangle (or q for exit): ")
            if t.lower() == 'q' or  t.lower() == 'e':
                exit()
            else:
                lines_in_triangle = int(t)
        except ValueError:
            print("Sorry, it wasn't an int number. You can try again.")
        else:
            if (lines_in_triangle > 0):
                paskal_triangle(lines_in_triangle)    
            else:
                print("Don't play with me!! The number must be an integer greater than zero!")

if (__name__ == "__main__"):
    main()