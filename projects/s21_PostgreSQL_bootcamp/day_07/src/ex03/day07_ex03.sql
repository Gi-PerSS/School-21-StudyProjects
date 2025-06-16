/* ex03
Please write a SQL statement to see restaurants are grouping by visits and by orders and joined with each other by using restaurant name.
You can use internal SQLs from Exercise 02 (restaurants by visits and by orders) without limitations of amount of rows.

Additionally, please add the next rules.

calculate a sum of orders and visits for corresponding pizzeria (be aware, not all pizzeria keys are presented in both tables).
sort results by total_count column in descending mode and by name in ascending mode. Take a look at the data sample below.
name	total_count
Dominos	13
DinoPizza	9
...	...
*/
WITH visits AS
(
	SELECT  pizzeria.name
	       ,COUNT(*) AS count
	       ,'visit'  AS action_type
	FROM person_visits
	JOIN pizzeria
	ON person_visits.pizzeria_id = pizzeria.id
	GROUP BY  pizzeria.name
), orders AS
(
	SELECT  pizzeria.name
	       ,COUNT(*) AS count
	       ,'order'  AS action_type
	FROM person_order
	JOIN menu
	ON person_order.menu_id = menu.id
	JOIN pizzeria
	ON menu.pizzeria_id = pizzeria.id
	GROUP BY  pizzeria.name
), orders_and_visits AS
(
	SELECT  name
	       ,count
	       ,action_type
	FROM visits
	UNION
	SELECT  name
	       ,count
	       ,action_type
	FROM orders
)
SELECT  name
       ,SUM(orders_and_visits.count) AS total_count
FROM orders_and_visits
GROUP BY  name
ORDER BY total_count desc
         ,name asc;