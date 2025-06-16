
/* ex02
Please write a SQL statement that returns orders with actual price and price with applied discount for each person in the corresponding pizzeria restaurant and sort by person name, and pizza name. Please take a look at the sample of data below.

name	pizza_name	price	discount_price	pizzeria_name
Andrey	cheese pizza	800	624	Dominos
Andrey	mushroom pizza	1100	858	Dominos
...	...	...	...	...
*/

SELECT  person.name
       ,menu.pizza_name
       ,menu.price
       ,ROUND(menu.price - (menu.price * (person_discounts.discount / 100)),0) AS discount_price
       ,pizzeria.name                                                          AS pizzeria_name
FROM person_order
JOIN person
ON person_order.person_id = person.id
JOIN menu
ON person_order.menu_id = menu.id
JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id
JOIN person_discounts
ON (person_discounts.person_id = person_order.person_id AND pizzeria.id = person_discounts.pizzeria_id)
ORDER BY person.name, menu.pizza_name;

