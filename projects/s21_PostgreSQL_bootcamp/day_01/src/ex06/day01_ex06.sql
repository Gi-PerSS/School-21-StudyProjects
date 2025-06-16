
/* 	ex06

Let's return our mind back to exercise #03 and change our SQL statement to return person names instead of person identifiers and change ordering by action_date in ascending mode and then by person_name in descending mode. Please take a look at a data sample below.

action_date	person_name
2022-01-01	Irina
2022-01-01	Anna
2022-01-01	Andrey
...	...
*/
SELECT  ex03.action_date
       ,person.name
FROM
(
	SELECT  visit_date AS action_date
	       ,person_id
	FROM person_visits intersect
	SELECT  order_date AS action_date
	       ,person_id
	FROM person_order
) ex03
JOIN person
ON person_id = person.id
ORDER BY 1 asc, 2 desc;
