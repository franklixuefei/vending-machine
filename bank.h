#ifndef BANK_H_CS343
#define BANK_H_CS343 


_Monitor Bank {
	uCondition * mSuffFund;
	int * mAccountBal;
	unsigned int mNumStudents;
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
