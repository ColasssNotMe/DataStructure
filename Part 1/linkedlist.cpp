#include "linkedlist.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Class
class Patient {
public:
  string PatientID;
  int age;
  string careType;
  int lengthOfStay;
  int baseCostPerHour;
  int daysVisitsPerYear;
  double totalMedicalCost;
};

class PatientNode {
public:
  PatientNode(Patient patientParam) {
    patient = patientParam;
    nextPatient = nullptr;
  }
  Patient patient;
  PatientNode *nextPatient;
};

const int MAX_PATIENTS = 200;
const int MAX_PATIENTS_ALL_DATASET = 600;

PatientNode *patientNode = nullptr;
PatientNode *unsortedPatientNode = nullptr;
PatientNode *searchResult = nullptr;

string datasetFileName = "";

//  0–17: Pediatrics & Adolescents
//  18–25: Young Adults / University Students
//  26–45: Working Adults (Early Career)
//  46–60: Working Adults (Late Career)
//  61–100: Senior Citizens / Geriatric Care
PatientNode *category1 = nullptr;
PatientNode *category2 = nullptr;
PatientNode *category3 = nullptr;
PatientNode *category4 = nullptr;
PatientNode *category5 = nullptr;

// helper function

void insertToEnd(PatientNode *&head, Patient patient) {
  PatientNode *newNode = new PatientNode(patient);

  if (head == nullptr) {
    head = newNode;
    return;
  }

  PatientNode *current = head;

  // if current node have nextPatient
  while (current->nextPatient != nullptr) {
    // switch current node to next node
    current = current->nextPatient;
  }

  // make the newly created node.nextpatient to become the patient to be insert
  current->nextPatient = newNode;
}

// different param same function
void insertToEnd(PatientNode *&head, PatientNode *&patient) {
  patient->nextPatient = nullptr;

  if (head == nullptr) {
    head = patient;
    return;
  }

  PatientNode *current = head;

  // if current node have nextPatient
  while (current->nextPatient != nullptr) {
    // switch current node to next node
    current = current->nextPatient;
  }

  // make the newly created node.nextpatient to become the patient to be insert
  current->nextPatient = patient;
}

void readFromDataset(string fileName, PatientNode *&head) {
  ifstream file(fileName);
  if (!file.is_open()) {
    cerr << "Error: Could not open the file " << fileName << endl;
    return;
  }
  string line;
  int lineCount = 0;
  // Remove header row
  getline(file, line);

  while (getline(file, line) && lineCount < MAX_PATIENTS) {
    Patient tempPatient;

    stringstream ss(line);
    string token;

    getline(ss, token, ',');
    tempPatient.PatientID = token;

    getline(ss, token, ',');
    tempPatient.age = stoi(token);

    getline(ss, token, ',');
    tempPatient.careType = token;

    getline(ss, token, ',');
    tempPatient.lengthOfStay = stoi(token);

    getline(ss, token, ',');
    tempPatient.baseCostPerHour = stoi(token);

    getline(ss, token, ',');
    tempPatient.daysVisitsPerYear = stoi(token);

    insertToEnd(head, tempPatient);

    lineCount++;
  }

  file.close();
}

void freeList(PatientNode *&head) {
  while (head != nullptr) {
    PatientNode *next = head->nextPatient;
    delete head;
    head = next;
  }
}

int countNodes(PatientNode *head) {
  int count = 0;

  PatientNode *current = head;

  while (current != nullptr) {
    count++;
    current = current->nextPatient;
  }

  return count;
}

double totalMedicalCostArray(Patient patient) {
  return patient.lengthOfStay * patient.baseCostPerHour *
         patient.daysVisitsPerYear;
}

double totalMedicalCost(PatientNode *&patient) {
  return patient->patient.lengthOfStay * patient->patient.baseCostPerHour *
         patient->patient.daysVisitsPerYear;
}

// ---end of helper function---

void tempPrintNode(PatientNode *patientNode) {

  cout << left << setw(12) << "Patient ID" << setw(8) << "Age" << setw(20)
       << "Care Type" << setw(20) << "Stay" << setw(20) << "Cost/Hour"
       << setw(20) << "Visits/Year" << endl;

  cout << string(80, '-') << endl;

  PatientNode *current = patientNode;

  while (current != nullptr) {
    cout << left << setw(12) << current->patient.PatientID << setw(8)
         << current->patient.age << setw(20) << current->patient.careType
         << setw(20) << current->patient.lengthOfStay << setw(20)
         << current->patient.baseCostPerHour << setw(20)
         << current->patient.daysVisitsPerYear << endl;

    current = current->nextPatient;
  }
}

