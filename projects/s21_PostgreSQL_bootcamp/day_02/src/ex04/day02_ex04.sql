/*
Find full information about all possible pizzeria names and prices to get mushroom or pepperoni pizzas. Please sort the result by pizza name and pizzeria name then. The result of sample data is below (please use the same column names in your SQL statement).

pizza_name	pizzeria_name	price
mushroom pizza	Dominos	1100
mushroom pizza	Papa Johns	950
pepperoni pizza	Best Pizza	800
...	...	...
*/

SELECT  m.pizza_name
       ,p.name AS pizzeria_name
       ,m.price
FROM menu m
JOIN pizzeria p
ON m.pizzeria_id = p.id
WHERE m.pizza_name IN ('mushroom pizza', 'pepperoni pizza')
ORDER BY m.pizza_name, pizzeria_name;
