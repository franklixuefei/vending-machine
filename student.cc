#ifndef STUDENT_CC_CS343
#define STUDENT_CC_CS343 

#include "student.h"



void Student::main() {
	unsigned int numPurchases = RANDOM(1, mMaxPurchases);
	VendingMachine::Flavours flavour = static_cast<VendingMachine::Flavours>(RANDOM(3));
	this->mPrinter.print(Printer::Student, this->mId, 'S', flavour, mMaxPurchases);	
	WATCard::FWATCard fWATCard = mCardOffice.create(this->mId, 5);
	VendingMachine *vm = mNameServer.getMachine(this->mId);
	for (unsigned int i = 0; i < numPurchases; ++i) {
		RETRY_ANOTHER_MACHINE:
		yield(RANDOM(1,10));
		RETRY_GET_CARD:
		try {
			this->mCard = fWATCard();
		} catch(WATCardOffice::Lost e) {
			mPrinter.print(Printer::Student, 'L');
			fWATCard = mCardOffice.create(this->mId, 5);
			goto RETRY_GET_CARD;
		} // try-catch block


		VendingMachine::Status status = vm->buy(flavour, *mCard);
		switch(status) {
			case VendingMachine::BUY:
				mPrinter.print(Printer::Student, this->mId, 'B', this->mCard->getBalance());
				break;
			case VendingMachine::STOCK: // unavailable for now
				vm = mNameServer.getMachine(this->mId);
				mPrinter.print(Printer::Student, this->mId, 'V', vm->getId());
				goto RETRY_ANOTHER_MACHINE;
			case VendingMachine::FUNDS: // insufficient fund for now
				fWATCard = mCardOffice.transfer(this->mId, vm->cost() + 5, this->mCard);
				goto RETRY_GET_CARD;
			default:
				// impossible.
				;
		} // switch
	} // for
} // Student::main

Student::Student( Printer &prt, NameServer &nameServer, 
	WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases )
		: mPrinter(prt), mNameServer(nameServer), mCardOffice(cardOffice), mId(id), mMaxPurchases(maxPurchases) {}

Student::~Student() {
	mPrinter.print(Printer::Student, this->mId, 'F');
	delete this->mCard;
} // Student::~Student

#endif
