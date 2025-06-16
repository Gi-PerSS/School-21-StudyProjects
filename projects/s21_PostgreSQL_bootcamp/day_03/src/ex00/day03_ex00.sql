/*  ex00
Please write a SQL statement which returns a list of pizza names, pizza prices, pizzerias names and dates of visit for Kate and for prices in range from 800 to 1000 rubles. Please sort by pizza, price and pizzeria names. Take a look at the sample of data below.

pizza_name  	price	pizzeria_name	visit_date
cheese pizza	950	    DinoPizza   	2022-01-04

*/

SELECT  menu.pizza_name
       ,menu.price
       ,pizzeria.name AS pizzeria_name
       ,person_visits.visit_date
FROM menu
JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id
JOIN person_visits
ON person_visits.pizzeria_id = pizzeria.id
JOIN person
ON person.id = person_visits.person_id
WHERE person.name = 'Kate'
AND menu.price BETWEEN 800 AND 1000
ORDER BY menu.pizza_name, menu.price, pizzeria.name;

-- другой вариант
WITH kate_visits AS
(
	SELECT  *
	FROM person_visits
	WHERE person_id = (
	SELECT  id
	FROM person
	WHERE name = 'Kate')
)
SELECT  menu.pizza_name
       ,menu.price
       ,pizzeria.name AS pizzeria_name
       ,visit_date
FROM kate_visits
JOIN pizzeria
ON pizzeria.id = kate_visits.pizzeria_id
JOIN menu
ON menu.pizzeria_id = kate_visits.pizzeria_id
WHERE menu.price BETWEEN 800 AND 1000
ORDER BY 1, 2, 3;