SELECT mo.title
  FROM movies as mo
  JOIN stars as st
    ON mo.id = st.movie_id
  JOIN people as pe
    ON pe.id = st.person_id
  JOIN ratings as ra
    ON ra.movie_id = mo.id
  WHERE pe.name = "Chadwick Boseman"
  ORDER BY ra.rating DESC
  LIMIT 5;