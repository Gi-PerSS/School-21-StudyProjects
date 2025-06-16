/*
Please find the names of all males from Moscow or Samara cities who orders either pepperoni or mushroom pizzas (or both) . Please order the result by person name in descending mode. The sample of output is presented below.

name
Dmitriy
...
*/

SELECT name 
FROM person 
JOIN person_order ON person.id = person_order.person_id
JOIN menu ON person_order.menu_id = menu.id
WHERE (menu.pizza_name = 'pepperoni pizza' OR menu.pizza_name = 'mushroom pizza') AND (person.gender = 'male' and person.address = 'Moscow' OR person.address = 'Samara')
ORDER BY name DESC;
