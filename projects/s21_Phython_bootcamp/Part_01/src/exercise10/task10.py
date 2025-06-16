from itertools import combinations

def get_data_from_user():
    t = input("Входные данные: Два натуральных числа через пробел, количество доступных аппаратов N и требуемое общее время работы соответственно. Welcome!: ")
    t = t.split()
    try:
        if len(t) != 2:
            raise ValueError("Входные данные => Два натуральных числа через пробел...")
        number_of_available_devices = int(t[0])
        total_working_hours = int(t[1])
        if number_of_available_devices <= 1 or  total_working_hours <= 0:
            raise ValueError("Аппратов должно быть хотя бы 2, и время работы должно быть больше 0")
    except ValueError as e:
        print(f"Something went wrong...\n{e}\n Try again, maybe... ")
        exit()
    else:            
        int_devices_data = []    
        for i in range(number_of_available_devices):
            while True:
                try:    
                    string_device_data = input(f"Введи данные для аппарата номер {i} - три натуральных числа через пробел: год выпуска, стоимость и время работы аппарата соответственно: ")
                    string_parts = string_device_data.split()
                    if len(string_parts) !=3:
                        raise ValueError(f"Мало введено данных на аппарат номер {i}!")
                    elif len(string_parts[0]) != 4:
                        raise ValueError("В году неправильное количество цифр...")
                    int_device_data = []
                    int_device_data = list(map(int, string_parts))
                    int_devices_data.append(int_device_data)
                    if not all(x > 0 for x in int_device_data):
                        raise ValueError(f"Какой-то параметр аппарата номер {i} меньше или равен 0...")                    
                except ValueError as e:
                    print(f"Something went wrong...\n{e}\n Try again, maybe... \n")
                    continue
                else:
                    break
    print(f"\nnumber_of_available_devices = {number_of_available_devices}")
    print(f"total_working_hours = {total_working_hours}")
    print(f"year_cost_time = ")
    print(*int_devices_data, sep='\n')
    return total_working_hours, int_devices_data

def analyze_data(total_working_hours:int, devices_data: list[list[int]])->float:
    # группируем аппараты в словарь по годам
    devices_by_the_years = {}  
    for dd in devices_data:
        devices_by_the_years.setdefault(dd[0], []).append(dd[1:])

    # проходим по всем ключам-годам
    min_cost = float('inf') # бесконечность.
    for k in devices_by_the_years.keys():
         # если в году 2+ аппарата проверяем их на соответствие условиям
        if len(devices_by_the_years[k]) >= 2:
            # перебираем всех возможные комбинаций аппаратов 
            for a, b in combinations(devices_by_the_years[k], 2):
                # если часы сходятся, проверяем цену.
                if a[1] + b[1] >= total_working_hours:
                    cost = a[0] + b[0]
                    min_cost = min(min_cost, cost)
    return min_cost

def main():
    total_working_hours, devices_data = get_data_from_user() 
    print() 
    # devices_data = [
    #     [2023, 100, 14],
    #     [2020, 18, 347],
    #     [2023, 10000000, 34],
    #     [2023, 1000, 34],
    #     [2022, 10, 34]
    # ]
    # total_working_hours = 48

    min_cost = analyze_data(total_working_hours, devices_data)
    if min_cost != float('inf'):    
        print(f"Минимальная стоимость: {min_cost:.2f}")
    else:
        print("Подходящих под условие задачи аппаратов нет")

if __name__ == "__main__":
    main()