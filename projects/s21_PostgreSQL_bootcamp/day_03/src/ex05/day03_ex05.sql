
/* ex05
Please write a SQL statement which returns a list of pizzerias which Andrey visited but did not make any orders. Please order by the pizzeria name. The sample of data is provided below.

pizzeria_name
Pizza Hut
*/

WITH andrey_visited AS
(
	SELECT  DISTINCT pizzeria.name AS pizzeria_name
	FROM person_visits
	JOIN person
	ON person_visits.person_id = person.id
	JOIN pizzeria
	ON pizzeria.id = person_visits.pizzeria_id
	WHERE person.name = 'Andrey'
), andrey_ordered AS
(
	SELECT  DISTINCT pizzeria.name AS pizzeria_name
	FROM person_order
	JOIN person
	ON person_order.person_id = person.id
	JOIN menu
	ON person_order.menu_id = menu.id
	JOIN pizzeria
	ON menu.pizzeria_id = pizzeria.id
	WHERE person.name = 'Andrey' 
)
SELECT  pizzeria_name
FROM andrey_visited EXCEPT
SELECT  pizzeria_name
FROM andrey_ordered
ORDER BY 1;