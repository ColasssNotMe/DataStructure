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
PatientNode *patientNode1;
PatientNode *patientNode2;
PatientNode *patientNode3;

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

// FIXME: remove this later
void tempPrintNode(PatientNode *patientNode) {

  cout << left << setw(12) << "Patient ID" << setw(8) << "Age" << setw(15)
       << "Care Type" << setw(15) << "Stay" << setw(15) << "Cost/Hour"
       << setw(15) << "Visits/Year" << endl;

  cout << string(80, '-') << endl;

  PatientNode *current = patientNode;

  while (current != nullptr) {
    cout << left << setw(12) << current->patient.PatientID << setw(8)
         << current->patient.age << setw(15) << current->patient.careType
         << setw(15) << current->patient.lengthOfStay << setw(15)
         << current->patient.baseCostPerHour << setw(15)
         << current->patient.daysVisitsPerYear << endl;

    current = current->nextPatient;
  }
}

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

void sortIntoCategory(PatientNode *&head) {
  PatientNode *current = nullptr;
  PatientNode *nextHead = nullptr;

  if (head == nullptr) {
    cerr << "Unable to sort into category: Node empty" << endl;
  }
  current = head;
  while (current != nullptr) {
    // to not lose the head ptr after sorting the current head
    nextHead = current->nextPatient;
    // remove the old next patient so it doesnt connect to 2 node
    current->nextPatient = nullptr;

    if (current->patient.age == 0) {
      return;
    } else if (current->patient.age <= 17) {
      insertToEnd(category1, current);
      // cout << "pass 1" << endl;
    } else if (current->patient.age <= 25) {
      insertToEnd(category2, current);
      // cout << "pass 2" << endl;
    } else if (current->patient.age <= 45) {
      insertToEnd(category3, current);
      // cout << "pass 3" << endl;
    } else if (current->patient.age <= 60) {
      insertToEnd(category4, current);
      // cout << "pass 4" << endl;
    } else if (current->patient.age <= 100) {
      insertToEnd(category5, current);
      // cout << "pass 5" << endl;
    }
    current = nextHead;
  }
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
  cout << left << setw(15) << "Care Type" << setw(15) << "Patient Count"
       << setw(15) << "Total Cost ($)" << setw(15)
       << "Average Cost per Patient ($)" << endl;

  cout << string(80, '-') << endl;

  int totalBillingForAgeGroup = 0;
  if (vaccineCounter != 0) {
    cout << left << setw(15) << "Vaccination" << setw(15) << vaccineCounter
         << setw(15) << totalMedicalCostVaccine << setw(15) << vacAvg << endl;
    totalBillingForAgeGroup += totalMedicalCostVaccine;
  }
  if (rehabCounter != 0) {
    cout << left << setw(15) << "Rehabilitation" << setw(15) << rehabCounter
         << setw(15) << totalMedicalCostRehab << setw(15) << rehabAvg << endl;
    totalBillingForAgeGroup += totalMedicalCostRehab;
  }
  if (routineCounter != 0) {
    cout << left << setw(15) << "Routine Checkup" << setw(15) << routineCounter
         << setw(15) << totalMedicalCostRoutine << setw(15) << routineAvg
         << endl;
    totalBillingForAgeGroup += totalMedicalCostRoutine;
  }
  if (emergencyCounter != 0) {
    cout << left << setw(15) << "Emergency" << setw(15) << emergencyCounter
         << setw(15) << totalMedicalCostEmergency << setw(15) << emergencyAvg
         << endl;
    totalBillingForAgeGroup += totalMedicalCostEmergency;
  }
  if (outpatientCounter != 0) {
    cout << left << setw(15) << "Outpatient" << setw(15) << outpatientCounter
         << setw(15) << totalMedicalCostOutpatient << setw(15) << outAvg
         << endl;
    totalBillingForAgeGroup += totalMedicalCostOutpatient;
  }
  if (inpatientCounter != 0) {
    cout << left << setw(15) << "Inpatient" << setw(15) << inpatientCounter
         << setw(15) << totalMedicalCostInpatient << setw(15) << inAvg << endl;
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
}

int main() {
  readFromDataset(
      "/home/azuki/Documents/Sem2/DSTR/Part 1/dataset1 facility_a.csv",
      patientNode1);

  sortIntoCategory(patientNode1);

  mostPreferredCareType(category4);

  tempPrintNode(category4);
  cout << endl;
  cout << endl;
  cout << endl;
  cout << "Sort bubble" << endl;
  sortByBubble(category4, "age");

  tempPrintNode(category4);
}
