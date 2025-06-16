
/* ex04
Please find a union of pizzerias that have orders either from women or from men. Other words, you should find a set of pizzerias names have been ordered by females only and make "UNION" operation with set of pizzerias names have been ordered by males only. Please be aware with word “only” for both genders. For any SQL operators with sets don’t save duplicates (UNION, EXCEPT, INTERSECT). Please sort a result by the pizzeria name. The data sample is provided below.

pizzeria_name
Papa Johns

*/

with d_order as -- денормализованная таблица заказов
(
	SELECT  person_order.person_id, person.gender, pizzeria.name as pizzeria_name
	FROM person_order
	JOIN person
	ON  person_order.person_id = person.id 
	join 
	menu on person_order.menu_id = menu.id
	join 
	pizzeria on menu.pizzeria_id = pizzeria.id
), females_pizzerias as
(
	(select DISTINCT pizzeria_name from d_order where gender = 'female')
	except 
	(select DISTINCT pizzeria_name from d_order where gender  = 'male')
	 
), males_pizzerias as 
(
	(select DISTINCT pizzeria_name from d_order where gender = 'male')
	except 
	(select DISTINCT pizzeria_name from d_order where gender  = 'female')	
)

(select * 
from males_pizzerias)
union
(select * 
from females_pizzerias);