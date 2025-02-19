-- Keep a log of any SQL queries you execute as you solve the mystery.

--how many tables are there
.tables

--get schema for crime_scenes_reports table
.schema crime_scenes_reports

--get the description of the crime from the day it occurred
SELECT description
FROM crime_scene_reports
WHERE day = 28 AND month = 7
AND street = 'Humphrey Street';

--get schema for interviews table
.schema interviews

--get the transcipts of the interviews of the witnesses of the crimeSELECT transcript
SELECT transcript
FROM interviews
WHERE day = 28 AND month = 7 AND year = 2021
AND transcript LIKE '%bakery%';

--get schema for bakery_security_logs table
.schema bakery_security_logs

--get the license plates and the time at wich the car left
SELECT license_plate, hour, minute
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute >= 15 AND minute <= 25
ORDER BY hour;

--get schema from atm_transactions table
.schema atm_transactions

--get id, account number and amount collumns from atm_transactions table
SELECT id, account_number, amount
FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location = 'Leggett Street';

--get schema for phone_calls table
.schema phone_calls

--get id, caller, receiver and duration collumns from phone_calls table
SELECT id, caller, receiver, duration
FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021
AND duration < 60;

--get schema for people table
.schema people

--get the names of the people that left the bakery parking lot
--within 10 mins of the robery, the thief is one of them
SELECT p.name
FROM people AS p
JOIN bakery_security_logs AS bsl
ON p.license_plate = bsl.license_plate
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute >= 15 AND minute <= 25;

--get the names of the people that left the bakery parking lot within 10 mins of the robery, and
-- withdrew some money at the atm in Legget Street in the morning of the theft
SELECT p.name
FROM people AS p
JOIN bakery_security_logs AS bsl
ON p.license_plate = bsl.license_plate
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute >= 15 AND minute <= 25
AND p.id IN
(SELECT ba.person_id
FROM bank_accounts AS ba
JOIN atm_transactions AS atmt
ON ba.account_number = atmt.account_number
WHERE atmt.day = 28 AND atmt.month = 7 AND atmt.year = 2021
AND atmt.atm_location = 'Leggett Street');

--get the names of the people that left the bakery parking lot within 10 mins of the robery, and
-- withdrew some money at the atm in Legget Street in the morning of the theft and that had phone calls
--lesser than 1 min in the day of the theft
SELECT p.name
FROM people AS p
JOIN bakery_security_logs AS bsl
ON p.license_plate = bsl.license_plate
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute >= 15 AND minute <= 25
AND p.id IN
(SELECT ba.person_id
FROM bank_accounts AS ba
JOIN atm_transactions AS atmt
ON ba.account_number = atmt.account_number
JOIN phone_calls AS pc
ON atmt.day = pc.day
WHERE atmt.day = 28 AND atmt.month = 7 AND atmt.year = 2021
AND atmt.atm_location = 'Leggett Street'
AND pc.duration < 60);

--get schema from flights table
.schema flights

--get schema from passengers table
.schema passengers

--get the name of the people that took the earliest flight out of fiftyville
--the folling day of the theft
SELECT p.name, f.hour
FROM people AS p
JOIN passengers AS pa
ON p.passport_number = pa.passport_number
JOIN flights AS f
ON pa.flight_id = f.id
JOIN airports AS a
ON f.origin_airport_id = a.id
WHERE f.day = 29 AND f.month = 7 AND f.year = 2021 AND f.hour = 8
AND a.city = 'Fiftyville';

--get the names of the people that left the bakery parking lot within 10 mins of the robery, and
--withdrew some money at the atm in Legget Street in the morning of the theft and that had phone calls
--lesser than 1 min in the day of the theft and the name of the people that took the earliest flight out of fiftyville
--the folling day of the theft
SELECT p.name
FROM people AS p
JOIN bakery_security_logs AS bsl
ON p.license_plate = bsl.license_plate
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute >= 15 AND minute <= 25
AND p.id IN
(SELECT ba.person_id
FROM bank_accounts AS ba
JOIN atm_transactions AS atmt
ON ba.account_number = atmt.account_number
JOIN phone_calls AS pc
ON atmt.day = pc.day
WHERE atmt.day = 28 AND atmt.month = 7 AND atmt.year = 2021
AND atmt.atm_location = 'Leggett Street'
AND pc.duration < 60 AND ba.person_id IN
(SELECT p.id
FROM people AS p
JOIN passengers AS pa
ON p.passport_number = pa.passport_number
JOIN flights AS f
ON pa.flight_id = f.id
JOIN airports AS a
ON f.origin_airport_id = a.id
WHERE f.day = 29 AND f.month = 7 AND f.year = 2021 AND f.hour = 8
AND a.city = 'Fiftyville'));

--get the name of the thief
SELECT name
FROM people AS p
JOIN phone_calls AS pc
ON p.phone_number = pc.caller
WHERE pc.day = 28 AND pc.month = 7 AND pc.year = 2021
AND pc.duration < 60 AND pc.caller IN
(SELECT p.phone_number
FROM people AS p
JOIN bakery_security_logs AS bsl
ON p.license_plate = bsl.license_plate
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute >= 15 AND minute <= 25
AND p.id IN
(SELECT ba.person_id
FROM bank_accounts AS ba
JOIN atm_transactions AS atmt
ON ba.account_number = atmt.account_number
JOIN phone_calls AS pc
ON atmt.day = pc.day
WHERE atmt.day = 28 AND atmt.month = 7 AND atmt.year = 2021
AND atmt.atm_location = 'Leggett Street'
AND pc.duration < 60 AND ba.person_id IN
(SELECT p.id
FROM people AS p
JOIN passengers AS pa
ON p.passport_number = pa.passport_number
JOIN flights AS f
ON pa.flight_id = f.id
JOIN airports AS a
ON f.origin_airport_id = a.id
WHERE f.day = 29 AND f.month = 7 AND f.year = 2021 AND f.hour = 8
AND a.city = 'Fiftyville')));

--get the name of the accomplice
SELECT p.name
FROM people AS p
WHERE p.phone_number IN
(SELECT pc.receiver
FROM phone_calls AS pc
WHERE pc.day = 28 AND pc.month = 7 AND pc.year = 2021
AND pc.duration < 60 AND pc.caller IN
(SELECT p.phone_number
FROM people AS p
JOIN bakery_security_logs AS bsl
ON p.license_plate = bsl.license_plate
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute >= 15 AND minute <= 25
AND p.id IN
(SELECT ba.person_id
FROM bank_accounts AS ba
JOIN atm_transactions AS atmt
ON ba.account_number = atmt.account_number
JOIN phone_calls AS pc
ON atmt.day = pc.day
WHERE atmt.day = 28 AND atmt.month = 7 AND atmt.year = 2021
AND atmt.atm_location = 'Leggett Street'
AND pc.duration < 60 AND ba.person_id IN
(SELECT p.id
FROM people AS p
JOIN passengers AS pa
ON p.passport_number = pa.passport_number
JOIN flights AS f
ON pa.flight_id = f.id
JOIN airports AS a
ON f.origin_airport_id = a.id
WHERE f.day = 29 AND f.month = 7 AND f.year = 2021 AND f.hour = 8
AND a.city = 'Fiftyville'))));


--get hte name of the city the thief escaped to
SELECT a.city
FROM airports AS a
WHERE a.id IN
(SELECT f.destination_airport_id
FROM flights AS f
JOIN passengers AS p
ON f.id = p.flight_id
WHERE day = 29 AND month = 7 AND year = 2021
AND p.passport_number IN
(SELECT people.passport_number
FROM people
WHERE name = 'Bruce'));