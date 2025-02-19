SELECT title FROM movies AS m
JOIN stars AS s ON m.id = s.movie_id
JOIN people AS p ON s.person_id = p.id
WHERE p.name = 'Bradley Cooper' AND m.title IN
(SELECT title FROM movies AS m
JOIN stars AS s ON m.id = s.movie_id
JOIN people AS p ON s.person_id = p.id
WHERE p.name = 'Jennifer Lawrence');