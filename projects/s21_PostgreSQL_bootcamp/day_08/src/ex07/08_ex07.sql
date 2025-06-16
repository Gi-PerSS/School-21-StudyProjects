/* ex07
You can see a graphical presentation of the deadlock situation on a picture. Looks like a “christ-lock” between parallel sessions.

Please write any SQL statement with any isolation level (you can use default setting) on the pizzeria table to reproduce this deadlock situation
*/
-- s1
-- Session #1
begin;
-- Session #2
begin;

-- s2
-- Session #1
update pizzeria set rating = 0 where id = 1;
-- Session #2
update pizzeria set rating = 0 where id = 2;

-- s3
-- Session #1
update pizzeria set rating = 0 where id = 2;
-- Session #2
update pizzeria set rating = 0 where id = 1;

-- s4
-- Session #1
commit;
-- Session #2
commit;