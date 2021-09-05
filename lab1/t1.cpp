#include <vector>
#include <iostream>

using namespace std;

vector<int> readVector(int size);
unsigned int getCost(vector<int> items, const vector<int>& requisitions,
                     unsigned int (*function)(vector<int>& items, int request));
unsigned int calculateMoveToFrontCost(vector<int>& items, int request);
unsigned int calculateTranspositionCost(vector<int>& items, int request);
unsigned int getFrequencyCountCost(const vector<int>& items, const vector<int>& requisitions);
unsigned int getBitCost(const vector<int>& items, const vector<int>& requisitions, const vector<int>& bitValues);

int main() {
    int itemsSize;
    vector<int> items;
    vector<int> bitValues;
    int requisitionsSize;
    vector<int> requisitions;

    cin >> itemsSize;
    items = readVector(itemsSize);
    bitValues = readVector(itemsSize);
    cin >> requisitionsSize;
    requisitions = readVector(requisitionsSize);

    cout << getCost(items, requisitions, calculateMoveToFrontCost) << "\n";
    cout << getCost(items, requisitions, calculateTranspositionCost) << "\n";
    cout << getFrequencyCountCost(items, requisitions) << "\n";
    cout << getBitCost(items, requisitions, bitValues) << "\n";

    return 0;
}

vector<int> readVector(int size) {
    vector<int> vector;
    int value;

    for (int i = 0; i < size; i++) {
        cin >> value;
        vector.push_back(value);
    }
    return vector;
}

unsigned int getCost(vector<int> items, const vector<int>& requisitions, unsigned int (*function)(vector<int>& items, int request)) {
    unsigned int cost = 0;

    for (int request : requisitions) {
        cost += function(items, request);
    }
    return cost;
}

unsigned int calculateMoveToFrontCost(vector<int>& items, int request) {
    bool found = false;
    unsigned int i;

    for (i = 0; i < items.size() && !found; i++) {
        if (items[i] == request) {
            found = true;
            items.erase(items.begin() + i);
            items.emplace(items.begin(), request);
        }
    }

    if (found) {
        return i;
    }
    return i + 1;
}

unsigned int calculateTranspositionCost(vector<int>& items, int request) {
    bool found = false;
    unsigned int i;

    for (i = 0; i < items.size() && !found; i++) {
        if (items[i] == request) {
            found = true;
            if (i != 0) {
                int temp = items[i];
                items.erase(items.begin() + i);
                items.emplace(items.begin() + i - 1, temp);
            }
        }
    }

    if (found) {
        return i;
    }
    return i + 1;
}

void sortByDecreasingFrequency(vector<pair<int, int>>& v, unsigned int index) {
    pair<int, int> p = v[index];
    v.erase(v.begin() + index);

    bool sorted = false;

    for (unsigned int i = 0; i < v.size() && !sorted; i++) {
        if (p.second >= v[i].second) {
            v.emplace(v.begin() + i, p);
            sorted = true;
        }
    }
}

unsigned int getFrequencyCountCost(const vector<int>& items, const vector<int>& requisitions) {
    unsigned int cost = 0;
    vector<pair<int, int>> frequencyCount;
    frequencyCount.reserve(items.size());

    for (int item : items) {
        frequencyCount.emplace_back(pair<int, int>(item, 0));
    }

    bool found = false;
    unsigned int i;

    for (int request : requisitions) {
        for (i = 0; i < frequencyCount.size() && !found; i++) {
            if (frequencyCount[i].first == request) {
                found = true;
                frequencyCount[i].second++;
                sortByDecreasingFrequency(frequencyCount, i);
            }
        }

        if (found) {
            cost += i;
        } else {
            cost += i + 1;
        }

        found = false;
    }
    return cost;
}

unsigned int getBitCost(const vector<int>& items, const vector<int>& requisitions, const vector<int>& bitValues) {
    unsigned int cost = 0;
    vector<pair<int, int>> v;
    v.reserve(items.size());

    for (unsigned int i = 0; i < items.size(); i++) {
        v.emplace_back(pair<int, int>(items[i], bitValues[i]));
    }

    bool found = false;
    unsigned int i;

    for (int request : requisitions) {
        for (i = 0; i < v.size() && !found; i++) {
            if (v[i].first == request) {
                found = true;
                if (v[i].second == 1) {
                    v[i].second = 0;
                    pair<int, int> p = v[i];
                    v.erase(v.begin() + i);
                    v.emplace(v.begin(), p);
                } else {
                    v[i].second = 1;
                }
            }
        }

        if (found) {
            cost += i;
        } else {
            cost += i + 1;
        }

        found = false;
    }
    return cost;
}
