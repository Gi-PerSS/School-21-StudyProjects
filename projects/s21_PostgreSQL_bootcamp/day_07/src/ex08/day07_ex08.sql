
/* ex08

We know about personal addresses from our data. Let’s imagine, that particular person visits pizzerias in his/her city only. Please write a SQL statement that returns address, pizzeria name and amount of persons’ orders. The result should be sorted by address and then by restaurant name. Please take a look at the sample of output data below.

address	name	count_of_orders
Kazan	Best Pizza	4
Kazan	DinoPizza	4
...	...	...

*/

SELECT  person.address
       ,pizzeria.name
       ,COUNT(*) AS count_of_orders
FROM person_order
JOIN person
ON person_order.person_id = person.id
JOIN menu
ON person_order.menu_id = menu.id
JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id
GROUP BY  person.address
         ,pizzeria.name
ORDER BY 1
         ,2;