#ifndef SORT_H
#define SORT_H
#include<bits/stdc++.h>
#include"customerBookedStruct.h"
class Sorting{
    public:
        bookedCustomer* c_table;
        int c_start;
        int c_end;
        int c_type;
        Sorting(bookedCustomer o_table[],int o_start, int o_end , int o_type=0){
            //if type = 0, then sort booking Id wise
            //else sort Name wise
            c_table = o_table;
            c_start = o_start;
            c_end = o_end;
            c_type = o_type;
            sort(c_table,c_start,c_end,c_type);
        }
        void sort(bookedCustomer table[],int start, int end , int type){
        //quick sort to sort final list of booked customer according to 
            if(start<end){
                int pivot_index;
                if(type==0){
                //their booking id
                    pivot_index = partition1(table,start,end);
                }
                else{
                //their name
                    pivot_index = partition2(table,start,end);
                }
                sort(table,start,pivot_index-1,type);
                sort(table,pivot_index+1,end,type);
            }
        }   
    private:
        int partition1(bookedCustomer table[], int start, int end){
            bookedCustomer pivot_ele = table[end];
            int i = start-1;
            for(int j=start; j<end; j++){
               if(table[j].B_ID<pivot_ele.B_ID){
                    i++;
                    swap(table[j],table[i]);
                }
            }
            swap(table[i+1],table[end]);
            return i+1;
        }
        int partition2(bookedCustomer table[], int start, int end){
            bookedCustomer pivot_ele = table[end];
            int i = start-1;
            for(int j=start; j<end; j++){
               if(table[j].Name<pivot_ele.Name){
                    i++;
                    swap(table[j],table[i]);
                }
            }
            swap(table[i+1],table[end]);
            return i+1;
        }
};
#endif