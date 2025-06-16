import random

def get_numbers_from_user():
    number_of_numbers = int(input("Enter the number of numbers, please: "))
    print(f"Number of the numbers = {number_of_numbers}")
    numbers = []
    t = input("Generate values automatically? (y => True) ")
    if t.lower() == 'y':
        for counter in range(number_of_numbers) :
            numbers.append(random.randint(0, 11))
    else:
        for counter in range(number_of_numbers) :
            numbers.append(int(input(f"Enter the number number {counter}: "))) 
    return numbers

def main():
    user_numbers = get_numbers_from_user()
    print("source row: ", *user_numbers)
    numbers_set = set(user_numbers)
    print("set row: ", *numbers_set)
    print(f"Unique numbers in a row: {len(numbers_set)}")

if __name__ == "__main__":
    main()