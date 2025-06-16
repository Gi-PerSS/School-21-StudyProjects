/* ex04
Denied	
Syntax construction	WHERE
Please write a SQL statement that returns the person name and corresponding number of visits in any pizzerias if the person has visited more than 3 times (> 3).Please take a look at the sample of data below.

name	count_of_visits
Dmitriy	4
*/

SELECT  person.name
       ,COUNT(*) AS count_of_visits
FROM person_visits
JOIN pizzeria
ON person_visits.pizzeria_id = pizzeria.id
JOIN person
ON person_visits.person_id = person.id
GROUP BY  person.name
HAVING COUNT(*) > 3;