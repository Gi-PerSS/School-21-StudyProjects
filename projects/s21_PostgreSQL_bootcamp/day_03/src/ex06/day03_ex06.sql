
/*
Please find the same pizza names who have the same price, but from different pizzerias. Make sure that the result is ordered by pizza name. The sample of data is presented below. Please make sure your column names are corresponding column names below.

pizza_name	    pizzeria_name_1 	pizzeria_name_2	    price
cheese pizza	Best Pizza	        Papa Johns	         700
...	...	...	...

pizza_name,  pizzeria_name_1,	pizzeria_name_2, price
*/

with d_menu as ( -- денормализуем меню
	select menu.pizza_name, pizzeria.name as pizzeria_name, menu.price from menu 
	join 
	pizzeria on menu.pizzeria_id = pizzeria.id
)
select distinct d_menu_1.pizza_name, d_menu_1.pizzeria_name as pizzeria_name_1, d_menu_2.pizzeria_name as  pizzeria_name_2, d_menu_1.price 
from d_menu as d_menu_1
join d_menu as d_menu_2 on d_menu_2.pizza_name = d_menu_1.pizza_name
where d_menu_1.price = d_menu_2.price and d_menu_1.pizzeria_name < d_menu_2.pizzeria_name -- уничтожаем зеркальные повторы через лексикографическое сравнение
order by 1;