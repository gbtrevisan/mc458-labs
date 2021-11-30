#include <iostream>
#include <vector>

using namespace std;

long long int findMinimalTravelTime(const vector<unsigned int>& travel_time, unsigned int travelers);

int main() {
    unsigned int travelers;
    vector<unsigned int> travel_time;

    cin >> travelers;

    travel_time.reserve(travelers);

    for (unsigned int i = 0; i < travelers; i++) {
        unsigned int time;
        cin >> time;
        travel_time.push_back(time);
    }

    cout << findMinimalTravelTime(travel_time, travelers) << endl;

    return 0;
}

long long int findMinimalTravelTime(const vector<unsigned int>& travel_time, unsigned int travelers) {
    long long int time = travel_time[1];

    while (travelers > 2) {
        if (travel_time[0] + travel_time[travelers - 2] > 2 * travel_time[1]) {
            time += 2 * travel_time[1] + travel_time[0] + travel_time[travelers - 1];
            travelers = travelers - 2;
        } else {
            time += travel_time[travelers - 1] + travel_time[0];
            travelers = travelers - 1;
        }
    }

    return time;
}
