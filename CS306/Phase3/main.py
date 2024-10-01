#Author: Ertuğrul Mert Taylan   ID: 32005
import mysql.connector

cnx = mysql.connector.connect(
    user="root", password="1234", database="cs306phase3"
)
print("\nConnection established with the database\n")

cursor = cnx.cursor()
#connected to the database -----------------------------------------

def read(query):
    print("Query: " + query)
    cursor.execute(query)
    records = cursor.fetchall()
    return records


print("\nMovies Table:")
query3 = "SELECT * FROM movies"
records = read(query3)
for record in records:
    print(record)

print("\nGenre Table:")
query4 = "SELECT * FROM genre"
records = read(query4)
for record in records:
    print(record)

print("-----------------------------------------------------------------------------\n")



def insert(query, values, msg=""):
    print("Query: " + query)
    cursor.execute(query, values)
    cnx.commit()
    print(msg)

query1 = "INSERT INTO movies (Movie_id, Movie_name, Release_date, Movie_Length,Movie_Language) VALUES (%s,%s, %s, %s, %s);"

movie = (2423, "Megamind", "2011-01-14", 95, "English")
insert(query1, movie,"Movie inserted\n")

query2 = "INSERT INTO genre (Genre_id, Genre_name) VALUES (%s, %s);"

genre = (1421, "Family")
insert(query2, genre, "Genre inserted")

print("-----------------------------------------------------------------------------\n")
#inserted a movie and a genre --------------------------------------------------

def read(query):
    print("Query: " + query)
    cursor.execute(query)
    records = cursor.fetchall()
    return records


print("\nRead Movies After Insertion:")
query3 = "SELECT * FROM movies"
read(query3)
cursor.execute(query3)
records = cursor.fetchall()
for record in records:
    print(record)

print("\nRead Genres After Insertion:")
query4 = "SELECT * FROM genre"
read(query4)
cursor.execute(query4)
records = cursor.fetchall()
for record in records:
    print(record)

print("-----------------------------------------------------------------------------\n")
#read movies and genres -------------------------------------------------------

def update(query, values, msg=""):
    print("\nQuery: " + query, end="\n")
    cursor.execute(query, values)
    cnx.commit()
    print(msg)

query5 = "UPDATE movies SET movie_length = %s WHERE movie_id = %s"
movieToUpdate = (110, 2423)
update(query5, movieToUpdate, "Movie updated")

print("\nMovies after update:")
cursor.execute(query3)
records = cursor.fetchall()
for record in records:
    print(record)


query6 = "UPDATE genre SET genre_name = %s WHERE genre_id = %s"
genreToUpdate = ("Science Fiction", 1417)
update(query6, genreToUpdate, "Genre updated")

print("\nGenre after update:")
cursor.execute(query4)
records = cursor.fetchall()
for record in records:
    print(record)

print("-----------------------------------------------------------------------------\n")
#updated movie length and genre name ----------------------------------------------

def delete(query, values, msg=""):
    print("\nQuery: " + query)
    cursor.execute(query, values)
    cnx.commit()
    print(msg)

query7 = "DELETE FROM movies WHERE movie_id = %s"
movieToDelete = (2423,)
delete(query7, movieToDelete, "Movie deleted")

print("\nMovies after deletion:")
cursor.execute(query3)
records = cursor.fetchall()
for record in records:
    print(record)

query8 = "DELETE FROM genre WHERE genre_id = %s"
genreToDelete = (1421,)
delete(query8, genreToDelete, "Genre deleted")

print("\nGenre after deletion:")
cursor.execute(query4)
records = cursor.fetchall()
for record in records:
    print(record)

print("-----------------------------------------------------------------------------\n")

#deleted a movie and a genre -----------------------------------------------------

cursor.close()
cnx.close()
print("Database connection closed.\n")
