#include "booker.h"
#include "shower.h"
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <thread>
using namespace std;

//menu of the program
void menu(){
    cout<<"***********************************************************\n";
    cout<<"                   Welcome to XYZ Cinemas                  \n";
    cout<<"***********************************************************\n";
    cout<<"            1. Open Counter to book tickets                \n";
    cout<<"            2. View details of booked customer             \n";
    cout<<"***********************************************************\n";
    cout<<"Enter your choice : ";
}
//function to take user choice
char getChoice(){
    char ch;
    cin>>ch;
    while(ch!='1' && ch!='2'){
        cout<<"Wrong Choice\n";
        cout<<"Enter Again : ";
        cin>>ch;
    }
    return ch;
}
//function to display directory
void displayDirectoryContents(string path){
    DIR* directory = opendir(path.c_str());
    if (directory){
        struct dirent* entry;    
        cout<<"************************************************************\n";
        cout<<"                        Today's Show                        \n";
        cout<<"************************************************************\n";
        while ((entry = readdir(directory)) != nullptr){
            if(!strcmp(entry->d_name , "..") || !strcmp(entry->d_name,"."))
                continue;
            cout<<entry->d_name<<endl;
            cout<<"************************************************************\n";
        }
        closedir(directory);
    }
}

//function to enter csv file
string getFile(string message,string folderPath){
    string fileName;
    cout<<message;
    cin>>fileName;
    string filePath = folderPath + "/" + fileName;
    const char* temp = filePath.c_str();
    while(access(temp,F_OK)==-1){
        cout<<"File Does not exist\n";
        cout<<"Enter Again : ";
        cin>>fileName;
        filePath = folderPath + "/" + fileName;
        temp = filePath.c_str();
    }
    return fileName;
}

//Main Program for ticket bbooking
int main(){

    //print menu to user
    menu();
    //define folder path for choice 1
    string folderPath_1 = "C:\\Users\\abhis\\Downloads\\Movie Hall Ticket Booking Assignment\\Shows";
    
    //define folder path for choice 2
    string folderPath_2 = "C:\\Users\\abhis\\Downloads\\Movie Hall Ticket Booking Assignment\\BookedShowsDetails";
        

    //take user choice
    char ch = getChoice();
    if(ch=='1'){
        // Display the contents of the folder
        displayDirectoryContents(folderPath_1);

        //to open counter to book tickets for a show
        string fileName = getFile("Enter Movie Show CSV file that contains customer details in queue: ",folderPath_1);
        string filePath = folderPath_1+"/"+fileName;
        //creating object of showBooking 
        showBooking show(filePath);
    
        /*creating queue of customers coming to book tickets at counter
          counterQueue(name,n,pref1,pref2)*/
        counterQueue Q("NULL",0,"NULL","NULL");

        //adding data from csv to counter Queue
        show.customerComing(Q);

        //displaying counter Queue
        Q.display();
        this_thread::sleep_for(chrono::milliseconds(1000));
        int n = Q.size(); //no of customers at queue

        //Booking of a show get started
        //ticketBooking(no of customers, Queue at counter)
        show.ticketBooking(n,Q);
        this_thread::sleep_for(chrono::milliseconds(1000));

        //displaying booked customers details
        show.displayFinalList();
        this_thread::sleep_for(chrono::milliseconds(1000));
        //save the final list into a CSV file
        show.bookedTicketCSV(folderPath_2+"/booked-"+fileName);
        this_thread::sleep_for(chrono::milliseconds(1000));
        //sorting the data of booked customers acc to their booking ID
        show.sort();
        cout<<"***********************************************************\n";
        cout<<"                        After Sorting                      \n";
        cout<<"***********************************************************\n";
        show.displayFinalList();
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout<<"***********************************************************\n";
        cout<<"                       Counter Closed                      \n";
        cout<<"***********************************************************\n";

    }
    else{
        // Display the contents of the folder
        displayDirectoryContents(folderPath_2);

        //to get CSV file of booked tickets for a show
        string fileName = getFile("Enter CSV file that contains booked customer details: ",folderPath_2);
        string filePath = folderPath_2+"/"+fileName;
        //creating object of customerChecker class
        customerChecker bookedShow(filePath);

        //createing customerBookedStruct array
        bookedShow.bookedCustomers();
        this_thread::sleep_for(chrono::milliseconds(1000));
        //showing complete list to user
        bookedShow.displayFinalList();
        this_thread::sleep_for(chrono::milliseconds(1000));
        //sort the table with respect to customer name
        bookedShow.sort(1);
        while(true){
            char ch;
            cout<<"Want to check any customer details (Y/N) : ";
            cin>>ch;
            cout<<endl;
            if(ch=='y'||ch=='Y'){
                string name,fName,lName="";
                cout<<"Enter Name of customer to get details";
                cout<<"\nFirst Name : ";
                cin>>fName;
                this_thread::sleep_for(chrono::milliseconds(500));
                cout<<"Last Name(Enter .(dot) If not) : ";
                cin>>lName;
                this_thread::sleep_for(chrono::milliseconds(500));
                if(lName=="."){
                    name=fName;
                }
                else{
                    name=fName+" "+lName;
                }
                bookedShow.getDetails(name);
            }
            else{
                this_thread::sleep_for(chrono::milliseconds(2000));
                //sorted back the table again to Booking Id wise
                cout<<"***********************************************************\n";
                cout<<"                          GoodBye                          \n";
                cout<<"***********************************************************\n";
                break;
            }
        }
    }
}