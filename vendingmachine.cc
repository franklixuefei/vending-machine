#include "vendingmachine.h"



/*
A vending machine's function is to sell soda to students at so me cost. 

Each vending machine is passed an id in the range [0, NumVendingMachines) for identification, MSRP price for a bottle of soda, 
and the maximum number of bottles of each flavor in a vending machine. A new vending machineis empty (nostock) and begins
by registering with the name server. 

A student calls buy to obtain one of their favorite sodas. If the specified soda is unavailable => STOCK
or 
the student has insufficient funds to purchase the soda, buy returns =>FUNDS 
otherwise, 
the student's WATCard is debited by the cost of a soda and buy returns BUY.


Periodically, the truck comes by to restock the vending machines with new soda from the bottling plant. Re-
stocking is performed in two steps. The truck calls inventory to return a pointer to an array containing the amount
of each kind of soda currently in the vending machine. 
The truck uses this information to transfer into each machine as much of its stock of new soda as fits; 
for each kind of so da, no more than MaxStockPerFlavour per flavor can be added to a machine. 
If the truck cannot top-up a particular flavour, it transfers as many bottles as it has (which could be 0). 
After transferring new soda into the machine by directly modifying the array passed
from inventory , the truck calls restocked to indicate the operation is complete. 


The vending machine cannot
accept buy calls during restocking. The cost member returns the cost of purchasing a soda for this machine . The
getIdmember returns the identification number of the vending machine. You define the public type Flavors to
represent the differentflavours of soda.
*/




void VendingMachine::main() {
    mPrt.print(Printer::Vending, mId, 'S', mSodaCost);
    mNameServer.VMregister(this);
    for( ;; ) {
    _Accept( ~VendingMachine ){
      break;
    } or _Accept( buy ) {
    } or _Accept( inventory ){
      mPrt.print( Printer::Vending, mId, 'r' );
      _Accept( restocked ){
        mPrt.print(Printer::Vending, mId, 'R' );
      }
    }
  }

}

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour )
    : mPrt(prt), 
    mNameServer(nameServer), 
    mId(id), 
    mSodaCost(sodaCost), 
    mMaxStockPerFlavour(maxStockPerFlavour),
    mStocksLevel(new unsigned int[4]) {
      for (unsigned int i = 0; i < 4; ++i) {
        mStocksLevel[i] = mMaxStockPerFlavour;
      }
}

VendingMachine::~VendingMachine() {
  mPrt.print(Printer::Vending, mId, 'F' );
  delete[] mStocksLevel;
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
  if( mStocksLevel[ flavour ] <= 0 ) {
    return STOCK;
  }else if( card.getBalance() < mSodaCost ) {
    return FUNDS;
  }
  card.withdraw( mSodaCost );
  mStocksLevel[ flavour ] -= 1;
  mPrt.print( Printer::Vending, mId, 'B', flavour, mStocksLevel[ flavour ] );
  return BUY;
}

unsigned int * VendingMachine::inventory() {
  return mStocksLevel;
}

void VendingMachine::restocked() {
}

_Nomutex unsigned int VendingMachine::cost() {
  return mSodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
  return mId;
}
