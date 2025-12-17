SELECT name
FROM people
Where id in (
    SELECT person_id FROM directors where movie_id IN (
        SELECT id FROM movies where id IN (
            SELECT movie_id FROM ratings WHERE rating >= 9.0
        )
    )
)
GROUP BY name;