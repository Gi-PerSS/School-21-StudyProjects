/* ex07

Denied	
SQL Syntax Pattern	Don’t use direct numbers for identifiers of Primary Key, person and pizzeria

Let's refresh data in our Materialized View mv_dmitriy_visits_and_eats from exercise #06. Before this action, please generate one more Dmitriy visit that satisfies the SQL clause of Materialized View except pizzeria that we can see in a result from exercise #06. After adding a new visit please refresh a state of data for mv_dmitriy_visits_and_eats.

*/

WITH pizzeria_ids AS
(
	SELECT pizzeria.id
	FROM menu
	JOIN pizzeria
	ON menu.pizzeria_id = pizzeria.id
	WHERE menu.price < 800 except (
	SELECT  pizzeria.id
	FROM mv_dmitriy_visits_and_eats
	JOIN pizzeria
	ON pizzeria.name = mv_dmitriy_visits_and_eats.name)
	limit 1
)

INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date) values (
	(select MAX(person_visits.id)+1 from person_visits) ,
	(select person.id from person where name = 'Dmitriy'),
	(select * from pizzeria_ids),
	'2022-01-08'
);

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;

SELECT  *
FROM mv_dmitriy_visits_and_eats;