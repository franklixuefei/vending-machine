#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "global.h"
#include "nameserver.h"
#include "watcard.h"

_Task VendingMachine {
    void main();
    Printer & mPrt;
    NameServer & mNameServer;
    unsigned int mId;
    unsigned int mSodaCost;
    unsigned int mMaxStockPerFlavour;
    bool mRestocking;
    unsigned int mSodaStock[4];
  public:
    enum Flavours { ORANGE, APPLE, LEMON, GRAPE };  // flavours of soda
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif /* __VENDINGMACHINE_H__ */