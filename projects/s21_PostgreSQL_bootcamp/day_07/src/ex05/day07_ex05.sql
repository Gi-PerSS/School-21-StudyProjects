/* ex05

Denied	
Syntax construction	GROUP BY, any type (UNION,...) working with sets

Please write a simple SQL query that returns a list of unique person names who made orders in any pizzerias. The result should be sorted by person name. Please take a look at the sample below.

name
Andrey
Anna
...
*/
SELECT  distinct person.name
FROM person_order
JOIN person
ON person_order.person_id = person.id
ORDER BY 1;