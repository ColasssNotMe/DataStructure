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
Patient patientList1[MAX_PATIENTS];
Patient patientList2[MAX_PATIENTS];
Patient patientList3[MAX_PATIENTS];

void readFromDataset(string fileName, Patient patient[]) {

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

    stringstream ss(line);
    string token;

    getline(ss, token, ',');
    patient[lineCount].PatientID = token;

    getline(ss, token, ',');
    patient[lineCount].age = stoi(token);

    getline(ss, token, ',');
    patient[lineCount].careType = token;

    getline(ss, token, ',');
    patient[lineCount].lengthOfStay = stoi(token);

    getline(ss, token, ',');
    patient[lineCount].baseCostPerHour = stoi(token);

    getline(ss, token, ',');
    patient[lineCount].daysVisitsPerYear = stoi(token);

    lineCount++;
  }

  file.close();
}

PatientNode *convertToLinkedList(Patient patient[]) {
  PatientNode *head = nullptr;
  PatientNode *next = nullptr;
  for (int i = 0; i < MAX_PATIENTS; i++) {
    PatientNode *temp = new PatientNode(patient[i]);
    if (head == nullptr) {
      head = temp;
      next = temp;
    } else {
      next->nextPatient = temp;
      next = temp;
    }
  }
  return head;
}

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
void addToList(PatientNode *&head, Patient patient) {
  PatientNode *newNode = new PatientNode(patient);

  if (head == nullptr) {
    head = newNode;
    return;
  }

  PatientNode *current = head;

  while (current->nextPatient != nullptr) {
    current = current->nextPatient;
  }

  current->nextPatient = newNode;
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

// FIXME: uncomplete linked list implementation
void sortIntoCategory(Patient toBeSortList[]) {
  PatientNode *temp = nullptr;
  for (int i = 0; i < MAX_PATIENTS; i++) {
    if (toBeSortList[i].age == 0) {
      return;
    } else if (toBeSortList[i].age <= 17) {
      addToList(category1, toBeSortList[i]);
      cout << "pass 1" << endl;
    } else if (toBeSortList[i].age <= 25) {
      addToList(category2, toBeSortList[i]);
      cout << "pass 2" << endl;
    } else if (toBeSortList[i].age <= 45) {
      addToList(category3, toBeSortList[i]);
      cout << "pass 3" << endl;
    } else if (toBeSortList[i].age <= 60) {
      addToList(category4, toBeSortList[i]);
      cout << "pass 4" << endl;
    } else if (toBeSortList[i].age <= 100) {
      addToList(category5, toBeSortList[i]);
      cout << "pass 5" << endl;
    }
  }
}

// FIXME: change from array to linkedlist
void mostPreferredCareType(Patient array[], int totalNumberOfPatient) {
  int vaccineCounter, rehabCounter, emergencyCounter, outpatientCounter,
      inpatientCounter, routineCounter;
  int totalMedicalCostVaccine, totalMedicalCostRehab, totalMedicalCostEmergency,
      totalMedicalCostOutpatient, totalMedicalCostInpatient,
      totalMedicalCostRoutine;
  int vacAvg, rehabAvg, routineAvg, emergencyAvg, outAvg, inAvg;
  for (int i = 0; i < totalNumberOfPatient; i++) {
    if (stoi(array[i].PatientID) == 0) {
      return;
    } else {
      int lengthOfStay = array[i].lengthOfStay;
      int baseCostPerHour = array[i].baseCostPerHour;
      int daysVisitsPerYear = array[i].daysVisitsPerYear;

      // Count the total medical cost and print out the table
      if (array[i].careType == "Vaccination") {
        int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
        vaccineCounter++;
        totalMedicalCostVaccine +=
            lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      } else if (array[i].careType == "Rehabilitation") {
        int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
        rehabCounter++;
        totalMedicalCostRehab +=
            lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      } else if (array[i].careType == "Routine Checkup") {
        int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
        routineCounter++;
        totalMedicalCostRoutine +=
            lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      } else if (array[i].careType == "Emergency") {
        int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
        emergencyCounter++;
        totalMedicalCostEmergency +=
            lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      } else if (array[i].careType == "Outpatient") {
        int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
        outpatientCounter++;
        totalMedicalCostOutpatient +=
            lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      } else if (array[i].careType == "Inpatient") {
        int totalCost = lengthOfStay * baseCostPerHour * daysVisitsPerYear;
        inpatientCounter++;
        totalMedicalCostInpatient +=
            lengthOfStay * baseCostPerHour * daysVisitsPerYear;
      } else {
        cout << "Unknown care type: " << array[i].careType << endl;
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
    }
  }
}
int main() {
  readFromDataset(
      "/home/azuki/Documents/Sem2/DSTR/Part 1/dataset1 facility_a.csv",
      patientList1);

  sortIntoCategory(patientList1);

  tempPrintNode(category3);
}
