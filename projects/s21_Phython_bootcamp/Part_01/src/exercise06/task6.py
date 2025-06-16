import json
from functools import reduce

try:
    import jsonschema
except:
    print("Please, make 'pip install -r requirements.txt' and try again.")
    exit()
else:
    from jsonschema import validate

def check_the_year(json_data)->bool:

    first_film = 1895
    max_year = 9999
    is_dates_correct = True

    for film_list, films in json_data.items():
        for film in films:
            year = film.get("year")            
            if year < first_film or year > max_year :
                is_dates_correct = False
    return is_dates_correct

def read_json_from_file(json_file_path)->dict:
    try:
        with open(json_file_path, 'r') as file:
            json_data = json.load(file)
        with open("jsonscheme.txt", 'r') as scheme:
            json_schema = json.load(scheme)
        validate(instance=json_data, schema=json_schema)
        if not check_the_year(json_data):
            raise ValueError("Incorrect film year.")
    except FileNotFoundError as e:
        print(f"File not found: {e}")
        return None
    except json.JSONDecodeError as e:
        print(f"Error deserializing the json file: {e}")
        return None
    except jsonschema.exceptions.ValidationError as e:
        print(f"json does not match a valid template: {e}")
        return None
    except Exception as e:
        print(f"Error: {e}")
        return None
    else:        
        return json_data

def main():
    new_films = input("Please, enter the path to the file with the films data or 'Enter' for default file: ")

    if new_films == "":
        json_data = read_json_from_file("input.txt")
    else:
        json_data = read_json_from_file(new_films)
        
    if json_data == None:
        print("Something went wrong. Exit.")
        exit()

    combined_dicts = {'list0': []}
    for film_list in json_data.keys():
        for film_item in json_data[film_list]:
            combined_dicts['list0'].append(film_item)
    s = sorted(combined_dicts['list0'], key=lambda x: x['year'])
    combined_dicts['list0'] = s
    formatted = json.dumps(combined_dicts, indent=5)
    print(f'Sorted films:\n{formatted}')
    

if __name__ == "__main__":
    main()