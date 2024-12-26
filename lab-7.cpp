#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;
std::random_device r;
std::default_random_engine e(r());
std::uniform_int_distribution<int> dist(1,100);

int maxCoins(vector<int>& nums) {
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    int n = nums.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int length = 2; length < n; ++length) {
        for (int left = 0; left < n - length; ++left) {
            int right = left + length;
            for (int k = left + 1; k < right; ++k) {
                dp[left][right] = max(
                        dp[left][right],
                        dp[left][k] + nums[left] * nums[k] * nums[right] + dp[k][right]);
            }
        }
    }

    return dp[0][n - 1];
}

int main(){
    vector<int> nums;
    for (int i = 100; i < 10000; i+=100) {
        for (int j = 0; j < i; j++){
            nums.push_back(dist(e));
        }
        auto start_time = chrono::high_resolution_clock::now();
        maxCoins(nums);
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_time = end_time - start_time;
        cout << "Time: " << elapsed_time.count() << " seconds. Elems: " << i << endl;
        nums.clear();
    }
}