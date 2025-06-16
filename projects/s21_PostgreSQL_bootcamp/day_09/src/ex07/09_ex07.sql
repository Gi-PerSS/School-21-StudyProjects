/* ex07
Please write a SQL or pl/pgsql function func_minimum (it’s up to you) that has an input parameter is an array of numbers and the function should return a minimum value.

To check yourself and call a function, you can make a statement like below.

SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);
*/

CREATE function func_minimum(variadic arr numeric[]) returns numeric AS $$
SELECT  MIN(values)
FROM unnest
(arr
) AS values; $$ language sql;

SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);

-- variadic - указание на то, что аргументом функции является массив (или набор аргументов), => - присвоение аргументу arr значения массива.