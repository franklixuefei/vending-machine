#include "vendingmachine.h"

/***************** vendingmachine::main ****************
 Purpose:   since vending machine is a Task it has to have a main
 return:  void
 ******************************************************/
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
            } // _Accept
        } // _Accept
    } // for
} // VendingMachine::main



/***************** VendingMachine::VendingMachine ****************
 Purpose:   constructor 
 ****************************************************************/
VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                               unsigned int maxStockPerFlavour )
: mPrt(prt), 
mNameServer(nameServer), 
mId(id), 
mSodaCost(sodaCost), 
mMaxStockPerFlavour(maxStockPerFlavour),
mStocksLevel(new unsigned int[4]) {
    for (unsigned int i = 0; i < 4; ++i) {
        mStocksLevel[i] = 0;
    } // for
} // VendingMachine::VendingMachine


/***************** VendingMachine::~VendingMachine ****************
 Purpose:   destructor
 ******************************************************/
VendingMachine::~VendingMachine() {
    mPrt.print(Printer::Vending, mId, 'F' );
    delete[] mStocksLevel;
} // VendingMachine::~VendingMachine


/*****************  vendingmachine::buy ****************
 Purpose:   student buys soda from 
 return:  the status of the purchase (vendingmachine::Status)
 ******************************************************/

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
    if( mStocksLevel[ flavour ] <= 0 ) {
        return STOCK;
    }else if( card.getBalance() < mSodaCost ) {
        return FUNDS;
    } // if
    card.withdraw( mSodaCost );
    mStocksLevel[ flavour ] -= 1;
    mPrt.print( Printer::Vending, mId, 'B', flavour, mStocksLevel[ flavour ] );
    return BUY;
} // VendingMachine::buy


/***************** VendingMachine::inventory ****************
 Purpose:   request the inventory of the current vending machine
 return:   the inventory (unsigned int*)
 ******************************************************/
unsigned int * VendingMachine::inventory() {
    return mStocksLevel;
} // VendingMachine::inventory

/***************** vendingmachine::restocked ****************
 Purpose:   tell vending it has been restocked
 return:  void
 ******************************************************/
void VendingMachine::restocked() {
} // VendingMachine::restocked


/***************** vendingmachine::cost ****************
 Purpose:   get the price of soda in vending machine
 return:  the price (unsigned int)
 ******************************************************/
_Nomutex unsigned int VendingMachine::cost() {
    return mSodaCost;
} // VendingMachine::cost

/***************** VendingMachine::getId ****************
 Purpose:   get the id of current vending machine
 return:  the vending machine id (unsigned int)
 ******************************************************/
_Nomutex unsigned int VendingMachine::getId() {
    return mId;
} // VendingMachine::getId
