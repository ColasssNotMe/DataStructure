#include "iostream"
#include <fstream>
#include <iomanip>
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

// Dataset 1
const int MAX_PATIENTS = 200;
Patient patientList1[MAX_PATIENTS];
Patient patientList2[MAX_PATIENTS];
Patient patientList3[MAX_PATIENTS];

class PatientNode {
public:
  PatientNode(Patient patientParam) { patient = patientParam; }
  Patient patient;
  PatientNode *nextPatient;
};

// Use this to read data into array
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

  while (getline(file, line)) {
    // Read up to ,
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

void sortDataset1() {}

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

void tempPrintArr(Patient arr[]) {
  cout << left << setw(12) << "Patient ID" << setw(8) << "Age" << setw(15)
       << "Care Type" << setw(15) << "Stay" << setw(15) << "Cost/Hour"
       << setw(15) << "Visits/Year" << endl;

  cout << string(80, '-') << endl;

  for (int i = 0; i < MAX_PATIENTS; i++) {
    cout << left << setw(12) << arr[i].PatientID << setw(8) << arr[i].age
         << setw(15) << arr[i].careType << setw(15) << arr[i].lengthOfStay
         << setw(15) << arr[i].baseCostPerHour << setw(15)
         << arr[i].daysVisitsPerYear << endl;
  }
}

int main() {
  readFromDataset(
      "/home/azuki/Documents/Sem2/DSTR/Part 1/dataset1 facility_a.csv",
      patientList1);

  PatientNode *linkedList1 = convertToLinkedList(patientList1);
  tempPrintNode(linkedList1);
  // tempPrintArr(patientList1);
}
