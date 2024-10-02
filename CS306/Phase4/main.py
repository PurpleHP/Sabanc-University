import sys
import os
import certifi

#these lines are for checking the interpreter and python versions (to see any mismatch)
print("Python version:", sys.version)
print("Python executable:", sys.executable)
print("Python path:", os.environ.get('PYTHONPATH'))

# these lines are for checking the pymongo whetjher or not it is installed right
try:
    import pymongo
    from pymongo import MongoClient
    print("pymongo module found")
except ImportError as e:
    print("pymongo module not found:", e)
    sys.exit(1)

# mongodb atlas connection string // username emrebulbul22 pass xs3cICS8Y3BcgJ21
CONNECTION_STRING = "mongodb+srv://emrebulbul22:xs3cICS8Y3BcgJ21@cluster0.jyr1r89.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"

# cpnect mongodb atlas certifi is needed to certificate the pc
client = MongoClient(CONNECTION_STRING, tlsCAFile=certifi.where())
db = client['cluster0']

# create a collection
def create_collection(collection_name):
    db.create_collection(collection_name)
    print(f"Collection '{collection_name}' created successfully.")


# read all data from a collection name
def read_all_data(collection_name):
    collection = db[collection_name]
    documents = collection.find()
    for document in documents:
        print(document)


# disoplay data by a filter
def read_filtered_data(collection_name, filter_criteria):
    collection = db[collection_name]
    documents = collection.find(filter_criteria)
    for document in documents:
        print(document)

#ins ert data into a collection created b4
def insert_data(collection_name, data):
    collection = db[collection_name]
    collection.insert_one(data)
    print("Data inserted successfully.")


#delete data by filtering 
def delete_data(collection_name, filter_criteria):
    collection = db[collection_name]
    collection.delete_one(filter_criteria)
    print("Data deleted successfully.")


# update data using filter
def update_data(collection_name, filter_criteria, new_data):
    collection = db[collection_name]
    collection.update_one(filter_criteria, {"$set": new_data})
    print("Data updated successfully.")

# list all collections from the database
def list_collections():
    collections = db.list_collection_names()
    return collections

def main():
    while True:
        print("Welcome to the MongoDB Management System!")
        user_id = input("Please enter your user id: ")
        
        print("Please pick the option that you want to proceed.")
        print("1 - Create a collection.")
        print("2 - Read all data in a collection.")
        print("3 - Read some part of the data while filtering.")
        print("4 - Insert data.")
        print("5 - Delete data.")
        print("6 - Update data.")
        
        selected_option = input("Selected option: ")
        
        if selected_option == '1':
            collection_name = input("Please enter the collection name: ")
            create_collection(collection_name)
        elif selected_option == '2':
            collection_name = input("Please enter the collection name: ")
            read_all_data(collection_name)
        elif selected_option == '3':
            collection_name = input("Please enter the collection name: ")
            filter_field = input("Enter the field to filter by: ")
            filter_value = input("Enter the value to filter by: ")
            filter_criteria = {filter_field: {'$regex': filter_value, '$options': 'i'}}
            read_filtered_data(collection_name, filter_criteria)
        elif selected_option == '4':
            collections = list_collections()
            if not collections:
                print("No collections found. Please create a collection first.")
                continue
            print("Please select the collection you want to insert data into:")
            for i, col in enumerate(collections, start=1):
                print(f"{i} - {col}")
            collection_choice = int(input("Selected option: "))
            if 1 <= collection_choice <= len(collections):
                collection_name = collections[collection_choice - 1]
            else:
                print("Invalid collection choice")
                continue

            data = {}
            while True:
                field = input("Enter field name (or 'done' to finish): ")
                if field == 'done':
                    break
                value = input(f"Enter value for {field}: ")
                data[field] = value
            insert_data(collection_name, data)
        elif selected_option == '5':
            collection_name = input("Please enter the collection name: ")
            filter_field = input("Enter the field to filter by: ")
            filter_value = input("Enter the value to filter by: ")
            filter_criteria = {filter_field: filter_value}
            delete_data(collection_name, filter_criteria)
        elif selected_option == '6':
            collection_name = input("Please enter the collection name: ")
            filter_field = input("Enter the field to filter by: ")
            filter_value = input("Enter the value to filter by: ")
            filter_criteria = {filter_field: filter_value}
            new_data = {}
            while True:
                field = input("Enter field name to update (or 'done' to finish): ")
                if field == 'done':
                    break
                value = input(f"Enter new value for {field}: ")
                new_data[field] = value
            update_data(collection_name, filter_criteria, new_data)
        else:
            print("Invalid option, please try again.")

        continue_choice = input("Would you like to perform another action? (yes/no): ")
        if continue_choice.lower() != 'yes':
            break

if __name__ == "__main__":
    main()
