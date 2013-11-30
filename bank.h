#ifndef BANK_H_CS343
#define BANK_H_CS343 


_Monitor Bank {
	unsigned int mNumStudents;
	uCondition * mSuffFund;
	int * mAccountBal;
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
