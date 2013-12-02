//
//  main.cpp
//  343a6
//
//  Created by Frank Li on 12/2/2013.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "MPRNG.h"
using namespace std;

MPRNG prng;

void uMain::main()
{
    prng.seed(getpid());

    // insert code here...
    cout << "SodaCost\t\t\t" << prng(2,20) << endl;
    cout << "NumStudents\t\t"   <<   prng(1,30) << endl;
    cout << "MaxPurchases\t\t"    <<   prng(1,30) << endl;
    cout << "NumVendingMachines\t"  <<  prng(1,30) << endl;
    cout << "MaxStockPerFlavour\t"  <<   prng(1,10) << endl;
    cout << "MaxShippedPerFlavour\t" << prng(1,10) << endl;
    cout << "TimeBetweenShipments\t" << prng(1,30) << endl;
    cout << "ParentalDelay\t\t"    <<    prng(1,10) << endl;
    cout << "NumCouriers\t\t"    <<    prng(1,20) << endl;
    

}

