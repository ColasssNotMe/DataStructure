#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Patient {
public:
  string PatientID;
  int age;
  string careType;
  int lengthOfStay;
  int baseCostPerHour;
  int daysVisitsPerYear;
};

const int MAX_PATIENTS = 200;
Patient patientList1[MAX_PATIENTS];
Patient patientList2[MAX_PATIENTS];
Patient patientList3[MAX_PATIENTS];

class PatientNode {
public:
  PatientNode(Patient patientParam) {
    patient = patientParam;
    nextPatient = nullptr;
  }

  Patient patient;
  PatientNode *nextPatient;
};

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

int main() {
  readFromDataset(
      "/home/azuki/Documents/Sem2/DSTR/Part 1/dataset1 facility_a.csv",
      patientList1);
}