void sortIntoCategory(PatientNode *&head) {
  PatientNode *current = nullptr;
  PatientNode *nextHead = nullptr;

  if (head == nullptr) {
    cerr << "Unable to sort into category: Node empty" << endl;
    return;
  }
  current = head;
  while (current != nullptr) {
    // to not lose the head ptr after sorting the current head
    nextHead = current->nextPatient;
    // remove the old next patient so it doesnt connect to 2 node
    current->nextPatient = nullptr;

    if (current->patient.age <= 17) {
      insertToEnd(category1, current);
    } else if (current->patient.age <= 25) {
      insertToEnd(category2, current);
    } else if (current->patient.age <= 45) {
      insertToEnd(category3, current);
    } else if (current->patient.age <= 60) {
      insertToEnd(category4, current);
    } else if (current->patient.age <= 100) {
      insertToEnd(category5, current);
    }
    current = nextHead;
  }

  head = nullptr;

  cout << "Sort into category done" << endl;
}

// TODO: verify implementation
void mostPreferredCareType(PatientNode *&head) {
  int vaccineCounter = 0, rehabCounter = 0, emergencyCounter = 0,
      outpatientCounter = 0, inpatientCounter = 0, routineCounter = 0;
  int totalMedicalCostVaccine = 0, totalMedicalCostRehab = 0,
      totalMedicalCostEmergency = 0, totalMedicalCostOutpatient = 0,
      totalMedicalCostInpatient = 0, totalMedicalCostRoutine = 0;
  int vacAvg = 0, rehabAvg = 0, routineAvg = 0, emergencyAvg = 0, outAvg = 0,
      inAvg = 0;

  if (head == nullptr) {
    cerr << "Unable to execute mostPreferredCareType: head is null" << endl;
    return;
  }

  PatientNode *current = head;
  while (current != nullptr) {
    int lengthOfStay = current->patient.lengthOfStay;
    int baseCostPerHour = current->patient.baseCostPerHour;
    int daysVisitsPerYear = current->patient.daysVisitsPerYear;

    // Count the total medical cost and print out the table
    if (current->patient.careType == "Vaccination") {
      int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      vaccineCounter++;
      totalMedicalCostVaccine +=
          lengthOfStay * baseCostPerHour * daysVisitsPerYear;
    } else if (current->patient.careType == "Rehabilitation") {
      int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      rehabCounter++;
      totalMedicalCostRehab +=
          lengthOfStay * baseCostPerHour * daysVisitsPerYear;
    } else if (current->patient.careType == "Routine Checkup") {
      int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      routineCounter++;
      totalMedicalCostRoutine +=
          lengthOfStay * baseCostPerHour * daysVisitsPerYear;
    } else if (current->patient.careType == "Emergency") {
      int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      emergencyCounter++;
      totalMedicalCostEmergency +=
          lengthOfStay * baseCostPerHour * daysVisitsPerYear;
    } else if (current->patient.careType == "Outpatient") {
      int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      outpatientCounter++;
      totalMedicalCostOutpatient +=
          lengthOfStay * baseCostPerHour * daysVisitsPerYear;
    } else if (current->patient.careType == "Inpatient") {
      int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      inpatientCounter++;
      totalMedicalCostInpatient +=
          lengthOfStay * baseCostPerHour * daysVisitsPerYear;
    } else {
      cout << "Unknown care type: " << current->patient.careType << endl;
    }
    current = current->nextPatient;
  }

  // Check which care type >0 and calculate avg
  if (vaccineCounter) {
    vacAvg = totalMedicalCostVaccine / vaccineCounter;
  }
  if (rehabCounter) {
    rehabAvg = totalMedicalCostRehab / rehabCounter;
  }
  if (routineCounter) {
    routineAvg = totalMedicalCostRoutine / routineCounter;
  }
  if (emergencyCounter) {
    emergencyAvg = totalMedicalCostEmergency / emergencyCounter;
  }
  if (outpatientCounter) {
    outAvg = totalMedicalCostOutpatient / outpatientCounter;
  }
  if (inpatientCounter) {
    inAvg = totalMedicalCostInpatient / inpatientCounter;
  }

  // Print the result
  cout << left << setw(20) << "Care Type" << setw(20) << "Patient Count"
       << setw(20) << "Total Cost ($)" << setw(20)
       << "Average Cost per Patient ($)" << endl;

  cout << string(80, '-') << endl;

  int totalBillingForAgeGroup = 0;
  if (vaccineCounter != 0) {
    cout << left << setw(20) << "Vaccination" << setw(20) << vaccineCounter
         << setw(20) << totalMedicalCostVaccine << setw(20) << vacAvg << endl;
    totalBillingForAgeGroup += totalMedicalCostVaccine;
  }
  if (rehabCounter != 0) {
    cout << left << setw(20) << "Rehabilitation" << setw(20) << rehabCounter
         << setw(20) << totalMedicalCostRehab << setw(20) << rehabAvg << endl;
    totalBillingForAgeGroup += totalMedicalCostRehab;
  }
  if (routineCounter != 0) {
    cout << left << setw(20) << "Routine Checkup" << setw(20) << routineCounter
         << setw(20) << totalMedicalCostRoutine << setw(20) << routineAvg
         << endl;
    totalBillingForAgeGroup += totalMedicalCostRoutine;
  }
  if (emergencyCounter != 0) {
    cout << left << setw(20) << "Emergency" << setw(20) << emergencyCounter
         << setw(20) << totalMedicalCostEmergency << setw(20) << emergencyAvg
         << endl;
    totalBillingForAgeGroup += totalMedicalCostEmergency;
  }
  if (outpatientCounter != 0) {
    cout << left << setw(20) << "Outpatient" << setw(20) << outpatientCounter
         << setw(20) << totalMedicalCostOutpatient << setw(20) << outAvg
         << endl;
    totalBillingForAgeGroup += totalMedicalCostOutpatient;
  }
  if (inpatientCounter != 0) {
    cout << left << setw(20) << "Inpatient" << setw(20) << inpatientCounter
         << setw(20) << totalMedicalCostInpatient << setw(20) << inAvg << endl;
    totalBillingForAgeGroup += totalMedicalCostInpatient;
  }
  cout << string(80, '-') << endl;
  cout << "Total Billing for Current Age Group: " << totalBillingForAgeGroup
       << endl;
}

