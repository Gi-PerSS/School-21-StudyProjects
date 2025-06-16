insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

-- Функция для поиска ближайшего к upd курса обмена
CREATE OR REPLACE FUNCTION fnc_find_currency_rate_ondate(upd TIMESTAMP, pcurrency_id INTEGER) RETURNS NUMERIC
AS $$
	BEGIN 
		RETURN CASE
			WHEN (SELECT rate_to_usd FROM currency 
				WHERE (pcurrency_id = currency.id) AND (upd > updated)
				ORDER BY updated DESC LIMIT 1) != 0
			THEN 
				(SELECT rate_to_usd FROM currency 
				WHERE (pcurrency_id = currency.id) AND (upd > updated)
				ORDER BY updated DESC LIMIT 1)
			ELSE
				(SELECT rate_to_usd FROM currency 
				WHERE pcurrency_id = currency.id AND upd < updated
				ORDER BY updated LIMIT 1)
		END;
	END;
$$ LANGUAGE PLPGSQL;
-- Выбор названий валют для упрощения JOIN и расчет баланса в USD
WITH currency_code AS (SELECT DISTINCT id, name FROM currency)
SELECT
	COALESCE(public.user.name, 'not defined') AS full_name,
    COALESCE(public.user.lastname, 'not defined') AS last_name,
    currency_code.name AS currency_name, 
    money* fnc_find_currency_rate_ondate(balance.updated, balance.currency_id) AS currency_in_usd
FROM balance
FULL JOIN public.user ON balance.user_id = public.user.id
JOIN currency_code ON currency_id = currency_code.id
ORDER BY 1 DESC, 2, 3;

-- SELECT * FROM fnc_find_currency_rate_ondate('2022-01-09 12:29', 100);