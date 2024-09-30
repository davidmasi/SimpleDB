# Simple Database Management System in C
This project is a basic database management system implemented in C. It simulates a lightweight, interactive command-line tool for managing three categories of data: programming languages, operating systems, and databases. Each category is modeled as a dynamically allocated table of structs, with support for common database operations like inserting, modifying, soft-deleting, and retrieving records.

Features:
- Data Management for Multiple Categories: Manage records for programming languages, operating systems, and databases, with separate fields for each category.
- Soft Delete Mechanism: Records can be marked as deleted without freeing the associated memory, ensuring data integrity.
- Dynamic Memory Allocation: Tables are dynamically allocated based on user input, with efficient management of record insertion and deletion.
- Command-line Interaction: Users can interact with the system through a command-line interface (CLI), using specific commands to manage the records.
  
Commands:
1. setup {table} {numRows}: Initializes a table (programmingLanguages, operatingSystems, or databases) with a specified number of rows.
2. insert {table} {data}: Inserts a record into the specified table.
3. delete {table} {id}: Marks a record as deleted.
4. modify {table} {id} {data}: Modifies the contents of a record with the given ID.
5. get {table}: Retrieves and displays all non-deleted records from the specified table.
6. exit: Frees allocated memory and exits the program.
   
Project Structure:
- language_t, system_t, database_t: Structs representing programming languages, operating systems, and databases, respectively.
- metadata_t: A struct for managing metadata (e.g., record count, next available index) for each table.
- Main Functions: Includes functions for inserting, modifying, deleting, and fetching records, as well as handling user input and dynamically managing memory.
  
How to Run:
1. Compile the program using a C compiler (e.g., gcc).
2. Run the compiled executable to enter the command-line interface.
3. Use the commands listed above to manage records.
