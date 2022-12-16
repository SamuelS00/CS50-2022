SELECT mo.title
  FROM people as pe
       JOIN stars as st
         ON pe.id = st.person_id
       JOIN movies as mo
         ON st.movie_id = mo.id
  WHERE pe.name = "Johnny Depp"
    AND mo.title IN
  (SELECT movies.title
     FROM people
          JOIN stars
            ON people.id = stars.person_id
          JOIN movies
            ON stars.movie_id = movies.id
     WHERE people.name = "Helena Bonham Carter");