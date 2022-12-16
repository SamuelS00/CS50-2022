SELECT mo.title, ra.rating
  FROM ratings as ra
  JOIN movies as mo
    ON mo.id = ra.movie_id
    WHERE year = 2010
    ORDER BY ra.rating DESC, mo.title ASC;