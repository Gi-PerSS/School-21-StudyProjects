
/* ex01
Denied	 
SQL Syntax Construction	any type of JOINs
Please find all menu identifiers which are not ordered by anyone. The result should be sorted by identifiers. The sample of output data is presented below.

menu_id
5
10
...
*/

-- в чек-листе в ответе не полный вывод, в чем легко убедиться, запустив код из чек-листа
SELECT menu.id
FROM menu
WHERE id not IN ( SELECT menu_id FROM person_order)
ORDER BY 1;

-- другое решение
SELECT  *
FROM
(
	SELECT  menu.id
	FROM menu
) AS m EXCEPT (
SELECT  menu_id
FROM person_order)
ORDER BY 1;