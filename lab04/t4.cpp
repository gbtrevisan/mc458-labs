#include <vector>
#include <string>
#include <iostream>

using namespace std;

#define ACCOUNT_DIGITS_BLOCKS_NUMBER 6
#define ACCOUNT_DIGITS_NUMBER 26

void radix_sort(vector<string>& v);

int main() {
    unsigned int n;
    vector<string> accounts;

    cin >> n;

    accounts.reserve(n);

    for (unsigned int i = 0; i < n; i++) {
        string account_number;

        for (unsigned int j = 0; j < ACCOUNT_DIGITS_BLOCKS_NUMBER; j++) {
            string account_digit;
            cin >> account_digit;
            account_number += account_digit;
        }

        accounts.push_back(account_number);
    }

    radix_sort(accounts);

    vector<pair<string, int>> diff_accounts;
    string current = accounts[0];
    diff_accounts.emplace_back(pair<string, int>(current, 1));

    for (unsigned int i = 1; i < accounts.size(); i++) {
        if (equal(current.begin(), current.end(), accounts[i].begin())) {
            diff_accounts[diff_accounts.size() - 1].second++;
        } else {
            diff_accounts.emplace_back(accounts[i], 1);
            current = accounts[i];
        }
    }

    cout << diff_accounts.size() << endl;

    for (auto & account : diff_accounts) {
        cout << account.first.substr(0, 2) << " ";
        cout << account.first.substr(2, 8) << " ";
        cout << account.first.substr(10, 4) << " ";
        cout << account.first.substr(14, 4) << " ";
        cout << account.first.substr(18, 4) << " ";
        cout << account.first.substr(22, 4) << " ";
        cout << account.second << endl;
    }

    return 0;
}

unsigned int get_position(char c) {
    if (c >= 48 && c <= 57) {
        return c - 48;
    }

    return c - 55;
}

void counting_sort_to_hex_digits(vector<string>& v, unsigned int digit) {
    vector<pair<vector<string>, int>> counter(16, pair<vector<string>, int>(vector<string>(), 0));

    for (auto & x : v) {
        unsigned int pos = get_position(x[digit]);
        counter[pos].first.push_back(x);
        counter[pos].second++;
    }

    for (int i = 1; i < 16; i++) {
        counter[i].second += counter[i - 1].second;
    }

    for (int j = 0; j < 16; j++) {
        while(!counter[j].first.empty()) {
            string s = counter[j].first[counter[j].first.size() - 1];
            v[counter[j].second - 1] = s;
            counter[j].second--;
            counter[j].first.pop_back();
        }
    }
}

void radix_sort(vector<string>& v) {
    for (int i = ACCOUNT_DIGITS_NUMBER - 1; i >= 0; i--) {
        counting_sort_to_hex_digits(v, i);
    }
}
