
/* ex06
Let’s create a Database Sequence with the name seq_person_discounts (starting from 1 value) and set a default value for id attribute of person_discounts table to take a value from seq_person_discounts each time automatically. Please be aware that your next sequence number is 1, in this case please set an actual value for database sequence based on formula “amount of rows in person_discounts table” + 1. Otherwise you will get errors about Primary Key violation constraint.
*/

CREATE SEQUENCE seq_person_discounts START 1 INCREMENT 1;

-- устнавливаем новое текущее значение, соответственно количеству строк в таблице
SELECT  setval('seq_person_discounts',(
SELECT  COUNT(*)
FROM person_discounts) + 1);
-- ставим как дефолт извлечение индекса из последовательности.

ALTER TABLE person_discounts

ALTER COLUMN id

SET DEFAULT nextval('seq_person_discounts');