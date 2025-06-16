/*

Denied	
SQL Syntax Construction	other type of JOINs

Please rewrite a SQL statement from exercise #07 by using NATURAL JOIN construction. The result must be the same like for exercise #07.

*/

SELECT order_date, (person.name || ' (' || 'age:' || person.age || ')') AS person_information
FROM person_order
NATURAL JOIN person AS person(person_id, name, age) -- переназываем столбцы
ORDER BY 1;
