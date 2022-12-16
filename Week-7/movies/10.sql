SELECT DISTINCT pe.name
  FROM people as pe
  JOIN directors as di
    ON di.person_id = pe.id
  JOIN movies as mo
    ON mo.id = di.movie_id
  JOIN ratings as ra
    ON ra.movie_id = mo.id
  WHERE rating = 9.0 OR rating > 9.0;
