
/* ex01

Allowed	
Language	SQL, DML, DDL
Actually, we created a structure to store our discounts and we are ready to go further and fill our person_discounts table with new records.

So, there is a table person_order that stores the history of a person's orders. Please write a DML statement (INSERT INTO ... SELECT ...) that makes inserts new records into person_discounts table based on the next rules.

take aggregated state by person_id and pizzeria_id columns

calculate personal discount value by the next pseudo code:

if “amount of orders” = 1 then “discount” = 10.5 else if “amount of orders” = 2 then “discount” = 22 else “discount” = 30

to generate a primary key for the person_discounts table please use SQL construction below (this construction is from the WINDOW FUNCTION SQL area).

... ROW_NUMBER( ) OVER ( ) AS id ...
*/

INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
SELECT  row_number() over()                         AS id
       ,person_order.person_id
       ,menu.pizzeria_id
       ,CASE WHEN COUNT(*) = 1 THEN 10.5
             WHEN COUNT(*) = 2 THEN 22  ELSE 30 END AS discount
FROM person_order
JOIN menu
ON person_order.menu_id = menu.id
GROUP BY  person_order.person_id
         ,menu.pizzeria_id
ORDER BY 2; 

delete
FROM person_discounts;