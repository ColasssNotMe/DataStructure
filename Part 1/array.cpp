#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

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
Patient searchResult[MAX_PATIENTS];

//  0-17:  Pediatrics & Adolescents
//  18-25: Young Adults / University Students
//  26-45: Working Adults (Early Career)
//  46-60: Working Adults (Late Career)
//  61-100: Senior Citizens / Geriatric Care
Patient category1[MAX_PATIENTS];
Patient category2[MAX_PATIENTS];
Patient category3[MAX_PATIENTS];
Patient category4[MAX_PATIENTS];
Patient category5[MAX_PATIENTS];

int category1Count = 0;
int category2Count = 0;
int category3Count = 0;
int category4Count = 0;
int category5Count = 0;

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

  // skip header row
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

void sortIntoCategory(Patient toBeSortList[]) {
  for (int i = 0; i < MAX_PATIENTS; i++) {
    if (toBeSortList[i].age == 0) {
      return; // assumes age 0 means "no more data"
    } else if (toBeSortList[i].age <= 17) {
      category1[category1Count++] = toBeSortList[i];
    } else if (toBeSortList[i].age <= 25) {
      category2[category2Count++] = toBeSortList[i];
    } else if (toBeSortList[i].age <= 45) {
      category3[category3Count++] = toBeSortList[i];
    } else if (toBeSortList[i].age <= 60) {
      category4[category4Count++] = toBeSortList[i];
    } else if (toBeSortList[i].age <= 100) {
      category5[category5Count++] = toBeSortList[i];
    }
  }
}

Patient *getCategoryArray(int categoryNumber) {
  switch (categoryNumber) {
  case 1:
    return category1;
  case 2:
    return category2;
  case 3:
    return category3;
  case 4:
    return category4;
  case 5:
    return category5;
  default:
    return nullptr;
  }
}

int getCategoryCount(int categoryNumber) {
  switch (categoryNumber) {
  case 1:
    return category1Count;
  case 2:
    return category2Count;
  case 3:
    return category3Count;
  case 4:
    return category4Count;
  case 5:
    return category5Count;
  default:
    return 0;
  }
}

void mostPreferredCareType(Patient array[], int totalNumberOfPatient) {
  int vaccineCounter = 0, rehabCounter = 0, emergencyCounter = 0,
      outpatientCounter = 0, inpatientCounter = 0, routineCounter = 0;
  int totalMedicalCostVaccine = 0, totalMedicalCostRehab = 0,
      totalMedicalCostEmergency = 0, totalMedicalCostOutpatient = 0,
      totalMedicalCostInpatient = 0, totalMedicalCostRoutine = 0;

  for (int i = 0; i < totalNumberOfPatient; i++) {
    if (array[i].PatientID == "") {
      return;
    }

    int cost = array[i].lengthOfStay * array[i].baseCostPerHour *
               array[i].daysVisitsPerYear;

    if (array[i].careType == "Vaccination") {
      vaccineCounter++;
      totalMedicalCostVaccine += cost;
    } else if (array[i].careType == "Rehabilitation") {
      rehabCounter++;
      totalMedicalCostRehab += cost;
    } else if (array[i].careType == "Routine Checkup") {
      routineCounter++;
      totalMedicalCostRoutine += cost;
    } else if (array[i].careType == "Emergency") {
      emergencyCounter++;
      totalMedicalCostEmergency += cost;
    } else if (array[i].careType == "Outpatient") {
      outpatientCounter++;
      totalMedicalCostOutpatient += cost;
    } else if (array[i].careType == "Inpatient") {
      inpatientCounter++;
      totalMedicalCostInpatient += cost;
    } else {
      cout << "Unknown care type: " << array[i].careType << endl;
    }
  }

  int vacAvg = vaccineCounter ? totalMedicalCostVaccine / vaccineCounter : 0;
  int rehabAvg = rehabCounter ? totalMedicalCostRehab / rehabCounter : 0;
  int routineAvg =
      routineCounter ? totalMedicalCostRoutine / routineCounter : 0;
  int emergencyAvg =
      emergencyCounter ? totalMedicalCostEmergency / emergencyCounter : 0;
  int outAvg =
      outpatientCounter ? totalMedicalCostOutpatient / outpatientCounter : 0;
  int inAvg =
      inpatientCounter ? totalMedicalCostInpatient / inpatientCounter : 0;

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
      bool shouldSwap = false;

      if (fieldToBeCompare == "age") {
        shouldSwap = patientList[j].age > patientList[j + 1].age;
      } else if (fieldToBeCompare == "lengthOfStay") {
        shouldSwap =
            patientList[j].lengthOfStay > patientList[j + 1].lengthOfStay;
      } else if (fieldToBeCompare == "totalMedicalCost") {
        shouldSwap = totalMedicalCost(patientList[j]) >
                     totalMedicalCost(patientList[j + 1]);
      }

      if (shouldSwap) {
        swap(patientList[j], patientList[j + 1]);
        swapped = true;
      }
    }

    if (!swapped)
      break;
  }

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << string(80, '*') << endl;
  cout << "Sorting took " << duration.count() << " microseconds" << endl;
  cout << string(80, '*') << endl;
}

