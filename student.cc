#ifndef STUDENT_CC_CS343
#define STUDENT_CC_CS343 

#include "student.h"


/****************************** Student::main ******************************
  A student begins by 
  and  A student Before each attempt to buy a soda,  , and re-attempt to buy a soda but without yielding as no call to buy has occurred. Note, a courier can lose a student’s WATCard during the transfer for the new create so this issue can occur repeatedly.   (Hence, a student may busy wait among vending machines until its specific soda appears from the bottling plant.)

 Purpose:
 	- 	A Student’s function is to periodically buy some of their favourite soda 
 		from a vending machine (a bottle costs whatever the vending machine is 
 		charging).

	• select a random number of bottles to purchase [1, MaxPurchases] 
	• select a random favourite flavour [0, 3]
	• start message
	• create a WATCard via the WATCardOffice with a $5 balance
	• obtain the location of a vending machine from the name server.
	• loop
		- yield a random number of times in the range [1, 10].
		– the student may have to block until the amount transfered from the 
			WATCardOffice appears on their WATCard. If a courier has lost a 
			student’s WATCard during a transfer (see WATCardOffice::Courier), the 
			exception WATCardOffice::Lost is raised when the future value is 
			accessed. In this case, the student must create a new WATCard via the 
			WATCardOffice with a $5 balance.
		– buy a soda
		– If the vending machine delivers a bottle of soda, the student drinks it 
			and attempts another purchase. If the vending machine indicates 
			insufficient funds, a student transfers the current vending-machine 
			soda-cost plus $5 to their WATCard via the WATCard office.
		– If the vending machine is out of the student’s favourite flavour, the 
			student must obtain a new vending machine from the name server.
		– terminate after purchasing all the soda initially selected
	• finished message
 
 Returns:   void
 ****************************************************************************/
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
			this->mPrinter.print(Printer::Student, mId, 'L');
			fWATCard = mCardOffice.create(this->mId, 5);
			goto RETRY_GET_CARD;
		} // try-catch block


		VendingMachine::Status status = vm->buy(flavour, *mCard);
		switch(status) {
			case VendingMachine::BUY:
				this->mPrinter.print(Printer::Student, this->mId, 'B', this->mCard->getBalance());
				break;
			case VendingMachine::STOCK: // unavailable for now
				vm = mNameServer.getMachine(this->mId);
				this->mPrinter.print(Printer::Student, this->mId, 'V', vm->getId());
				goto RETRY_ANOTHER_MACHINE;
			case VendingMachine::FUNDS: // insufficient fund for now
				fWATCard = mCardOffice.transfer(this->mId, vm->cost() + 5, this->mCard);
				goto RETRY_GET_CARD;
			default:
				// impossible.
				;
		} // switch
	} // for
	this->mPrinter.print(Printer::Student, this->mId, 'F');
} // Student::main

/****************************** Student::Student ***************************
 Purpose:  The constructor of Task Student. 
****************************************************************************/
Student::Student( Printer &prt, NameServer &nameServer, 
	WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases )
		: mPrinter(prt), mNameServer(nameServer), mCardOffice(cardOffice), mId(id), mMaxPurchases(maxPurchases) {}

/************************** Student::~Student ******************************
 Purpose:  The destructor of Task Student. 
****************************************************************************/
Student::~Student() {
	delete this->mCard;
} // Student::~Student

#endif
