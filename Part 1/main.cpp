#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "array.h"
#include "linkedlist.h"

using namespace std;

int loadDatasetOnce(const string &fileName) {
  ifstream file(fileName);
  if (!file.is_open()) {
    cerr << "Error: Could not open the file " << fileName << endl;
    return 0;
  }

  string line;
  getline(file, line); // header

  int count = 0;

  while (getline(file, line) && Array::patientCount < 600) {
    if (line.empty()) {
      continue;
    }

    stringstream ss(line);
    string token;

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

    // Store in array
    Array::patientList[Array::patientCount] = arrayPatient;

    // Store in linked list
    LinkedList::insertToEnd(LinkedList::patientNode, linkedPatient);

    // Store original/unsorted copy
    Array::unsortedPatientList[Array::patientCount] = arrayPatient;

    // Store original/unsorted copy
    LinkedList::insertToEnd(LinkedList::unsortedPatientNode, linkedPatient);

    Array::patientCount++;
    count++;
  }

  file.close();

  return count;
}

void showComparisonMenu() {
  int choice;

  do {
    cout << "\n" << string(80, '=') << endl;
    cout << "Menu" << endl;
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
      LinkedList::freeList(LinkedList::patientNode);
      LinkedList::freeList(LinkedList::unsortedPatientNode);

      Array::patientCount = 0;

      loadDatasetOnce("dataset1_facility_a.csv");
      loadDatasetOnce("dataset2_facility_b.csv");
      loadDatasetOnce("dataset3_facility_c.csv");
      cout << "Patients Loaded" << endl;
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
  // Load dataset
  LinkedList::freeList(LinkedList::patientNode);
  LinkedList::freeList(LinkedList::unsortedPatientNode);

  showComparisonMenu();
  LinkedList::freeList(LinkedList::patientNode);
  LinkedList::freeList(LinkedList::unsortedPatientNode);
  return 0;
}
