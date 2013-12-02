#include "bottlingplant.h"
#include "truck.h"



/***************** BottlingPlant::main ****************
 Purpose:   since BottlingPlant is a task it has to have a main
 return:  void
 ******************************************************/
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
			break;
		} or _Accept(getShipment) {
			this->mPrinter.print(Printer::BottlingPlant, 'P');
		}
	}
}


/***************** BottlingPlant::_calcTotalProd ****************
 Purpose:   calculate the amount it should be produced
 return:  the amount (unsigned int)
 ******************************************************/
unsigned int BottlingPlant::_calcTotalProd() {
	unsigned int tot = 0;
	for (unsigned int i = 0; i < 4; ++i) {
		tot += this->mCurrentProdRun[i];
	}
	return tot;
}

/***************** BottlingPlant::BottlingPlant ****************
 Purpose:   the constructor
 ******************************************************/
BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments )
	: mPrinter(prt), 
	mNameServer(nameServer),
	mNumVendingMachines(numVendingMachines), 
	mMaxShippedPerFlavour(maxShippedPerFlavour), 
	mMaxStockPerFlavour(maxStockPerFlavour), 
	mTimeBetweenShipments(timeBetweenShipments), 
	mPlantClosingDown(false), 
	truck(new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour)), 
	truckShouldDestroy(false) {
		
		for (unsigned int i = 0; i < 4; ++i) {
			this->mCurrentProdRun[i] = 0;
		}
}

/***************** BottlingPlant::~BottlingPlant ****************
 Purpose:   the destructor
 ******************************************************/
BottlingPlant::~BottlingPlant() {
	delete truck;
	this->mPrinter.print(Printer::BottlingPlant, 'F'); 
}

/***************** BottlingPlant::getShipment ****************
 Purpose:   bottling plant load the truck for shipment
 return:  statue of current truck cargo
 ******************************************************/
bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (this->mPlantClosingDown) {
		truckShouldDestroy = true;
		return true;
	}
	for (unsigned int i = 0; i < 4; ++i) {
		cargo[i] = this->mCurrentProdRun[i];
	}
	return false;
}
