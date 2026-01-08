✈️ Airline Reservation System (C Language)

A menu-driven Airline Reservation System developed in C that allows admins, customers, and staff to manage flights, bookings, passengers, and staff records efficiently.
The project uses file handling to store data permanently and demonstrates core Computer Fundamentals and C programming concepts.

--------------------------------------------------

FEATURES

ADMIN MODULE
- Add new flights
- View all available flights
- Add airline staff
- View staff details

CUSTOMER MODULE
- Search flights by source and destination
- Book flight tickets
- Automatic seat number generation
- View bookings
- Cancel bookings

STAFF MODULE
- View flight details
- View passenger booking records

--------------------------------------------------

TECHNOLOGIES USED

Language:
- C

Concepts Used:
- Structures
- File Handling (.dat files)
- Arrays
- Functions
- Random seat generation
- Menu-driven programming

--------------------------------------------------

DATA STORAGE

The system uses binary files for permanent storage:
- flights.dat      -> Flight records
- passengers.dat   -> Passenger booking records
- staff.dat        -> Staff information

--------------------------------------------------

PROJECT STRUCTURE

Airline-Reservation-System/
|
|-- main.c
|-- flights.dat
|-- passengers.dat
|-- staff.dat
|-- README.md

--------------------------------------------------

HOW TO RUN THE PROGRAM

1. Open terminal / command prompt
2. Compile the code using:
   gcc main.c -o airline
3. Run the program using:
   ./airline

--------------------------------------------------

MENU OPTIONS

MAIN MENU
1. Admin
2. Customer
3. Staff
4. Exit

Each module contains its own sub-menu for specific operations.

--------------------------------------------------

LEARNING OUTCOMES

- Practical use of structures and arrays
- Understanding of file handling in C
- Real-world implementation of a reservation system
- Improved logic building and modular programming skills

--------------------------------------------------

FUTURE ENHANCEMENTS

- Login authentication system
- Seat availability visualization
- Date-wise flight search
- Ticket fare calculation with discounts
- Graphical User Interface (GUI)

--------------------------------------------------

AUTHOR

Name: Moksh Khera
Course: BCA
Role: Aspiring Software Developer

--------------------------------------------------

If you like this project, don’t forget to give it a star on GitHub!
