#include "bottlingplant.h"
#include "truck.h"



/************************************* BottlingPlant::main ************************************
 Purpose: 
 	- The bottling plant periodically produces random new quantities of each flavour of soda, 
 		[0, MaxShippedPerFlavour] per flavour.  

	• start message
	• loop
		- yield for TimeBetweenShipments times
		– randomly generate number of productions in range [0, MaxShippedPerFlavour]
		- generating soda message
		– accept destructor, in which the loop breaks
		– or accept getShipment, in which shipment pickup message is printed.
	• finished message
 
 Returns:   void
 **********************************************************************************************/
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
		} // _Accept
	} // for
	this->mPrinter.print(Printer::BottlingPlant, 'F'); 
} // BottlingPlant::main


/***************** BottlingPlant::_calcTotalProd ****************
 Purpose:   calculate the amount it should be produced
 return:  	the amount (unsigned int)
 ****************************************************************/
unsigned int BottlingPlant::_calcTotalProd() {
	unsigned int tot = 0;
	for (unsigned int i = 0; i < 4; ++i) {
		tot += this->mCurrentProdRun[i];
	} // for
	return tot;
} // BottlingPlant::_calcTotalProd

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
truck(new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour)), truckShouldDestroy(false) {
	for (unsigned int i = 0; i < 4; ++i) {
		this->mCurrentProdRun[i] = 0;
	} // for
} // BottlingPlant::BottlingPlant

/***************** BottlingPlant::~BottlingPlant ****************
 Purpose:   the destructor
 ******************************************************/
BottlingPlant::~BottlingPlant() {
	delete truck;
} // BottlingPlant::~BottlingPlant

/***************** BottlingPlant::getShipment ******************
 Purpose:   he truck calls getShipment to obtain a shipment from 
 			the plant (i.e., the production run), and the shipment 
 			is copied into the cargo array passed by the truck. 
 			getShipment returns true if the bottling plant is closing 
 			down and cargo is not changed, and false otherwise with 
 			the shipment copied into the cargo array passed by the truck.
 return:  statue of current truck cargo (bool)
 **************************************************************/
bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (this->mPlantClosingDown) {
		truckShouldDestroy = true;
		return true;
	} // if
	for (unsigned int i = 0; i < 4; ++i) {
		cargo[i] = this->mCurrentProdRun[i];
	} // for
	return false;
} // BottlingPlant::getShipment
