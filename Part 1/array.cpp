#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

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

//  0–17: Pediatrics & Adolescents
//  18–25: Young Adults / University Students
//  26–45: Working Adults (Early Career)
//  46–60: Working Adults (Late Career)
//  61–100: Senior Citizens / Geriatric Care
Patient sort1[200];
Patient sort2[200];
Patient sort3[200];
Patient sort4[200];
Patient sort5[200];

void sortIntoCategory(Patient toBeSortList[]) {
  int arr1Index = 0;
  int arr2Index = 0;
  int arr3Index = 0;
  int arr4Index = 0;
  int arr5Index = 0;

  for (int i = 0; i < MAX_PATIENTS; i++) {
    if (toBeSortList[i].age <= 17) {
      sort1[arr1Index] = toBeSortList[i];
      arr1Index++;
    } else if (toBeSortList[i].age <= 25) {
      sort2[arr2Index] = toBeSortList[i];
      arr2Index++;
    } else if (toBeSortList[i].age <= 45) {
      sort3[arr3Index] = toBeSortList[i];
      arr3Index++;
    } else if (toBeSortList[i].age <= 60) {
      sort4[arr4Index] = toBeSortList[i];
      arr4Index++;
    } else if (toBeSortList[i].age <= 100) {
      sort5[arr5Index] = toBeSortList[i];
      arr5Index++;
    }
  }
}

int main() {}
