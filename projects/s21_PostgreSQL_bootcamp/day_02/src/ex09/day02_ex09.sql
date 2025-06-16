/*
Please find the names of all females who ordered both pepperoni and cheese pizzas (at any time and in any pizzerias). Make sure that the result is ordered by person name. The sample of data is presented below.

name
Anna

*/

WITH pizza_orders AS (
  SELECT person.name, menu.pizza_name
  FROM person
  JOIN person_order ON person.id = person_order.person_id
  JOIN menu ON person_order.menu_id = menu.id
  WHERE menu.pizza_name IN ('pepperoni pizza', 'cheese pizza')
    AND person.gender = 'female'
)
SELECT name
FROM pizza_orders
GROUP BY name -- считаем строки в поименных группах
HAVING COUNT(DISTINCT pizza_name) = 2 -- проверяем, что именований пиццы 2.
ORDER BY name;
