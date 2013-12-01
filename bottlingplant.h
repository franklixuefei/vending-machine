#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "global.h"
#include "printer.h"
#include "nameserver.h"

_Task Truck;

_Task BottlingPlant {
    void main();
    Printer & mPrinter;
    NameServer & mNameServer;
    unsigned int mNumVendingMachines;
    unsigned int mMaxShippedPerFlavour;
    unsigned int mMaxStockPerFlavour;
    unsigned int mTimeBetweenShipments;
    bool mPlantClosingDown;
    unsigned int mCurrentProdRun[4];
    Truck *truck;
    unsigned int _calcTotalProd();
    bool truckShouldDestroy;
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
    ~BottlingPlant();
};

#endif /* __BOTTLINGPLANT_H__ */