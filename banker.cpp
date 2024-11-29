#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

const int NUM_RESOURCES = 3; // Number of resource 

vector<vector<int> > allocation, maxMatrix, need;
vector<int> available;
vector<int> safeSequence;

//  input file
void parseFile(const string &filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    string line;
    string current = ""; // Track current section 

    while (getline(inFile, line)) {
        if (line.empty()) continue; 

        // find sections in file
        if (line == "Allocation") {
            current = "Allocation";
            continue;
        } else if (line == "Max") {
            current = "Max";
            continue;
        } else if (line == "Available") {
            current = "Available";
            continue;
        }

        // enter each section then push in vector
        stringstream ss(line);

        if (current == "Allocation") {
            vector<int> alloc(NUM_RESOURCES);
            for (int i = 0; i < NUM_RESOURCES; ++i) {
                ss >> alloc[i];
            }
            allocation.push_back(alloc);
        } else if (current == "Max") {
            vector<int> maxRow(NUM_RESOURCES);
            for (int i = 0; i < NUM_RESOURCES; ++i) {
                ss >> maxRow[i];
            }
            maxMatrix.push_back(maxRow);
        } else if (current == "Available") {
            int resource;
            while (ss >> resource) {
                available.push_back(resource);
            }
        }
    }

    inFile.close();
}

// Calculate the Need = Max - Allocate
void calculateNeed() {
    for (size_t i = 0; i < allocation.size(); ++i) {
        vector<int> temp(NUM_RESOURCES);
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            temp[j] = maxMatrix[i][j] - allocation[i][j];
        }
        need.push_back(temp);
    }
}

// Check if the system is in a safe state
bool isSafe() {
    vector<bool> finished(allocation.size(), false);
    vector<int> work = available;

    // Loop until all processes are in the safe sequence
    while (safeSequence.size() < allocation.size()) {
        bool progress = false;

        for (size_t i = 0; i < allocation.size(); ++i) {
            if (!finished[i]) {
                // Check if Need can be satisfied: Need <= Work then Work = Work + Allocation
                bool canRun = true;
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    // Add process to the safe sequence
                    safeSequence.push_back(i);
                    finished[i] = true;
                    progress = true;

                    //update available resources (work += allocation)
                    for (int j = 0; j < NUM_RESOURCES; ++j) {
                        work[j] += allocation[i][j];
                    }
                }
            }
        }

        if (!progress) return false; // unsafe state
    }
    return true; 
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }

    parseFile(argv[1]);
    calculateNeed();

    if (isSafe()) {
    cout << "The system is in a safe state.\nSafe sequence: ";
    string separator = "";
    for (size_t i = 0; i < safeSequence.size(); ++i) {
        cout << separator << "P" << safeSequence[i];
        separator = " -> "; 
    }
        cout << endl;
    } else {
        cout << "The system is not in a safe state." << endl;
    }

    return 0;
}
