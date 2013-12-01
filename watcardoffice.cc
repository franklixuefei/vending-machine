#ifndef WATCARDOFFICE_CC_CS343
#define WATCARDOFFICE_CC_CS343 

#include "watcardoffice.h"

WATCardOffice::Courier::Courier(WATCardOffice &office, Bank &bank, unsigned int id)
	: mOffice(office), mBank(bank), mId(id) {}

WATCardOffice::Courier::~Courier() {
	this->mOffice.mPrinter.print(Printer::Courier, this->mId, 'F');
}
void WATCardOffice::Courier::main() {
	this->mOffice.mPrinter.print(Printer::Courier, this->mId, 'S');
	for (;;) {
		Job* job = this->mOffice.requestWork();
		if (!job) {
			break;
		}
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
		}
		delete job;
	}
}

void WATCardOffice::main() {
	for (;;) {
		_Accept(~WATCardOffice) {
			this->mDone = true;
			break;
		} or _Accept(create) {

		} or _Accept(transfer) {

		} or _Accept(requestWork) {

		}
	}
}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
: mPrinter(prt), mBank(bank), mNumCouriers(numCouriers), mDone(false) {
	this->mCouriers = new Courier* [mNumCouriers];
	for (unsigned int i = 0; i < this->mNumCouriers; ++i) {
		this->mCouriers[i] = new Courier(*this, mBank, i);
	}
}

WATCardOffice::~WATCardOffice() {
	if (!this->mWorkRequest.empty()) {
		this->mWorkRequest.signalBlock();
	}
	// maybe deadlock here?????
	for (unsigned int i = 0; i < this->mNumCouriers; ++i) {
		delete this->mCouriers[i];
	}
	delete [] this->mCouriers;
	while(!this->mJobs.empty()) {
		delete this->mJobs.front();
		this->mJobs.pop();
	}
	this->mPrinter.print(Printer::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCardOffice::Args args;
	args.mCard = new WATCard();
	args.mId = sid;
	args.mTransAmount = amount;
	Job *job = new Job(args);
	this->mJobs.push(job);
	this->mWorkRequest.signal();
	this->mPrinter.print(Printer::WATCardOffice, 'C', (int)sid, (int)amount);
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	WATCardOffice::Args args;
	args.mCard = card;
	args.mId = sid;
	args.mTransAmount = amount;
	Job *job = new Job(args);
	this->mJobs.push(job);
	this->mWorkRequest.signal();
	this->mPrinter.print(Printer::WATCardOffice, 'T', (int)sid, (int)amount);
	return job->result;
}

WATCardOffice::Job * WATCardOffice::requestWork() {
	if (this->mDone == false && this->mJobs.empty()) {
		this->mWorkRequest.wait();	
	}
	if (this->mDone) {
		this->mWorkRequest.signal();
		return NULL;
	}
	Job* job = this->mJobs.front();
	this->mJobs.pop();
	return job;
}


#endif
