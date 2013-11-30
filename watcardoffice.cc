#ifndef WATCARDOFFICE_CC_CS343
#define WATCARDOFFICE_CC_CS343 

#include "watcardoffice.h"

WATCardOffice::Courier::Courier(WATCardOffice &office, Bank &bank, unsigned int id)
	: mOffice(office), mBank(bank), mId(id) {}

void WATCardOffice::Courier::main() {
	for (;;) {
		Job* job = this->mOffice.requestWork();
		this->mBank.withdraw(job->mId);
		WATCard *card = job->mCard;
		card->deposit(job->mTransAmount);
		if (RANDOM(5) == 0) {
			job->result.exception(Lost());
			delete card;
		} else {
			job->result.delivery(card);
		}
		delete job;
	}
}

void WATCardOffice::main() {
	for (;;) {
		_Accept(~WATCardOffice) {
			break;
		} or _Accept(create) {

		} or _Accept(transfer) {

		} or _Accept(requestWork) {

		}
	}
}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
: mPrinter(prt), mBank(bank), mNumCouriers(numCouriers) {
	this->mCouriers = new Courier* [mNumCouriers];
	for (int i = 0; i < mNumCouriers; ++i) {
		this->mCouriers[i] = new WATCardOffice::Courier(*this, mBank, i);
	}
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCardOffice::Args args;
	args.mCard = new WATCard();
	args.mId = sid;
	args.mTransAmount = amount;
	Job *job = new Job(args);
	this->jobs.push(job);
	this->workRequest.signal();
	return job.result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	WATCardOffice::Args args;
	args.mCard = card;
	args.mId = sid;
	args.mTransAmount = amount;
	Job *job = new Job(args);
	this->jobs.push(job);
	this->workRequest.signal();
	return job.result;
}

WATCardOffice::Job * WATCardOffice::requestWork() {
	if (this->jobs.empty()) {
		this->workRequest.wait();
	}
	Job* job = this->jobs.front();
	this->jobs.pop();
	return job;
}


#endif
