#ifndef ARRAY_H
#define ARRAY_H

#include <string>

namespace Array {

using namespace std;

class Patient {
public:
    string PatientID;
    int age;
    std::string careType;
    int lengthOfStay;
    int baseCostPerHour;
    int daysVisitsPerYear;
};

extern Patient patientList[];
extern Patient unsortedPatientList[];
extern Patient sortedPatientList[];
extern int patientCount;

extern Patient category1[];
extern Patient category2[];
extern Patient category3[];
extern Patient category4[];
extern Patient category5[];

extern int category1Count;
extern int category2Count;
extern int category3Count;
extern int category4Count;
extern int category5Count;

extern Patient searchResult[];

double totalMedicalCost(Patient patient);

int readFromDataset(string fileName, Patient patientListToBeAppend[]);

void tempPrintArr(Patient arr[], int count);

void sortIntoCategory(Patient toBeSortList[]);

void mostPreferredCareType(Patient array[], int totalNumberOfPatient);

void sortByBubble(Patient patientList[], string fieldToBeCompare,
                  int patientCount);

void searchUsingLinear(Patient patientList[], int category = 1,
                       int visitDuration = 0,
                       float totalMedicalCost = 0.0);

void loadDatasetMenu();
void categorySummaryMenu();
void sortMenu();
void searchMenu();

} // namespace Array

#endif
