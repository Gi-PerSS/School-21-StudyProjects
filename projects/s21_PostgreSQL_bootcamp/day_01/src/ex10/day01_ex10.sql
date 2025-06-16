/*

Please write a SQL statement which returns a list of the person names which made an order for pizza in the corresponding pizzeria. The sample result (with named columns) is provided below and yes ... please make ordering by 3 columns (person_name, pizza_name, pizzeria_name) in ascending mode.

person_name	pizza_name	pizzeria_name
Andrey	cheese pizza	Dominos
Andrey	mushroom pizza	Dominos
Anna	cheese pizza	Pizza Hut
...	...	...

*/
SELECT  person.name   AS person_name
       ,menu.pizza_name
       ,pizzeria.name AS pizzeria_name
FROM person_order
JOIN person
ON person.id = person_order.person_id
JOIN menu
ON person_order.menu_id = menu.id
JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id
ORDER BY 1, 2, 3;