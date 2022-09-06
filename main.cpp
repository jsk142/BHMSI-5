/*
 *  main.cpp                                 
 *                                                
 *  COSC 051 Spring 2019                          
 *  Project #5                                    
 *                                                
 *  Due on: April 30, 2019                  
 *  Author: jsk142                           
 * 
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the 
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project. 
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor, 
 *  or any code taken from the class textbooks.
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

const string ERROR_COMMAND = "Not enough command line arguments, please pass the complete path "
                             "and name\nof one of the \"ALL\" input data files as a command line "
                             "argument.";
const string ERROR_BYE = "Test cannot continue... Goodbye";
const string PROMPT_WELCOME = "\nWelcome to the BHMSI move cost calculator.";
const string PROMPT_CHOICE = "\n\nPlease enter your choice: ";
const string PROMPT_ENTER = "The user entered: ";
const string ERROR_CHOICE = "Your previous selection was not a valid option...";
const string PROMPT_FILE = "Please enter the full path and filename to load: ";
const string PROMPT_CLEAR = "ALL vectors have been emptied of data.";
const string ERROR_CLEAR = "Nothing to do, vectors are already empty.";
const string ERROR_DISPLAY = "Please load at least one data file before attempting to display" 
                             " data.";
const string PROMPT_ESTIMATE = "Enter the estimate number to display: ";
const string PROMPT_BYE = "\nThank you for using the BHMSI move calculator" 
                          " (Object Oriented Version).";
const string ERROR_FILE_OPEN = "ERROR opening input data file, please check name and path:";
const string SUCCESS_FILE_OPEN = "File succesfully opened for input:";
const string PROMPT_TEST = "TESTING: output of each row of the file:";
const string ERROR_MOVE_SOON = "\tERROR: the move date is too soon after the estimate date\n";
const string ERROR_MOVE_LONG = "\tERROR: the move date is too long after the estimate date\n"; 
const string ERROR_MOVE_TYPE = "\tERROR: the move type is not valid\n";
const string ERROR_DISTANCE = "\tERROR: the distance of this move is over the maximum allowed\n";
const string ERROR_WEIGHT_MIN = "\tERROR: the weight of items moved is under the minimum"
                                " allowed\n";
const string ERROR_WEIGHT_MAX = "\tERROR: the weight of items moved is over the maximum allowed\n";
const string ERROR_PIANO = "\tERROR: the number of pianos moved is over the maximum allowed\n";
const string ERROR_ORIGIN = "\tERROR: the answer for stairs > 15 at origin is not valid\n";
const string ERROR_DESTINATION = "\tERROR: the answer for stairs > 15 at destination is not valid\n";

const double PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B = 0.065;   
const double PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W = 0.256;
const double PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C = 0.459;
const double PRICE_PER_POUND_PER_MILE_B = 0.0011;
const double PRICE_PER_POUND_PER_MILE_W = 0.0011;
const double PRICE_PER_POUND_PER_MILE_C = 0.0012;

const int PIANO_SURCHARGE_0 = 275;
const int PIANO_SURCHARGE_1 = 575;
const int PIANO_SURCHARGE_2 = 1075;
const int STAIRS_SURCHARGE = 132;
const int DISTANCE_MIN = 1;
const int DISTANCE_MAX = 3200;
const int WEIGHT_MAX = 18000;
const int WEIGHT_MIN = 1200;
const int PIANO_MAX = 3;
const int PIANO_MIN = 0;

/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 class MoveOrder declaration                     **
 **                                                                 **
 **            This code is provided to students                    **
 **            in COSC 051 Spring 2019 to use in                    **
 **            part or in total for class projects.                 **
 **            Students may use this code as their                  **
 **            own, without any attribution.                        **
 **                                                                 **
 *********************************************************************
 *********************************************************************/

/**
 * <P>A class for storing all information relating to one move
 * estimate for Bubba Hotep Moving and Storage, Inc. (BHMSI).</P>
 *
 * <P>MoveOrder objects shall store any values entered or input from
 * a data file.  NOTE: this means that MoveOrder objects may store
 * values that are NOT valid based upon BHMSI business rules.  The
 * class has several accessor methods that may be called to determine
 * if a specific object contains any invalid values.</P>
 *
 * @author W. A. Woods (waw23 at georgetown dot edu)
 * @version 1.1, 2019/03/17
 * @version 1.2, 2019/04/08
 * @version 2.1, 2019/04/09
 *
 */

class MoveOrder
{
    //overloaded stream insertion operator
    friend ostream& operator<<( ostream &os, const MoveOrder &rhsObj );
    
