#include "truck.h"

void Truck::main() {
	VendingMachine** machineList = this->mNameServer.getMachineList();
	mPrinter.print(Printer::Truck, 'S');
	for (;;) {
		this->_clearCargoArray();
		yield(RANDOM(1,10));
		if (mPlant.getShipment(mCargo)) {
			break;
		}

		mPrinter.print(Printer::Truck, 'P', this->_calcTotalCargoNum());

		for (unsigned int i = 0; i < mNumVendingMachines; ++i) {
			unsigned int unfilled = 0;
			unsigned int cargoNum = this->_calcTotalCargoNum();
			if (!cargoNum) {
				break;
			}
			VendingMachine *machine = machineList[i];

			mPrinter.print(Printer::Truck, 'd', (int)i, (int)cargoNum);

			unsigned int * machineInventory = machine->inventory();
			for (unsigned int j = 0; j < 4; ++j) {
				unsigned int difference = min(this->mMaxStockPerFlavour - machineInventory[j], this->mCargo[j]);
				machineInventory[j] += difference;
				this->mCargo[j] -= difference;
				assert(this->mCargo[j] >= 0);
				unfilled += this->mMaxStockPerFlavour - machineInventory[j];
			}
			if (unfilled) {
				mPrinter.print(Printer::Truck, 'U', (int)i, (int)unfilled);
			}
			machine->restocked();
			mPrinter.print(Printer::Truck, 'D', (int)i, (int)this->_calcTotalCargoNum());
		}
	}
	mPrinter.print(Printer::Truck, 'F');
}

void Truck::_clearCargoArray() {
	for (unsigned int i = 0; i < 4; ++i) {
		this->mCargo[i] = 0;
	}
}

unsigned int Truck::_calcTotalCargoNum() {
	unsigned int tot = 0;
	for (unsigned int i = 0; i < 4; ++i) {
		tot += this->mCargo[i];
	}
	return tot;
}

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
	unsigned int numVendingMachines, unsigned int maxStockPerFlavour)
	: mPrinter(prt), mNameServer(nameServer), mPlant(plant),
	 mNumVendingMachines(numVendingMachines), mMaxStockPerFlavour(maxStockPerFlavour) {}

Truck::~Truck() {

}	 