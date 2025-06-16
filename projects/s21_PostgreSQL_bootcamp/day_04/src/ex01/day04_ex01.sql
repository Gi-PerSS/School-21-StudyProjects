
/* ex01

Please use 2 Database Views from Exercise #00 and write SQL to get female and male person names in one list. Please set the order by person name. The sample of data is presented below.

name
Andrey
Anna
...

*/

SELECT name FROM v_persons_female
UNION
SELECT name from v_persons_male
ORDER by name;