#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>

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

void readFromDataset(string fileName, Patient patient[]) {

    ifstream file(fileName);

    if (!file.is_open()) {
       cerr << "Error: Could not open the file "
             << fileName << endl;
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