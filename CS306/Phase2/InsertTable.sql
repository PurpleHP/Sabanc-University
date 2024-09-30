INSERT INTO Movies (Movie_id, Movie_name, Release_date, movie_language, Movie_Length) VALUES 
(2411, 'Blade Runner 2049', '2017-10-03', "English", 164), 
(2412, 'The Dark Knight Rises', '2012-07-27', "English", 164), 
(2413, 'Matrix', '1999-07-03',"English",136), 
(2414, 'Back to the Future', '1987-02-14',"English", 116), 
(2415, 'Truman Show', '1998-10-16', "English",103 ), 
(2416, 'Toy Story 3', '2010-07-02', "English", 103), 
(2417, 'Cars', '2006-08-15',"English", 116), 
(2418, '3 Idiots', '2009-11-09', "Hindi", 170), 
(2419, 'Kral Sakir: Mikrop Avcilari', '2021-01-22', "Turkish",41 ), 
(2420, 'Tonari no Totoro', '2007-06-06', "Japanese", 86);

#------------------------------------------------------------------------------------------------

INSERT INTO Genre (Genre_Id, Genre_Name) VALUES 
(1411, 'Action'),
(1412, 'Adventure'),
(1413, 'Drama'),
(1414, 'Thriller'),
(1415, 'Comedy'),
(1416, 'Fantasy'),
(1417, 'Sci-Fi'),
(1418, 'Romance'),
(1419, 'Crime'),
(1420, 'Animation'); 

#------------------------------------------------------------------------------------------------

INSERT INTO Genres (Genre_Id, Movie_id) VALUES 
(1414, 2411),
(1411, 2411),
(1417, 2411),
(1413, 2411),
(1411, 2412),
(1413, 2412),
(1414, 2412),
(1411, 2413),
(1417, 2413),
(1417, 2414),
(1415, 2414),
(1415, 2415),
(1413, 2415),
(1415, 2416),
(1420, 2416),
(1412, 2416),
(1420, 2417),
(1412, 2417),
(1415, 2418),
(1413, 2418),
(1420, 2419),
(1420, 2420),
(1416,2420),
(1415, 2420);

#------------------------------------------------------------------------------------------------

SELECT * FROM movies;
SELECT * FROM genres;
SELECT * FROM genre;
