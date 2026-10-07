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

    arrayPatient.totalMedicalCost = Array::totalMedicalCost(arrayPatient);
    linkedPatient.totalMedicalCost =
        LinkedList::totalMedicalCostArray(linkedPatient);

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

  Array::Patient tempList1[200];
  Array::Patient tempList2[200];
  Array::Patient tempList3[200];

  do {
    cout << "\n" << string(80, '=') << endl;
    cout << "Menu" << endl;
    cout << string(80, '=') << endl;
    cout << "1. Load dataset (read CSV once)" << endl;
    cout << "2. Print array" << endl;
    cout << "3. Print linked list" << endl;
    cout << "4. Sort" << endl;
    cout << "5. Show total medical billing costs per dataset" << endl;
    cout << "6. Compare expenditure and visit durations across datasets and "
            "age groups. "
         << endl;
    cout << "7. Array care-type summary" << endl;
    cout << "8. Linked-list care-type summary" << endl;
    cout << "9. Linear search" << endl;
    cout << "10. Binary search" << endl;
    cout << "11. Identify highest billing and patient traffic" << endl;
    cout << "0. Exit" << endl;
    cout << "Selection: ";
    cin >> choice;

    if (choice == 1) {
      LinkedList::freeList(LinkedList::patientNode);
      LinkedList::freeList(LinkedList::unsortedPatientNode);

      Array::patientCount = 0;

      string datasetChoosen;
      cout << "Choose a dataset to load: " << endl;
      cout << "1. Dataset 1 " << endl;
      cout << "2. Dataset 2" << endl;
      cout << "3. Dataset 3" << endl;
      cout << "4. All dataset" << endl;
      cin >> datasetChoosen;
      if (datasetChoosen == "1") {
        loadDatasetOnce("dataset1_facility_a.csv");

        cout << "Dataset 1 loaded " << endl;
      } else if (datasetChoosen == "2") {
        loadDatasetOnce("dataset2_facility_b.csv");
        cout << "Dataset 2 loaded " << endl;
      } else if (datasetChoosen == "3") {
        loadDatasetOnce("dataset3_facility_c.csv");
        cout << "Dataset 3 loaded " << endl;
      } else {
        loadDatasetOnce("dataset1_facility_a.csv");
        loadDatasetOnce("dataset2_facility_b.csv");
        loadDatasetOnce("dataset3_facility_c.csv");
        cout << "All dataset loaded " << endl;
      }
      Array::readFromDataset("dataset1_facility_a.csv", tempList1, 0);
      Array::readFromDataset("dataset2_facility_b.csv", tempList2, 0);
      Array::readFromDataset("dataset3_facility_c.csv", tempList3, 0);

    } else if (Array::patientCount == 0 && choice != 0) {
      cout << "Please load a dataset first." << endl;
    } else if (choice == 2) {
      Array::tempPrintArr(Array::patientList, Array::patientCount);
    } else if (choice == 3) {
      LinkedList::tempPrintNode(LinkedList::patientNode);
    } else if (choice == 4) {
      int sortChoice;
      string field;

      cout << "\n" << string(80, '=') << endl;
      cout << "Sort Menu" << endl;
      cout << string(80, '=') << endl;
      cout << "1. Bubble sort" << endl;
      cout << "2. Selection sort" << endl;
      cout << "0. Back" << endl;
      cout << "Selection: ";
      cin >> sortChoice;

      if (sortChoice == 1 || sortChoice == 2) {
        cout << "Sort field (age / stay / cost): ";
        cin >> field;
      }

      if (sortChoice == 1) {
        cout << string(30, '*') << endl;
        cout << "Array Bubble Sort" << endl;
        cout << string(30, '*') << endl;
        Array::sortByBubble(Array::patientList, field, Array::patientCount);
        cout << string(30, '*') << endl;
        cout << "Linked List Bubble Sort" << endl;
        cout << string(30, '*') << endl;
        LinkedList::sortByBubble(LinkedList::patientNode, field);
      } else if (sortChoice == 2) {
//         cout << "Linked List Selection Sort" << endl;
//         LinkedList::sortBySelection(LinkedList::patientNode, field);
// 
//         cout << "Array Selection Sort" << endl;
//         Array::sortBySelection(Array::patientList, field, Array::patientCount);
//         cout << endl;
//         cout << endl;
        cout << string(30, '*') << endl;
        cout << "Array Selection Sort" << endl;
        cout << string(30, '*') << endl;
        Array::sortBySelection(Array::patientList, field, Array::patientCount);
        cout << string(30, '*') << endl;
        cout << "Linked List Selection Sort" << endl;
        cout << string(30, '*') << endl;
        LinkedList::sortBySelection(LinkedList::patientNode, field);
      }
    } else if (choice == 5) {
      double total = 0.0;
      for (int i = 0; i < 200; i++) {
        total += Array::totalMedicalCost(tempList1[i]);
      }
      cout << "The total medical cost for dataset 1: " << total << endl;

      total = 0;
      for (int i = 0; i < 200; i++) {
        total += Array::totalMedicalCost(tempList2[i]);
      }
      cout << "The total medical cost for dataset 2: " << total << endl;

      total = 0;
      for (int i = 0; i < 200; i++) {
        total += Array::totalMedicalCost(tempList3[i]);
      }
      cout << "The total medical cost for dataset 3: " << total << endl;
    } else if (choice == 6) {
      cout << "Must run option 5 to get result" << endl;
      Array::compareExpenditureAndVisitDuration(tempList1, 200, "Dataset 1");
      Array::compareExpenditureAndVisitDuration(tempList2, 200, "Dataset 2");
      Array::compareExpenditureAndVisitDuration(tempList3, 200, "Dataset 3");
    } else if (choice == 7) {
      Array::sortIntoCategory(Array::patientList);

      Array::mostPreferredCareType(Array::category1, Array::category1Count);
      Array::mostPreferredCareType(Array::category2, Array::category2Count);
      Array::mostPreferredCareType(Array::category3, Array::category3Count);
      Array::mostPreferredCareType(Array::category4, Array::category4Count);
      Array::mostPreferredCareType(Array::category5, Array::category5Count);
    } else if (choice == 8) {
      LinkedList::sortIntoCategory(LinkedList::patientNode);
      LinkedList::mostPreferredCareType(LinkedList::category1);
      LinkedList::mostPreferredCareType(LinkedList::category2);
      LinkedList::mostPreferredCareType(LinkedList::category3);
      LinkedList::mostPreferredCareType(LinkedList::category4);
      LinkedList::mostPreferredCareType(LinkedList::category5);
    } else if (choice == 9) {
      int category;
      int visitDuration;
      float maxCost;

      cout << "Category: ";
      cin >> category;
      cout << "Minimum visit duration: ";
      cin >> visitDuration;
      cout << "Maximum total medical cost: ";
      cin >> maxCost;

      cout << string(30, '-') << endl;
      cout << "Searching on Sorted List" << endl;
      cout << string(30, '-') << endl;
      Array::searchUsingLinear(Array::patientList, category, visitDuration,
                               maxCost);
      LinkedList::searchUsingLinear(LinkedList::patientNode, category,
                                    visitDuration, maxCost);
      cout << endl << endl;

      cout << string(30, '-') << endl;
      cout << "Searching on unsorted List" << endl;
      cout << string(30, '-') << endl;
      Array::searchUsingLinear(Array::unsortedPatientList, category,
                               visitDuration, maxCost);
      LinkedList::searchUsingLinear(LinkedList::unsortedPatientNode, category,
                                    visitDuration, maxCost);
      cout << endl << endl;
    } else if (choice == 10) {
      string fieldToSearch;
      double value;

      cout << "Search field (age / visitDuration): ";
      cin >> fieldToSearch;

      cout << "Value: ";
      cin >> value;

      cout << string(30, '-') << endl;
      cout << "Searching on Sorted List" << endl;
      cout << string(30, '-') << endl;

      Array::searchUsingBinary(Array::patientList, fieldToSearch, value);
      LinkedList::searchUsingBinary(LinkedList::patientNode, fieldToSearch,
                                    value);

      cout << endl << endl;
    } else if (choice == 11) {
      Array::identifyHighestBillingAndTraffic(Array::patientList,
                                              Array::patientCount);
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
