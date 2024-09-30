ALTER TABLE Movies 
ADD CONSTRAINT  MovieShouldBeBefore2024
CHECK (release_date < '2024-01-01');

INSERT INTO Movies (Movie_id, Movie_name, Release_date, movie_language, Movie_Length) VALUES 
(2421, 'Kung Fu Panda 4', '2024-04-05', "English", 94);


INSERT INTO Movies (Movie_id, Movie_name, Release_date, movie_language, Movie_Length) VALUES 
(2422, "Five Nights at Freddy's", '2023-11-03', "English", 109);

#Error Code: 3819. Check constraint 'MovieShouldBeAfter2004' is violated.
