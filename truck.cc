#include "truck.h"

/******************* Truck::main **********************
  Purpose:  
  	- The truck moves soda from the bottling plant to the vending machines.

	• obtain the location of each vending machine from the name server
	• start message
	• loop
		– clear up overdue products
		– yield a random number of times [1, 10]
		– if the bottling plant is closing down, the truck terminates
		– picked up shipment message
		– The vending machines are restocked in the order given by the name server, 
			until there is no more soda on the truck or the truck has made a complete 
			cycle of all the vending machines.
		– The truck can only restock up to MaxStockPerFlavour for each flavour in each vending machine.
	• finished message
 
 Returns:   void
 ******************************************************/
void Truck::main() {
	VendingMachine** machineList = this->mNameServer.getMachineList();
	mPrinter.print(Printer::Truck, 'S');
	for (;;) {
		this->_clearCargoArray();
		yield(RANDOM(1,10));
		if (mPlant.getShipment(mCargo)) {
			break;
		} // if
		mPrinter.print(Printer::Truck, 'P', this->_calcTotalCargoNum());
		for (unsigned int i = 0; i < mNumVendingMachines; ++i) {
			unsigned int unfilled = 0;
			unsigned int cargoNum = this->_calcTotalCargoNum();
			if (!cargoNum) {
				break;
			} // if
			VendingMachine *machine = machineList[i];
			mPrinter.print(Printer::Truck, 'd', (int)i, (int)cargoNum);
			unsigned int * machineInventory = machine->inventory();
			for (unsigned int j = 0; j < 4; ++j) {
				unsigned int difference = min(this->mMaxStockPerFlavour - machineInventory[j], this->mCargo[j]);
				machineInventory[j] += difference;
				this->mCargo[j] -= difference;
				assert(this->mCargo[j] >= 0);
				unfilled += this->mMaxStockPerFlavour - machineInventory[j];
			} // for
			if (unfilled) {
				mPrinter.print(Printer::Truck, 'U', (int)i, (int)unfilled);
			} // if
			machine->restocked();
			mPrinter.print(Printer::Truck, 'D', (int)i, (int)this->_calcTotalCargoNum());
		} // for
	} // for
	mPrinter.print(Printer::Truck, 'F');
} // Truck::main


/******************* Truck::_clearCargoArray **********************
 Purpose:   clear up the overdue products
 ******************************************************************/
void Truck::_clearCargoArray() {
	for (unsigned int i = 0; i < 4; ++i) {
		this->mCargo[i] = 0;
	} // for
} // Truck::_clearCargoArray


/*************** Truck::_calcTotalCargoNum ******************
 Purpose:   calculate the total number of products in a
 			production run.
 Return:	unsigned int
 ************************************************************/
unsigned int Truck::_calcTotalCargoNum() {
	unsigned int tot = 0;
	for (unsigned int i = 0; i < 4; ++i) {
		tot += this->mCargo[i];
	} // for
	return tot;
} // Truck::_calcTotalCargoNum


/******************* Truck::Truck **********************
 Purpose:   The constructor of Task Truck
 ******************************************************/
Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
	unsigned int numVendingMachines, unsigned int maxStockPerFlavour)
	: mPrinter(prt), mNameServer(nameServer), mPlant(plant),
	 mNumVendingMachines(numVendingMachines), mMaxStockPerFlavour(maxStockPerFlavour) {}


/******************* Truck::~Truck **********************
 Purpose:   The destructor of Task Truck
 ******************************************************/
Truck::~Truck() {}	 