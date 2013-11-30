#include "vendingmachine.h"

void VendingMachine::main() {
    this->mPrt.print(Printer::Vending, this->mId, 'S', this->mSodaCost);
}

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour )
    : mPrt(prt), mNameServer(nameServer), mId(id), mSodaCost(sodaCost), mMaxStockPerFlavour(maxStockPerFlavour), mRestocking(false) {
        this->mNameServer.VMregister(this);
        for (unsigned int i = 0; i < 4; ++i) {
            this->mSodaStock[i] = 0;
        }
    }

VendingMachine::~VendingMachine() {

}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {

}

unsigned int * VendingMachine::inventory() {

}

void VendingMachine::restocked() {

}

unsigned int VendingMachine::cost() {
    return this->mSodaCost;
}

unsigned int VendingMachine::getId() {
    return this->mId;
}