int searchUsingLinear(Patient patientList[], int category = 1,
                      int visitDuration = 0, double maxCost = 0.0) {
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

  for (int i = 0; i < MAX_PATIENTS; i++) {
    if (patientList[i].PatientID == "")
      continue;

    double cost = totalMedicalCost(patientList[i]);
    bool match = patientList[i].age >= minAge && patientList[i].age <= maxAge;

    if (visitDuration > 0)
      match = match && patientList[i].lengthOfStay > visitDuration;
    if (maxCost > 0)
      match = match && cost < maxCost;

    if (match) {
      searchResult[counter] = patientList[i];
      counter++;
    }
  }

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << string(80, '*') << endl;
  cout << "Searching took " << duration.count() << " microseconds" << endl;
  cout << string(80, '*') << endl;

  return counter;
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

// Menu

int getMenuChoice(const string &title, const vector<string> &options) {
  int choice = -1;

  while (true) {
    cout << string(80, '=') << endl;
    cout << title << endl;
    cout << string(80, '-') << endl;
    for (int i = 0; i < (int)options.size(); i++) {
      cout << i + 1 << ". " << options[i] << endl;
    }
    cout << "Enter choice (1-" << options.size() << "): ";

    if (cin >> choice && choice >= 1 && choice <= (int)options.size()) {
      return choice;
    }

    cout << "Invalid choice, please try again." << endl;
    cin.clear(); // recover from a failed extraction
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

int readInt(const string &prompt) {
  int value;
  while (true) {
    cout << prompt;
    if (cin >> value)
      return value;
    cout << "Please enter a number." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

double readDouble(const string &prompt) {
  double value;
  while (true) {
    cout << prompt;
    if (cin >> value)
      return value;
    cout << "Please enter a number." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

// Menus (one function per menu)
void datasetMenu() {
  cout << string(80, '=') << endl;
  cout << "Please enter absolute path, or input 1, 2 or 3" << endl;
  cout << "1. Dataset 1" << endl;
  cout << "2. Dataset 2" << endl;
  cout << "3. Dataset 3" << endl;

  string selection;
  cin >> selection;

  string chosenFile;
  if (selection == "1") {
    chosenFile = "dataset1_facility_a.csv";
  } else if (selection == "2") {
    chosenFile = "dataset2_facility_b.csv";
  } else if (selection == "3") {
    chosenFile = "dataset3_facility_c.csv";
  } else {
    chosenFile = selection;
  }

  readFromDataset(chosenFile, patientList);
  readFromDataset(chosenFile, unsortedPatientList);
}

void displayCategoryReports() {
  for (int i = 1; i <= 5; i++) {
    cout << string(80, '-') << endl;
    cout << "Category " << i << endl;
    cout << string(80, '-') << endl;
    mostPreferredCareType(getCategoryArray(i), getCategoryCount(i));
    cout << endl << endl;
  }
}

void sortMenu() {
  int algoChoice = getMenuChoice("Select sorting algorithm", {"Bubble Sort"});

  int categoryChoice =
      getMenuChoice("Select category to be sorted",
                    {"Category 1", "Category 2", "Category 3", "Category 4",
                     "Category 5", "All Categories"});

  int fieldChoice = getMenuChoice(
      "Select field to be sorted",
      {"Age", "Visit Duration (Length of Stay)", "Total Medical Cost"});

  string field;
  if (fieldChoice == 1) {
    field = "age";
  } else if (fieldChoice == 2) {
    field = "lengthOfStay";
  } else {
    field = "totalMedicalCost";
  }

  if (categoryChoice == 6) {
    for (int i = 1; i <= 5; i++) {
      cout << endl
           << "Sorting Category " << i << " by " << field << "..." << endl;
      sortByBubble(getCategoryArray(i), field, getCategoryCount(i));
    }
  } else {
    sortByBubble(getCategoryArray(categoryChoice), field,
                 getCategoryCount(categoryChoice));
    cout << endl << "Sorted result:" << endl;
    tempPrintArr(getCategoryArray(categoryChoice),
                 getCategoryCount(categoryChoice));
  }
}

void searchMenu() {
  int sourceChoice = getMenuChoice(
      "Search - select data source",
      {"Unsorted Data", "Sorted Data (patient list sorted by age)"});

  int categoryChoice = getMenuChoice(
      "Search - enter age group",
      {"Category 1 (0-17)", "Category 2 (18-25)", "Category 3 (26-45)",
       "Category 4 (46-60)", "Category 5 (61-100)"});

  int minStay = readInt("Minimum length of stay (0 = no filter): ");
  double maxCost = readDouble("Maximum total medical cost (0 = no filter): ");

  if (sourceChoice == 2) {
    sortByBubble(patientList, "age", MAX_PATIENTS);
  }

  Patient *dataSource = (sourceChoice == 1) ? unsortedPatientList : patientList;
  int found = searchUsingLinear(dataSource, categoryChoice, minStay, maxCost);

  cout << "Found " << found << " patient(s)." << endl;
  if (found > 0) {
    tempPrintArr(searchResult, found);
  }
}

void printMenu() {
  int choice = getMenuChoice(
      "Print array",
      {"Unsorted dataset (as read from file)", "Working patient list",
       "Category 1", "Category 2", "Category 3", "Category 4", "Category 5"});

  switch (choice) {
  case 1:
    tempPrintArr(unsortedPatientList);
    break;
  case 2:
    tempPrintArr(patientList);
    break;
  case 3:
    tempPrintArr(category1, category1Count);
    break;
  case 4:
    tempPrintArr(category2, category2Count);
    break;
  case 5:
    tempPrintArr(category3, category3Count);
    break;
  case 6:
    tempPrintArr(category4, category4Count);
    break;
  case 7:
    tempPrintArr(category5, category5Count);
    break;
  }
}

void mainMenu() {
  while (true) {
    int choice =
        getMenuChoice("Main Menu", {"Sort", "Search", "Print Array", "Exit"});

    switch (choice) {
    case 1:
      sortMenu();
      break;
    case 2:
      searchMenu();
      break;
    case 3:
      printMenu();
      break;
    case 4:
      cout << "Goodbye!" << endl;
      return;
    }
  }
}

int main() {
  datasetMenu();

  cout << string(80, '=') << endl;
  cout << "Categorizing..." << endl << endl;
  sortIntoCategory(patientList);

  displayCategoryReports();

  mainMenu();

  return 0;
}
