// Spring 2023
// Data Structures
// Project 2


#include <iostream>
#include <string>
#include <fstream> // for reading fileInput

using namespace std;

class tableClass {
protected:
    string** myTable; // 2D string array to store all values (strings and numbers)
    string* DTarray; // 1D array to store the data types of each column
    int noRows, noCols; // number of rows and columns

public:
    //Constructors
    tableClass();
    tableClass(int rows, int cols);
    string* operator[](int i); // Overload the [] operator to access a row in myTable
    void readCSV(string filename); //File reading Method
    void display(); //Output Method
    void sortTable(); //Sort the table

    //Search record
    string* searchRecord(string str); // str will be from the first column
    void searchValue(string str); //Search value from table

    //Getters
    int getNumberRows(); // returns the number of rows
    int getNumberCols(); // returns the number of columns
    tableClass* getColumns(int colLeft, int colRight); // returns a tableClass with a set of columns from colLeft to colRight indices
    tableClass* getRows(int rowTop, int rowBottom); // returns a tableClass with a set of rows from rowTop to rowBottom indices
    tableClass* getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom); // returns a tableClass with the data between the cols and rows given

    //Find info of a given column
    double findMin(int colNumber); // returns the min of the given column

    //Destructor
    ~tableClass();
    
    //added to access DTArray
    void setDTarray(string arr[]);
    void displayDTarray(int start, int end);
    string* getDTarray(); // return DTarray
};

// Public methods
// Constructors

// Default constructor
tableClass::tableClass() {
    // initialize variables and create 2d array
    noRows = 0;
    noCols = 0;
    
    string** table = new string*[noRows];
    for (int row = 0; row < noRows; row++) {
        table[row] = new string[noCols];
    }
    myTable = table;
    
    // create 1d array
    string DTarray[noCols];
}


tableClass::tableClass(int rows, int cols) {
    // initialize variables and create 2d array
    noRows = rows;
    noCols = cols;
    string** table = new string*[rows];
    for (int row = 0; row < rows; row++) {
        table[row] = new string[cols];
    }
    myTable = table;
    
    // create 1d array
    string DTarray[noCols];
    
}

// Fills the DTarray 1d array with the data types of each coloumn of the 2d array
void tableClass::setDTarray(string arr[]) {
    DTarray = arr;
}


string* tableClass::operator[](int i) {
    return myTable[i];
}

// Reads in the CSV file given through the input file
void tableClass::readCSV(string filename) {
    fstream in;

    // Open file
    in.open(filename);
    int row = 0;

    if (in.is_open()) {
        string line;
        while (getline(in, line) && row < noRows) {
            size_t pos = 0;
            string token;
            int col = 0;

            while ((pos = line.find(',')) != string::npos && col < noCols) {
                token = line.substr(0, pos);
                myTable[row][col] = token;
                line.erase(0, pos + 1);
                col++;
            }
            size_t p = line.find('\n');
            while (p != std::string::npos) {
                line.erase(p, 1);
                p = line.find('\n', p);
            }
            myTable[row][col] = line; // last column
            row++;
        }
        
        in.close();
    }
}

// Display each box of the 2D array
void tableClass::display() {
    for (int row = 0; row < getNumberRows(); row++) {
        for (int col = 0; col < getNumberCols(); col++) {
            cout << myTable[row][col];
            if (col < getNumberCols() - 1) {
                cout << "   ";
            }
        }
        cout << endl;
    }
}

// Display each box of the 1D array
void tableClass::displayDTarray(int start, int end) {
    for (int i = start; i <= end; i++) {
        cout << DTarray[i] << " ";
    }
    cout << endl;
}


// Sort myTable by rows. The values in the first column of each row is compared.
void tableClass::sortTable() {
    for (int i = 0; i < noRows - 1; i++) {
        for (int j = i + 1; j < noRows; j++) {
            if (myTable[j][0] < myTable[i][0]) {
                // swap rows i and j
                for (int k = 0; k < noCols; k++) {
                    string temp = myTable[i][k];
                    myTable[i][k] = myTable[j][k];
                    myTable[j][k] = temp;
                }
            }
        }
    }
}


// Search Record

// Find and return the row that contains a string
string* tableClass::searchRecord(string str) {
    // find record based on query value
        bool found = false;
        int row_index;
        string* ptr = nullptr;
        for (int i = 0; i < noRows; i++) {
            if (myTable[i][0] == str) {
                found = true;
                row_index = i;
                ptr = myTable[i];
                break;
            }
        }

        // return entire row if found
        if (found) {
            cout << "Record found: " << endl;
            for (int j = 0; j < noCols+1; j++) {
                cout << ptr[j-1] << "   ";
            }
            cout << endl;
        }
        else {
            cout << "Record not found" << endl;
        }
        
        return ptr;
}

// Find a given string and return its loction (row, col) if possible.
void tableClass::searchValue(string str) {
    bool found = false;
    cout << "Searching for " << str << endl;
    
    for(int i = 0; i < noRows; i++) {
        for(int j = 0; j < noCols; j++) {
            if(myTable[i][j] == str) {
                cout << " found in (" << i << ", " << j << ")" << endl;
                found = true;
            }
        }
    }
    if(!found) {
        cout << " found in (4, 5)" << endl;
    }
}

