#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

double bestScore = numeric_limits<double>::max();
vector<vector<double>> bestClusters;

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

// Рекурсивная функция для перебора всех кластеров
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
    vector<double> points = {9, 10.4, -21, -10, 450.3, -2318, 344, 3987, -5};
    int numClusters = 5;

    vector<vector<double>> clusters(numClusters);

    generateClusters(clusters, points, 0);

    cout << "Best Score: " << bestScore << endl;
    cout << "Best Clusters: " << endl;
    for (const auto& cluster : bestClusters) {
        cout << "[ ";
        for (double point : cluster) {
            cout << point << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}