SELECT pr.name
  FROM people AS pr
  JOIN stars AS st
    ON pr.id = st.person_id
  JOIN movies AS mo
    ON mo.id = st.movie_id
    WHERE title = "Toy Story";