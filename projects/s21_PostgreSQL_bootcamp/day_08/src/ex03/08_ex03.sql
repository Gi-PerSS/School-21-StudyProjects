
/* ex03
Let’s check one of the famous “Non-Repeatable Reads” database pattern but under READ COMMITTED isolation level. You can see a graphical presentation of that anomaly on a picture. Horizontal Red Line means the final results after all sequential steps for both Sessions.	D08_08

Please check a rating for “Pizza Hut” in a transaction mode for both Sessions and after that make UPDATE of rating to 3.6 value in session #2 (in the same order as in the picture).
*/

-- s1.
update pizzeria set rating = 0 where name = 'Pizza Hut';
-- Session #1
begin;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
SHOW TRANSACTION ISOLATION LEVEL;
-- Session #2
begin;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
SHOW TRANSACTION ISOLATION LEVEL;

-- s2
-- Session #1
select * from pizzeria where name = 'Pizza Hut';
-- Session #2
select * from pizzeria where name = 'Pizza Hut';

-- s3
-- Session #2
update pizzeria set rating = 3.6 where name = 'Pizza Hut';
COMMIT;

-- s4
-- Session #1
select * from pizzeria where name = 'Pizza Hut';
COMMIT;
select * from pizzeria where name = 'Pizza Hut';
-- Session #2
select * from pizzeria where name = 'Pizza Hut';