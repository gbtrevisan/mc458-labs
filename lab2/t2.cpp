#include <iostream>
#include <vector>

using namespace std;

pair<unsigned int, unsigned int> findMaxSequence(const vector<int>& v);

int main() {
    unsigned int n;
    int value;
    vector<int> niceness;

    cin >> n;
    niceness.reserve(n - 1);

    for (unsigned int i = 0; i < n - 1; i++) {
        cin >> value;
        niceness.push_back(value);
    }

    pair<unsigned int, unsigned int> ij = findMaxSequence(niceness);
    cout << ij.first << " " << ij.second << "\n";

    return 0;
}

pair<unsigned int, unsigned int> findMaxSequence(const vector<int>& v) {
    pair<unsigned int, unsigned int> maxSequenceInterval = pair<int, int>(0, 0);
    pair<unsigned int, unsigned int> maxSuffixInterval = pair<int, int>(0, 0);
    int maxSequence = 0;
    int maxSuffix = 0;

    if (!v.empty()) {
        if (v[0] >= 0) {
            maxSequence = maxSuffix = v[0];
            maxSequenceInterval = maxSuffixInterval = pair<int , int>(1, 1);
        }
    }

    for (unsigned  int i = 1; i < v.size(); i++) {
        maxSuffix += v[i];

        if (maxSuffixInterval.first == 0) {
            maxSuffixInterval.first = i + 1;
        }

        maxSuffixInterval.second = i + 1;

        if (maxSuffix > maxSequence || (maxSuffix == maxSequence &&
                (maxSuffixInterval.second - maxSuffixInterval.first) >
                (maxSequenceInterval.second - maxSequenceInterval.first))) {
            maxSequence = maxSuffix;
            maxSequenceInterval = maxSuffixInterval;
        } else if (maxSuffix < 0) {
                maxSuffix = 0;
                maxSuffixInterval = pair<int, int>(0, 0);
        }
    }

    return maxSequenceInterval;
}
