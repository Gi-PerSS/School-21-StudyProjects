/* ex06
Let’s look at pl/pgsql functions right now.

Please create a pl/pgsql function fnc_person_visits_and_eats_on_date based on SQL statement that finds the names of pizzerias which person (IN pperson parameter with default value is ‘Dmitriy’) visited and bought pizza for less than the given sum in rubles (IN pprice parameter with default value is 500) on the specific date (IN pdate parameter with default value is 8th of January 2022).

To check yourself and call a function, you can make a statement like below.

select *
from fnc_person_visits_and_eats_on_date(pprice := 800);

select *
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');
*/

create or replace function fnc_person_visits_and_eats_on_date(pperson varchar default 'Dmitriy', pprice numeric default 500, pdate date default '2022-01-08')
returns table (name varchar)
 as  $$
 begin
    RETURN QUERY
    select distinct pizzeria.name from person_visits
    join pizzeria on person_visits.pizzeria_id = pizzeria.id
    join menu on person_visits.pizzeria_id = menu.pizzeria_id 
    join person on person_visits.person_id = person.id
    where person.name = pperson and menu.price < pprice and person_visits.visit_date = pdate;
end
    $$ language plpgsql;