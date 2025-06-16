
/* ex04

Denied
SQL Syntax Construction	any type of JOINs

Please write a SQL statement which returns a difference (minus) of person_id column values with saving duplicates between person_order table and person_visits table for order_date and visit_date are for 7th of January of 2022

*/

(
	SELECT  person_order.person_id
	FROM person_order
	WHERE order_date = '2022-01-07') EXCEPT all (
	SELECT  person_visits.person_id
	FROM person_visits
	WHERE visit_date = '2022-01-07');
