#include "vendingmachine.h"

void VendingMachine::main() {

}

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour )
    : mPrt(prt), mNameServer(nameServer), mId(id), mSodaCost(sodaCost), mMaxStockPerFlavour(maxStockPerFlavour) {}

VendingMachine::~VendingMachine() {

}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {

}

unsigned int * VendingMachine::inventory() {

}

void VendingMachine::restocked() {

}

unsigned int VendingMachine::cost() {

}

unsigned int VendingMachine::getId() {

}