
/*

SQL Syntax Pattern	Don’t use direct numbers for identifiers of Primary Key and pizzeria

Please register new visits into Dominos restaurant from Denis and Irina on 24th of February 2022.

*/
	-- Денис
INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
VALUES(
	(select max(id)+1 from person_visits),
	(select id from person where name  = 'Denis'),
	(select id from pizzeria where name = 'Dominos'),
	'2022-02-24'
);

	-- Ирина
INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)  
VALUES(
	(select max(id)+1 from person_visits),
	(select id from person where name  = 'Irina'),
	(select id from pizzeria where name = 'Dominos'),
	'2022-02-24'
);