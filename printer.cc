#include "printer.h"

void Printer::main() {
        
  _printHeader();
  for(;;){
    if (!_canInsertData()) {
      _flashMap();
    }
    if (mState == 'F' && !mDataMap.empty()) {
      _flashMap();
    }
    _insertData();
    if (mState == 'F') {
      _flashMap(true);
    }
    suspend();
  }
}

void Printer::_printHeader(){
  cout<<"Parent\tWATOff\tNames\tTruck\tPlant";
  for (unsigned int i = 0; i < mNumStudents; ++i) {
    cout << "\t" << "Stud" << i;
  }
  for (unsigned int i = 0; i < mNumVendingMachines; ++i) {
    cout << "\t" << "Mach" << i ;
  }
  for (unsigned int i = 0; i < mNumCouriers; ++i) {
    cout << "\t" << "Cour" << i;
  }
  cout << endl;
  cout <<"*******";
  for (unsigned int i = 0; i < (4 + mNumStudents + mNumVendingMachines + mNumCouriers); ++i)
  {
    cout  << "\t" <<"*******";
  }
  cout << endl;
}


void Printer::_flashMap(bool isDotFlash){
  for (unsigned int k = 0; k < (3 + 5); ++k) {
    if (mDataMap.find(k) != mDataMap.end()) {

      if (k == ((unsigned int) Printer::Student) || 
          k == ((unsigned int) Printer::Vending) || 
          k == ((unsigned int) Printer::Courier) ) {
        unsigned int times;
        switch (k){


          case ((unsigned int) Printer::Student):
          {
            times = mNumStudents;
          }
          break;
          case ((unsigned int) Printer::Vending):
          {
            times = mNumVendingMachines;
          }
          break;
          case ((unsigned int) Printer::Courier):
          {
            times = mNumCouriers;
          }
          break;
          default:
          {
            assert (false);
          }
        }
        for (int i = 0; i < times; ++i) {
          if (mDataMap[k].find(i) != mDataMap[k].end()){
            cout << mDataMap[k][i].first;
            if (mDataMap[k][i].second.first != ((unsigned int)-1)) {
              cout << mDataMap[k][i].second.first;
              if (mDataMap[k][i].second.second != ((unsigned int)-1)) {
                cout << "," <<mDataMap[k][i].second.second;
              }
            }
          } else if (isDotFlash) {
            cout << "...";
          }
          cout << "\t";
        }
      } else {
        unsigned int i = 0;
        if (mDataMap[k].find(i) != mDataMap[k].end()){
          cout << mDataMap[k][i].first;
          if (mDataMap[k][i].second.first != ((unsigned int)-1)) {
            cout << mDataMap[k][i].second.first;
            if (mDataMap[k][i].second.second != ((unsigned int)-1))
            {
              cout << "," <<mDataMap[k][i].second.second;
            }
          }
        } else if (isDotFlash) {
          cout << "...";
        }
        cout << "\t";
      }

    } else if (isDotFlash) {
      if (k == ((unsigned int) Printer::Student) || 
          k == ((unsigned int) Printer::Vending) || 
          k == ((unsigned int) Printer::Courier) ) {
        unsigned int times;
        switch (k){
          case ((unsigned int) Printer::Student):
          {
            times = mNumStudents;
          }
          break;
          case ((unsigned int) Printer::Vending):
          {
            times = mNumVendingMachines;
          }
          break;
          case ((unsigned int) Printer::Courier):
          {
            times = mNumCouriers;
          }
          break;
          default:
          {
            assert (false);
          }
        }
        for (int i = 0; i < times; ++i) {
          cout << "...";
          cout << "\t";
        }
      }else {
        cout << "...";
        cout << "\t";
      }
    }else {
      cout << "\t";
    }
  }
  cout << endl;
  mDataMap.clear();

}



void Printer::_insertData(){
  if (mDataMap.find(mKind) == mDataMap.end()) {
    mDataMap[mKind] = std::map<unsigned int, pair<char, 
                            pair<unsigned int , unsigned int > 
                                                  > 
                              > ();
  }
  if (mDataMap[mKind].find(mLid) == mDataMap[mKind].end()) {
    mDataMap[mKind][mLid] = pair<char, 
                                pair <unsigned int , unsigned int > > (
                                  mState,
                                    pair <unsigned int , unsigned int >(
                                      mValue1, mValue2
                                      )
                                  );
                  
  } else {
    assert(false);
  }
}

bool Printer::_canInsertData(){
  if (!mDataMap.empty()) {
    if (mDataMap.find(mKind) != mDataMap.end()) {
      if (mKind <= ((unsigned int) BottlingPlant)) {
        return false;
      } else {
        if (!(mDataMap[mKind].find(mLid) == mDataMap[mKind].end())) {
          return false;
        }
      }
    }
  }
  return true;
}



Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )
	: mNumStudents(numStudents), mNumVendingMachines(numVendingMachines),
	mNumCouriers(numCouriers) {

}


Printer::~Printer(){
  if (!mDataMap.empty()) {
    _flashMap();
  }
}


void Printer::print( Kind kind, char state ) {
  mKind = (unsigned int)kind;
  mState = state;
  mLid = 0;
  mValue1 = (unsigned int)-1;
  mValue2 = (unsigned int)-1;

  resume();
}



void Printer::print( Kind kind, char state, int value1 ) {
  mKind = (unsigned int)kind;
  mState = state;
  mLid = 0;
  mValue1 = value1;
  mValue2 = (unsigned int)-1;

  resume();
}



void Printer::print( Kind kind, char state, int value1, int value2 ) {
  mKind = (unsigned int)kind;
  mLid = 0;
  mState = state;
  mValue1 = value1;
  mValue2 = value2;

  resume();
}



void Printer::print( Kind kind, unsigned int lid, char state ) {
  mKind = (unsigned int)kind;
  mLid = lid;
  mState = state;
  mValue1 = (unsigned int)-1;
  mValue2 = (unsigned int)-1;

  resume();
}



void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
  mKind = (unsigned int)kind;
  mLid = lid;
  mState = state;
  mValue1 = value1;
  mValue2 = (unsigned int)-1;


  resume();
}



void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
  mKind = (unsigned int)kind;
  mLid = lid;
  mState = state;
  mValue1 = value1;
  mValue2 = value2;

  resume();	
}

