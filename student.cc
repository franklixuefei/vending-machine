#ifndef STUDENT_CC_CS343
#define STUDENT_CC_CS343 

#include "student.h"

void Student::main() {
	unsigned int numPurchases = RANDOM(1, maxPurchases);
	VendingMachine::Flavours flavour = RANDOM(3);
	WATCard::FWATCard fWATCard = cardOffice.create(this->id, 5);
	VendingMachine *vm = nameServer.getMachine(this->id);
	for (unsigned int i = 0; i < numPurchases; ++i) {
		RETRY_ANOTHER_MACHINE:
		yield(RANDOM(1,10));
		RETRY_GET_CARD:
		try {
			this->card = fWATCard();
		} catch(WATCardOffice::Lost e) {
			prt.print(Printer::Student, 'L');
			fWATCard = cardOffice.create(this->id, 5);
			goto RETRY_GET_CARD;
		}


		VendingMachine::Status status = vm->buy(flavour, *card);
		switch(status) {
			case VendingMachine::BUY:
				prt.print(Printer::Student, this->id, 'B', this->card->getBalance());
				break;
			case VendingMachine::STOCK: // unavailable for now
				vm = nameServer.getMachine(this->id);
				prt.print(Printer::Student, this->id, 'V', vm->getId());
				goto RETRY_ANOTHER_MACHINE;
			case VendingMachine::FUNDS: // insufficient fund for now
				fWATCard = cardOffice.transfer(this->id, vm->cost() + 5, this->card);
				goto RETRY_GET_CARD;
			default:
				// impossible.
				;
		}
	}
}

Student::Student( Printer &prt, NameServer &nameServer, 
	WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases )
		: prt(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases) {}

Student::~Student() {
	prt.print(Printer::Student, this->id, 'F');
	delete this->card;
}

#endif
