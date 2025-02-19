SELECT r.rating, m.title FROM ratings AS r
JOIN movies AS m ON r.movie_id = m.id
WHERE m.year = 2010
ORDER BY r.rating DESC, m.title;