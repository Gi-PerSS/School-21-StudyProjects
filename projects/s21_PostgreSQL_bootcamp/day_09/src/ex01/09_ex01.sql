
/* ex01
Let’s continue to implement our audit pattern for the person table. Just define a trigger trg_person_update_audit and corresponding trigger function fnc_trg_person_update_audit to handle all UPDATE traffic on the person table. We should save OLD states of all attribute’s values.

When you are ready please apply UPDATE’s statements below.

UPDATE person SET name = 'Bulat' WHERE id = 10; UPDATE person SET name = 'Damir' WHERE id = 10;
*/

create trigger fnc_trg_person_update_audit
after update on person
for each row
execute function fnc_trg_person_update_audit();

create FUNCTION fnc_trg_person_update_audit()
returns trigger as $$ 
begin 
    insert into person_audit (created, type_event, row_id, name, age, gender, address)
    values (CURRENT_TIMESTAMP, 'U', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
    return NULL;
end;
$$ language plpgsql;

UPDATE person SET name = 'Bulat' WHERE id = 10; UPDATE person SET name = 'Damir' WHERE id = 10;