    //overloaded stream extraction operator
    friend istream& operator>>( istream &is, MoveOrder &rhsObj );
    
private:
    //the data members below are required (you may change identifiers)
    //there is no need for additional data members
    int estimateYear;     /*!< the year the estimate was prepared */
    int estimateMonth;    /*!< the month the estimate was prepared */
    int estimateDay;      /*!< the day the estimate was prepared */
    int moveYear;         /*!< the year the move is scheduled to occur */
    int moveMonth;        /*!< the month the move is scheduled to occur */
    int moveDay;          /*!< the day the move is scheduled to occur */
    char type;            /*!< the move type */
    int givenDistance;    /*!< the distance value that was in the data file */
    int distance;        /*!< the distance value to use, may have been adjusted from given value */
    int weight;           /*!< the weight of contents to move */
    int givenPianos;      /*!< the pianos value that was in the data file */
    int pianos;           /*!< the pianos value to use, may have been adjusted from given value */
    char stairsOrigin;         /*!< are there > 15 stairs at the origin? */
    char stairsDestination;    /*!< are there > 15 stairs at the destination? */
    string estimateNumber;     /*!< the estimate number */
    string region;             /*!< the region of the move origin */
    string customerNameEmail;  /*!< the customer's name and email address */
    
    MoveOrder *next;      /*!< P5 - the address of the next MoveOrder object in the linked-list */
    
public:
    //required constructors
    //you may change parameter identifiers, but the order and types of the parameters
    //must be the same as shown in the prototypes
    
    // destructor
    ~MoveOrder();   /*!< P5 - may NOT be implemented in-line (new mutator)  */
    
    //default constructor
    MoveOrder();
    
    //constructor with parameters
    MoveOrder(int eYYYY, int eMM, int eDD, int mYYYY, int mMM, int mDD,
              char typ, int dst, int wgt, int pno, char sO, char sD,
              string eNum, string reg, string nameEmail, MoveOrder *ptr = NULL);
    
    //copy constructor
    MoveOrder( const MoveOrder &otherObj );
    
    //overloaded assignment operator
    MoveOrder& operator=( const MoveOrder &otherObj );
    
    //required basic mutator functions, in-line implementation is OK for most
    //you may change parameter identifiers but NOT the function identifiers
    void setEstimateYear( int value ) { estimateYear = value; } /*!< in-line mutator  */
    void setEstimateMonth( int value ) { estimateMonth = value; } /*!< in-line mutator  */
    void setEstimateDay( int value ) { estimateDay = value; } /*!< in-line mutator  */
    void setMoveYear( int value ) { moveYear = value; } /*!< in-line mutator  */
    void setMoveMonth( int value ) { moveMonth = value; } /*!< in-line mutator  */
    void setMoveDay( int value ) { moveDay = value; } /*!< in-line mutator  */
    void setType( char value ) { type = value; } /*!< in-line mutator  */
    
    void setDistance( int value ); // given value may be adjusted, may NOT implement in-line
    
    void setWeight( int value ) { weight = value; } /*!< in-line mutator  */
    
    void setPianos( int value );  // given value may be adjusted, may NOT implement in-line
    
    void setStairsOrigin( char value ) { stairsOrigin = value; } /*!< in-line mutator  */
    void setStairsDestination( char value ) { stairsDestination = value; } /*!< in-line mutator  */
    void setEstimateNumber( string value ) { estimateNumber = value; } /*!< in-line mutator  */
    void setRegion( string value ) { region = value; } /*!< in-line mutator  */
    void setCustomerNameEmail( string value ) {customerNameEmail = value;} /*!< in-line mutator  */
    
    void setNext(MoveOrder *ptr) { next = ptr; } 
    /*!< P5 - may be implemented in-line (new mutator)  */
    
    //required basic accessor functions, in-line implementation
    //you may change parameter identifiers but NOT the function identifiers
    int getEstimateYear() const { return estimateYear; } /*!< in-line accessor  */
    int getEstimateMonth() const { return estimateMonth; } /*!< in-line accessor  */
    int getEstimateDay() const { return estimateDay; } /*!< in-line accessor  */
    int getMoveYear() const { return moveYear; } /*!< in-line accessor  */
    int getMoveMonth() const { return moveMonth; } /*!< in-line accessor  */
    int getMoveDay() const { return moveDay; } /*!< in-line accessor  */
    char getType() const { return type; } /*!< in-line accessor  */
    int getGivenDistance() const { return givenDistance; } /*!< in-line accessor  */
    int getDistance() const { return distance; } /*!< in-line accessor  */
    int getWeight() const { return weight; } /*!< in-line accessor  */
    int getGivenPianos() const { return givenPianos; } /*!< in-line accessor  */
    int getPianos() const { return pianos; } /*!< in-line accessor  */
    char getStairsOrigin() const { return stairsOrigin; } /*!< in-line accessor  */
    char getStairsDestination() const { return stairsDestination; } /*!< in-line accessor  */
    string getEstimateNumber() const { return estimateNumber; } /*!< in-line accessor  */
    string getRegion() const { return region; } /*!< in-line accessor  */
    string getCustomerNameEmail() const { return customerNameEmail; } /*!< in-line accessor  */
    
    MoveOrder* getNext() const { return next; } 
    /*!< P5 - may be implemented in-line (new accessor)  */
    
    //required accessor functions that perform more detailed calculations
    //you may change parameter identifiers but NOT the function identifiers
    
