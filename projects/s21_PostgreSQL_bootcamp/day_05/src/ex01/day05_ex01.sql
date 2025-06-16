
/* ex01
Before further steps please write a SQL statement that returns pizzas’ and corresponding pizzeria names. Please take a look at the sample result below (no sort needed).

pizza_name	pizzeria_name
cheese pizza	Pizza Hut
...	...
Let’s provide proof that your indexes are working for your SQL. The sample of proof is the output of the EXPLAIN ANALYZE command. Please take a look at the sample output command.

...
->  Index Scan using idx_menu_pizzeria_id on menu m  (...)
...
Hint: please think why your indexes are not working in a direct way and what should we do to enable it?
*/

SET enable_seqscan = off; 
EXPLAIN ANALYZE
SELECT  menu.pizza_name
       ,pizzeria.name AS pizzeria_name
FROM menu
JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id;