
/* ex05
Please create a Database View v_price_with_discount that returns a person's orders with person names, pizza names, real price and calculated column discount_price (with applied 10% discount and satisfies formula price - price*0.1). The result please sort by person name and pizza name and make a round for discount_price column to integer type. Please take a look at a sample result below.
name	pizza_name	price	discount_price
Andrey	cheese pizza	800	720
Andrey	mushroom pizza	1100	990
...	...	...	...
*/
DROP VIEW IF EXISTS v_price_with_discount;

CREATE view  v_price_with_discount AS (
	WITH d_person_order as (
	select person.name, menu.pizza_name, menu.price, ROUND((price - price * 0.1))  as discount_price
	from 
	person_order 
	join 
	person on person_order.person_id = person.id 
	join 
	menu on person_order.menu_id = menu.id 
	order by 1, 2
)

select * from d_person_order
);

select * from v_price_with_discount;