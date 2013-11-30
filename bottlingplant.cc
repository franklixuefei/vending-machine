#include "bottlingplant.h"
#include "truck.h"

void BottlingPlant::main() {
	this->mPrinter.print(Printer::BottlingPlant, 'S');
	for(;;) {
		yield(this->mTimeBetweenShipments);
		for (unsigned int i = 0; i < 4; ++i) {
			this->mCurrentProdRun[i] = RANDOM(this->mMaxShippedPerFlavour);
		}
		this->mPrinter.print(Printer::BottlingPlant, 'G', this->_calcTotalProd());
		_Accept(~BottlingPlant) {
			this->mPlantClosingDown = true;
			_Accept(getShipment); // propagate getShipment true.
			// maybe deadlock here????
			break;
		} or _Accept(getShipment) {
			this->mPrinter.print(Printer::BottlingPlant, 'P');
		}
	}
}

unsigned int BottlingPlant::_calcTotalProd() {
	unsigned int tot = 0;
	for (unsigned int i = 0; i < 4; ++i) {
		tot += this->mCurrentProdRun[i];
	}
	return tot;
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
	if (this->mCurrentProdRun) {
		return true;
	}
	for (unsigned int i = 0; i < 4; ++i) {
		cargo[i] = this->mCurrentProdRun[i];
	}
	return false;
}

BottlingPlant::~BottlingPlant() {
	delete truck;
}