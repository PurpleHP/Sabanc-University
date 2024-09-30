CREATE TABLE Movies(
    Movie_id INT,
    Movie_name CHAR(128),
    Release_date DATE,
    Language CHAR(64),
    Length INT,
    PRIMARY KEY (Movie_id)
);

CREATE TABLE Genre(
    Genre_name CHAR(64),
    PRIMARY KEY (Genre_name)
);

CREATE TABLE Genres(
    Genre_name CHAR(64) NOT NULL,
    Movie_id INT,
    PRIMARY KEY (Genre_name, Movie_id),
    FOREIGN KEY (Genre_name) REFERENCES Genre(Genre_name),
    FOREIGN KEY (Movie_id) REFERENCES Movies(Movie_id)
);

CREATE TABLE Money(
    Country CHAR(64),
    Box_Office INT,
    Movie_id INT NOT NULL,
    PRIMARY KEY (Country, Movie_id),
    FOREIGN KEY (Movie_id) REFERENCES Movies(Movie_id) ON DELETE CASCADE
);

CREATE TABLE Person(
    Birth_date DATE,
    ID INT,
    Full_Name CHAR(64),
    Gender CHAR(20),
    PRIMARY KEY(ID)
);

CREATE TABLE Critic(
    ID INT,
    Metascore INT,
    PRIMARY KEY(ID),
    FOREIGN KEY(ID) REFERENCES Person(ID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Rated_critic(
    ID INT NOT NULL,
    Movie_id INT,
    Date DATE,
    PRIMARY KEY (ID, Movie_id),
    FOREIGN KEY (ID) REFERENCES Critic(ID) ON DELETE NO ACTION,
    FOREIGN KEY (Movie_id) REFERENCES Movies(Movie_id) ON DELETE CASCADE
);



CREATE TABLE Regular(
    ID INT,
    IMDB_rating DECIMAL(3,1),
    PRIMARY KEY(ID),
    FOREIGN KEY(ID) REFERENCES Person(ID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Rated_regular(
    ID INT NOT NULL,
    Movie_id INT,
    Date DATE,
    PRIMARY KEY (ID, Movie_id),
    FOREIGN KEY (ID) REFERENCES Regular(ID) ON DELETE NO ACTION,
    FOREIGN KEY (Movie_id) REFERENCES Movies(Movie_id) ON DELETE CASCADE
);

CREATE TABLE Producer(
    ID INT,
    PRIMARY KEY(ID),
    FOREIGN KEY(ID) REFERENCES Person(ID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Director(
    ID INT,
    PRIMARY KEY(ID),
    FOREIGN KEY(ID) REFERENCES Person(ID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Actor_Actress(
    ID INT,
    PRIMARY KEY(ID),
    FOREIGN KEY(ID) REFERENCES Person(ID) ON DELETE CASCADE ON UPDATE CASCADE
);



CREATE TABLE Produced(
    ID INT NOT NULL,
    Movie_id INT,
    PRIMARY KEY (ID, Movie_id),
    FOREIGN KEY (ID) REFERENCES Producer(ID) ON DELETE NO ACTION,
    FOREIGN KEY (Movie_id) REFERENCES Movies(Movie_id) ON DELETE CASCADE
);

CREATE TABLE Directed(
    ID INT NOT NULL,
    Movie_id INT,
    PRIMARY KEY (ID, Movie_id),
    FOREIGN KEY (ID) REFERENCES Director(ID) ON DELETE NO ACTION,
    FOREIGN KEY (Movie_id) REFERENCES Movies(Movie_id) ON DELETE CASCADE
);

CREATE TABLE Acted_in(
    ID INT NOT NULL,
    Role CHAR(128),
    Movie_id INT,
    PRIMARY KEY (ID, Movie_id),
    FOREIGN KEY (ID) REFERENCES Actor_Actress(ID) ON DELETE NO ACTION,
    FOREIGN KEY (Movie_id) REFERENCES Movies(Movie_id) ON DELETE CASCADE
);

INSERT INTO Person (Birth_date, ID, Full_Name, Gender)
VALUES
('1990-08-15', 3401, 'Jennifer Lawrence', 'Female'),
('1968-10-12', 3402, 'Hugh Jackman', 'Male'),
('1970-10-08', 3403, 'Matt Damon', 'Male'),
('1981-06-09', 3404, 'Natalie Portman', 'Female'),
('1975-01-05', 3405, 'Bradley Cooper', 'Male'),
('1968-08-09', 3406, 'Eric Bana', 'Male'),
('1963-12-18', 3407, 'Brad Pitt', 'Male'),
('1988-11-06', 3408, 'Emma Stone', 'Female'),
('1980-11-12', 3409, 'Ryan Gosling', 'Male'),
('1958-10-20', 3410, 'Viggo Mortensen', 'Male'),
('1956-11-03', 3501, 'Gary Ross', 'Male'),
('1963-12-16', 3502, 'James Mangold', 'Male'), 
('1937-11-30', 3503, 'Ridley Scott', 'Male'),
('1931-11-06', 3504, 'Mike Nichols', 'Male'),     
('1970-12-20', 3505, 'Todd Phillips', 'Male'),
('1941-03-14', 3506, 'Wolfgang Petersen', 'Male'),
('1962-08-28', 3507, 'David Fincher', 'Male'),
('1985-01-19', 3508, 'Damien Chazelle', 'Male'),
('1970-09-29', 3509, 'Nicolas Winding Refn', 'Male'),
('1961-10-31', 3510, 'Peter Jackson', 'Male'),
('1965-07-05', 3601, 'Nina Jacobson', 'Female'),
('1964-11-20', 3602, 'Hutch Parker', 'Male'),
('1973-08-02', 3603, 'Simon Kinberg', 'Male'),
('1931-11-06', 3604, 'Mazo Baba', 'Male'),
('1970-12-20', 3605, 'Hiko Baba', 'Male'),
('1950-01-01', 3606, 'Colin Wilson', 'Male'),
('1942-01-01', 3607, 'Art Linson', 'Male'),
('1981-01-01', 3608, 'Fred Berger', 'Male'),
('1957-01-01', 3609, 'Marc Platt', 'Male'),
('1944-01-01', 3610, 'Barrie M. Osborne', 'Male'),
('2002-02-26', 3701, 'Berk Bilgic', 'Male'),
('2001-02-26', 3702, 'Emre Bumblebee', 'Female'),
('2002-02-26', 3703, 'Person A', 'Male'),
('2002-02-27', 3704, 'Person B', 'Female'),
('2002-02-28', 3705, 'Person C', 'Male'),
('2002-03-01', 3706, 'Person D', 'Female'),
('2002-03-02', 3707, 'Person E', 'Male'),
('2002-03-03', 3708, 'Person F', 'Female'),
('2002-03-04', 3709, 'Person G', 'Male'),
('2002-03-05', 3710, 'Person H', 'Female'),
('2002-02-26', 3801, 'Individual I', 'Male'),
('2002-02-27', 3802, 'Individual J', 'Female'),
('2002-02-28', 3803, 'Individual K', 'Male'),
('2002-03-01', 3804, 'Individual L', 'Female'),
('2002-03-02', 3805, 'Individual M', 'Male'),
('2002-03-03', 3806, 'Individual N', 'Female'),
('2002-03-04', 3807, 'Individual O', 'Male'),
('2002-03-05', 3808, 'Individual P', 'Female'),
('2002-03-06', 3809, 'Individual Q', 'Male'),
('2002-03-07', 3810, 'Individual R', 'Female');

INSERT INTO Acted_in (ID, Role, Movie_id) 
VALUES
(3401, 'Katniss Everdeen', 2401),
(3402, 'Logan', 2402),
(3403, 'Mark Watney', 2403),
(3404, 'Alice', 2404),
(3405, 'Phil', 2405),
(3406, 'Hector', 2406),
(3407, 'Tyler Durden', 2407),
(3408, 'Mia', 2408),
(3409, 'Driver', 2409),
(3410, 'Aragorn', 2410);

INSERT INTO Movies (Movie_id, Movie_name, Release_date, Language, Length) VALUES
(2401, 'The Hunger Games', '2012-03-23', 'English', 142),
(2402, 'Logan', '2017-03-03', 'English', 137),
(2403, 'The Martian', '2015-10-02', 'English', 144),
(2404, 'Closer', '2004-12-03', 'English', 104),
(2405, 'Hangover', '2009-06-05', 'English', 100),
(2406, 'Troy', '2004-05-14', 'English', 163),
(2407, 'Fight Club', '1999-10-15', 'English', 139),
(2408, 'La La Land', '2016-12-09', 'English', 128),
(2409, 'Drive', '2011-09-16', 'English', 100),
(2410, 'The Lord Of The Rings: The Fellowship Of The Ring', '2001-12-19', 'English', 178);

INSERT INTO Directed (ID, Movie_id) VALUES
(3501, 2401),
(3502, 2402),
(3503, 2403),
(3504, 2404),
(3505, 2405),
(3506, 2406),
(3507, 2407),
(3508, 2408),
(3509, 2409),
(3510, 2410);

INSERT INTO Produced (ID, Movie_id) VALUES
(3601, 2401),
(3602, 2402),
(3603, 2403),
(3604, 2404),
(3605, 2405),
(3606, 2406),
(3607, 2407),
(3608, 2408),
(3609, 2409),
(3610, 2410);

INSERT INTO Rated_regular (ID, Movie_id, Date) VALUES
(3701, 2401, '2024-03-05'),
(3702, 2402, '2024-03-05'),
(3703, 2403, '2024-03-05'),
(3704, 2404, '2024-03-05'),
(3705, 2405, '2024-03-05'),
(3706, 2406, '2024-03-05'),
(3707, 2407, '2024-03-05'),
(3708, 2408, '2024-03-05'),
(3709, 2409, '2024-03-05'),
(3710, 2410, '2024-03-05');

INSERT INTO Rated_critic (ID, Movie_id, Date) VALUES
(3801, 2401, '2024-03-05'),
(3802, 2402, '2024-03-05'),
(3803, 2403, '2024-03-05'),
(3804, 2404, '2024-03-05'),
(3805, 2405, '2024-03-05'),
(3806, 2406, '2024-03-05'),
(3807, 2407, '2024-03-05'),
(3808, 2408, '2024-03-05'),
(3809, 2409, '2024-03-05'),
(3810, 2410, '2024-03-05');

INSERT INTO Critic (ID, Metascore) VALUES
(3801, 85),
(3802, 70),
(3803, 90),
(3804, 80),
(3805, 75),
(3806, 65),
(3807, 88),
(3808, 82),
(3809, 95),
(3810, 78);

INSERT INTO Regular (ID, IMDB_rating) VALUES
(3701, 7.5),
(3702, 6.8),
(3703, 8.2),
(3704, 6.4),
(3705, 7.1),
(3706, 5.9),
(3707, 8.4),
(3708, 9.0),
(3709, 6.7),
(3710, 7.3);

INSERT INTO Money (Country, Box_Office, Movie_id) VALUES
('USA', 408010692, 2401),
('USA', 226277068, 2402),
('USA', 228433663, 2403),
('USA', 33987757, 2404),
('USA', 277339746, 2405),
('USA', 133378256, 2406),
('USA', 37030102, 2407),
('USA', 151101803, 2408),
('USA', 35061555, 2409),
('USA', 316115420, 2410);

INSERT INTO Genre (Genre_name) VALUES
('Action'),
('Adventure'),
('Drama'),
('Thriller'),
('Comedy'),
('Fantasy'),
('Sci-Fi'),
('Romance'),
('Crime'),
('Animation');

INSERT INTO Genres (Genre_name, Movie_id) VALUES
('Action', 2401),
('Action', 2402),
('Sci-Fi', 2403),
('Romance', 2404),
('Comedy', 2405),
('Adventure', 2406),
('Drama', 2407),
('Romance', 2408),
('Action', 2409),
('Adventure', 2410);

INSERT INTO Producer (ID) VALUES
(3601),
(3602),
(3603),
(3604),
(3605),
(3606),
(3607),
(3608),
(3609),
(3610);

INSERT INTO Director (ID) VALUES
(3501),
(3502),
(3503),
(3504),
(3505),
(3506),
(3507),
(3508),
(3509),
(3510);

INSERT INTO Actor_Actress (ID) VALUES
(3401),
(3402),
(3403),
(3404),
(3405),
(3406),
(3407),
(3408),
(3409),
(3410);
