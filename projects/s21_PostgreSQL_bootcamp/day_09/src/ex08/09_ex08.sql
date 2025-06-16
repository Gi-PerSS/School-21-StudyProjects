/* ex08
Please write a SQL or pl/pgsql function fnc_fibonacci (it’s up to you) that has an input parameter pstop with type integer (by default is 10) and the function output is a table with all Fibonacci numbers less than pstop.

To check yourself and call a function, you can make a statements like below.

select * from fnc_fibonacci(100);
select * from fnc_fibonacci();
*/

CREATE or replace function fnc_fibonacci(pstop integer default 10) returns table(f_numbers integer) AS $$
WITH recursive f_numbers
(counter, first_N, second_N
) AS (
SELECT  1
       ,0
       ,1
UNION ALL
SELECT  counter+1
       ,second_N
       ,first_N + second_N
FROM f_numbers
WHERE second_N < pstop )
SELECT  first_N AS fibonacci_number
FROM f_numbers; $$ language sql;