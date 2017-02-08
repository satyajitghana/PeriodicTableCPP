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

void welcome();

void clearscr() {
    system("clear");
}

void errf() {
    cout<<"\nCouldnt Open the file. Exiting Now in 3 Seconds ..."; usleep(3000000); exit(2);
}

void ptread() {
    clearscr();
    ifstream ptable; element tmp;
    char ch;
    cout<<"\n-------------------PERIODIC TABLE-------------------\n";
    cout<<"\n1. View Element Details.";
    cout<<"\n2. View Elements of Specific Block.";
    cout<<"\n3. Search Elements with Range of Mass.";
    cout<<"\n4. Exit";
    cout<<"\n\nEnter your choice : ";
    cin>>ch;
    switch (ch) {
        case '1' :
            int a_no;
            cout<<"\nEnter the Atomic Number to Search for : "; cin>>a_no;
            ptable.open("ptdata.dat",ios::in|ios::binary|ios::beg);
            //ptable.seekg(--a_no*sizeof(element),ios::beg); -- didn't work if the there are missing elements
            while (ptable) {
                ptable.read((char*)&tmp,sizeof(tmp));
                if (tmp.geta_no()==a_no) {tmp.getdata(); break;}
                else if (ptable.eof()) {cout<<"\nElement not Found !"; usleep(2000000); ptread(); }
            } break;
        case '2' : cout<<"\nEnter the block whose Elements you want to see : ";
            char s; cin>>s;
            ptable.open("ptdata.dat",ios::in|ios::binary|ios::beg);
            while (ptable) {
                ptable.read((char*)&tmp,sizeof(tmp));
                if (tmp.get_s()==s) {if (ptable.eof()) break; else tmp.getdata();}
                else if (ptable.eof()) {cout<<"\nFinished."; break;}
            }  break;
        case '3' : {cout<<"\nEnter Lower Limit for the mass : ";
            int l,u;
            cin>>l;
                    cout<<"Enter Upper Limit for the mass : ";
            cin>>u;
            ptable.open("ptdata.dat",ios::in|ios::binary|ios::beg);
            while (ptable) {
                ptable.read((char*)&tmp,sizeof(tmp));
                cout<<tmp.get_mass();
                if (tmp.get_mass()>l && tmp.get_mass()<u) {if (ptable.eof()) break; else tmp.getdata();}
                else if (ptable.eof()) {cout<<"\nFinished."; break;}
            }}break;
        case '4' : exit(0); break;
        default : cout<<"\nWrong choice, Try again."; usleep(3000000); ptread();
    }
    char c; cout<<"\nGo to Periodic Table Menu ? "; cin>>c; if(c=='y' || c=='Y') ptread(); else welcome();
}

void putdata() {
    clearscr();
    fstream ptable;
    char ch;
    cout<<"\n--------------DATA MODIFICATION MODULE---------------\n";
    element tmp;
    cout<<"\n1. Add Data.";
    cout<<"\n2. Modify Data.";
    cout<<"\n3. Exit";
    cout<<"\n\nEnter your choice : ";
    cin>>ch;
    switch(ch) {
        case '1' : ptable.open("ptdata.dat",ios::in|ios::out|ios::binary|ios::app);
                   tmp.update();
                   ptable.write((char*)&tmp,sizeof(element));
                   ptable.close(); break;
        case '2' : {int no; element e; long pos=NULL; cout<<"\nEnter the atomic number of the element to modify : "; cin>>no;
            ptable.open("ptdata.dat",ios::in|ios::out|ios::binary|ios::beg);
            while (ptable) {
                pos=ptable.tellg();
                ptable.read((char*)&e,sizeof(e));
                if (ptable.eof()) break;
                else if (e.geta_no()==no) {
                    cout<<"\nCurrent Data\n"; e.getdata();
                    cout<<"\n\nEnter New Data for the Element ";
                    e.update();
                    ptable.seekp(pos,ios::beg);
                    ptable.write((char*)&e,sizeof(e));
                    cout<<"\nData is now modified !";
                }
                else if (ptable.eof()) {cout<<"\nElement not Found !"; usleep(4000000); putdata(); }
            }

            
            ptable.close(); break;}
        case '3' : exit(0); break;
        default: cout<<"\nWrong Choice !"; usleep(3000000); putdata();
    }
        
    

}

void maintain() {
    system("clear");
    char ch;
    cout<<"\n--------------------DATA MAINTENANCE------------------\n";
    cout<<"\n1. Sort Data with Atomic Number ";
    cout<<"\n2. Exit";
    cout<<"\n\nEnter your choice : ";
    cin>>ch;
    switch(ch) {
        case '1' : {cout<<"\nSorting your data with Bubble Sort (Ascending Order) ";
            element e1,e2; long pos; int n=0;;
            ifstream noe("ptable.dat",ios::in|ios::binary|ios::beg);
            while(noe.read((char*)&e1,sizeof(e1))) {n++;};
            fstream ptdata("ptdata.dat",ios::in|ios::out|ios::binary|ios::beg);
            for (int i=0;i<--n;i++)
            while(ptdata) {
                pos=ptdata.tellg();
                ptdata.read((char*)&e1,sizeof(e1));
                ptdata.read((char*)&e2,sizeof(e2));
                if (e1.geta_no()>e2.geta_no()) {
                    ptdata.seekp(pos,ios::beg);
                    ptdata.write((char*)&e2,sizeof(e2));
                    ptdata.write((char*)&e1,sizeof(e1));
                }
            }
            ptdata.close(); cout<<"\nYour Data should be sorted now . "; usleep(3000000); welcome();}
        case '2': exit(0);
        default: cout<<"\nWrong Choice ! "; usleep(3000000); maintain();
    }
}

void readme() {
    cout<<"\n-------------------------README-----------------------\n";
    cout<<"\nThis is a very small and simple program of the Periodic Table.\n"
    <<"Make sure you have the file in place along with this program file\n"
    <<"else this wont work.\n"
    <<"\n1. If you add any data to the file. Make sure you do the data maintenance.\n"
    <<"2. Some of the data for elements might be missing."
    <<"\n3. That is all . Have a Good Day !";
    cout<<"\n\nGo to Main Menu ? : "; char ch; cin>>ch; if(ch!='Y' || ch!='y') exit(0); else welcome();
}

void welcome() {
    clearscr();
    char ch;
    cout<<"\n------------------------WELCOME-----------------------\n";
    cout<<"\nMAIN MENU\n";
    cout<<"\n1. Enter the Periodic Table.";
    cout<<"\n2. Modify Periodic Table Data.";
    cout<<"\n3. Data Maintenance ";
    cout<<"\n4. ReadME before using this program.";
    cout<<"\n\nEnter your choice : ";
    cin>>ch;
    switch(ch) {
        case '1' : ptread(); break;
        case '2' : putdata(); break;
        case '3' : maintain(); break;
        case '4' : readme(); break;
        default : cout<<"  Wrong Choice "; usleep(3000000); welcome();
    }
}

int main(int argc, const char * argv[]) {
    welcome();
    return 0;
}
