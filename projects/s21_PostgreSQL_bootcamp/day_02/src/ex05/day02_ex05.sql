/*

Find names of all female persons older than 25 and order the result by name. The sample of output is presented below.

name
Elvira
...

*/

SELECT  name
FROM person
WHERE age > 25
AND gender = 'female'
ORDER BY name;