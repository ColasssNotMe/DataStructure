#include <algorithm>
#include <chrono>
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
const int MAX_PATIENT_ALL_DATASET = 600;

Patient patientList[MAX_PATIENT_ALL_DATASET];
Patient unsortedPatientList[MAX_PATIENT_ALL_DATASET];
Patient sortedPatientList[MAX_PATIENT_ALL_DATASET];

int patientCount = 0;

// helper function
double totalMedicalCost(Patient patient) {
  return patient.lengthOfStay * patient.baseCostPerHour *
         patient.daysVisitsPerYear;
}

int readFromDataset(string fileName, Patient patientListToBeAppend[]) {
  ifstream file(fileName);
  if (!file.is_open()) {
    cerr << "Error: Could not open the file " << fileName << endl;
    return 0;
  }

  string line;
  int lineCount = 0;

  // Remove header row
  getline(file, line);

  while (getline(file, line) && lineCount < MAX_PATIENTS) {
    if (line.empty()) {
      continue;
    }

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
  return lineCount;
}

void tempPrintArr(Patient arr[], int count) {
  cout << left << setw(12) << "Patient ID" << setw(8) << "Age" << setw(20)
       << "Care Type" << setw(20) << "Stay" << setw(20) << "Cost/Hour"
       << setw(20) << "Visits/Year" << endl;

  cout << string(80, '-') << endl;

  for (int i = 0; i < count; i++) {
    cout << left << setw(12) << arr[i].PatientID << setw(8) << arr[i].age
         << setw(20) << arr[i].careType << setw(20) << arr[i].lengthOfStay
         << setw(20) << arr[i].baseCostPerHour << setw(20)
         << arr[i].daysVisitsPerYear << endl;
  }
}
// end of helper section

//  0–17: Pediatrics & Adolescents
//  18–25: Young Adults / University Students
//  26–45: Working Adults (Early Career)
//  46–60: Working Adults (Late Career)
//  61–100: Senior Citizens / Geriatric Care
Patient category1[600];
Patient category2[600];
Patient category3[600];
Patient category4[600];
Patient category5[600];

int category1Count = 0;
int category2Count = 0;
int category3Count = 0;
int category4Count = 0;
int category5Count = 0;

void sortIntoCategory(Patient toBeSortList[]) {
  category1Count = 0;
  category2Count = 0;
  category3Count = 0;
  category4Count = 0;
  category5Count = 0;

  for (int i = 0; i < patientCount; i++) {
    if (toBeSortList[i].age <= 17) {
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

void compareExpenditureAndVisitDuration(Patient patientList[], int patientCount,
                                        string datasetName) {

  int minAge[5] = {0, 18, 26, 46, 61};
  int maxAge[5] = {17, 25, 45, 60, 100};

  string ageGroup[5] = {"0-17", "18-25", "26-45", "46-60", "61-100"};

  cout << "\n" << string(140, '=') << endl;
  cout << datasetName << endl;
  cout << string(140, '=') << endl;

  cout << left << setw(12) << "Age Group" << setw(12) << "Patients" << setw(20)
       << "Total Expenditure" << setw(20) << "Avg Expenditure" << setw(20)
       << "Total Visit Duration" << setw(20) << "Avg Visit Duration" << setw(18)
       << "Total Visits" << setw(18) << "Avg Visits" << endl;

  cout << string(140, '-') << endl;

  for (int group = 0; group < 5; group++) {

    int patientCounter = 0;
    double totalExpenditure = 0.0;
    double totalVisitDuration = 0.0;
    double totalVisits = 0.0;

    for (int i = 0; i < patientCount; i++) {

      if (patientList[i].age >= minAge[group] &&
          patientList[i].age <= maxAge[group]) {

        double expenditure = totalMedicalCost(patientList[i]);

        totalExpenditure += expenditure;

        totalVisitDuration +=
            patientList[i].lengthOfStay * patientList[i].daysVisitsPerYear;

        totalVisits += patientList[i].daysVisitsPerYear;

        patientCounter++;
      }
    }

    double averageExpenditure = 0.0;
    double averageVisitDuration = 0.0;
    double averageVisits = 0.0;

    if (patientCounter > 0) {
      averageExpenditure = totalExpenditure / patientCounter;
      averageVisitDuration = totalVisitDuration / patientCounter;
      averageVisits = totalVisits / patientCounter;
    }

    cout << left << setw(12) << ageGroup[group] << setw(12) << patientCounter
         << setw(20) << totalExpenditure << setw(20) << averageExpenditure
         << setw(20) << totalVisitDuration << setw(20) << averageVisitDuration
         << setw(18) << totalVisits << setw(18) << averageVisits << endl;
  }

  cout << string(140, '=') << endl;
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

void sortByBubble(Patient patientList[], string fieldToBeCompare,
                  int patientCount) {
  auto start = chrono::high_resolution_clock::now();
  for (int i = 0; i < patientCount - 1; i++) {
    bool swapped = false;

    for (int j = 0; j < patientCount - 1 - i; j++) {
      if (fieldToBeCompare == "age") {
        if (patientList[j].age > patientList[j + 1].age) {
          swap(patientList[j], patientList[j + 1]);
          swapped = true;
        }
      } else if (fieldToBeCompare == "stay") {
        if (patientList[j].lengthOfStay > patientList[j + 1].lengthOfStay) {
          swap(patientList[j], patientList[j + 1]);
          swapped = true;
        }
      } else if (fieldToBeCompare == "cost") {
        if (totalMedicalCost(patientList[j]) >
            totalMedicalCost(patientList[j + 1])) {
          swap(patientList[j], patientList[j + 1]);
          swapped = true;
        }
      }
    }

    if (not swapped) {
      break;
    }
  }

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << string(80, '*') << endl;
  cout << "Sorting took " << duration.count() << " microseconds" << endl;
  size_t arrayMemory = patientCount * sizeof(*patientList);
  cout << "Array memory usage: " << arrayMemory << " bytes" << endl;
  cout << string(80, '*') << endl;
}

void sortBySelection(Patient patientList[], string fieldToBeCompare,
                     int patientCount) {
  auto start = chrono::high_resolution_clock::now();
  for (int i = 0; i < patientCount - 1; i++) {
    int minIndex = i;

    for (int j = i + 1; j < patientCount; j++) {
      if (fieldToBeCompare == "age") {
        if (patientList[j].age < patientList[minIndex].age) {
          minIndex = j;
        }
      }

      if (fieldToBeCompare == "stay") {
        if (patientList[j].lengthOfStay < patientList[minIndex].lengthOfStay) {
          minIndex = j;
        }
      }

      if (fieldToBeCompare == "cost") {
        if (totalMedicalCost(patientList[j]) <
            totalMedicalCost(patientList[minIndex])) {
          minIndex = j;
        }
      }
    }

    if (minIndex != i) {
      swap(patientList[i], patientList[minIndex]);
    }
  }

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << string(80, '*') << endl;
  cout << "Sorting took " << duration.count() << " microseconds" << endl;
  size_t arrayMemory = patientCount * sizeof(*patientList);
  cout << "Array memory usage: " << arrayMemory << " bytes" << endl;
  cout << string(80, '*') << endl;
}

Patient searchResult[600];

void identifyHighestBillingAndTraffic(Patient patientList[], int patientCount) {
  int minAge[5] = {0, 18, 26, 46, 61};
  int maxAge[5] = {17, 25, 45, 60, 100};

  string ageGroup[5] = {"0-17", "18-25", "26-45", "46-60", "61-100"};

  double totalBilling[5] = {0, 0, 0, 0, 0};
  int careTypeCount[5] = {0, 0, 0, 0, 0};

  string careTypes[5] = {"Emergency", "Inpatient", "Outpatient",
                         "Rehabilitation", "Vaccination"};

  for (int i = 0; i < patientCount; i++) {

    for (int group = 0; group < 5; group++) {
      if (patientList[i].age >= minAge[group] &&
          patientList[i].age <= maxAge[group]) {

        totalBilling[group] += totalMedicalCost(patientList[i]);
        break;
      }
    }

    for (int type = 0; type < 5; type++) {
      if (patientList[i].careType == careTypes[type]) {
        careTypeCount[type]++;
        break;
      }
    }
  }

  int highestBillingGroup = 0;

  for (int i = 1; i < 5; i++) {
    if (totalBilling[i] > totalBilling[highestBillingGroup]) {
      highestBillingGroup = i;
    }
  }

  int highestTrafficType = 0;

  for (int i = 1; i < 5; i++) {
    if (careTypeCount[i] > careTypeCount[highestTrafficType]) {
      highestTrafficType = i;
    }
  }

  cout << string(60, '=') << endl;
  cout << "Highest Healthcare Billing and Patient Traffic" << endl;
  cout << string(60, '=') << endl;

  cout << "Highest Healthcare Billing" << endl;
  cout << "Demographic Group : " << ageGroup[highestBillingGroup] << endl;
  cout << "Total Billing     : " << totalBilling[highestBillingGroup] << endl;

  cout << "Highest Patient Traffic" << endl;
  cout << "Care Type         : " << careTypes[highestTrafficType] << endl;
  cout << "Patient Count     : " << careTypeCount[highestTrafficType] << endl;

  cout << string(60, '=') << endl;
}

void searchUsingLinear(Patient patientList[], int category = 1,
                       int visitDuration = 0, float totalMedicalCost = 0.0) {
  auto start = chrono::high_resolution_clock::now();
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

  for (int i = 0; i < patientCount; i++) {
    // TODO: maybe change this to earlier part where the totalmedicalcost is
    // calculated and store it instead of recalculating
    int calculateMedicalCost = patientList[i].lengthOfStay *
                               patientList[i].baseCostPerHour *
                               patientList[i].daysVisitsPerYear;
    if (patientList[i].age >= minAge && patientList[i].age <= maxAge &&
        patientList[i].lengthOfStay > visitDuration &&
        (totalMedicalCost <= 0 || calculateMedicalCost < totalMedicalCost)) {
      searchResult[counter] = patientList[i];
      counter++;
    }
  }
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

  cout << string(80, '*') << endl;
  cout << "Searching took " << duration.count() << " microseconds" << endl;
  size_t arrayMemory = sizeof(*patientList);
  cout << "Array memory usage: " << arrayMemory << " bytes" << endl;
  cout << string(80, '*') << endl;

  cout << "Found " << counter << " matching patient(s)" << endl << endl;

  if (counter > 0) {
    cout << left << setw(12) << "Patient ID" << setw(8) << "Age" << setw(20)
         << "Care Type" << setw(20) << "Stay" << setw(20) << "Cost/Hour"
         << setw(20) << "Visits/Year" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < counter; i++) {
      cout << left << setw(12) << searchResult[i].PatientID << setw(8)
           << searchResult[i].age << setw(20) << searchResult[i].careType
           << setw(20) << searchResult[i].lengthOfStay << setw(20)
           << searchResult[i].baseCostPerHour << setw(20)
           << searchResult[i].daysVisitsPerYear << endl;
    }
  }
}

void searchUsingBinary(Patient patientList[], string fieldToSearch,
                       double value) {
  auto start = chrono::high_resolution_clock::now();
  int counter = 0;
  int minAge = 0;
  int maxAge = 100;

  int low = 0;
  int high = patientCount - 1;

  Patient tempPatient;

  bool found = false;

  if (fieldToSearch == "age") {
    while (low <= high) {
      int mid = low + (high - low) / 2;

      if (patientList[mid].age == value) {
        tempPatient = patientList[mid];
        found = true;
        counter++;
        break;
      } else if (patientList[mid].age < value) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
  } else if (fieldToSearch == "visitDuration") {
    while (low <= high) {
      int mid = low + (high - low) / 2;

      if (patientList[mid].lengthOfStay == value) {
        tempPatient = patientList[mid];
        found = true;
      } else if (patientList[mid].lengthOfStay < value) {
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
  size_t arrayMemory = sizeof(*patientList);
  cout << "Array memory usage: " << arrayMemory << " bytes" << endl;
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

