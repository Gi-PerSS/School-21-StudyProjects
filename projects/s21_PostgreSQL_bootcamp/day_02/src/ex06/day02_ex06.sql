/*
Please find all pizza names (and corresponding pizzeria names using menu table) that Denis or Anna ordered. Sort a result by both columns. The sample of output is presented below.

pizza_name	pizzeria_name
cheese pizza	Best Pizza
cheese pizza	Pizza Hut
...	...
*/

SELECT  menu.pizza_name
       ,pizzeria.name
FROM person
JOIN person_order
ON person.id = person_order.person_id
JOIN menu
ON person_order.menu_id = menu.id
JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id
WHERE person.name IN ('Denis', 'Anna')
ORDER BY menu.pizza_name, pizzeria.name;