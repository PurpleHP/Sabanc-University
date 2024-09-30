CREATE TABLE Movies( 
  Movie_id INT, 
  Movie_name CHAR(128), 
  Release_date DATE, 
  Movie_Length INT, 
  Movie_Language char(32),
  PRIMARY KEY (Movie_id) 
); 

CREATE TABLE Genre( 
  Genre_name CHAR(64), 
  Genre_Id INT,
  PRIMARY KEY (Genre_Id) 
); 

CREATE TABLE Genres( 
  Genre_ID INT NOT NULL, 
  Movie_id INT NOT NULL, 
  PRIMARY KEY (Genre_Id, Movie_id), 
  FOREIGN KEY (Genre_Id) REFERENCES Genre(Genre_Id) ON DELETE CASCADE, 
  FOREIGN KEY (Movie_id) REFERENCES Movies(Movie_id) ON DELETE CASCADE
);
