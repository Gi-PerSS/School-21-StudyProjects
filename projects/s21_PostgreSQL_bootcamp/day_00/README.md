# Piscine SQL - Day 00

## Basic SQL Exercises

### Exercise 00
**Task:** Write a SELECT query that returns names and ages of all people from 'Kazan' city.

### Exercise 01
**Task:** Write a SELECT query that returns names and ages of all women from 'Kazan' city, sorted by name.

### Exercise 02
**Task:** Write 2 different SELECT queries that return pizzerias (name and rating) with rating between 3.5 and 5 (inclusive), ordered by rating:
1. Using comparison operators (<=, >=)
2. Using BETWEEN keyword

### Exercise 03
**Task:** Write a SELECT query that returns unique person IDs who visited pizzerias between January 6 and 9, 2022 (inclusive) OR visited pizzeria with id=2. Sort by person ID in descending order.

### Exercise 04
**Task:** Write a SELECT query that returns a calculated field 'person_information' in format: `Name (age:value,gender:'value',address:'value')`. Sort by calculated field in ascending order.

### Exercise 05
**Task:** Write a SELECT query that returns person names (via subquery in SELECT) who ordered menu items with id 13, 14 or 18 on January 7, 2022. Without using IN or JOINs.

### Exercise 06
**Task:** Modify query from Exercise 05 by adding calculated field 'check_name' that returns true if person name is 'Denis', false otherwise.

### Exercise 07
**Task:** Write a SELECT query that returns person IDs, names and age interval ('interval_info'):
- 'interval #1' if age between 10 and 20
- 'interval #2' if age between 21 and 23
- 'interval #3' otherwise
Sort by 'interval_info' in ascending order.

### Exercise 08
**Task:** Write a SELECT query that returns all columns from person_order table where ID is even number. Sort by ID.

### Exercise 09
**Task:** Write a SELECT query that returns person names and pizzeria names based on person_visits table for visits between January 7-9, 2022 (inclusive). Without JOINs. Sort by person name (asc) and pizzeria name (desc).

[Русская версия](README_RUS.md)