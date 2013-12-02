#ifndef WATCARDOFFICE_CC_CS343
#define WATCARDOFFICE_CC_CS343 

#include "watcardoffice.h"
/***************** WATCardOffice::Courier::Courier ****************
 Purpose:   the constructor for Courier
 *******************************************************************/
WATCardOffice::Courier::Courier(WATCardOffice &office, Bank &bank, unsigned int id)
	: mOffice(office), mBank(bank), mId(id) {}

/***************** WATCardOffice::Courier::~Courier ****************
 Purpose:   the destructor for Courier
 *******************************************************************/
WATCardOffice::Courier::~Courier() {
	this->mOffice.mPrinter.print(Printer::Courier, this->mId, 'F');
} // Courier::~Courier


/***************** WATCardOffice::Courier::Courier ****************
 Purpose:   the execution body of Task Courier.
 			The WATCard office is empowered to transfer funds from a 
 			student’s bank-account to its WATCard by sending a request 
 			through a courier to the bank. As soon as the request is 
 			satisfied (i.e., money is obtained from the bank), the courier
 			 updates the student’s WATCard. There is a 1 in 6 chance a 
 			 courier loses a student’s WATCard after the update. When the 
 			 card is lost, the exception WATCardOffice::Lost is inserted 
 			 into the future, rather than making the future available, 
 			 and the current WATCard is deleted.
 Return: void
 *******************************************************************/
void WATCardOffice::Courier::main() {
	this->mOffice.mPrinter.print(Printer::Courier, this->mId, 'S');
	for (;;) {
		Job* job = this->mOffice.requestWork();
		if (!job) { // if job is not available, 
			break;
		} // if
		this->mOffice.mPrinter.print(Printer::Courier, this->mId, 't', (int)job->args.mId, (int)job->args.mTransAmount);
		this->mBank.withdraw(job->args.mId, job->args.mTransAmount);
		this->mOffice.mPrinter.print(Printer::Courier, this->mId, 'T', (int)job->args.mId, (int)job->args.mTransAmount);
		WATCard *card = job->args.mCard;
		card->deposit(job->args.mTransAmount);
		if (RANDOM(5) == 0) { // lose card!!!
			job->result.exception(new Lost());
			delete card;
		} else { // normal case
			job->result.delivery(card);
			this->mOffice.mPrinter.print(Printer::WATCardOffice, 'W');
		} // if
		delete job;
	}
} // WATCardOffice::Courier::main

/***************** WATCardOffice::main **********************
 Purpose:   The execution body of Administrator WATCardOffice.
 ************************************************************/
void WATCardOffice::main() {
	for (;;) {
		_Accept(~WATCardOffice) {
			this->mDone = true;
			break;
		} or _Accept(create) {

		} or _Accept(transfer) {

		} or _Accept(requestWork) {

		} // _Accept
	} // for
} // WATCardOffice::main

/******************* WATCardOffice::WATCardOffice **********************
 Purpose:   The constructor for administrator WATCardOffice
 ***********************************************************************/
WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
: mPrinter(prt), mBank(bank), mNumCouriers(numCouriers), mDone(false) {
	this->mCouriers = new Courier* [mNumCouriers];
	for (unsigned int i = 0; i < this->mNumCouriers; ++i) {
		this->mCouriers[i] = new Courier(*this, mBank, i);
	} // for
	this->mPrinter.print(Printer::WATCardOffice, 'S');
} // WATCardOffice::WATCardOffice


/******************* WATCardOffice::~WATCardOffice **********************
 Purpose:   The destructor for administrator WATCardOffice
 ***********************************************************************/
WATCardOffice::~WATCardOffice() {
	if (!this->mWorkRequest.empty()) {
		this->mWorkRequest.signalBlock(); // in case there are sleeping couriers
	} // if
	for (unsigned int i = 0; i < this->mNumCouriers; ++i) {
		delete this->mCouriers[i];
	} // for
	delete [] this->mCouriers;
	while(!this->mJobs.empty()) {
		delete this->mJobs.front();
		this->mJobs.pop();
	} // while
	this->mPrinter.print(Printer::WATCardOffice, 'F');
} // WATCardOffice::~WATCardOffice


/***************************** WATCardOffice::create ********************************
 Purpose:   A student performs an asynchronous call to create to create a 
 			“real” WATCard with an initial balance. A future WATCard is 
 			returned and sufficient funds are subsequently obtained from 
 			the bank (see Parent task) via a courier to satisfy the transfer request.
 Return:	WATCard::FWATCard (Future WATCard)
 ************************************************************************************/
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCardOffice::Args args;
	args.mCard = new WATCard();
	args.mId = sid;
	args.mTransAmount = amount;
	Job *job = new Job(args);
	this->mJobs.push(job);
	this->mWorkRequest.signal(); // signal Courier for new job available
	this->mPrinter.print(Printer::WATCardOffice, 'C', (int)sid, (int)amount);
	return job->result;
}

/***************************** WATCardOffice::transfer ********************************
 Purpose:   A student performs an asynchronous call to transfer when its WATCard indicates 
 			there is insufficient funds to buy a soda. A future WATCard is returned and sufficient 
 			funds are subsequently obtained from the bank (see Parent task) via a courier to 
 			satisfy the transfer request. 
 Return:	WATCard::FWATCard (Future WATCard)
 ************************************************************************************/
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	WATCardOffice::Args args;
	args.mCard = card;
	args.mId = sid;
	args.mTransAmount = amount;
	Job *job = new Job(args);
	this->mJobs.push(job);
	this->mWorkRequest.signal(); // signal Courier for new job available
	this->mPrinter.print(Printer::WATCardOffice, 'T', (int)sid, (int)amount);
	return job->result;
} // WATCardOffice::transfer

/*************************** WATCardOffice::requestWork *****************************
 Purpose:   Each courier task calls requestWork, blocks until a Job request is ready, 
 			and then receives the next Job request as the result of the call.
 Return:	WATCardOffice::Job*
 ************************************************************************************/
WATCardOffice::Job * WATCardOffice::requestWork() {
	if (this->mDone == false && this->mJobs.empty()) {
		this->mWorkRequest.wait();	
	} // if
	// after waking up, if the program is terminating, wake
	// up other sleeping Couriers. Otherwise, pop a job from
	// job queue and return it to Courier.
	if (this->mDone) {
		this->mWorkRequest.signal();
		return NULL;
	} // if
	Job* job = this->mJobs.front();
	this->mJobs.pop();
	return job;
} // WATCardOffice::requestWork


#endif
