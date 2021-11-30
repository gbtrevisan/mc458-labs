#include <vector>
#include <iostream>

using namespace std;

pair<unsigned int, unsigned int> find_min_coins_to_reach_value(const vector<unsigned int>& coins, unsigned int value);

int main() {
    unsigned int value;
    unsigned int n;

    cin >> value;
    cin >> n;

    vector<unsigned int> coins(n);

    for (unsigned int i = 0; i < n; i++) {
        unsigned int coin_value;
        cin >> coin_value;
        coins[i] = coin_value;
    }

    pair<unsigned int, unsigned int> min_coins = find_min_coins_to_reach_value(coins, value);

    cout << min_coins.first << " " << min_coins.second << endl;

    return 0;
}

unsigned int min(unsigned int a, unsigned int b) {
    unsigned int min;
    if (a < b) {
        min = a;
    } else {
        min = b;
    }

    return min;
}

pair<unsigned int, unsigned int> find_min_coins_to_reach_value(const vector<unsigned int>& coins, unsigned int value) {
    vector<vector<unsigned int>> m =
            vector<vector<unsigned int>>(coins.size(), vector<unsigned int>(value + 1, 0));
    vector<vector<unsigned int>> e =
            vector<vector<unsigned int>>(coins.size(), vector<unsigned int>(value + 1, 0));

    for (unsigned int j = 1; j < value + 1; j++) {
        if (coins[0] < j) {
            m[0][j] = j / coins[0];
            if (j - m[0][j] * coins[0] != 0) {
                m[0][j]++;
            }
            e[0][j] = m[0][j] * coins[0] - j;
        } else {
            m[0][j] = 1;
            e[0][j] = coins[0] - j;
        }
    }

    for (unsigned int i = 1; i < coins.size(); i++) {
        for (unsigned int j = 1; j < value + 1; j++) {
            m[i][j] = m[i - 1][j];
            e[i][j] = e[i - 1][j];
            if (coins[i] <= j ) {
                if (e[i][j - coins[i]] == e[i - 1][j]) {
                    m[i][j] = min(m[i][j - coins[i]] + 1, m[i - 1][j]);
                    e[i][j] = e[i][j - coins[i]];
                } else if (e[i][j - coins[i]] < e[i - 1][j]) {
                    m[i][j] = m[i][j - coins[i]] + 1;
                    e[i][j] = e[i][j - coins[i]];
                }
            } else {
                if (coins[i] < coins[i - 1]) {
                    m[i][j] = 1;
                    e[i][j] = coins[i] - j;
                }
            }
        }
    }

    return {value + e[coins.size() - 1][value], m[coins.size() - 1][value]};
}