void sortByBubble(PatientNode *&head, string fieldToBeCompare) {
  if (head == nullptr || head->nextPatient == nullptr) {
    cerr << "Unable to execute sortByBubble: "
         << "head is null or next patient is null" << endl;
    return;
  }

  int nodeCount = countNodes(head);

  auto start = chrono::high_resolution_clock::now();
  bool swapped;

  do {
    swapped = false;

    PatientNode *current = head;

    while (current->nextPatient != nullptr) {

      PatientNode *next = current->nextPatient;

      if (fieldToBeCompare == "age") {

        if (current->patient.age > next->patient.age) {
          swap(current->patient, next->patient);
          swapped = true;
        }

      } else if (fieldToBeCompare == "stay") {

        if (current->patient.lengthOfStay > next->patient.lengthOfStay) {

          swap(current->patient, next->patient);
          swapped = true;
        }

      } else if (fieldToBeCompare == "cost") {

        if (current->patient.totalMedicalCost >
            next->patient.totalMedicalCost) {

          swap(current->patient, next->patient);
          swapped = true;
        }
      }

      current = current->nextPatient;
    }

  } while (swapped);

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << string(80, '*') << endl;
  cout << "Sorting took " << duration.count() << " microseconds" << endl;
  size_t linkedListMemory = nodeCount * sizeof(PatientNode);
  cout << "Linked list memory usage: " << linkedListMemory << " bytes" << endl;
  cout << string(80, '*') << endl;
}

void sortBySelection(PatientNode *&head, string fieldToBeCompare) {
  if (head == nullptr || head->nextPatient == nullptr) {
    cerr << "Unable to execute sortBySelection: "
         << "head is null or next patient is null" << endl;
    return;
  }
  int nodeCount = countNodes(head);

  auto start = chrono::high_resolution_clock::now();
  PatientNode *current = head;

  while (current->nextPatient != nullptr) {

    PatientNode *minNode = current;
    PatientNode *scanner = current->nextPatient;

    while (scanner != nullptr) {

      if (fieldToBeCompare == "age") {
        if (scanner->patient.age < minNode->patient.age) {
          minNode = scanner;
        }

      } else if (fieldToBeCompare == "stay") {
        if (scanner->patient.lengthOfStay < minNode->patient.lengthOfStay) {
          minNode = scanner;
        }

      } else if (fieldToBeCompare == "cost") {
        if (scanner->patient.totalMedicalCost <
            minNode->patient.totalMedicalCost) {
          minNode = scanner;
        }
      }

      scanner = scanner->nextPatient;
    }

    if (minNode != current) {
      swap(current->patient, minNode->patient);
    }

    current = current->nextPatient;
  }

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << string(80, '*') << endl;
  cout << "Sorting took " << duration.count() << " microseconds" << endl;
  size_t linkedListMemory = nodeCount * sizeof(PatientNode);
  cout << "Linked list memory usage: " << linkedListMemory << " bytes" << endl;
  cout << string(80, '*') << endl;
}

int searchUsingLinear(PatientNode *&head, int category = 1,
                      int visitDuration = 0, float totalMedicalCost = 0.0) {
  auto start = chrono::high_resolution_clock::now();

  PatientNode *current = nullptr;

  if (head == nullptr) {
    cerr << "The Patient is empty [searchUsingLinear]" << endl;
    return 0;
  }

  freeList(searchResult);

  int counter = 0;
  int minAge = 0;
  int maxAge = 100;

  if (category == 1) {
    minAge = 0;
    maxAge = 17;
  } else if (category == 2) {
    minAge = 18;
    maxAge = 25;
  } else if (category == 3) {
    minAge = 26;
    maxAge = 45;
  } else if (category == 4) {
    minAge = 46;
    maxAge = 60;
  } else if (category == 5) {
    minAge = 61;
    maxAge = 100;
  }

  if (current == nullptr) {
    current = head;
  }

  while (current != nullptr) {
    int calculateMedicalCost = current->patient.lengthOfStay *
                               current->patient.baseCostPerHour *
                               current->patient.daysVisitsPerYear;
    if (current->patient.age >= minAge && current->patient.age <= maxAge &&
        current->patient.lengthOfStay > visitDuration &&
        (totalMedicalCost <= 0 || calculateMedicalCost < totalMedicalCost)) {
      PatientNode *newNode = new PatientNode(current->patient);

      if (searchResult == nullptr) {
        searchResult = newNode;
      } else {
        PatientNode *temp = searchResult;

        while (temp->nextPatient != nullptr) {
          temp = temp->nextPatient;
        }
        temp->nextPatient = newNode;
      }
      counter++;
    }

    current = current->nextPatient;
  }

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << string(80, '*') << endl;
  cout << "Searching took " << duration.count() << " microseconds" << endl;
  size_t linkedListMemory = counter * sizeof(PatientNode);
  cout << "Linked list memory usage: " << linkedListMemory << " bytes" << endl;
  cout << string(80, '*') << endl;

  if (counter > 0) {
    cout << left << setw(12) << "Patient ID" << setw(8) << "Age" << setw(20)
         << "Care Type" << setw(20) << "Stay" << setw(20) << "Cost/Hour"
         << setw(20) << "Visits/Year" << endl;
    cout << string(80, '-') << endl;

    PatientNode *result = searchResult;

    while (result != nullptr) {
      cout << left << setw(12) << result->patient.PatientID << setw(8)
           << result->patient.age << setw(20) << result->patient.careType
           << setw(20) << result->patient.lengthOfStay << setw(20)
           << result->patient.baseCostPerHour << setw(20)
           << result->patient.daysVisitsPerYear << endl;

      result = result->nextPatient;
    }
  }

  return counter;
}

void searchUsingBinary(PatientNode *&head, string fieldToSearch, double value) {
  auto start = chrono::high_resolution_clock::now();
  int counter = 0;

  int nodeCount = 0;
  PatientNode *current = head;

  while (current != nullptr) {
    nodeCount++;
    current = current->nextPatient;
  }

  int low = 0;
  int high = nodeCount - 1;

  Patient tempPatient;

  bool found = false;

  if (fieldToSearch == "age") {
    while (low <= high) {
      int mid = low + (high - low) / 2;

      current = head;

      for (int i = 0; i < mid; i++) {
        current = current->nextPatient;
      }

      if (current->patient.age == value) {
        tempPatient = current->patient;
        found = true;
        counter++;
        break;
      } else if (current->patient.age < value) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
  } else if (fieldToSearch == "visitDuration") {
    while (low <= high) {
      int mid = low + (high - low) / 2;

      current = head;

      for (int i = 0; i < mid; i++) {
        current = current->nextPatient;
      }

      if (current->patient.lengthOfStay == value) {
        tempPatient = current->patient;
        found = true;
        counter++;
        break;
      } else if (current->patient.lengthOfStay < value) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
  }

  if (found == false) {
    cout << "No result from the query" << endl;
  }

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

  cout << string(80, '*') << endl;
  cout << "Searching took " << duration.count() << " microseconds" << endl;
  size_t linkedListMemory = counter * sizeof(PatientNode);
  cout << "Linked list memory usage: " << linkedListMemory << " bytes" << endl;
  cout << string(80, '*') << endl;

  if (counter > 0) {
    cout << left << setw(12) << "Patient ID" << setw(8) << "Age" << setw(20)
         << "Care Type" << setw(20) << "Stay" << setw(20) << "Cost/Hour"
         << setw(20) << "Visits/Year" << endl;

    cout << string(80, '-') << endl;

    cout << left << setw(12) << tempPatient.PatientID << setw(8)
         << tempPatient.age << setw(20) << tempPatient.careType << setw(20)
         << tempPatient.lengthOfStay << setw(20) << tempPatient.baseCostPerHour
         << setw(20) << tempPatient.daysVisitsPerYear << endl;
  }
}
