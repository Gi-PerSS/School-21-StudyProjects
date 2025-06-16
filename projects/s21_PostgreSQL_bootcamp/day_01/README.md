# Piscine SQL - Day 01

## Exercises on Sets and JOINs in SQL

### Exercise 00
**Task:** Write a SQL query that returns a combined list of:
- Pizza ids and names from `menu` table
- Person ids and names from `person` table
Order by object_id, then by object_name.

### Exercise 01
**Task:** Modify query from Exercise 00 by removing object_id column. Order by person names first, then pizza names (keeping duplicates).

### Exercise 02
**Task:** Write a query returning unique pizza names from `menu` table in reverse alphabetical order. Without using DISTINCT, GROUP BY, HAVING or JOINs.

### Exercise 03
**Task:** Find common rows (dates and person ids) between `person_order` and `person_visits` tables (people who both ordered and visited pizzerias on the same day). Order by date (asc) and person id (desc).

### Exercise 04
**Task:** Find difference between person ids from `person_order` and `person_visits` for January 7, 2022 (keeping duplicates). Without JOINs.

### Exercise 05
**Task:** Write a query returning all possible row combinations from `person` and `pizzeria` tables (Cartesian product). Order by person id, then pizzeria id.

### Exercise 06
**Task:** Modify query from Exercise 03 to show person names instead of ids. Order by date (asc) and name (desc).

### Exercise 07
**Task:** Write a JOIN query returning order dates and person information in "Name (age:value)" format. Order by both columns ascending.

### Exercise 08
**Task:** Rewrite query from Exercise 07 using NATURAL JOIN.

### Exercise 09
**Task:** Write 2 queries returning pizzerias that no one visited:
1. Using IN
2. Using EXISTS

### Exercise 10
**Task:** Write a query returning people who ordered pizza from specific pizzerias. Show person name, pizza name and pizzeria name. Order by name, pizza name and pizzeria name.

[Русская версия](README_RUS.md)