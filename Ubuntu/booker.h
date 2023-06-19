#ifndef BOOKER_H
#define BOOKER_H
#include <iostream>
#include <cstdio>
#include "customerQueue.h"
#include "stallStack.h"
#include "sort.h"
class showBooking{
    public:
        //Number of customers booked for the show
        int s_no = 0; 

        //creating stack of tickets for all stalls
        stall front = stall(1,30);
        stall middle = stall(31,70);
        stall balcony = stall(71,100);

        //csv file containing data
        string fileName;

        //array of customers whose ticket get booked
        bookedCustomer table[100];
        
        //constructor of class showBooking
        showBooking(string file){
            fileName = file; //initialising file name
        }

        void customerComing(counterQueue Q){
        //function to take customer data from csv file and create a queue of customers
            ifstream fin(fileName);
            if (!fin.is_open()){
                cout <<"Error opening file: "<<fileName<<endl;
                return;
            }
            string line;
            string arr[4];
            string word;
            while(getline(fin,line)){
                stringstream s(line);
                int i=0;
                while(i<4 && getline(s,word,',')){
                    arr[i]=word;
                    i++;
                }
                Q.enqueue(arr[0],stoi(arr[1]),arr[2],arr[3]);
            }
        }

        void ticketBooking(int n,counterQueue Q){
            //function to book the ticket for customer
            this_thread::sleep_for(chrono::milliseconds(1000));
            cout<<"****************************************************************************\n";
            cout<<"                            Ticket Booking Open                             \n";
            cout<<"****************************************************************************\n";
            this_thread::sleep_for(chrono::milliseconds(1000));
            customer d;
            for(int j=0; j<n+1; j++){
                d = Q.dequeue(); //customer will get dequeue from queue
                if(d.name=="NULL"){
                    continue;
                }
                else{
                    cout<<"=============================================================================\n";
                    cout<<"                                 Next Customer                               \n";
                    cout<<"=============================================================================\n";
                    //ticket counter function will check if ticket is available
                    int status = ticketCounter(d.ticketNo,d.pref1,d.pref2); 
                    if (status==-1){
                        cout<<"Ticket Not Availavle as per customer preference for customer : "<<d.name<<endl;
                        s_no++;
                    }
                    else{
                        //if ticket available
                        table[j].B_ID = bookID(d);
                        table[j].Name = d.name;
                        table[j].no_of_tickets = d.ticketNo;
                        if(status==1){
                            for(int k=0;k<d.ticketNo;k++){
                                table[j].seat_no[k]=front.pop();
                            }
                        }
                        else if(status==2){
                            for(int k=0;k<d.ticketNo;k++){
                                table[j].seat_no[k]=middle.pop();
                            }
                        }
                        else if(status==3){
                            for(int k=0;k<d.ticketNo;k++){
                                table[j].seat_no[k]=balcony.pop();
                            }
                        }
                        cout<<table[j].no_of_tickets<<" Ticket Booked for customer "<<table[j].Name
                        <<" with Booking ID "<<table[j].B_ID<<endl;
                    }
                }
                this_thread::sleep_for(chrono::milliseconds(1000));
                //printing number of left tickets in each stalls
                cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
                cout<<"seat left: "<<endl;
                cout<<"front : "<<front.size<<endl;
                cout<<"middle : "<<middle.size<<endl;
                cout<<"balcony : "<<balcony.size<<endl;
                cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
            cout<<"----------------------------------------------------------------------------\n";
            cout<<"                               Booking Closed                               \n";
            cout<<"----------------------------------------------------------------------------\n";
        }
        void displayFinalList(){
            //final list of customers whose tickets get booked
            cout<<"\n***********************************************************\n";
            cout<<"                         Final List                        \n";
            cout<<"===========================================================\n";
            cout<<"Booking ID          Name                Seats        \n";
            cout<<"===========================================================\n";
            this_thread::sleep_for(chrono::milliseconds(500));
            for(int j = 0 ; j<s_no+1;j++){
                if(table[j].B_ID=="NULL"){
                    continue;
                }
                else{
                    cout<<table[j].B_ID;
                    space(table[j].B_ID.length());
                    cout<<table[j].Name;
                    space(table[j].Name.length());
                    cout<<"|";
                    for(int x=0;x<table[j].no_of_tickets;x++){
                        cout<<table[j].seat_no[x]<<"|";
                    }
                    cout<<endl;
                    this_thread::sleep_for(chrono::milliseconds(500));
                }
            }
            cout<<"===========================================================\n";
        }
        void sort(int type = 0){
            Sorting s(table,0,s_no,type); 
        }
        void bookedTicketCSV(string outFilePath){
            ofstream fout;
            fout.open(outFilePath);
            if(!fout.is_open()){
                cout<< "Error opening file: "<<outFilePath <<endl;
                return;
            }
            for(int i=0; i<=s_no; i++){
                if(table[i].B_ID=="NULL"){
                    continue;
                }
                else{
                    fout<<table[i].B_ID<<","<<table[i].Name<<","<<table[i].no_of_tickets<<",";
                    for(int j=0; j<table[i].no_of_tickets;j++){
                        fout<<table[i].seat_no[j];
                        if(j<table[i].no_of_tickets-1){
                            fout<<",";
                        }
                    }
                    if(i!=s_no)
                        fout<<"\n";
                }
            }
            cout<<"Output File Created Succesfully at path : \n"<<outFilePath<<endl;
            fout.close();
        }
    private:
        int ticketCounter(int n,string p1,string p2="No"){
        /*ticket counter function to check if ticket is availavle for any
        customer, according to customer's first and second preference.*/
            if(p1=="Front"){
                if(front.size>n){
                    return 1;
                }
                else{
                    if(p2=="Middle"){
                        if(middle.size>n){
                            return 2;
                        }
                    }
                    else if(p2=="Balcony"){
                        if(balcony.size>n){
                            return 3;
                        }
                    }
                    else{
                        return -1;
                    }
                }
            }
            else if(p1=="Middle"){
                if(middle.size>n){
                    return 2;
                }
                else{
                    if(p2=="Front"){
                        if(front.size>n){
                            return 1;
                        }
                    }
                    else if(p2=="Balcony"){
                        if(balcony.size>n){
                            return 3;
                        }
                    }
                    else{
                        return -1;
                    }
                }
            }
            else if(p1=="Balcony"){
                if(balcony.size>n){
                    return 3;
                }
                else{
                    if(p2=="Middle"){
                        if(middle.size>n){
                            return 2;
                        }
                    }
                    else if(p2=="Front"){
                        if(front.size>n){
                            return 1;
                        }
                    }
                    else{
                        return -1;
                    }
                }
            }
            return -1;
        }
        string bookID(customer d){
            //function to genrate booking id for booked tickets
            s_no++;
            if(s_no<10){
                string id = d.name[0]+to_string(d.ticketNo)+"MYSHOW0"+to_string(s_no);
                return id;
            }
            string id = d.name[0]+to_string(d.ticketNo)+"MYSHOW"+to_string(s_no);
            return id;
        }

        void space(int size){
            for(int k=0;k<20-size;k++){
                cout<<" ";
            }
        }
};
#endif