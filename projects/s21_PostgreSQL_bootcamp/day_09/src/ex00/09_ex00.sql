/* ex00
*/

-- вариант номер 1
create table person_audit AS
select * from person where false;

alter table person_audit 
    RENAME COLUMN  id TO row_id;

alter table person_audit 
    add column created  timestamptz DEFAULT current_timestamp NOT NULL,
    add column type_event char(1) CONSTRAINT ch_type_event CHECK (type_event IN ('I', 'U', 'D')) default 'I' not null;

-- вариант номер 2
create table person_audit 
(
    created timestamptz DEFAULT current_timestamp NOT NULL,
    type_event char(1) CONSTRAINT ch_type_event CHECK (type_event IN ('I', 'U', 'D')) default 'I' not null,
    row_id bigint not null,
    name varchar,
    age integer,
    gender varchar,
    address varchar
);

create trigger trg_person_insert_audit
after insert on person
for each row
execute function fnc_trg_person_insert_audit();

create function fnc_trg_person_insert_audit()
returns trigger as $$
begin 
    insert into person_audit (created, type_event, row_id, name, age, gender, address)
    values (CURRENT_TIMESTAMP, 'I', NEW.id, NEW.name, NEW.age, NEW.gender, NEW.address); -- 
    return NULL;
end;
$$ language plpgsql;

-- NEW является специальной псевдотаблицей в PostgreSQL, которая представляет новую вставленную или обновленную запись в триггере. Она предоставляет доступ к значениям полей новой записи, с которой связан триггер.

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk');