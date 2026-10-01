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

// remembered so the Search menu can re-load the file for "sorted data"
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

void freeList(PatientNode *&head) {
  while (head != nullptr) {
    PatientNode *next = head->nextPatient;
    delete head;
    head = next;
  }
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

      } else if (fieldToBeCompare == "lengthOfStay") {

        if (current->patient.lengthOfStay > next->patient.lengthOfStay) {

          swap(current->patient, next->patient);
          swapped = true;
        }

      } else if (fieldToBeCompare == "totalMedicalCost") {

        if (totalMedicalCost(current) > totalMedicalCost(next)) {

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
  cout << string(80, '*') << endl;
}

int searchUsingLinear(PatientNode *&head, int category = 1,
                      int visitDuration = 0, float totalMedicalCost = 0.0) {

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
    // TODO: maybe change this to earlier part where the totalmedicalcost is
    // calculated and store it instead of recalculating
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

  return counter;
}

// Menus

void datasetMenu() {
  string selection = "";

  cout << string(80, '=') << endl;
  cout << "Dataset Selection" << endl;
  cout << string(80, '=') << endl;

  cout << "Please enter absolute path, or input 1, 2 or 3" << endl;
  cout << "1. Dataset 1" << endl;
  cout << "2. Dataset 2" << endl;
  cout << "3. Dataset 3" << endl;
  cout << "4. All Dataset" << endl;
  cout << "Selection: ";

  cin >> selection;

  if (selection == "1") {
    datasetFileName = "dataset1_facility_a.csv";
  } else if (selection == "2") {
    datasetFileName = "dataset2_facility_b.csv";
  } else if (selection == "3") {
    datasetFileName = "dataset3_facility_c.csv";
  } else if (selection == "4") {
    readFromDataset("dataset1_facility_a.csv", patientNode);
    readFromDataset("dataset2_facility_b.csv", patientNode);
    readFromDataset("dataset3_facility_c.csv", patientNode);
    readFromDataset("dataset1_facility_a.csv", unsortedPatientNode);
    readFromDataset("dataset2_facility_b.csv", unsortedPatientNode);
    readFromDataset("dataset3_facility_c.csv", unsortedPatientNode);
    return;
  } else {
    datasetFileName = selection;
  }

  readFromDataset(datasetFileName, patientNode);
  readFromDataset(datasetFileName, unsortedPatientNode);
}

void sortMenu() {
  string sortSelection = "";
  string categorySelection = "";
  string fieldSelection = "";
  PatientNode *category = nullptr;
  string field = "";

  cout << endl;
  cout << string(80, '=') << endl;
  cout << "Sorting Menu" << endl;
  cout << string(80, '=') << endl;

  do {
    cout << "Select sorting algorithm" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. -" << endl;
    cout << "Selection: ";

    cin >> sortSelection;
  } while (sortSelection != "1");

  cout << endl;

  do {
    cout << "Select category to be sorted" << endl;
    cout << "1. Category 1" << endl;
    cout << "2. Category 2" << endl;
    cout << "3. Category 3" << endl;
    cout << "4. Category 4" << endl;
    cout << "5. Category 5" << endl;
    cout << "6. All Category" << endl;

    cout << "Selection: ";

    cin >> categorySelection;
  } while (categorySelection != "1" && categorySelection != "2" &&
           categorySelection != "3" && categorySelection != "4" &&
           categorySelection != "5" && categorySelection != "6");

  if (categorySelection == "1") {
    category = category1;
  } else if (categorySelection == "2") {
    category = category2;
  } else if (categorySelection == "3") {
    category = category3;
  } else if (categorySelection == "4") {
    category = category4;
  } else if (categorySelection == "5") {
    category = category5;
  }

  cout << endl;

  do {
    cout << "Select field to be sorted" << endl;
    cout << "1. Age" << endl;
    cout << "2. Visit Duration (Length of Stay)" << endl;
    cout << "3. Total Medical Cost" << endl;
    cout << "Selection: ";

    cin >> fieldSelection;
  } while (fieldSelection != "1" && fieldSelection != "2" &&
           fieldSelection != "3");

  if (fieldSelection == "1") {
    field = "age";
  } else if (fieldSelection == "2") {
    field = "lengthOfStay";
  } else if (fieldSelection == "3") {
    field = "totalMedicalCost";
  }

  cout << endl;
  cout << string(80, '=') << endl;
  cout << "Sorting Result" << endl;
  cout << string(80, '=') << endl;

  if (sortSelection == "1") {
    if (categorySelection == "6") {
      sortByBubble(category1, field);
      sortByBubble(category2, field);
      sortByBubble(category3, field);
      sortByBubble(category4, field);
      sortByBubble(category5, field);
    } else {
      sortByBubble(category, field);
      tempPrintNode(category);
    }
  }
}

void searchMenu() {
  string searchSelection = "";
  do {
    cout << string(80, '=') << endl;
    cout << "Search" << endl;
    cout << string(80, '=') << endl;
    cout << "Select 1 data from below" << endl;
    cout << "1. Unsorted Data" << endl;
    cout << "2. Sorted Data" << endl;
    cout << "Selection: ";
    cin >> searchSelection;
  } while (searchSelection != "1" && searchSelection != "2");

  string searchCategory = "";
  do {
    cout << string(80, '=') << endl;
    cout << "Search" << endl;
    cout << string(80, '=') << endl;
    cout << "Enter age group" << endl;
    cout << "1. Category 1 (0-17)" << endl;
    cout << "2. Category 2 (18-25)" << endl;
    cout << "3. Category 3 (26-45)" << endl;
    cout << "4. Category 4 (46-60)" << endl;
    cout << "5. Category 5 (61-100)" << endl;
    cout << "Selection: ";
    cin >> searchCategory;
  } while (searchCategory != "1" && searchCategory != "2" &&
           searchCategory != "3" && searchCategory != "4" &&
           searchCategory != "5");

  int found = 0;

  if (searchSelection == "1") {
    found = searchUsingLinear(unsortedPatientNode, stoi(searchCategory));
  } else {
    freeList(patientNode);
    readFromDataset(datasetFileName, patientNode);
    sortByBubble(patientNode, "age");
    found = searchUsingLinear(patientNode, stoi(searchCategory));
  }

  cout << "Found " << found << " patient(s)." << endl;
  if (found > 0) {
    tempPrintNode(searchResult);
  }
}

void printMenu() {
  string printSelection = "";
  do {
    cout << string(80, '=') << endl;
    cout << "Print List" << endl;
    cout << string(80, '=') << endl;
    cout << "Select 1 data from below" << endl;
    cout << "1. Unsorted Data" << endl;
    cout << "2. Main Patient List" << endl;
    cout << "3. Category 1" << endl;
    cout << "4. Category 2" << endl;
    cout << "5. Category 3" << endl;
    cout << "6. Category 4" << endl;
    cout << "7. Category 5" << endl;
    cout << "Selection: ";
    cin >> printSelection;
  } while (printSelection != "1" && printSelection != "2" &&
           printSelection != "3" && printSelection != "4" &&
           printSelection != "5" && printSelection != "6" &&
           printSelection != "7");

  if (printSelection == "1") {
    tempPrintNode(unsortedPatientNode);
  } else if (printSelection == "2") {
    tempPrintNode(patientNode);
  } else if (printSelection == "3") {
    tempPrintNode(category1);
  } else if (printSelection == "4") {
    tempPrintNode(category2);
  } else if (printSelection == "5") {
    tempPrintNode(category3);
  } else if (printSelection == "6") {
    tempPrintNode(category4);
  } else if (printSelection == "7") {
    tempPrintNode(category5);
  }
}

void mainMenu() {
  string choice = "";

  do {
    cout << string(80, '=') << endl;
    cout << "Main Menu" << endl;
    cout << string(80, '=') << endl;
    cout << "1. Sort" << endl;
    cout << "2. Search" << endl;
    cout << "3. Print List" << endl;
    cout << "4. Exit" << endl;
    cout << "Selection: ";

    cin >> choice;

    if (choice == "1") {
      sortMenu();
    } else if (choice == "2") {
      searchMenu();
    } else if (choice == "3") {
      printMenu();
    } else if (choice == "4") {
      cout << "Goodbye!" << endl;
    } else {
      cout << "Invalid selection." << endl;
    }
  } while (choice != "4");
}

int main() {
  datasetMenu();

  cout << endl;
  cout << string(80, '=') << endl;
  cout << "Categorizing..." << endl;
  cout << string(80, '=') << endl;

  sortIntoCategory(patientNode);

  cout << endl;
  cout << string(80, '=') << endl;
  cout << "Category 1" << endl;
  cout << string(80, '=') << endl;
  mostPreferredCareType(category1);

  cout << endl;
  cout << string(80, '=') << endl;
  cout << "Category 2" << endl;
  cout << string(80, '=') << endl;
  mostPreferredCareType(category2);

  cout << endl;
  cout << string(80, '=') << endl;
  cout << "Category 3" << endl;
  cout << string(80, '=') << endl;
  mostPreferredCareType(category3);

  cout << endl;
  cout << string(80, '=') << endl;
  cout << "Category 4" << endl;
  cout << string(80, '=') << endl;
  mostPreferredCareType(category4);

  cout << endl;
  cout << string(80, '=') << endl;
  cout << "Category 5" << endl;
  cout << string(80, '=') << endl;
  mostPreferredCareType(category5);

  mainMenu();

  return 0;
}
