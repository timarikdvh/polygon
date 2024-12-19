#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <chrono>

using namespace std;

double bestScore = numeric_limits<double>::max();
vector<vector<double>> bestClusters;

//Функция для проверки метрики в кластерах
void clustersDistCheck(vector<vector<double>> clusters) {
    double score = 0;

    for (auto & cluster : clusters) {
        double middle_sum = 0;
        double sum = 0;

        for (double j : cluster) {
            sum += j;
        }

        middle_sum = sum / cluster.size();

        for (double j : cluster) {
            score += abs(j - middle_sum);
        }
    }

    if (score < bestScore) {
        bestScore = score;
        bestClusters = clusters;
    }
}

// Функция для перебора всех кластеров
void generateClusters(vector<vector<double>>& clusters, vector<double>& points, int index) {
    if (index == points.size()) {
        clustersDistCheck(clusters);
        return;
    }

    for (int i = 0; i < clusters.size(); ++i) {
        clusters[i].push_back(points[index]);
        generateClusters(clusters, points, index + 1);
        clusters[i].pop_back();
    }
}

int main() {
    vector<double> points = {9, 10.4, -21, -10, 450.3, 1230, 3478, -1234, -123.12, -21,12, 123, -1239};
    int numClusters = 5;

    vector<vector<double>> clusters(numClusters);

    auto start_time = chrono::high_resolution_clock::now();
    generateClusters(clusters, points, 0);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end_time - start_time;


    cout << "Best Score: " << bestScore << endl;
    cout << "Best Clusters: " << endl;
    for (const auto& cluster : bestClusters) {
        cout << "[ ";
        for (double point : cluster) {
            cout << point << " ";
        }
        cout << "]" << endl;
    }

    cout << "Time: " << elapsed_time.count() << " seconds." << endl;

    return 0;
}