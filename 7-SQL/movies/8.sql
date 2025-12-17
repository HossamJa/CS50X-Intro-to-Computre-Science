SELECT name FROM people WHERE id IN (
    SELECT person_id from stars where movie_id = (
        SELECT id FROM movies WHERE title = 'Toy Story'
    )
);