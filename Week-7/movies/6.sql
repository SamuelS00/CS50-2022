SELECT avg(ra.rating) as avg
  FROM ratings as ra
  JOIN movies as mo
    ON mo.id = ra.movie_id
    WHERE year = 2012;