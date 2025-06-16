/* ex06
Let’s check one of the famous “Phantom Reads” database pattern but under REPEATABLE READ isolation level. You can see a graphical presentation of that anomaly on a picture. Horizontal Red Line means the final results after all sequential steps for both Sessions.

Please summarize all ratings for all pizzerias in a transaction mode for both Sessions and after that make UPDATE of rating to 5 value for “Pizza Hut” restaurant in session #2 (in the same order as in the picture).
*/

update pizzeria set rating = 0 where name = 'Pizza Hut';
-- s1
-- Session #1
begin;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SHOW TRANSACTION ISOLATION LEVEL;
-- Session #2
begin;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SHOW TRANSACTION ISOLATION LEVEL;

-- s2
-- Session #1
select sum(rating) from pizzeria;
-- Session #2
update pizzeria set rating = 5 where name = 'Pizza Hut';
COMMIT;

-- s3
-- Session #1
select sum(rating) from pizzeria;
COMMIT;

-- s4
-- Session #1
select sum(rating) from pizzeria;
-- Session #2
select sum(rating) from pizzeria;