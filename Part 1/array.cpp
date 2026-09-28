#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

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

Patient patientList[MAX_PATIENTS];

// helper function
double totalMedicalCost(Patient patient) {
  return patient.lengthOfStay * patient.baseCostPerHour *
         patient.daysVisitsPerYear;
}

void readFromDataset(string fileName, Patient patientListToBeAppend[]) {
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
    patientListToBeAppend[lineCount].PatientID = token;
    getline(ss, token, ',');
    patientListToBeAppend[lineCount].age = stoi(token);
    getline(ss, token, ',');
    patientListToBeAppend[lineCount].careType = token;
    getline(ss, token, ',');
    patientListToBeAppend[lineCount].lengthOfStay = stoi(token);
    getline(ss, token, ',');
    patientListToBeAppend[lineCount].baseCostPerHour = stoi(token);
    getline(ss, token, ',');
    patientListToBeAppend[lineCount].daysVisitsPerYear = stoi(token);
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
// end of helper section

//  0–17: Pediatrics & Adolescents
//  18–25: Young Adults / University Students
//  26–45: Working Adults (Early Career)
//  46–60: Working Adults (Late Career)
//  61–100: Senior Citizens / Geriatric Care
Patient category1[200];
Patient category2[200];
Patient category3[200];
Patient category4[200];
Patient category5[200];

int category1Count = 0;
int category2Count = 0;
int category3Count = 0;
int category4Count = 0;
int category5Count = 0;

void sortIntoCategory(Patient toBeSortList[]) {
  for (int i = 0; i < MAX_PATIENTS; i++) {
    if (toBeSortList[i].age == 0) {
      return;
    } else if (toBeSortList[i].age <= 17) {
      category1[category1Count] = toBeSortList[i];
      category1Count++;
    } else if (toBeSortList[i].age <= 25) {
      category2[category2Count] = toBeSortList[i];
      category2Count++;
    } else if (toBeSortList[i].age <= 45) {
      category3[category3Count] = toBeSortList[i];
      category3Count++;
    } else if (toBeSortList[i].age <= 60) {
      category4[category4Count] = toBeSortList[i];
      category4Count++;
    } else if (toBeSortList[i].age <= 100) {
      category5[category5Count] = toBeSortList[i];
      category5Count++;
    }
  }
}

void mostPreferredCareType(Patient array[], int totalNumberOfPatient) {
  int vaccineCounter = 0, rehabCounter = 0, emergencyCounter = 0,
      outpatientCounter = 0, inpatientCounter = 0, routineCounter = 0;
  int totalMedicalCostVaccine = 0, totalMedicalCostRehab = 0,
      totalMedicalCostEmergency = 0, totalMedicalCostOutpatient = 0,
      totalMedicalCostInpatient = 0, totalMedicalCostRoutine = 0;
  int vacAvg = 0, rehabAvg = 0, routineAvg = 0, emergencyAvg = 0, outAvg = 0,
      inAvg = 0;
  for (int i = 0; i < totalNumberOfPatient; i++) {
    if (array[i].PatientID == "") {
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

void sortByBubble(Patient patientList[], string fieldToBeCompare,
                  int patientCount) {
  for (int i = 0; i < patientCount - 1; i++) {
    bool swapped = false;

    for (int j = 0; j < patientCount - 2 - i; j++) {
      if (fieldToBeCompare == "age") {
        if (patientList[j].age > patientList[j + 1].age) {
          swap(patientList[j], patientList[j + 1]);
          swapped = true;
        }
      }

      if (fieldToBeCompare == "lengthOfStay") {
        if (patientList[j].lengthOfStay > patientList[j + 1].lengthOfStay) {
          swap(patientList[j], patientList[j + 1]);
          swapped = true;
        }
      }

      if (fieldToBeCompare == "totalMedicalCost") {
        if (totalMedicalCost(patientList[j]) >
            totalMedicalCost(patientList[j + 1])) {
          swap(patientList[j], patientList[j + 1]);
          swapped = true;
        }
      }
    }

    if (not swapped) {
      return;
    }
  }
}

int main() {

  string selection = "";

  // ----Start of menu---
  cout << string(80, '=') << endl;
  cout << "Please enter absolute path, or input 1,2 or 3" << endl;
  cout << "1. Dataset 1" << endl;
  cout << "2. Dataset 2" << endl;
  cout << "3. Dataset 3" << endl;

  cin >> selection;

  if (selection == "1") {
    readFromDataset("dataset1 facility_a.csv", patientList);
  } else if (selection == "2") {
    readFromDataset("dataset2 facility_a.csv", patientList);
  } else if (selection == "3") {
    readFromDataset("dataset3 facility_a.csv", patientList);
  } else {
    readFromDataset(selection, patientList);
  }

  // ---End of menu---

  cout << string(80, '=') << endl;
  cout << "Categorizing..." << endl << endl;
  sortIntoCategory(patientList);

  cout << string(80, '-') << endl;
  cout << "Category 1" << endl;
  cout << string(80, '-') << endl;
  mostPreferredCareType(category1, category1Count);
  cout << endl << endl;
  cout << string(80, '-') << endl;
  cout << "Category 2" << endl;
  cout << string(80, '-') << endl;
  mostPreferredCareType(category2, category2Count);
  cout << endl << endl;
  cout << string(80, '-') << endl;
  cout << "Category 3" << endl;
  cout << string(80, '-') << endl;
  mostPreferredCareType(category3, category3Count);
  cout << endl << endl;
  cout << string(80, '-') << endl;
  cout << "Category 4" << endl;
  cout << string(80, '-') << endl;
  mostPreferredCareType(category4, category4Count);
  cout << endl << endl;
  cout << string(80, '-') << endl;
  cout << "Category 5" << endl;
  cout << string(80, '-') << endl;
  mostPreferredCareType(category5, category5Count);
  cout << endl << endl;

  // --Start of menu--
  string sortSelection = "";
  string categorySelection = "";
  string fieldSelection = "";

  Patient *category = nullptr;
  int categoryCount = 0;
  string field = "";

  do {
    cout << string(80, '=') << endl;
    cout << "Select sorting algorithm" << endl;
    cout << "1. Bubble Sort" << endl;
    // cout << "2. -" << endl;
    cin >> sortSelection;
  } while (sortSelection == "" &&
           (sortSelection != "1" || sortSelection != "2"));

  cout << string(80, '-') << endl;

  do {
    cout << string(80, '=') << endl;
    cout << "Select category to be sorted" << endl;
    cout << "1. Category 1" << endl;
    cout << "2. Category 2" << endl;
    cout << "3. Category 3" << endl;
    cout << "4. Category 4" << endl;
    cout << "5. Category 5" << endl;
    cin >> categorySelection;
  } while (categorySelection == "" &&
           (categorySelection != "1" || categorySelection != "2" ||
            categorySelection != "3" || categorySelection != "4" ||
            categorySelection != "5"));

  cout << string(80, '-') << endl;
  if (categorySelection == "1") {
    category = category1;
    categoryCount = category1Count;
  } else if (categorySelection == "2") {
    category = category2;
    categoryCount = category2Count;
  } else if (categorySelection == "3") {
    category = category3;
    categoryCount = category3Count;
  } else if (categorySelection == "4") {
    category = category4;
    categoryCount = category4Count;
  } else if (categorySelection == "5") {
    category = category5;
    categoryCount = category5Count;
  }

  do {
    cout << string(80, '=') << endl;
    cout << "Select field to be sorted" << endl;
    cout << "1. Age" << endl;
    cout << "2. Visit Duration (Length of Stay)" << endl;
    cout << "3. Total Medical Cost" << endl;
    cin >> fieldSelection;
  } while (fieldSelection == "" &&
           (fieldSelection != "1" || fieldSelection != "2" ||
            fieldSelection != "3"));

  if (fieldSelection == "1") {
    field = "age";
  } else if (fieldSelection == "2") {
    field = "lengthOfStay";
  } else if (fieldSelection == "3") {
    field = "totalMedicalCost";
  }

  if (sortSelection == "1") {
    sortByBubble(category, field, categoryCount);
    tempPrintArr(category);
    cout << string(80, '-') << endl;
  } else if (selection == "2") {
    // TODO: add sorting algo here
  }

  cout << string(80, '-') << endl;
  // ---End of menu---
}
