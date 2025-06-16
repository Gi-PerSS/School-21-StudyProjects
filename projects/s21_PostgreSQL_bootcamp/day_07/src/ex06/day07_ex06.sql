
/* ex06
Please write a SQL statement that returns the amount of orders, average of price, maximum and minimum prices for sold pizza by corresponding pizzeria restaurant. The result should be sorted by pizzeria name. Please take a look at the data sample below. Round your average price to 2 floating numbers.

name	count_of_orders	average_price	max_price	min_price
Best Pizza	5	        780	              850	        700
DinoPizza	5	        880 	        1000        	800
...	...	...	...	...
*/

SELECT  pizzeria.name
       ,COUNT(pizzeria.name)      AS count_of_orders
       ,round(AVG(menu.price) ,2) AS average_price
       ,MAX(menu.price)           AS max_price
       ,MIN(menu.price)           AS min_price
FROM person_order
JOIN menu
ON person_order.menu_id = menu.id
JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id
GROUP BY  pizzeria.name
ORDER BY 1;