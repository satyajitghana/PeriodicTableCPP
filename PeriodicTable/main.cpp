//
//  main.cpp
//  PeriodicTable
//
//  Created by Satyajit Ghana on 07/02/17.
//  Copyright © 2017 Satyajit Ghana. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <ncurses.h>
#include "ptable_access.h"

using namespace std;

void clearscr() {
    system("clear");
}

void ptread() {
    clearscr();
    cout<<"\n-------------------PERIODIC TABLE-------------------\n";
    int a_no;
    element tmp;
    cout<<"\nEnter the Atomic Number to Search for : "; cin>>a_no;
    ifstream ptable("ptdata.dat",ios::in|ios::binary);
    ptable.seekg(--a_no*sizeof(element),ios::beg);
    ptable.read((char*)&tmp,sizeof(element));
    tmp.getdata();
    
}

void putdata() {
    fstream ptable;
    char ch;
    cout<<"\n--------------DATA MODIFICATION MODULE---------------\n";
    element tmp;
    cout<<"\n1. Add Data.";
    cout<<"\n2. Modify Data.";
    cout<<"\n\nEnter your choice : ";
    cin>>ch;
    switch(ch) {
        case '1' : ptable.open("ptdata.dat",ios::in|ios::out|ios::binary|ios::app);
            tmp.update(); ptable.write((char*)&tmp,sizeof(element)); ptable.close(); break;
        case '2' :;
    }
        
    

}

void maintain() {
    system("clear");
    char ch;
    cout<<"\n--------------------DATA MAINTENANCE------------------\n";
    cout<<"\n1. Sort Data with Atomic Number ";
    cout<<"\n\nEnter your choice : ";
    cin>>ch;
    switch(ch) {
        case '1' : cout<<"\nSorting your data with Bubble Sort ";
            element e;
            fstream ptdata("ptdata.dat",ios::in|ios::out|ios::binary);
            while(!ptdata.eof()) {
                ptdata.read((char*)&e,sizeof(e));
            }
    }
}

void welcome() {
    char ch;
    cout<<"\n------------------------WELCOME-----------------------\n";
    cout<<"\nMAIN MENU\n";
    cout<<"\n1. Enter the Periodic Table.";
    cout<<"\n2. Modify Periodic Table Data.";
    cout<<"\n3. Data Maintenance ";
    cout<<"\n\nEnter your choice : ";
    cin>>ch;
    switch(ch) {
        case '1' : ptread(); break;
        case '2' : putdata(); break;
        case '3' : maintain(); break;
        default : cout<<"  Wrong Choice "; usleep(3000000);
    }
}

int main(int argc, const char * argv[]) {
    welcome();
    return 0;
}
