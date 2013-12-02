#include "printer.h"

/***************** Printer::main **********************
 Purpose:   Coroutine main of Cormonitor Printer
 ******************************************************/
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


/***************** Printer::_printHeader ****************
 Purpose:   printer the header of program
 return:  void
 ******************************************************/
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


/***************** Printer::_upperRangTranslation ****************
 Purpose:   translatable how many time need to print for each Kind
 return:    number of time (unsigned int)
 ******************************************************/
unsigned int Printer::_upperRangTranslation(unsigned int k){
  switch (k){
    case ((unsigned int) Printer::Student):
      return mNumStudents;
    case ((unsigned int) Printer::Vending):
      return mNumVendingMachines;
    case ((unsigned int) Printer::Courier):
      return mNumCouriers;
    default:
      return 1;
  }
}

/***************** Printer::_flashMap ****************
 Purpose:   print the contain of map and clears it
 return:    void
 ******************************************************/
void Printer::_flashMap(bool isDotFlash){
  // goes though 8 kind of value
  for (unsigned int k = 0; k < (3 + 5); ++k) {
    // if the value exist print its value, otherwise print a tab
    if (mDataMap.find(k) != mDataMap.end()) {
      // if k is in upper range of the enum, which mean there could be multiple instance of the value
      if (k == ((unsigned int) Printer::Student) || 
          k == ((unsigned int) Printer::Vending) || 
          k == ((unsigned int) Printer::Courier) ) {
        // for the kind k find how many of those possible value could exits
        unsigned int times = _upperRangTranslation(k);
        // print that many kind 
        for (unsigned int i = 0; i < times; ++i) {
          if (mDataMap[k].find(i) != mDataMap[k].end()){
            // output the char
            cout << mDataMap[k][i].first;
            if (mDataMap[k][i].second.first != ((unsigned int)-1)) {
              // first number
              cout << mDataMap[k][i].second.first;
              if (mDataMap[k][i].second.second != ((unsigned int)-1)) {
                // second number
                cout << "," <<mDataMap[k][i].second.second;
              }
            }
          } else if (isDotFlash) {
            // if it is a dot flash
            cout << "...";
          }
          cout << "\t";
        }
      } else {
        // other wise it in lower range and should only have one instance
        unsigned int i = 0;
        if (mDataMap[k].find(i) != mDataMap[k].end()){
          // output the char
          cout << mDataMap[k][i].first;
          if (mDataMap[k][i].second.first != ((unsigned int)-1)) {
            // first number
            cout << mDataMap[k][i].second.first;
            if (mDataMap[k][i].second.second != ((unsigned int)-1))
            {
              // second number
              cout << "," <<mDataMap[k][i].second.second;
            }
          }
        } else if (isDotFlash) {
          cout << "...";
        }
        cout << "\t";
      }

    } else if (isDotFlash) {
      // if nothing is found should either print dots or a tab
      if (k == ((unsigned int) Printer::Student) || 
          k == ((unsigned int) Printer::Vending) || 
          k == ((unsigned int) Printer::Courier) ) {
        unsigned int times = _upperRangTranslation(k);
        for (unsigned int i = 0; i < times; ++i) {
          cout << "...";
          cout << "\t";
        }
      }else {
        cout << "...";
        cout << "\t";
      }
    }else {
      // if nothing is found should either print dots or a tab
      if (k == ((unsigned int) Printer::Student) || 
          k == ((unsigned int) Printer::Vending) || 
          k == ((unsigned int) Printer::Courier) ) {
        unsigned int times = _upperRangTranslation (k);
        for (unsigned int i = 0; i < times; ++i) {
          cout << "\t";
        }
      }else{
        cout << "\t";
      }
    }
  }
  cout << endl;
  mDataMap.clear();

}


/***************** Printer::_insertData ****************
 Purpose:   insert data into the map
 return:  void
 ******************************************************/
void Printer::_insertData(){


  // FIXME: THE BUG
  static int counter = 0;
  static char last_State = mState;
  if (last_State != mState) {
    counter =0;
    last_State= mState;
  }else{
    counter++;
    if (counter > 200)
    {
      exit(1);
    }
  }








  if (mDataMap.find(mKind) == mDataMap.end()) {
    // if the kind entry doesnt exist in the map
    mDataMap[mKind] = std::map<unsigned int, pair<char, 
                            pair<unsigned int , unsigned int > 
                                                  > 
                              > ();
  }
  // if there isnt a idea for it create one
  if (mDataMap[mKind].find(mLid) == mDataMap[mKind].end()) {
    mDataMap[mKind][mLid] = pair<char, 
                                pair <unsigned int , unsigned int > > (
                                  mState,
                                    pair <unsigned int , unsigned int >(
                                      mValue1, mValue2
                                      )
                                  );
                  
  } else {
    // some thing went really wrong.
    assert(false);
  }
}


/***************** Printer::_canInsertData ****************
 Purpose:   if with current number can be inserted into the map
 return:  result (bool)
 ******************************************************/
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


/***************** Printer::Printer ****************
 Purpose:   the constructor
 ******************************************************/
Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )
  : mNumStudents(numStudents), mNumVendingMachines(numVendingMachines),
  mNumCouriers(numCouriers) {

}


/***************** Printer::Printer ****************
 Purpose:   the destructor
 ******************************************************/
Printer::~Printer(){
  if (!mDataMap.empty()) {
    _flashMap();
  }
  cout << "***********************" << endl;
}

/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, char state ) {
  mKind = static_cast<unsigned int>(kind);
  mState = state;
  mLid = 0;
  mValue1 = (unsigned int)-1;
  mValue2 = (unsigned int)-1;

  resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, char state, int value1 ) {
  mKind = static_cast<unsigned int>(kind);
  mState = state;
  mLid = 0;
  mValue1 = value1;
  mValue2 = (unsigned int)-1;

  resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, char state, int value1, int value2 ) {
  mKind = static_cast<unsigned int>(kind);
  mLid = 0;
  mState = state;
  mValue1 = value1;
  mValue2 = value2;

  resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, unsigned int lid, char state ) {
  mKind = static_cast<unsigned int>(kind);
  mLid = lid;
  mState = state;
  mValue1 = (unsigned int)-1;
  mValue2 = (unsigned int)-1;

  resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
  mKind = static_cast<unsigned int>(kind);
  mLid = lid;
  mState = state;
  mValue1 = value1;
  mValue2 = (unsigned int)-1;


  resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
  mKind = static_cast<unsigned int>(kind);
  mLid = lid;
  mState = state;
  mValue1 = value1;
  mValue2 = value2;

  resume(); 
}
