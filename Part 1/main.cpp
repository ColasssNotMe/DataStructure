#include "iostream"
#include <fstream>
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
const int MAX_PATIENTS = 1200;
Patient patientList[MAX_PATIENTS];

void readFromDataset1(string fileName, Patient patient[]) {
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
    patientList[lineCount].PatientID = token;

    getline(ss, token, ',');
    patientList[lineCount].age = stoi(token);

    getline(ss, token, ',');
    patientList[lineCount].careType = token;

    getline(ss, token, ',');
    patientList[lineCount].lengthOfStay = stoi(token);

    getline(ss, token, ',');
    patientList[lineCount].baseCostPerHour = stoi(token);

    getline(ss, token, ',');
    patientList[lineCount].daysVisitsPerYear = stoi(token);

    lineCount++;
  }
}

void sortDataset1() {}

int main() {
  readFromDataset1(
      "/home/azuki/Documents/Sem2/DSTR/Part 1/dataset1 facility_a.csv",
      patientList);

  cout << patientList[2].PatientID << endl;
}
