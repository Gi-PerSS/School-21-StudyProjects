/*
Please find the name of pizzeria Dmitriy visited on January 8, 2022 and could eat pizza for less than 800 rubles.
*/

SELECT pizzeria.name 
FROM person_visits
JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
JOIN person ON person.id = person_visits.person_id
JOIN menu ON menu.pizzeria_id = person_visits.pizzeria_id
WHERE person_visits.visit_date = '2022-01-08' AND menu.price < 800;
