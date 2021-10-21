#include <iostream>
#include <vector>

using namespace std;

unsigned int calculateMinFlips(vector<int>& containers);

int main() {
    unsigned int n;
    vector<int> containers;

    cin >> n;

    containers.reserve(n);

    for (unsigned int i = 0; i < n; i++) {
        int value;
        cin >> value;
        containers.push_back(value);
    }

    cout << calculateMinFlips(containers) << endl;

    return 0;
}

unsigned int mergeToMinFlips(vector<int>& containers, unsigned int p, unsigned int q, unsigned int r) {
    vector<int> temp;
    temp.reserve(r - p + 1);
    unsigned int i = p, j = q + 1, k = 0;
    unsigned int flips = 0;

    while (i <= q && j <= r) {
        if (containers[i] <= containers[j]) {
            temp.push_back(containers[i]);
            k++;
            i++;
        } else {
            flips += abs(int (j - (k + p)));
            temp.push_back(containers[j]);
            k++;
            j++;
        }
    }

    while (i <= q) {
        temp.push_back(containers[i]);
        i++;
    }

    while (j <= r) {
        temp.push_back(containers[j]);
        j++;
    }

    for (i = p, k = 0; i <= r; i++, k++) {
        containers[i] = temp[k];
    }

    return flips;
}

unsigned int mergeSortToMinFlips(vector<int>& containers, unsigned int p, unsigned int r) {
    unsigned int flips = 0;
    if (p < r) {
        unsigned int q = (p + r) / 2;
        flips += mergeSortToMinFlips(containers, p, q);
        flips += mergeSortToMinFlips(containers, q + 1, r);
        flips += mergeToMinFlips(containers, p, q, r);
    }
    return flips;
}

unsigned int calculateMinFlips(vector<int>& containers) {
    return mergeSortToMinFlips(containers, 0, containers.size() - 1);
}
