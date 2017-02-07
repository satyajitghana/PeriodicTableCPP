//
//  ptable_access.h
//  PeriodicTable
//
//  Created by Satyajit Ghana on 07/02/17.
//  Copyright © 2017 Satyajit Ghana. All rights reserved.
//

#ifndef ptable_access_h
#define ptable_access_h

using namespace std;

class element {
private:
    int a_no;
    string name;
    string symbol;
    float mass;
    string ec;
    int year;
    float en;
    char block;
public:
    void getdata() {
        cout<<"\nAtomic Number : "<<a_no
        <<"\nName : "<<name
        <<"\nSymbol : "<<symbol
        <<"\nMass : "<<mass
        <<"\nBlock : "<<block
        <<"\nElectronic Configuration : "<<ec
        <<"\nYear of Discovery : "<<year;
        
    }
    
    void update() {
        cout<<"\nEnter Atomic Number : "; cin>>a_no;
        cout<<"Enter Name : "; cin>>name;
        cout<<"Enter Symbol : "; cin>>symbol;
        cout<<"Enter Mass : "; cin>>mass;
        cout<<"Enter Block : "; cin>>block; cin.ignore();
        cout<<"Enter Electronic Configuration : "; getline(cin,ec);
        cout<<"Enter Year of Discovery : "; cin>>year;
    }
    
    int geta_no() {
        return this->a_no;
    }
};

#endif /* ptable_access_h */
