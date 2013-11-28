#include "truck.h"

void Truck::main() {

}

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
	unsigned int numVendingMachines, unsigned int maxStockPerFlavour)
	: prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {}