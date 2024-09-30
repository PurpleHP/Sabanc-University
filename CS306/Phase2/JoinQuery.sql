SELECT M.movie_name as Movie_Name, C.Total_Genre_Count as Total_Genre_Count
FROM Movies as M
JOIN (
	SELECT S2.movie_id, COUNT(*) as Total_Genre_Count
	FROM Genre as G
	JOIN Genres as S2 on G.genre_id = S2.genre_id
	GROUP BY S2.Movie_id
	HAVING Count(*)>2
) as C
ON M.movie_id = C.movie_id;