    //these functions perform validation of the object's data values
    //same validation rules as project 1, project 2, and project 3
    //answer is set to true if validation test passes, false otherwise
    //message is set to the error message for that test
    void validDates( bool &answer, string &message, bool &tooSoon, bool &tooLate ) const;
    void validType( bool &answer, string &message ) const;
    void validDistance( bool &answer, string &message ) const;
    void validWeight( bool &answer, string &message ) const;
    void validPianoCount( bool &answer, string &message ) const;
    void validStairsOrigin( bool &answer, string &message ) const;
    void validStairsDestination( bool &answer, string &message ) const;
    
    //this function calls each of the other validation methods to
    //determine an overall validity check for this object
    //NOTE: the complete code for this method is given
    void validEstimate( bool &, string &, int & ) const;
    
    //this function outputs values and error messages (if applicable) for this object
    //NOTE: the complete code for this method is given
    void printWithMessages( ostream &os = cout ) const;
    
    //this function returns the calculated cost of this move object according to the
    //same calculation rules as project 1, project 2, and project 3
    double getTotalCost() const;
    
    
    //OPTIONAL
    //if you add any methods they should should go here
    //you may not add any member functions that supercede the required member functions
    //or the stand-alone functions, anything you add should enhance your solution
    //this function returns the full name of the move type:
    //     "Basic     " for b or B
    //     "Wall Pack " for w or W
    //     "Complete  " for c or C
    string getTypeName() const;
    
    
}; //END declaration class MoveOrder\

void loadFile(string fName, bool &loadSuccess, unsigned long &count, MoveOrder* &head);

void clearLL( unsigned long &count, MoveOrder* &head );

void summaryByType( unsigned long count, MoveOrder* head );

void summaryByRegion( unsigned long count, MoveOrder* head );

