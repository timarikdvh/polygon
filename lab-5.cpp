#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>

using namespace std;
using namespace chrono;

void combSort(vector<int>& arr) {
    int gap = arr.size();
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = max(1, gap * 10 / 13);
        swapped = false;
        for (size_t i = 0; i < arr.size() - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void countingSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    for (int num : arr) count[num]++;
    size_t index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i]-- > 0) arr[index++] = i;
    }
}

void bucketSort(vector<int>& arr) {
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    // Количество ведер: максимум 1000 или меньше, если элементов в массиве меньше
    int bucketCount = min(1000, static_cast<int>(arr.size()));
    vector<vector<int>> buckets(bucketCount);

    // Распределение элементов по ведрам
    for (int num : arr) {
        int bucketIndex = (bucketCount * (num - minVal)) / range;
        if (bucketIndex == bucketCount) bucketIndex--; // Обеспечение корректного индекса
        buckets[bucketIndex].push_back(num);
    }

    // Очистка исходного массива и объединение отсортированных ведер
    arr.clear();
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
        for (int num : bucket) {
            arr.push_back(num);
        }
    }
}

vector<int> createBestCase(size_t size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    return arr;
}

vector<int> createWorstCase(size_t size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    reverse(arr.begin(), arr.end());
    return arr;
}

vector<int> createWorstCaseCombSort(size_t size) {
    vector<int> arr(size);
    vector<int> buffer(size);
    iota(buffer.begin(), buffer.end(), 1);
    size_t left = 0;
    size_t right = buffer.size() - 1;

    while (left <= right) {
        if (right >= left) {
            arr.push_back(buffer[right--]);
        }
        if (left <= right) {
            arr.push_back(buffer[left++]);
        }
    }
    return arr;
}

vector<int> createWorstCaseCountingSort(size_t size) {
    vector<int> arr(size);
    int j = 1;
    for(int i = 0;i < size; i++){
        arr.push_back(j);
        j++;
        if (j == 10000){
            j = 1;
        }
    }

    return arr;
}

vector<int> createWorstCaseBucketSort(size_t size) {
    vector<int> arr(size);
    int j = 1;
    for(int i = 0;i < size; i++){
        arr.push_back(j);
        j++;
        if (j == 10000){
            j = 1;
        }
    }

    return arr;
}

void testSorting(void (*sortFunction)(vector<int>&), const string& name, const vector<int>& testArray) {
    vector<int> arr = testArray;
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto end = high_resolution_clock::now();
    cout << name << ": " << duration_cast<milliseconds>(end - start).count() << "ms" << endl;
}

int main() {
    size_t size = 50000;

//    for (int i = 0; i < 20; i++){
//        vector<int> bestCase = createBestCase(size);
//        cout << "\nTesting Bucket Sort:" << size << endl;
//        testSorting(bucketSort, "Best Case", bestCase);
//        size += 50000;
//    }

    size = 100000;
    int move = 1;
    int j = move;

    cout << "\nTesting Comb Sort:" << size <<  endl;
    for (int i = 0; i < 50; i++){
        vector<int> worstCaseCombSort = createWorstCaseCombSort(size);
        testSorting(combSort, "Worst Case", worstCaseCombSort);
        size += j;
        if (j == move){
            j = -move;
        } else{
            j = move;
        }
    }

    cout << "\nTesting Counting Sort:" << size <<  endl;
    for (int i = 0; i < 50; i++){
        vector<int> worstCaseCountingSort = createWorstCaseBucketSort(size);
        testSorting(countingSort, "Worst Case", worstCaseCountingSort);
        size += j;
        if (j == move){
            j = -move;
        } else{
            j = move;
        }
    }

    cout << "\nTesting Bucket Sort:" << size <<  endl;
    for (int i = 0; i < 50; i++){
        vector<int> worstCaseBucketSort = createWorstCaseBucketSort(size);
        testSorting(bucketSort, "Worst Case", worstCaseBucketSort);
        size += j;
        if (j == move){
            j = -move;
        } else{
            j = move;
        }
    }

//    vector<int> worstCaseCountingSort = createWorstCase(size);
//    vector<int> worstCaseBucketSort = createWorstCase(size);
//
//    cout << "Testing Comb Sort " << size << ": "<< endl;
//    testSorting(combSort, "Best Case", bestCase);
//    testSorting(combSort, "Worst Case", worstCaseCombSort);
//
//    cout << "\nTesting Counting Sort:" << endl;
//    testSorting(countingSort, "Best Case", bestCase);
//    testSorting(countingSort, "Worst Case", worstCaseCountingSort);
//
//    cout << "\nTesting Bucket Sort:" << endl;
//    testSorting(bucketSort, "Best Case", bestCase);
//    testSorting(bucketSort, "Worst Case", worstCaseBucketSort);
//
//    return 0;
}
