// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2022

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
	   << pData->firstName << " " 
	   << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

// list<Data *> SortedMerge(list<Data *> a, list<Data *> b);
void FrontBackSplit(list<Data *> &source,
                    list<Data *> &frontRef, list<Data *> &backRef);

void sortDataList(list<Data *> &l) {
  // Fill this in
    cout << "size of list " << l.size() << "\n";

    // cout << "list contains: \n";
    // for (list<Data *>::iterator it=l.begin(); it != l.end(); it++)
    //     cout << (*it)->ssn << "\n";

    if ((l.size() == 0) || (l.size() == 1)) {
         return;
    }

    list<Data *> a;
    list<Data *> b;
    FrontBackSplit(l, a, b);
    cout << "size of list a: " << a.size() << "\n";
    cout << "size of list b: " << b.size() << "\n";

    sortDataList(a);
    sortDataList(b);

//  l = SortedMerge(a, b)
}

// list<Data *> SortedMerge(list<Data *> a, list<Data *> b)
// {
//     Node* result = NULL;
 
//     /* Base cases */
//     if (a == NULL)
//         return (b);
//     else if (b == NULL)
//         return (a);
 
//     /* Pick either a or b, and recur */
//     if (a->data <= b->data) {
//         result = a;
//         result->next = SortedMerge(a->next, b);
//     }
//     else {
//         result = b;
//         result->next = SortedMerge(a, b->next);
//     }
//     return (result);
// }

// split source into two lists at half length
void FrontBackSplit(list<Data *> &source,
                     list<Data *> &frontRef, list<Data *> &backRef)
{
    list<Data *> list2;

    list2.splice( list2.begin(),
                  source,
                  source.begin(),
                  next(source.begin(),source.size()/2));
 
    frontRef = list2;
    backRef = source;
}
