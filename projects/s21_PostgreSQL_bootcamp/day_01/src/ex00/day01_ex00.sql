/* ex00

Please write a SQL statement which returns menu’s identifier and pizza names from menu table and person’s identifier and person name from person table in one global list (with column names as presented on a sample below) ordered by object_id and then by object_name columns.

object_id	object_name
1	Anna
1	cheese pizza
...	...

*/

SELECT person.id as object_id, person.name as object_name from person
UNION
select menu.id as object_id, menu.pizza_name as object_name from menu
ORDER by 1,2;