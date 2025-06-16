
/* ex03

Denied
SQL Syntax Construction	any type of JOINs

Please write a SQL statement which returns common rows for attributes order_date, person_id from person_order table from one side and visit_date, person_id from person_visits table from the other side (please see a sample below). In other words, let’s find identifiers of persons, who visited and ordered some pizza on the same day. Actually, please add ordering by action_date in ascending mode and then by person_id in descending mode.

action_date	person_id
2022-01-01	6
2022-01-01	2
2022-01-01	1
2022-01-03	7
2022-01-04	3
...	...

*/
SELECT  visit_date AS action_date
       ,person_id
FROM person_visits intersect
SELECT  order_date AS action_date
       ,person_id
FROM person_order
ORDER BY 1, 2;
