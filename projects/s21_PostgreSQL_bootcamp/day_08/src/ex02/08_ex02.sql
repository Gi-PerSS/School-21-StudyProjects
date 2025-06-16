
/* ex02
Let’s check one of the famous “Lost Update Anomaly” database pattern but under REPEATABLE READ isolation level. You can see a graphical presentation of that anomaly on a picture. Horizontal Red Line means the final results after all sequential steps for both Sessions.	D08_07
Please check a rating for “Pizza Hut” in a transaction mode for both Sessions and after that make UPDATE of rating to 4 value in session #1 and make UPDATE of rating to 3.6 value in session #2 (in the same order as in the picture).
*/

-- s1.
update pizzeria set rating = 0 where name = 'Pizza Hut';
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
select * from pizzeria where name = 'Pizza Hut';
-- Session #2
select * from pizzeria where name = 'Pizza Hut';

-- s3
-- Session #1
update pizzeria set rating = 4 where name = 'Pizza Hut';
-- Session #2
-- терминал виснет, ожидая коммита
update pizzeria set rating = 3.6 where name = 'Pizza Hut';

-- s4
-- Session #1
COMMIT;
-- Session #2
COMMIT;

-- s5
-- Session #1
select * from pizzeria where name = 'Pizza Hut';
-- Session #2
select * from pizzeria where name = 'Pizza Hut';