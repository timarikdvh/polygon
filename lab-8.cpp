#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>
using namespace std;
std::random_device r;
std::default_random_engine e(r());
std::uniform_int_distribution<int> dist(0,20);

int minTaps(int n, vector<int>& ranges) {
    vector<int> maxRange(n + 1, 0);

    for (int i = 0; i <= n; ++i) {
        int left = max(0, i - ranges[i]);
        int right = min(n, i + ranges[i]);
        maxRange[left] = max(maxRange[left], right);
    }

    int taps = 0, currentEnd = 0, farthest = 0;

    for (int i = 0; i <= n; ++i) {
        if (i > farthest) {
            return -1;
        }

        farthest = max(farthest, maxRange[i]);

        if (i == currentEnd) {
            ++taps;
            currentEnd = farthest;
            if (currentEnd >= n) {
                break;
            }
        }
    }

    return taps;
}

int main(){
    vector<int> nums;
    for (int i = pow(10, 7); i < pow(10, 9); i += pow(10,7)) {
        for (int j = 0; j < i; j++){
            nums.push_back(dist(e));
        }
        auto start_time = chrono::high_resolution_clock::now();
        cout << minTaps(i - 1,nums) << endl;
//        for (int el : nums){
//            cout << el << " ";
//        }
//        cout << endl;
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_time = end_time - start_time;
        cout << "Time: " << elapsed_time.count() << " seconds. Elems: " << i << endl;
        nums.clear();
    }
}