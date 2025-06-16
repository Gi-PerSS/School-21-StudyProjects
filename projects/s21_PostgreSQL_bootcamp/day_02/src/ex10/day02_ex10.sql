/*
Please find the names of persons who live on the same address. Make sure that the result is ordered by 1st person, 2nd person's name and common address. The data sample is presented below. Please make sure your column names are corresponding column names below.

person_name1	person_name2	common_address
Andrey	Anna	Moscow
Denis	Kate	Kazan
Elvira	Denis	Kazan
...	...	...
*/

SELECT  persons_copy_1.name    AS person_name1
       ,persons_copy_2.name    AS person_name2
       ,persons_copy_1.address AS common_address
FROM person AS persons_copy_1
JOIN person AS persons_copy_2 -- умножаем множества
ON persons_copy_1.address = persons_copy_2.address
WHERE persons_copy_1.id < persons_copy_2.id -- исключаем дубликаты и зеркальные повторения
ORDER BY 1, 2, 3;
