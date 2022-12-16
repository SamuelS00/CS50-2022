SELECT DISTINCT(pe.name)
  FROM people AS pe
       JOIN stars AS st
         ON pe.id = st.person_id
       JOIN movies AS mo
         ON st.movie_id = mo.id
  WHERE mo.title IN
       (SELECT mo.title
          FROM movies AS mo
               JOIN stars AS st ON mo.id = st.movie_id
               JOIN people AS pe ON st.person_id = pe.id
          WHERE pe.name = "Kevin Bacon"
            AND pe.birth = 1958)
    AND pe.name != "Kevin Bacon";