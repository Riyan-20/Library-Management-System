# Library Management System

This C++ program implements a Library Management System using an AVL tree for efficient storage and retrieval of book records. It allows users to perform operations like creating, reviewing, updating, and deleting book records.

## Features

- **Create Book Record:** Users can add new book records to the library database, including details like ISSN, title, author, and the number of copies available for reference and issuance.

- **Review Book Record:** Users can review the details of a specific book record by entering its ISSN.

- **Update Book Record:** Existing book records can be updated, including modifying the title, author, and the number of copies available for reference and issuance.

- **Delete Book Record:** Users can delete a book record from the library database by specifying its ISSN.

- **Print All Records:** The program allows users to print the details of all book records stored in the library.

## Implementation

- The program utilizes a combination of classes, including `AVL` for AVL tree operations and `list` for managing the linked list of book records.

- Each book record is represented by a `Dnode` containing information such as ISSN, title, author, and copies available.

- The AVL tree ensures balanced storage of book records, optimizing search and retrieval operations.

## Usage

1. Run the program.
2. Choose an option from the menu:
   - Enter `1` to create a new book record.
   - Enter `2` to review a book record.
   - Enter `3` to update a book record.
   - Enter `4` to delete a book record.
   - Enter `0` to print all book records.
3. Follow the prompts to perform the desired operation.
4. Repeat steps 2-3 as needed.
5. Enter `C` to continue or exit the program.

## Dependencies

- This program requires a C++ compiler to build and run.

## License

This project is licensed under the [MIT License](LICENSE).
