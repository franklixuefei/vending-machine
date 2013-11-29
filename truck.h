#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "nameserver.h"
#include "bottlingplant.h"
#include "vendingmachine.h"
#include "global.h"

_Task Truck {
    void main();
    void _clearCargoArray();
    unsigned int _calcTotalCargoNum();
    unsigned int mCargo[4];
    Printer &mPrinter;
    NameServer &mNameServer;
    BottlingPlant &mPlant;
    unsigned int mNumVendingMachines;
    unsigned int mMaxStockPerFlavour;
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
};

#endif /* __TRUCK_H__ */