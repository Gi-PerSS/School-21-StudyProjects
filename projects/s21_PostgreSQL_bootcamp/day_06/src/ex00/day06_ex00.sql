/* ex00
Please think about personal discounts for people from one side and pizzeria restaurants from other. Need to create a new relational table (please set a name person_discounts) with the next rules.

set id attribute like a Primary Key (please take a look on id column in existing tables and choose the same data type)

set for attributes person_id and pizzeria_id foreign keys for corresponding tables (data types should be the same like for id columns in corresponding parent tables)

please set explicit names for foreign keys constraints by pattern fk_{table_name}_{column_name}, for example fk_person_discounts_person_id

add a discount attribute to store a value of discount in percent. Remember, discount value can be a number with floats (please just use numeric data type). So, please choose the corresponding data type to cover this possibility.
*/

DROP TABLE IF EXISTS person_discounts;

-- определение типа данных
SELECT distinct pg_typeof(id) FROM pizzeria;
SELECT distinct pg_typeof(id) FROM person;

create table person_discounts (
    id bigint primary key, 
    person_id bigint,
    pizzeria_id bigint,
    discount numeric,
    CONSTRAINT fk_person_discounts_person_id
    foreign key (person_id) references person(id),
    CONSTRAINT fk_person_discounts_pizzeria_id    
    foreign key (pizzeria_id) references pizzeria(id)
);