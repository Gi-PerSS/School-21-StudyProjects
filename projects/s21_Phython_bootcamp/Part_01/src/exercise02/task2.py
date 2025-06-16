def GetDigitInPosition(number: int, position: int)->int:
    """ Извлекает цифру из указанной позиции, отсчет от 1, справа налево. Корректность данных не проверяется. """
    number = abs(number)
    while (position and number):
        r = number % 10 # последний разряд
        number //= 10  # число без последнего разряда
        position -= 1
    return r

def GetNumberLenght(number:int)->int:
    counter=0
    while number:
        number//=10
        counter+=1
    return counter

def IsPalindromeNaive(number: int)->bool:
    number_length = GetNumberLenght(number)
    if (number < 0):
        return False
    elif (number_length==1):
        return True
    else: # Отсчет разрядов справа налево
        half_length = number_length//2
        left_side_counter = number_length
        right_side_counter = 1
        result = True
        while (half_length and result):
            result = (GetDigitInPosition(number, right_side_counter)== GetDigitInPosition(number, left_side_counter))
            right_side_counter+=1
            left_side_counter-=1
            half_length-=1
        return result

def IsPalindromeOptimized(number: int) -> bool:
    """ Выделяем число с конца и до середины и сравниваем с передней половиной <---"""
    if number < 0:
        return False
    if number < 10:
        return True
    reversed_half = 0
    while number > reversed_half:
        reversed_half = reversed_half * 10 + number % 10
        number //= 10
    # Отбрасываем последний разряд для нечетного числа разрядов.
    return number == reversed_half or number == reversed_half // 10

def main():
    while(True):
        try:
            t = int(input("Enter the numberrr! "))
        except ValueError:
            print("Have a nice day! Goodbye!")
            exit()
        else:
            if(IsPalindromeNaive(t) and IsPalindromeOptimized(t)):
                print("Congratulation!! The numberrr is a PALINDROME!!!")
            elif(not IsPalindromeNaive(t) and not IsPalindromeOptimized(t)):
                print("Sorry, it's not a palindrome... Feel free to try again!")
            else:
                print("Hmm... may be yes, may be no... who knows???")

if __name__ == "__main__":
    main()