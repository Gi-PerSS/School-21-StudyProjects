
/* ex03
Please find pizzerias that have been visited more often by women or by men. For any SQL operators with sets save duplicates (UNION ALL, EXCEPT ALL, INTERSECT ALL constructions). Please sort a result by the pizzeria name. The data sample is provided below.

pizzeria_name
Best Pizza
Dominos
...

*/
with visits as -- денормализованная таблица визитов
(
	SELECT  person_visits.person_id, person.gender, pizzeria.name as pizzeria_name
	FROM person_visits
	JOIN person
	ON person.id = person_visits.person_id
	join 
	pizzeria on person_visits.pizzeria_id = pizzeria.id
), females_count as -- женский счетчик
(
	SELECT  pizzeria_name, count(*) as females_count from visits where gender = 'female' group by visits.pizzeria_name
), males_count as -- мужской счетчик
(
	SELECT  pizzeria_name, count(*) as males_count from visits where gender = 'male' group by visits.pizzeria_name
)

SELECT  females_count.pizzeria_name
FROM females_count
JOIN males_count
ON females_count.pizzeria_name = males_count.pizzeria_name
WHERE COALESCE(females_count.females_count, 0) > COALESCE(males_count.males_count, 0) OR COALESCE(females_count.females_count, 0) < COALESCE(males_count.males_count, 0); -- выводим все пиццерии, которые больше посещали люди одного пола в сравнении с другим полом.