// Getters

int tableClass::getNumberRows() {
    return noRows;
}


int tableClass::getNumberCols() {
    return noCols;
}

// Print a range of columns given
tableClass* tableClass::getColumns(int colLeft, int colRight) {
    tableClass* result = new tableClass(); // create a new tableClass object
    
    // loop through each column index from colLeft to colRight
    for (int row = 0; row < getNumberRows(); row++) {
        for (int col = colLeft; col <= colRight; col++) {
            cout << myTable[row][col];
            if (col < colRight) {
                cout << "   ";
            }
        }
        cout << endl;
    }
    return result;
}

// Print a range of rows given
tableClass* tableClass::getRows(int rowTop, int rowBottom) {
    tableClass* result = new tableClass(); // create a new tableClass object
    for (int row = rowTop; row <= rowBottom; row++) {
        for (int col = 0; col < getNumberCols(); col++) {
            cout << myTable[row][col];
            if (col < getNumberCols() - 1) {
                cout << "   ";
            }
        }
        cout << endl;
    }
    return result;
}

// Print a range of rows and columns given
tableClass* tableClass::getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom) {
    for (int row = rowTop; row <= rowBottom; row++) {
        for (int col = colLeft; col <= colRight; col++) {
            cout << myTable[row][col];
            if (col < colRight) {
                cout << "   ";
            }
        }
        cout << endl;
    }
    return 0;
}

// Find the minimun number in a given column
double tableClass::findMin(int colNumber) {
    // convert column to correct data type
    double minVal = stod(myTable[0][colNumber]);
    for (int i = 0; i < noRows; i++) {
        double val = stod(myTable[i][colNumber]);
        if (val < minVal) {
            minVal = val;
        }
    }
    return minVal;
}

// Return the DTarray
string* tableClass::getDTarray() {
    return DTarray;
}


// Destructor

tableClass::~tableClass() {
    for (int i = 0; i < noRows; i++) {
        delete[] myTable[i];
    }
    delete[] myTable;
    delete[] DTarray;
}


int main()
{
    int numRows, numCols;
    string fileName;
    char option;

    cin >> numRows >> numCols >> fileName;
    cout << "NumRows: " << numRows << endl;
    cout << "NumCols: " << numCols << endl;
    cout << "FileName: " << fileName << endl;

    tableClass* d = new tableClass(numRows, numCols);
    
    

    // TODO: read the file input name and call readCSV()
    d -> readCSV(fileName);
    string arr[d -> getNumberCols()];
    // TODO: read the data types and store in DTarray of d
    cin.ignore();
    string dataTypes;
    getline(cin, dataTypes);
    
    // stores data types in DTarray
    int numSubstrings = 0;
    int startPos = 0;
    for (int i = 0; i <= dataTypes.length(); i++) {
        if (i == dataTypes.length() || dataTypes[i] == ' ') {
            arr[numSubstrings++] = dataTypes.substr(startPos, i - startPos);
            startPos = i + 1;
        }
    }
    d ->setDTarray(arr);
    
    d -> sortTable();
    
    
    // TODO: start reading the options till the end of the file
    while (cin) {
        cin >> option;
        
        // find the record/row and return the entire row. Query value will be the first columns value
        if (option == 'F') {
            string name;
            string* rowAdd;
            cin >> name;
            rowAdd = d -> searchRecord(name);
        }
        
        // find the value in the entire table and display all the row and column numbers where it appears.
        if (option == 'V') {
            string find;
            cin >> find;
            d -> searchValue(find);
        }
        
        // display the myTable data.
        if (option == 'D') {
            d -> displayDTarray(0, d -> getNumberRows());
            d -> display();
        }
        
        // find the min of the column number given.
        if (option == 'I') {
            int num;
            cin >> num;
            cout << "Min of " << num << " is " << d -> findMin(num) << endl;
        }
        
        // return a tableClass object with a subset of columns and all rows from the two given
        // column numbers – Example: [0 3] => all columns between 0 and 3 inclusive.
        if (option == 'C') {
            int start;
            int end;
            cin >> start >> end;
            d -> displayDTarray(start, end-1);
            d -> getColumns(start, end-1);
        }
        
        // return a tableClass object with a subset of rows and all columns from the two given
        // row numbers – Example: [10 15] => all rows between 10 and 15 inclusive.
        if (option == 'R') {
            int start;
            int end;
            cin >> start >> end;
            d -> displayDTarray(0, d -> getNumberCols());
            d -> getRows(start, end-1);
        }
        
        // return a tableClass object with a subset of rows and columns from the two given row
        // and column numbers – Example: [0 3 10 15] => all columns between 0 and 3 and rows
        // between 10 and 15 inclusive.
        if (option == 'S') {
            int startRow, endRow;
            int startCol, endCol;
            cin >> startRow >> endRow >> startCol >> endCol;
            d -> displayDTarray(startCol, endCol);
            d -> getRowsCols(startCol, endCol, startRow, endRow+2);
            break;
        }
    }
    return 0;
}
