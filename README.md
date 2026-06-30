# Student Management System (C)

A simple, menu-driven **Student Management System** built in C. It lets you add, view, search, update, and delete student records, with data persisted to disk between runs using binary file I/O.

This project is a classic beginner/intermediate C exercise that combines several core concepts into one working application.

## Features

- Add student records (ID, name, course, marks)
- Display all students in a formatted table
- Search for a student by ID (linear search)
- Update an existing student's details
- Delete a student record
- Save all data to a file (`students.dat`)
- Automatically load saved data on program startup
- Input validation for numeric fields (rejects non-numeric input instead of crashing/looping garbage)

## Concepts Practiced

- Structures (`struct Student`)
- Arrays of structures
- Functions and modular program design
- String handling (`fgets`, `strcpy`, `strlen`)
- File handling (binary `fwrite` / `fread`)
- Linear search algorithm
- Menu-driven program flow with `do...while` and `switch`

## Project Structure

```
.
├── student_management.c   # Main source file
├── students.dat            # Auto-generated data file (created after first save)
└── README.md
```

## Requirements

- A C compiler (GCC recommended)
- Works on Linux, macOS, or Windows (via MinGW/WSL)

## How to Compile

```bash
gcc -Wall -o student_management student_management.c
```

`-Wall` enables all warnings — good practice to catch issues early.

## How to Run

```bash
./student_management
```

On Windows (without WSL):

```bash
student_management.exe
```

## Usage

When you run the program, you'll see a menu like this:

```
===================================
   STUDENT MANAGEMENT SYSTEM
===================================
1. Add Student
2. Display All Students
3. Search Student by ID
4. Update Student
5. Delete Student
6. Save to File
0. Exit
===================================
Enter your choice:
```

Enter a number to choose an action. Data is automatically loaded from `students.dat` at startup (if the file exists) and automatically saved when you exit (option `0`). You can also save manually at any time with option `6`.

### Example Workflow

1. Choose `1` to add a student — enter ID, name, course, and marks.
2. Choose `2` to view all current records in a table.
3. Choose `3` and enter an ID to look up a specific student.
4. Choose `4` to update a student's name, course, or marks (leave name/course blank to keep the current value).
5. Choose `5` to delete a record (you'll be asked to confirm with `y`/`n`).
6. Choose `0` to save and exit.

## Data Storage

Records are stored in `students.dat` in **binary format** (not human-readable as plain text). This file is created automatically the first time you save. Deleting `students.dat` will reset the system to an empty student list.

## Limitations / Notes

- Maximum capacity is `MAX_STUDENTS` (100 by default) — adjustable in the source code.
- IDs must be unique; the system prevents adding a duplicate ID.
- Data is stored in binary form, so it isn't easily readable or editable outside the program (e.g., in a text editor). Switching to CSV/text storage is a good next exercise if you want human-readable data.

## Possible Improvements (Ideas for Practice)

- Switch from binary file storage to CSV/text format
- Add sorting (by ID, name, or marks)
- Replace linear search with binary search (requires keeping records sorted by ID)
- Add input length limits/sanitization for names and course fields
- Export records to a formatted report file