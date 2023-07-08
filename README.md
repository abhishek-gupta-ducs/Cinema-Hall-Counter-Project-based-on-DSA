# Cinema-Hall-Ticket-Counter-Project-based-on-DSA

This Cinema Hall ticket counter Booking System is a collection of programs that simulate a ticket booking process. It consists of several classes and functionalities to manage customers, queues, stalls, sorting of booked tickets, and the booking process itself.


# About All Classes Used


## customerStruct.h
This header file defines the structure of a customer who is standing in a row for ticket booking.

## customerBookedStruct.h
This header file defines the structure of a customer whose ticket has been booked, including the customer's name, booking ID, number of tickets booked, and seat numbers.

## customerQueue.h
This header file contains the implementation of a <b>Queue</b> (implemented using a linked list) of customers standing in a row for ticket booking.

## stallStack.h
This header file defines a <b>Stack</b> data structure to manage tickets for a particular stall (front, middle, or balcony).

## booker.h
The booker.h program contains the implementation of the showBooking class, which provides functions to handle the ticket booking workflow, including managing stalls and assigning seats to customers.

## shower.h
The shower.h file includes the customerChecker class, which provides functionalities to display the final list, search for customer details, and perform sorting.

## sort.h
The sort.h header file provides a class that implements quick sorting algorithm for the final list of booked customers. It supports sorting by booking ID or name.


# All Functionalities

## 1. Booking Customers:
   - The booker.h program provides classes and functions to manage the ticket booking process. It includes functionality to book customers, assign seats, and manage stalls.

## 2. Displaying Final List:
   - The customerChecker class in shower.h provides a function to display the final list of customers whose tickets have been booked. It shows the booking ID, customer name, and seat numbers.

## 3. Searching Customer Details:
   - The customerChecker class in shower.h allows searching for customer details based on their name. It provides a function to print all details of customers matching the given name.

## 4. Sorting the Final List:
   - The customerChecker class in shower.h supports sorting the final list of booked customers. It can be sorted by booking ID or name using the provided sorting functionalities.



# Installation Guide

## For Ubuntu
1. Download compressed file
2. Extract all
3. Open Ubuntu folder
4. In `main.cpp`  program, Just change the path of `../Ubuntu/Shows` and `../Ubuntu/BookedShowsDetails` folder in variable `folderPath_1` and `folderPath_2` respectively.
5. Use this [link](https://docs.google.com/forms/d/e/1FAIpQLSfQCV3UsKycpaVmtvheYkfGRkjk1URrdcPFmCC_UFRW48Fy3Q/viewform) to copy the google form , to take user's input for tickets.

6. Save the `.csv` files containing user input in `../Ubuntu/Shows` folder.

7. Run the code at terminal by running the following command...

    `g++ main.cpp -o main`

    or

    `gcc main.cpp -o main -lstdc++`

## For Windows

1. Download compressed file
2. Extract all
3. Open Windows folder
4. In `main.cpp`  program, Just change the path of `..\Windows\Shows` and `..\Windows\BookedShowsDetails` folder in variable `folderPath_1` and `folderPath_2` respectively.
5. Use this [link](https://docs.google.com/forms/d/e/1FAIpQLSfQCV3UsKycpaVmtvheYkfGRkjk1URrdcPFmCC_UFRW48Fy3Q/viewform) to copy the google form , to take user's input for tickets.

6. Save the `.csv` files containing user input in `..\Windows\Shows` folder.

7. Run the code at terminal by running the following command...

    `g++ main.cpp -o main`

    or

    `gcc main.cpp -o main -lstdc++`

# Results

![booker](/Presentation/booker.gif)
![booker](/Presentation/shower.gif)
