#include <algorithm>
#include <chrono>
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

Patient patientList[MAX_PATIENTS];
Patient unsortedPatientList[MAX_PATIENTS];
Patient sortedPatientList[MAX_PATIENTS];

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

void tempPrintArr(Patient arr[], int count = MAX_PATIENTS) {
  cout << left << setw(12) << "Patient ID" << setw(8) << "Age" << setw(15)
       << "Care Type" << setw(15) << "Stay" << setw(15) << "Cost/Hour"
       << setw(15) << "Visits/Year" << endl;

  cout << string(80, '-') << endl;

  for (int i = 0; i < count; i++) {
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
  auto start = chrono::high_resolution_clock::now();
  for (int i = 0; i < patientCount - 1; i++) {
    bool swapped = false;

    for (int j = 0; j < patientCount - 1 - i; j++) {
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
      break;
    }
  }

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << string(80, '*') << endl;
  cout << "Sorting took " << duration.count() << " microseconds" << endl;
  cout << string(80, '*') << endl;
}

Patient searchResult[200];

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
        calculateMedicalCost < totalMedicalCost) {
      searchResult[counter] = patientList[i];
      counter++;
    }
  }
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

  cout << string(80, '*') << endl;
  cout << "Searching took " << duration.count() << " microseconds" << endl;
  cout << string(80, '*') << endl;

  cout << "Found " << counter << " matching patient(s)" << endl << endl;

  if (counter > 0) {
    cout << left << setw(12) << "Patient ID" << setw(8) << "Age" << setw(15)
         << "Care Type" << setw(15) << "Stay" << setw(15) << "Cost/Hour"
         << setw(15) << "Visits/Year" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < counter; i++) {
      cout << left << setw(12) << searchResult[i].PatientID << setw(8)
           << searchResult[i].age << setw(15) << searchResult[i].careType
           << setw(15) << searchResult[i].lengthOfStay << setw(15)
           << searchResult[i].baseCostPerHour << setw(15)
           << searchResult[i].daysVisitsPerYear << endl;
    }
  }
}

// Menu
void loadDatasetMenu() {
  string selection = "";
  string fileName = "";

  cout << string(80, '=') << endl;
  cout << "Please enter absolute path, or input 1,2 or 3" << endl;
  cout << "1. Dataset 1" << endl;
  cout << "2. Dataset 2" << endl;
  cout << "3. Dataset 3" << endl;

  cin >> selection;

  if (selection == "1") {
    fileName = "dataset1_facility_a.csv";
  } else if (selection == "2") {
    fileName = "dataset2_facility_b.csv";
  } else if (selection == "3") {
    fileName = "dataset3_facility_c.csv";
  } else {
    fileName = selection;
  }

  patientCount = readFromDataset(fileName, patientList);
  readFromDataset(fileName, unsortedPatientList);

  if (patientCount == 0) {
    cout << "No patients were loaded, please check the file." << endl;
    return;
  }

  cout << "Loaded " << patientCount << " patients from " << fileName << endl;
  cout << "Categorizing..." << endl << endl;
  sortIntoCategory(patientList);
}

void categorySummaryMenu() {
  if (patientCount == 0) {
    cout << "No dataset loaded. Please load a dataset first." << endl;
    return;
  }

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
}

