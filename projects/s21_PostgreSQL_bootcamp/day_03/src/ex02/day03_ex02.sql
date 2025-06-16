
/* ex02
Denied	
SQL Syntax Construction	any type of JOINs

Please use SQL statement from Exercise #01 and show pizza names from pizzeria which are not ordered by anyone, including corresponding prices also. The result should be sorted by pizza name and price. The sample of output data is presented below.

pizza_name	    price	pizzeria_name
cheese pizza	700	    Papa Johns
cheese pizza	780	    DoDo Pizza
...	...	...
*/
 
WITH unordered_pizzas_ids AS
(
	SELECT  menu.id AS menu_id
	FROM menu
	WHERE id not IN ( SELECT menu_id FROM person_order)
	ORDER BY 1
)
SELECT  menu.pizza_name
       ,menu.price
       ,pizzeria.name
FROM unordered_pizzas_ids
JOIN menu
ON unordered_pizzas_ids.menu_id = menu.id
JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id
ORDER BY 1, 2;
