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

class CareType {
public:
  string typeOfTreatment;
  int totalMedicalCost;
  float average;
};

const int MAX_PATIENTS = 200;

Patient patientList1[MAX_PATIENTS];
Patient patientList2[MAX_PATIENTS];
Patient patientList3[MAX_PATIENTS];

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
      cout << "pass 1" << endl;
    } else if (toBeSortList[i].age <= 25) {
      category2[category2Count] = toBeSortList[i];
      category2Count++;
      cout << "pass 2" << endl;
    } else if (toBeSortList[i].age <= 45) {
      category3[category3Count] = toBeSortList[i];
      category3Count++;
      cout << "pass 3" << endl;
    } else if (toBeSortList[i].age <= 60) {
      category4[category4Count] = toBeSortList[i];
      category4Count++;
      cout << "pass 4" << category4[category4Count - 1].age << endl;
    } else if (toBeSortList[i].age <= 100) {
      category5[category5Count] = toBeSortList[i];
      category5Count++;
      cout << "pass 5" << endl;
    }
  }
}

// FIX: maybe need to create 6 type *3 dataset =18 new caretype variable
// CareType *dataset1Vaccination = new CareType();

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

  // Print the result
  cout << left << setw(15) << "Care Type" << setw(15) << "Patient Count"
       << setw(15) << "Total Cost ($)" << setw(15)
       << "Average Cost per Patient ($)" << endl;

  cout << string(80, '-') << endl;

  // TODO: havent done, prob need to sort based on patient count
  int totalBillingForAgeGroup = 0;
  if (vaccineCounter != 0) {
    cout << left << setw(15) << "Vaccination" << setw(15) << vaccineCounter
         << setw(15) << totalMedicalCostVaccine << setw(15) << vacAvg << endl;
  }
  if (rehabCounter != 0) {
    cout << left << setw(15) << "Rehabilitation" << setw(15) << rehabCounter
         << setw(15) << totalMedicalCostRehab << setw(15) << rehabAvg << endl;
  }
}

int main() {
  readFromDataset(
      "/home/azuki/Documents/Sem2/DSTR/Part 1/dataset1 facility_a.csv",
      patientList1);

  cout << "Categorised 1" << endl;
  sortIntoCategory(patientList1);
  tempPrintArr(category3);
}
