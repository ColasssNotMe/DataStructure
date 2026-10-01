#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

namespace LinkedList {

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

class PatientNode {
public:
    PatientNode(Patient patientParam) {
        patient = patientParam;
        nextPatient = nullptr;
    }

    Patient patient;
    PatientNode *nextPatient;
};

extern PatientNode *patientNode;
extern PatientNode *unsortedPatientNode;
extern PatientNode *searchResult;
extern string datasetFileName;

extern PatientNode *category1;
extern PatientNode *category2;
extern PatientNode *category3;
extern PatientNode *category4;
extern PatientNode *category5;

void insertToEnd(PatientNode *&head, Patient patient);
void insertToEnd(PatientNode *&head, PatientNode *&patient);
void freeList(PatientNode *&head);
void readFromDataset(string fileName, PatientNode *&head);
double totalMedicalCost(PatientNode *&patient);
void tempPrintNode(PatientNode *patientNode);
void sortIntoCategory(PatientNode *&head);
void mostPreferredCareType(PatientNode *&head);
void sortByBubble(PatientNode *&head, string fieldToBeCompare);
int searchUsingLinear(PatientNode *&head, int category = 1,
                      int visitDuration = 0,
                      float totalMedicalCost = 0.0);

void datasetMenu();
void sortMenu();
void searchMenu();
void printMenu();
void mainMenu();

} // namespace LinkedList

#endif
