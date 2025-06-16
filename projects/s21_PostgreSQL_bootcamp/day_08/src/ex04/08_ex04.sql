
/*ex04
Please for this task use the command line for PostgreSQL database (psql). You need to check how your changes will be published in the database for other database users.

Actually, we need two active sessions (meaning 2 parallel sessions in the command lines).

Let’s check one of the famous “Non-Repeatable Reads” database pattern but under SERIALIZABLE isolation level. You can see a graphical presentation of that anomaly on a picture. Horizontal Red Line means the final results after all sequential steps for both Sessions.	D08_09
Please check a rating for “Pizza Hut” in a transaction mode for both Sessions and after that make UPDATE of rating to 3.0 value in session #2 (in the same order as in the picture).
*/


update pizzeria set rating = 0 where name = 'Pizza Hut';
-- s1
-- Session #1
begin;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SHOW TRANSACTION ISOLATION LEVEL;
-- Session #2
begin;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SHOW TRANSACTION ISOLATION LEVEL;

-- s2
-- Session #1
select * from pizzeria where name = 'Pizza Hut';
-- Session #2
select * from pizzeria where name = 'Pizza Hut';

-- s3
-- Session #2
update pizzeria set rating = 3.0 where name = 'Pizza Hut';
COMMIT;

-- s4
-- Session #1
select * from pizzeria where name = 'Pizza Hut';
COMMIT;
select * from pizzeria where name = 'Pizza Hut';
-- Session #2
select * from pizzeria where name = 'Pizza Hut';