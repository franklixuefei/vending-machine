#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "printer.h"
#include "nameserver.h"


_Task BottlingPlant {
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif /* __BOTTLINGPLANT_H__ */