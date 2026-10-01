#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "array.h"
#include "linkedlist.h"

using namespace std;

// Reads the CSV once and stores every record in both implementations.
int loadDatasetOnce(const string &fileName) {
  ifstream file(fileName);
  if (!file.is_open()) {
    cerr << "Error: Could not open the file " << fileName << endl;
    return 0;
  }

  // Clear previous data if main is used to load another dataset.
  Array::patientCount = 0;
  LinkedList::freeList(LinkedList::patientNode);
  LinkedList::freeList(LinkedList::unsortedPatientNode);

  string line;
  getline(file, line); // header

  int count = 0;

  while (getline(file, line) && count < 200) {
    if (line.empty()) {
      continue;
    }

    stringstream ss(line);
    string token;

    // Create one array Patient and one linked-list Patient from the
    // same parsed CSV row. The file itself is still read only once.
    Array::Patient arrayPatient;
    LinkedList::Patient linkedPatient;

    getline(ss, token, ',');
    arrayPatient.PatientID = token;
    linkedPatient.PatientID = token;

    getline(ss, token, ',');
    arrayPatient.age = stoi(token);
    linkedPatient.age = arrayPatient.age;

    getline(ss, token, ',');
    arrayPatient.careType = token;
    linkedPatient.careType = token;

    getline(ss, token, ',');
    arrayPatient.lengthOfStay = stoi(token);
    linkedPatient.lengthOfStay = arrayPatient.lengthOfStay;

    getline(ss, token, ',');
    arrayPatient.baseCostPerHour = stoi(token);
    linkedPatient.baseCostPerHour = arrayPatient.baseCostPerHour;

    getline(ss, token, ',');
    arrayPatient.daysVisitsPerYear = stoi(token);
    linkedPatient.daysVisitsPerYear = arrayPatient.daysVisitsPerYear;

    // Main/current copy.
    Array::patientList[count] = arrayPatient;
    LinkedList::insertToEnd(LinkedList::patientNode, linkedPatient);

    // Unsorted/original copy.
    Array::unsortedPatientList[count] = arrayPatient;
    LinkedList::insertToEnd(LinkedList::unsortedPatientNode, linkedPatient);

    ++count;
  }

  file.close();
  Array::patientCount = count;

  return count;
}

void showComparisonMenu() {
  int choice;

  do {
    cout << "\n" << string(80, '=') << endl;
    cout << "DSTR Array vs Singly Linked List" << endl;
    cout << string(80, '=') << endl;
    cout << "1. Load dataset (read CSV once)" << endl;
    cout << "2. Print array" << endl;
    cout << "3. Print linked list" << endl;
    cout << "4. Sort array" << endl;
    cout << "5. Sort linked list" << endl;
    cout << "6. Categorize array" << endl;
    cout << "7. Categorize linked list" << endl;
    cout << "8. Array care-type summary" << endl;
    cout << "9. Linked-list care-type summary" << endl;
    cout << "10. Array linear search" << endl;
    cout << "11. Linked-list linear search" << endl;
    cout << "0. Exit" << endl;
    cout << "Selection: ";
    cin >> choice;

    if (choice == 1) {
      string fileName;
      cout << "Dataset file: ";
      cin >> fileName;

      int count = loadDatasetOnce(fileName);
      cout << "Loaded " << count << " patients." << endl;
    } else if (Array::patientCount == 0 && choice != 0) {
      cout << "Please load a dataset first." << endl;
    } else if (choice == 2) {
      Array::tempPrintArr(Array::patientList, Array::patientCount);
    } else if (choice == 3) {
      LinkedList::tempPrintNode(LinkedList::patientNode);
    } else if (choice == 4) {
      string field;
      cout << "Sort field (age / stay / cost): ";
      cin >> field;
      Array::sortByBubble(Array::patientList, field, Array::patientCount);
    } else if (choice == 5) {
      string field;
      cout << "Sort field (age / stay / cost): ";
      cin >> field;
      LinkedList::sortByBubble(LinkedList::patientNode, field);
    } else if (choice == 6) {
      Array::sortIntoCategory(Array::patientList);
    } else if (choice == 7) {
      LinkedList::sortIntoCategory(LinkedList::patientNode);
    } else if (choice == 8) {
      Array::mostPreferredCareType(Array::category1, Array::category1Count);
      Array::mostPreferredCareType(Array::category2, Array::category2Count);
      Array::mostPreferredCareType(Array::category3, Array::category3Count);
      Array::mostPreferredCareType(Array::category4, Array::category4Count);
      Array::mostPreferredCareType(Array::category5, Array::category5Count);
    } else if (choice == 9) {
      LinkedList::mostPreferredCareType(LinkedList::category1);
      LinkedList::mostPreferredCareType(LinkedList::category2);
      LinkedList::mostPreferredCareType(LinkedList::category3);
      LinkedList::mostPreferredCareType(LinkedList::category4);
      LinkedList::mostPreferredCareType(LinkedList::category5);
    } else if (choice == 10) {
      int category;
      int visitDuration;
      float maxCost;

      cout << "Category: ";
      cin >> category;
      cout << "Minimum visit duration: ";
      cin >> visitDuration;
      cout << "Maximum total medical cost: ";
      cin >> maxCost;

      Array::searchUsingLinear(Array::patientList, category, visitDuration,
                               maxCost);
    } else if (choice == 11) {
      int category;
      int visitDuration;
      float maxCost;

      cout << "Category: ";
      cin >> category;
      cout << "Minimum visit duration: ";
      cin >> visitDuration;
      cout << "Maximum total medical cost: ";
      cin >> maxCost;

      LinkedList::searchUsingLinear(LinkedList::patientNode, category,
                                    visitDuration, maxCost);
    }

  } while (choice != 0);
}

int main() {
  showComparisonMenu();
  LinkedList::freeList(LinkedList::patientNode);
  LinkedList::freeList(LinkedList::unsortedPatientNode);
  return 0;
}
