
/* ex02
Finally, we need to handle DELETE statements and make a copy of OLD states for all attribute’s values. Please create a trigger trg_person_delete_audit and corresponding trigger function fnc_trg_person_delete_audit.

When you are ready please apply the SQL statement below.

DELETE FROM person WHERE id = 10;
*/

create OR REPLACE  FUNCTION fnc_trg_person_update_audit()
returns trigger as $$ 
begin 
    insert into person_audit (created, type_event, row_id, name, age, gender, address)
    values (CURRENT_TIMESTAMP, 'D', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
    return NULL;
end;
$$ language plpgsql;

-- OLD является еще одной специальной псевдотаблицей в PostgreSQL, которая представляет старую запись, которая была обновлена или удалена в триггере. Она предоставляет доступ к значениям полей старой записи перед ее изменением или удалением.

create trigger trg_person_delete_audit
after delete on person
for each row
execute function fnc_trg_person_delete_audit();