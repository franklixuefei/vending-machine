#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "nameserver.h"
#include "bottlingplant.h"

_Task Truck {
    void main() {

    }
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) {
    	
    }
};

#endif /* __TRUCK_H__ */