void sortMenu() {
  if (patientCount == 0) {
    cout << "No dataset loaded. Please load a dataset first." << endl;
    return;
  }

  string sortSelection = "";
  string categorySelection = "";
  string fieldSelection = "";

  do {
    cout << string(80, '=') << endl;
    cout << "Select sorting algorithm" << endl;
    cout << "1. Bubble Sort" << endl;
    // cout << "2. -" << endl;
    cin >> sortSelection;
  } while (sortSelection != "1" && sortSelection != "2");

  cout << string(80, '-') << endl;

  do {
    cout << string(80, '=') << endl;
    cout << "Select category to be sorted" << endl;
    cout << "1. Category 1" << endl;
    cout << "2. Category 2" << endl;
    cout << "3. Category 3" << endl;
    cout << "4. Category 4" << endl;
    cout << "5. Category 5" << endl;
    cout << "6. All Category" << endl;
    cin >> categorySelection;
  } while (categorySelection != "1" && categorySelection != "2" &&
           categorySelection != "3" && categorySelection != "4" &&
           categorySelection != "5" && categorySelection != "6");

  cout << string(80, '-') << endl;

  Patient *category = nullptr;
  int categoryCount = 0;

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
  // "6" (All Category) is handled below

  do {
    cout << string(80, '=') << endl;
    cout << "Select field to be sorted" << endl;
    cout << "1. Age" << endl;
    cout << "2. Visit Duration (Length of Stay)" << endl;
    cout << "3. Total Medical Cost" << endl;
    cin >> fieldSelection;
  } while (fieldSelection != "1" && fieldSelection != "2" &&
           fieldSelection != "3");

  string field = "";
  if (fieldSelection == "1") {
    field = "age";
  } else if (fieldSelection == "2") {
    field = "lengthOfStay";
  } else if (fieldSelection == "3") {
    field = "totalMedicalCost";
  }

  if (sortSelection == "1") {
    if (categorySelection == "6") {
      Patient *allCategories[5] = {category1, category2, category3, category4,
                                   category5};
      int allCounts[5] = {category1Count, category2Count, category3Count,
                          category4Count, category5Count};

      for (int i = 0; i < 5; i++) {
        cout << string(80, '-') << endl;
        cout << "Category " << i + 1 << endl;
        cout << string(80, '-') << endl;
        sortByBubble(allCategories[i], field, allCounts[i]);
        tempPrintArr(allCategories[i], allCounts[i]);
      }
    } else {
      sortByBubble(category, field, categoryCount);
      tempPrintArr(category, categoryCount);
      cout << string(80, '-') << endl;
    }
  } else if (sortSelection == "2") {
    // TODO: add sorting algo here
    cout << "Sorting algorithm 2 is not implemented yet." << endl;
  }
}

void searchMenu() {
  if (patientCount == 0) {
    cout << "No dataset loaded. Please load a dataset first." << endl;
    return;
  }

  string searchSelection = "";
  do {
    cout << string(80, '=') << endl;
    cout << "Search" << endl;
    cout << string(80, '=') << endl;
    cout << "Select 1 data from below" << endl;
    cout << "1. Unsorted Data" << endl;
    cout << "2. Sorted Data" << endl;
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
    cin >> searchCategory;
  } while (searchCategory != "1" && searchCategory != "2" &&
           searchCategory != "3" && searchCategory != "4" &&
           searchCategory != "5");

  int visitDuration = 0;
  float maxTotalMedicalCost = 0.0f;

  cout << string(80, '=') << endl;
  cout << "Find patients with length of stay greater than: ";
  cin >> visitDuration;
  cout << "And total medical cost less than ($): ";
  cin >> maxTotalMedicalCost;

  if (searchSelection == "1") {
    searchUsingLinear(unsortedPatientList, stoi(searchCategory), visitDuration,
                      maxTotalMedicalCost);
  } else {
    sortByBubble(patientList, "age", patientCount);
    searchUsingLinear(patientList, stoi(searchCategory), visitDuration,
                      maxTotalMedicalCost);
  }
}

int main() {
  string menuSelection = "";
  bool exitProgram = false;

  do {
    cout << string(80, '=') << endl;
    cout << "Main Menu" << endl;
    cout << string(80, '=') << endl;
    cout << "1. Load Dataset" << endl;
    cout << "2. View Care Type Summary (All Categories)" << endl;
    cout << "3. Sort Category" << endl;
    cout << "4. Search Patients" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter selection: ";
    cin >> menuSelection;
    cout << string(80, '-') << endl;

    if (menuSelection == "1") {
      loadDatasetMenu();
    } else if (menuSelection == "2") {
      categorySummaryMenu();
    } else if (menuSelection == "3") {
      sortMenu();
    } else if (menuSelection == "4") {
      searchMenu();
    } else if (menuSelection == "5") {
      exitProgram = true;
    } else {
      cout << "Invalid selection, please enter 1-5." << endl;
    }
  } while (!exitProgram);

  return 0;
}
