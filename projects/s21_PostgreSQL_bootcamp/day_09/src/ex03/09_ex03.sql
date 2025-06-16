/* ex03
Actually, there are 3 triggers for one person table. Let’s merge all our logic to the one main trigger with the name trg_person_audit and a new corresponding trigger function fnc_trg_person_audit.

Other words, all DML traffic (INSERT, UPDATE, DELETE) should be handled from the one functional block. Please explicitly define a separated IF-ELSE block for every event (I, U, D)!

Additionally, please take the steps below .

to drop 3 old triggers from the person table.
to drop 3 old trigger functions
to make a TRUNCATE (or DELETE) of all rows in our person_audit table
When you are ready, please re-apply the set of DML statements. INSERT INTO person(id, name, age, gender, address)  VALUES (10,'Damir', 22, 'male', 'Irkutsk'); UPDATE person SET name = 'Bulat' WHERE id = 10; UPDATE person SET name = 'Damir' WHERE id = 10; DELETE FROM person WHERE id = 10;
*/

create function fnc_trg_person_audit()
returns trigger as $$
begin 
    if TG_OP = 'INSERT' THEN 
        insert into person_audit (created, type_event, row_id, name, age, gender, address)
        values (CURRENT_TIMESTAMP, 'I', NEW.id, NEW.name, NEW.age, NEW.gender, NEW.address);
    elsif TG_OP = 'UPDATE' THEN 
        insert into person_audit (created, type_event, row_id, name, age, gender, address)
        values (CURRENT_TIMESTAMP, 'U', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
    
    else -- TG_OP = 'DELETE'
        insert into person_audit (created, type_event, row_id, name, age, gender, address)
        values (CURRENT_TIMESTAMP, 'D', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
    end if;
    return NULL;
end;
$$ language plpgsql;

create trigger trg_person_audit
after insert or delete or update on person
for each row
execute function fnc_trg_person_audit();

-- удаление функций и триггеров
DROP function fnc_trg_person_delete_audit cascade;
DROP function fnc_trg_person_update_audit cascade;
DROP function fnc_trg_person_insert_audit cascade;

-- содержимого таблицы
delete from person_audit;

-- контроль 
-- все пользовательские функции
SELECT proname
FROM pg_proc
WHERE pronamespace = (SELECT oid FROM pg_namespace WHERE nspname = 'public') 
ORDER BY proname;

-- все триггеры
SELECT trigger_name, event_object_table, action_timing, event_manipulation
FROM information_schema.triggers
ORDER BY event_object_table, trigger_name;

INSERT INTO person(id, name, age, gender, address)  VALUES (10,'Damir', 22, 'male', 'Irkutsk'); 
UPDATE person SET name = 'Bulat' WHERE id = 10; UPDATE person SET name = 'Damir' WHERE id = 10; 
DELETE FROM person WHERE id = 10;