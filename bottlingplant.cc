#include "bottlingplant.h"
#include "truck.h"

void BottlingPlant::main() {
	for(;;) {
		_Accept(~BottlingPlant) {
			this->mPlantClosingDown = true;
			break;
		} or _Accept(getShipment) {

		}
	}
}

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments )
: mPrinter(prt), mNameServer(nameServer), mNumVendingMachines(numVendingMachines), 
mMaxShippedPerFlavour(maxShippedPerFlavour), mMaxStockPerFlavour(maxStockPerFlavour), 
mTimeBetweenShipments(timeBetweenShipments), mPlantClosingDown(false), 
truck(new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour)) {
	for (unsigned int i = 0; i < 4; ++i) {
		this->mCurrentProdRun[i] = 0;
	}
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {

}

BottlingPlant::~BottlingPlant() {
	delete truck;
}