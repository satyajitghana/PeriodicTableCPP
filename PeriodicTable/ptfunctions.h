//
//  ptfunctions.h
//  PeriodicTable
//
//  Created by Satyajit Ghana on 08/02/17.
//  Copyright © 2017 Satyajit Ghana. All rights reserved.
//

#ifndef ptfunctions_h
#define ptfunctions_h

#include "ptable_access.h"

void swap(long p1, long p2)
{
    fstream ptable("ptdata.dat",ios::in|ios::out|ios::binary);
    ptable.seekg(p1,ios::beg);
    
    ptable.close();
}
#endif /* ptfunctions_h */