int main (int argc, const char *argv[])
{
    /****************************************************************************
     *                                                                          *
     *                      COSC 051 Spring 2019                                 *
     *              Project #5 Milestone 5 Test Suite 1                         *
     *                                                                          *
     *                                                                          *
     *            This test code demonstrates the software as                   *
     *            specified in the project description.                         *
     *                                                                          *
     *            If this code runs and produces output consistent              *
     *            with the sample program then it appears that                  *
     *            you have completed the project.                               *
     *                                                                          *
     *            You may submit your file with this code                       *
     *            without attribution, as if it is your own.                    *
     *                                                                          *
     *                                                                          *
     *            NOTE: This does not guarantee that your project               *
     *                  is perfect.  There still may be issues                  *
     *                  within your code or line items in the rubric            *
     *                  that could result in deductions.                        *
     *                                                                          *
     *                                                                          *
     *                                                                          *
     *            Put this inside of your function main.                        *
     *                                                                          *
     ****************************************************************************/
    
    
    
    /*                   START: Milestone 5 Test Suite 1                       */
    


    cout << "Milestone 5, Test Suite 1 output:\n";


    MoveOrder *head = NULL;
    unsigned long count = 0;

    string inputFileName = "";
    ifstream inFile;
    
    bool loadSuccess = false;  
    int fileCount = 0;

    
    if ( argc < 2 )
    {
        cout << "Not enough command line arguments, please pass the complete path and name \n";
        cout << "of one of the \"All\" input data files as a command line argument.\n";
        cout << "Test cannot continue... Goodbye\n";
        cout << endl;
    }
    else 
    {
        //  everything else except return 0 goes here

        //  Assume that the first command line argument is an input data file and path
        
        inputFileName = argv[1];   //you may change inputFileName to match your identifier
        inFile.open(inputFileName.c_str());  //you may change inFile to match your identifier 
        
        if (!inFile)
        {
            cout << "ERROR - The input file:\n";
            cout << inputFileName << endl;
            cout << "Failed to open, the program cannot continue... Goodbye." << endl;
        }
        else 
        {
            loadSuccess = false;  
            fileCount = 0;
            
            count = 0;
            head = NULL;
            
            //load test data using loadFile function 
            
            cout << "calling loadFile function\n" << endl;
            
            loadFile( inputFileName, loadSuccess, count, head);
            
            //if loadFile function successfully processed the file data, 
            //then increment the count of files loaded, and run reports
            
            if (loadSuccess)
            {
                fileCount++;
                
                cout << "calling function summaryByType\n" << endl;
                
                summaryByType(count, head);
                
                cout << endl;
                
                cout << "calling function summaryByRegion\n" << endl;
                
                summaryByRegion(count, head);
            }
            else 
            {
                cout << "ERROR - something went wrong in the loadFile function." << endl;
            }
            
            //deallocate all deallocated memory
            
            cout << "calling clearLL function\n" << endl;
            clearLL(count, head);
            fileCount = 0;
            
            if ( head != NULL )
            {
                cout << "ERROR - Something does not seem correct\n";
                cout << "        after the clearLL function executes,\n";
                cout << "        the linked list should be empty and\n";
                cout << "        the pointer keeping track of the list\n";
                cout << "        head should be pointing to NULL.\n"; 
                cout << endl;
                
            } 
        
        }
        
        
    } //END else block paired with if (argc < 2)
    
    
    /*                   END: Milestone 5 Test Suite 1                         */

   return 0;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 ++                                                                        ++
 ++                      MoveOrder class destructor                        ++
 ++                                                                        ++
 ++                 This code is provided to students                      ++
 ++                 in COSC 051 Spring 2019 to use in                      ++
 ++                 part or in total for class projects.                   ++
 ++                 Students may use this code as their                    ++
 ++                 own, without any attribution.                          ++
 ++                                                                        ++
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * <P>Destructor.</P>
 *
 * <P>Really does not have anything to do in this class.</P>
 *
 * <P>Adding a cout statement during developement can be informative.  Then
 * you will want to comment out the cout statements once large linked lists
 * are added to memory.</P>
 *
 *
 */

MoveOrder::~MoveOrder()
{
    //cout << "Estimate number: " << this->estimateNumber << ",  ";
    //cout << "at address: " << this << " is going out of scope...";
    //cout << endl;
    
} // END destructor for MoveOrder class

/****************************************************************************
 *                   class MoveOrder default constructor                    *
 ****************************************************************************/

MoveOrder::MoveOrder()
{
   estimateYear = 2018;
   estimateMonth = 1;
   estimateDay = 1;
   moveYear = 2018;
   moveMonth = 1;
   moveDay = 1;
   type = 'C';
   distance = 0;
   weight = 0;
   pianos = 0;
   stairsOrigin = 'n';
   stairsDestination = 'n';
   estimateNumber = "none";
   region = "other";
   customerNameEmail = "none";

} // END class Moveorder default constructor

/****************************************************************************
 *                class MoveOrder constructor w/ Parameters                 *
 ****************************************************************************/

MoveOrder::MoveOrder(int eYYYY, int eMM, int eDD, int mYYYY, int mMM, int mDD,
                     char typ, int dst, int wgt, int pno, char sO, char sD,
                     string eNum, string reg, string nameEmail, MoveOrder *ptr)
{
   setEstimateYear(eYYYY);
   setEstimateMonth(eMM); 
   setEstimateDay(eDD); 
   setMoveYear(mYYYY); 
   setMoveMonth(mMM); 
   setMoveDay(mDD);
   setType(typ); 
   setDistance(dst); 
   setWeight(wgt);  
   setPianos(pno); 
   setStairsOrigin(sO); 
   setStairsDestination(sD); 
   setEstimateNumber(eNum);
   setRegion(reg); 
   setCustomerNameEmail(nameEmail); 

} // END class MoveOrder constructor with parameters

MoveOrder::MoveOrder( const MoveOrder &otherObj )
{
   this->setEstimateYear(otherObj.estimateYear);
   this->setEstimateMonth(otherObj.estimateMonth);
   this->setEstimateDay(otherObj.estimateDay);
   this->setMoveYear(otherObj.moveYear);
   this->setMoveMonth(otherObj.moveMonth);
   this->setMoveDay(otherObj.moveDay);
   this->setType(otherObj.type);
   this->setDistance(otherObj.distance);
   this->setWeight(otherObj.weight);
   this->setPianos(otherObj.pianos);
   this->setStairsOrigin(otherObj.stairsOrigin);
   this->setStairsDestination(otherObj.stairsDestination);
   this->setEstimateNumber(otherObj.estimateNumber);
   this->setRegion(otherObj.region);
   this->setCustomerNameEmail(otherObj.customerNameEmail);

} // END class MoveOrder copy constructor


MoveOrder& MoveOrder::operator=( const MoveOrder &otherObj )
{
   estimateYear = otherObj.estimateYear;
   estimateMonth = otherObj.estimateMonth;
   estimateDay = otherObj.estimateDay;
   moveYear = otherObj.moveYear;
   moveMonth = otherObj.moveMonth;
   moveDay = otherObj.moveDay;
   type = otherObj.type;
   distance = otherObj.distance;
   weight = otherObj.weight;
   pianos = otherObj.pianos;
   stairsOrigin = otherObj.stairsOrigin;
   stairsDestination = otherObj.stairsDestination;
   estimateNumber = otherObj.estimateNumber;
   region = otherObj.region;
   customerNameEmail = otherObj.customerNameEmail;

   return *this;

} // END class MoveOrder overloaded assignment operator

void MoveOrder::setDistance( int value )
{
   givenDistance = value;

   if (value >= DISTANCE_MIN)
   {  distance = value;
   }
   else
   {  distance = 1;
   }

}

void MoveOrder::setPianos( int value )
{
   givenPianos = value;

   if (value >= PIANO_MIN)
   {  pianos = value;
   }
   else
   {  pianos = 0;
   }

}

void MoveOrder::validDates( bool &answer, string &message, bool &tooSoon, bool &tooLate ) const
{
   int tempMonth;
 
   tempMonth = getMoveMonth();

   if (moveYear != estimateYear)
   {  tempMonth += 12;
   }
   
   if (tempMonth - estimateMonth < 2)
   {  tooSoon = true;
      message = ERROR_MOVE_SOON;
   }

   if (tempMonth - estimateMonth >= 7)
   {  tooLate = true;
      message = ERROR_MOVE_LONG;
   }

   if (tooSoon || tooLate)
   {  answer = false;
   }
   
}

void MoveOrder::validType( bool &answer, string &message ) const
{
   if (type != 'B' && type != 'b' && type != 'W' && 
       type != 'w' && type != 'C' && type != 'c')
   {  answer = false;
      message = ERROR_MOVE_TYPE;
   }

}

void MoveOrder::validDistance( bool &answer, string &message ) const
{
   if (distance > DISTANCE_MAX)
   {  answer = false;
      message = ERROR_DISTANCE;
   }

}

void MoveOrder::validWeight( bool &answer, string &message ) const
{
   int minimumWeight;

   if (distance >= 1 && distance <= 600)
   {  minimumWeight = WEIGHT_MIN;
   }

   if (distance > 600 && distance <= DISTANCE_MAX)
   {  minimumWeight = 2 * distance;
   }

   if (weight < minimumWeight)
   {  answer = false;
      message = ERROR_WEIGHT_MIN;
   }

   if (weight > WEIGHT_MAX)
   {  answer = false;
      message = ERROR_WEIGHT_MAX;
   }

}

void MoveOrder::validPianoCount( bool &answer, string &message ) const
{
   if (pianos > PIANO_MAX)
   {  answer = false;
      message = ERROR_PIANO;
   }

}

void MoveOrder::validStairsOrigin( bool &answer, string &message ) const
{
   if (stairsOrigin != 'Y' && stairsOrigin != 'y' && 
       stairsOrigin != 'N' && stairsOrigin != 'n')
   {  answer = false;
      message = ERROR_ORIGIN;
   }

}

void MoveOrder::validStairsDestination( bool &answer, string &message ) const
{
   if (stairsDestination != 'Y' && stairsDestination != 'y' &&
       stairsDestination != 'N' && stairsDestination != 'n')
   {  answer = false;
      message = ERROR_DESTINATION;
   }

}

double MoveOrder::getTotalCost() const
{
   int moveStairs = 0;

   double packingCost, 
          movingCost, 
          pianoCost, 
          stairsCost,
          totalCost;

   if (type == 'B' || type == 'b')
   {  packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B * weight;
      movingCost = PRICE_PER_POUND_PER_MILE_B * weight * distance;
   } 

   if (type == 'W' || type == 'w')
   {  packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W * weight; 
      movingCost = PRICE_PER_POUND_PER_MILE_W * weight * distance;
   }              

   if (type == 'C' || type == 'c')
   {  packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C * weight;
      movingCost = PRICE_PER_POUND_PER_MILE_C * weight * distance;
   } 

   if (stairsOrigin == 'Y' || stairsOrigin == 'y')
   {  moveStairs += 1;
   }

   if (stairsDestination == 'Y' || stairsDestination == 'y')
   {  moveStairs += 1;
   }

   if (moveStairs == 0)
   {  pianoCost = pianos * PIANO_SURCHARGE_0;
      stairsCost = moveStairs * STAIRS_SURCHARGE;
   }
 
   if (moveStairs == 1)
   {  pianoCost = pianos * PIANO_SURCHARGE_1;
      stairsCost = moveStairs * STAIRS_SURCHARGE;
   }

   if (moveStairs == 2)
   {  pianoCost = pianos * PIANO_SURCHARGE_2;
      stairsCost = moveStairs * STAIRS_SURCHARGE;
   }
     
   totalCost = packingCost + movingCost + pianoCost + stairsCost;

   return totalCost;
}

ostream& operator<<( ostream &os, const MoveOrder &rhsObj )
{
   double cost = 0.0;
   bool answer;
   string message;
   int errorCount;

   cost = rhsObj.getTotalCost();

   cout << setfill('0');
   cout << rhsObj.estimateYear << "/" << setw(2) << rhsObj.estimateMonth << "/" << setw(2) 
        << rhsObj.estimateDay << "  ";
   cout << rhsObj.moveYear << "/" << setw(2) << rhsObj.moveMonth << "/" << setw(2) 
        << rhsObj.moveDay << "  ";

   cout << setfill(' ');
   cout << rhsObj.type << setw(11) << rhsObj.distance << setw(11) << rhsObj.weight << setw(7)
        << rhsObj.pianos;
   cout << "       " << rhsObj.stairsOrigin << "    " << rhsObj.stairsDestination;

   cout << fixed << showpoint << setprecision(2);
   cout << "  " << rhsObj.estimateNumber << setw(12) << cost;

   rhsObj.validEstimate(answer, message, errorCount);

   if ( !answer )
   {  cout << "  E";
   }

   return os;
}

istream& operator>> (istream &is, MoveOrder &rhsObj)
{
   int eYYYY;
   int eMM;
   int eDD; 
   int mYYYY;
   int mMM;
   int mDD;
   char typ;
   int dst;
   int wgt;
   int pno;
   char sO;
   char sD;
   string eNum;
   string reg; 
   string nameEmail;
   string state;

   char ch = '?';
   
   is >> eNum >> eYYYY >> ch >> eMM >> ch >> eDD >> mYYYY >> ch >> mMM >> ch >> mDD
      >> typ >> dst >> wgt >> pno >> sO >> sD >> state >> reg;

   getline( is, nameEmail);

   rhsObj.setEstimateYear(eYYYY);
   rhsObj.setEstimateMonth(eMM); 
   rhsObj.setEstimateDay(eDD); 
   rhsObj.setMoveYear(mYYYY); 
   rhsObj.setMoveMonth(mMM); 
   rhsObj.setMoveDay(mDD);
   rhsObj.setType(typ); 
   rhsObj.setDistance(dst); 
   rhsObj.setWeight(wgt);  
   rhsObj.setPianos(pno); 
   rhsObj.setStairsOrigin(sO); 
   rhsObj.setStairsDestination(sD); 
   rhsObj.setEstimateNumber(eNum);
   rhsObj.setRegion(reg); 
   rhsObj.setCustomerNameEmail(nameEmail); 

   return is;
}


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +                                                                          +
 +                  MoveOrder class validEstimate method                    +
 +                                                                          +
 +                                                                          +
 +                 This code is provided to students                        +
 +                 in COSC 051 Spring 2019 to use in                        +
 +                 part or in total for class projects.                     +
 +                 Students may use this code as their                      +
 +                 own, without any attribution.                            +
 +                                                                          +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void MoveOrder::validEstimate( bool &answer, string &message, int &errorCount ) const
{
    // an estimate is valid overall if ALL of the individual validation tests pass
    
    // assume estimate is valied prior to testing
    errorCount = 0;
    
    // define variables to store error messages from the individual validation tests
    string messageDates = "";
    string messageType = "";
    string messageDistance = "";
    string messageWeight = "";
    string messagePiano = "";
    string messageStairsO = "";
    string messageStairsD = "";
    
    string overallMessage = "";  // store messages from all individual tests
    bool testGood = true;        // reuse this for each individual test function call
    bool overallGood = true;     // this is overall record validity
    bool moveTooSoon = false;    // true if there is not enough time between the estimate/move
    bool moveTooLate = false;    // true if there is too much enough time between the estimate/move
    
    // combine results from the individual validation test methods
    //     - call each individual validation test
    //     - update variable to keep count of errors found
    //     - update overallGood boolean
    //     - update overallMessage string
    
    validDates( testGood, messageDates, moveTooSoon, moveTooLate );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageDates;
    
    validType( testGood, messageType );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageType;
    
    validDistance( testGood, messageDistance );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageDistance;
    
    validWeight( testGood, messageWeight );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageWeight;
    
    validPianoCount( testGood, messagePiano );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messagePiano;
    
    validStairsOrigin( testGood, messageStairsO );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageStairsO;
    
    validStairsDestination( testGood, messageStairsD );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageStairsD;
    
    if (errorCount > 0)
    {
        overallMessage += "\tContact customer to resolve issues: ";
        overallMessage += customerNameEmail;
        overallMessage += "\n";
    }
    
    // update the parameters with final values that will be returned
    answer = overallGood;
    message = overallMessage;
    
} // END validEstimate method for MoveOrder class



/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +                                                                          +
 +                MoveOrder class printWithMessages method                  +
 +                                                                          +
 +                                                                          +
 +                 This code is provided to students                        +
 +                 in COSC 051 Spring 2019 to use in                        +
 +                 part or in total for class projects.                     +
 +                 Students may use this code as their                      +
 +                 own, without any attribution.                            +
 +                                                                          +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void MoveOrder::printWithMessages( ostream &os ) const
{
    // local variables that are necessary to call the validEstimate method
    string errMsgs = "";
    bool allOK = true;
    int totalErrors = 0;
    
    // call the validEstimate member function
    // this will store any error messages in the
    // local variable errMsgs, it will also store
    // zero (false) in the local variable allOK if
    // the object has any errors (fails any of the
    // various validation tests)
    validEstimate(allOK, errMsgs, totalErrors);
    
    // send the object to the stream defined in the parameter list
    os << *this;
    
    // if any validation tests failed, then also print out
    // the error messages
    if (!allOK)
    {
        os << endl;
        os << errMsgs;
    }
    
    os << endl;
    
} // END printWithMessages method for MoveOrder class

void loadFile (string fName, bool &loadSuccess, unsigned long &count, MoveOrder* &head)
{
   ifstream inFile;
   string headings;

   loadSuccess = true;

   MoveOrder mo1;

   bool answer;
   string message;
   int errorCount;
 
   int errorTotal = 0;
   int basicCount = 0;
   int wallCount = 0;
   int completeCount = 0;
   int distanceBTotal = 0;
   int distanceWTotal = 0;
   int distanceCTotal = 0;
   int weightBTotal = 0;
   int weightWTotal = 0;
   int weightCTotal = 0;

   double costBTotal = 0;
   double costWTotal = 0;
   double costCTotal = 0;
   double costTotal = 0;

   int tempDistance = 0;
   int tempWeight = 0;
 
   inFile.open( fName.c_str () );

   if ( !inFile ) 
   {  cout << ERROR_FILE_OPEN << endl << fName;
      loadSuccess = false;
   }
   else
   {  cout << SUCCESS_FILE_OPEN << endl << fName << endl;

      getline( inFile, headings );
  
      cout << "heading row: " << endl << headings << endl << endl;
      cout << PROMPT_TEST << endl << endl << endl;
      cout << "   Order       Move    Move      Dist.    Weight   Number    Stairs   Move" 
           << "          Total" << endl;
      cout << "   Date        Date    Code    (miles)   (pounds)  Pianos    O    D   Number" 
           << "        Cost ($)" << endl;
      cout << "-----------------------------------------------------------------------------" 
           << "----------------" << endl;

      while ( inFile >> mo1 )
      {  
         mo1.printWithMessages();
         mo1.validEstimate(answer, message, errorCount);
         costTotal = mo1.getTotalCost();
         tempDistance = mo1.getDistance();
         tempWeight = mo1.getWeight();

         count++;
         MoveOrder *current = NULL;

         current = new MoveOrder(mo1);
         current->setNext(head);
         head = current;
         
         if ( !answer )
         {  errorTotal ++;
         }
         else
         {  if ( mo1.getType() == 'B' || mo1.getType() == 'b' )
            {  basicCount++;
               distanceBTotal += tempDistance;
               weightBTotal += tempWeight;
               costBTotal += costTotal;
            }
            if ( mo1.getType() == 'W' || mo1.getType() == 'w' )
            {  wallCount++;
               distanceWTotal += tempDistance;
               weightWTotal += tempWeight;
               costWTotal += costTotal;
            }
            if ( mo1.getType() == 'C' || mo1.getType() == 'c' )
            {  completeCount++;
               distanceCTotal += tempDistance;
               weightCTotal += tempWeight;
               costCTotal += costTotal;
            }
         }
      }

   inFile.close();

   //Output summary table
  
   cout << endl << endl << endl << "Total Records = " << count;
   cout << "  Records with Errors = " << errorTotal;
   cout << "  Records without Errors = " << (count - errorTotal) << endl << endl;
   cout << "                  " << "TOTALS (records without errors)" << endl << endl;
   cout << "       Type        Count    Distance     Weight        Cost" << endl;
   cout << "       ----------------------------------------------------------" << endl;
   cout << "       Basic" << setw(11) << basicCount << setw(12) << distanceBTotal 
        << setw(12) << weightBTotal << "   $" << setw(12) << costBTotal << endl;
   cout << "       Wall Pack" << setw(7) << wallCount << setw(12) << distanceWTotal 
        << setw(12) << weightWTotal << "   $" << setw(12) << costWTotal << endl;
   cout << "       Complete" << setw(8) << completeCount << setw(12) << distanceCTotal 
        << setw(12) << weightCTotal << "   $" << setw(12) << costCTotal << endl;

   cout << PROMPT_BYE << endl << endl;
   
   }     
}

void clearLL( unsigned long &count, MoveOrder* &head )
{
   MoveOrder *current = NULL;

   current = head;

   int delCount = 0;

   cout << "entered stand-alone function clearLL(" << count << ", " << head << ")" << endl;

   while ( current != NULL )
   {   
      current = current->getNext();

      delete head;

      count--;

      delCount++;
   
      head = current;
   }
  
   current = head = NULL;

   cout << "exiting function:" << endl;
   cout << delCount << " objects deallocated and removed from the list." << endl;
   cout << count << " is new value for count." << endl;
   cout << head << " is new value for address stored in pointer variable head." << endl << endl;
    
}

void summaryByType( unsigned long count, MoveOrder* head )
{
   bool answer;
   string message;
   int errorCount;
   
   int errorTotal = 0;
   int rowCount = 0;

   int basicCount = 0;
   int wallCount = 0;
   int completeCount = 0;
   int distanceBTotal = 0;
   int distanceWTotal = 0;
   int distanceCTotal = 0;
   int weightBTotal = 0;
   int weightWTotal = 0;
   int weightCTotal = 0;
   int distanceTotal = 0;
   int weightTotal = 0;

   double costBTotal = 0;
   double costWTotal = 0;
   double costCTotal = 0;
   double costTotal = 0;

   double finalTotalCost = 0;

   int tempDistance = 0;
   int tempWeight = 0;

   MoveOrder *current = head;

   if ( count == 0 )
   {  cout << ERROR_DISPLAY;
   }
   else
   {  while (current)
      {
         current->validEstimate(answer, message, errorCount);
         costTotal = current->getTotalCost();
         tempDistance = current->getDistance();
         tempWeight = current->getWeight();
         
         if ( !answer )
         { errorTotal++;
         }
         else
         {  if ( current->getType() == 'B' || current->getType() == 'b' )
            {  basicCount++;
               distanceBTotal += tempDistance;
               weightBTotal += tempWeight;
               costBTotal += costTotal;
            }
            if ( current->getType() == 'W' || current->getType() == 'w' )
            {  wallCount++;
               distanceWTotal += tempDistance;
               weightWTotal += tempWeight;
               costWTotal += costTotal;
            }
            if ( current->getType() == 'C' || current->getType() == 'c' )
            {  completeCount++;
               distanceCTotal += tempDistance;
               weightCTotal += tempWeight;
               costCTotal += costTotal;
            }
            
            rowCount++;
         }
                
        current = current->getNext();

      }

      distanceTotal = distanceBTotal + distanceWTotal + distanceCTotal;
      weightTotal = weightBTotal + weightWTotal + weightCTotal;
      finalTotalCost = costBTotal + costWTotal + costCTotal;

      //Output summary table
  
      cout << "                   TOTALS ( " << rowCount << " records )" << endl << endl;
      cout << "       Type        Count    Distance     Weight        Cost" << endl;
      cout << "       ----------------------------------------------------------" << endl;
      cout << "       Basic" << setw(11) << basicCount << setw(12) << distanceBTotal 
           << setw(12) << weightBTotal << "   $" << setw(12) << costBTotal << endl;
      cout << "       Wall Pack" << setw(7) << wallCount << setw(12) << distanceWTotal 
           << setw(12) << weightWTotal << "   $" << setw(12) << costWTotal << endl;
      cout << "       Complete" << setw(8) << completeCount << setw(12) << distanceCTotal 
           << setw(12) << weightCTotal << "   $" << setw(12) << costCTotal << endl;
      cout << "       -----------------------------------------------------------" << endl;
      cout << "       Total" << setw(11) << rowCount << setw(12) << distanceTotal 
           << setw(12) << weightTotal << "   $" << setw(12) << finalTotalCost << endl;
   }

}

void summaryByRegion ( unsigned long count, MoveOrder* head )
{  
   int westCount = 0;
   int southCount = 0;
   int northCount = 0;
   int eastCount = 0;
   int otherCount = 0;
   int distanceWTotal = 0;
   int distanceSTotal = 0;
   int distanceNTotal = 0;
   int distanceETotal = 0;
   int distanceOTotal = 0;
   int weightWTotal = 0;
   int weightSTotal = 0;
   int weightNTotal = 0;
   int weightETotal = 0;
   int weightOTotal = 0;
   int distanceTotal = 0;
   int weightTotal = 0;

   double costWTotal = 0;
   double costSTotal = 0;
   double costNTotal = 0;
   double costETotal = 0;
   double costOTotal = 0;

   int tempDistance = 0;
   int tempWeight = 0;

   double costTotal = 0;
   double finalTotalCost = 0;

   int errorTotal = 0;
   int rowCount = 0;

   bool answer;
   string message;
   int errorCount;

   MoveOrder *current = head;

   if ( current == 0 )
   {  cout << ERROR_DISPLAY;
   }
   else
   {  while ( current )
      {  
         current->validEstimate(answer, message, errorCount);
         costTotal = current->getTotalCost();
         tempDistance = current->getDistance();
         tempWeight = current->getWeight();

         if ( !answer )
         { errorTotal++;
         }
         else
         {  rowCount++;

            if ( current->getRegion() == "West" )
            {   westCount++;
                distanceWTotal += tempDistance;
                weightWTotal +=  tempWeight;
                costWTotal += costTotal;
            }
            if ( current->getRegion() == "South" )
            {   southCount++;
                distanceSTotal += tempDistance;
                weightSTotal +=  tempWeight;
                costSTotal += costTotal;
            }
            if ( current->getRegion() == "North" )
            {   northCount++;
                distanceNTotal += tempDistance;
                weightNTotal +=  tempWeight;
                costNTotal += costTotal;
            }
            if ( current->getRegion()== "East" )
            {   eastCount++;
                distanceETotal += tempDistance;
                weightETotal +=  tempWeight;
                costETotal += costTotal;
            }     
            if ( current->getRegion() == "Other" )
            {   otherCount++;
                distanceOTotal += tempDistance;
                weightOTotal += tempWeight;
                costOTotal += costTotal;
            }
 
         }

         current = current->getNext();

      }     

      distanceTotal = distanceWTotal + distanceSTotal + distanceNTotal + distanceETotal + 
                      distanceOTotal;
      weightTotal = weightWTotal + weightSTotal + weightNTotal + weightETotal + weightOTotal;
      finalTotalCost = costWTotal + costSTotal + costNTotal + costETotal + costOTotal;

      cout << "                   TOTALS ( " << rowCount << " records )" << endl << endl;
      cout << "        Type        Count    Distance     Weight        Cost" << endl;
      cout << "        ----------------------------------------------------------" << endl;
      cout << "        South" << setw(11) << southCount << setw(12) << distanceSTotal 
           << setw(12) << weightSTotal << "   $" << setw(12) << costSTotal << endl;
      cout << "        West" << setw(12) << westCount << setw(12) << distanceWTotal 
           << setw(12) << weightWTotal << "   $" << setw(12) << costWTotal << endl;
      cout << "        North" << setw(11) << northCount << setw(12) << distanceNTotal 
           << setw(12) << weightNTotal << "   $" << setw(12) << costNTotal << endl;
      cout << "        East" << setw(12) << eastCount << setw(12) << distanceETotal 
           << setw(12) << weightETotal << "   $" << setw(12) << costETotal << endl;
      cout << "        Other" << setw(11) << otherCount << setw(12) << distanceOTotal 
           << setw(12) << weightOTotal << "   $" << setw(12) << costOTotal << endl;
      cout << "        ----------------------------------------------------------" << endl;
      cout << "        Total" << setw(11) << rowCount << setw(12) << distanceTotal 
           << setw(12) << weightTotal << "   $" << setw(12) << finalTotalCost << endl;
   }
}

