#ifndef SHOWER_H
#define SHOWER_H
#include <iostream>
#include <cstdio>
#include <dirent.h>
#include "customerQueue.h"
#include "stallStack.h"
#include "sort.h"
using namespace std;
class customerChecker{
    public:
        int n;
        bookedCustomer table[100];
        string fileName;
        customerChecker(string file){
            n = 0;
            fileName = file;
        }
        //function to take customer data from csv file and create a queue of customers
        void bookedCustomers(){
            ifstream fin(fileName);
            if(!fin.is_open()){
                cout<<"Error opening file: "<<fileName<<endl;
                return;
            }
            string line;
            while (getline(fin,line)){
                stringstream s(line);
                string word;
                getline(s, word, ',');  // Assuming the first field is a string
                table[n].B_ID = word;
                getline(s, word, ',');
                table[n].Name = word;  // Assuming the second field is an integer
                getline(s, word, ',');
                table[n].no_of_tickets = stoi(word);  // Assuming the third field is a string
                int i=0;
                while(i<6 && getline(s, word, ',')){
                    table[n].seat_no[i]=stoi(word);
                    i++;
                }
                n++;
            }
        }
        void displayFinalList(){
            //final list of customers whose tickets get booked
            cout<<"\n***********************************************************\n";
            cout<<"                         Final List                        \n";
            cout<<"===========================================================\n";
            cout<<"Booking ID          Name                Seats        \n";
            cout<<"===========================================================\n";
            this_thread::sleep_for(chrono::milliseconds(500));
            for(int j = 0 ; j<n+1;j++){
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
        void getDetails(string name){
            /*Function to print all details of searched names*/
            int start = getFirstDetail(table,name);
            int end = getLastDetail(table,name);
            if(start==-1){
                cout<<"User Not Found\n";
            }
            else{
                cout<<"===========================================================\n";
                cout<<"Booking ID          Name                Seats        \n";
                cout<<"===========================================================\n";
                for(int m=start; m<=end; m++){
                    cout<<table[m].B_ID;
                    space(table[m].B_ID.length());
                    cout<<table[m].Name;
                    space(table[m].Name.length());
                    cout<<"|";
                    for(int x=0;x<table[m].no_of_tickets;x++){
                        cout<<table[m].seat_no[x]<<"|";
                    }
                    cout<<endl; 
                }
                cout<<"===========================================================\n";
            }
        }
        void sort(int type = 0){
            Sorting s(table,0,n,type); 
        }
    private:
        void space(int size){
            for(int k=0;k<20-size;k++){
                cout<<" ";
            }
        }
        int getFirstDetail(bookedCustomer table[100],string name){
            /*Function to get the index of first occurence of the name*/
            int start = 0;
            int end = n;
            int mid,ans = -1;
            while(start<=end){
                mid = start + (end-start)/2;
                if(table[mid].Name.find(name)!=-1){
                    ans = mid;
                    end = mid-1;
                }
                else if(table[mid].Name<name){
                    start = mid+1;
                }
                else{
                    end = mid-1;
                }
            }
            return ans;
        }
        int getLastDetail(bookedCustomer table[100],string name){
            /*Function to get the index of last occurence of the name*/
            int start = 0;
            int end = n;
            int mid,ans = -1;
            while(start<=end){
                mid = start + (end-start)/2;
                if(table[mid].Name.find(name)!=-1){
                    ans = mid;
                    start = mid+1;
                }
                else if(table[mid].Name<name){
                    start = mid+1;
                }
                else{
                    end = mid-1;
                }
            }
            return ans;
        }
};
#endif