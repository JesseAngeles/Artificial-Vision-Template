#ifndef AHC_H
#define AHC_H

#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>

struct Cluster
{
    std::vector<int> indices;
    std::vector<std::vector<float>> points;

    Cluster(const std::vector<int> &indices, const std::vector<std::vector<float>> &points)
        : indices(indices), points(points)
    {
    }

    Cluster(const Cluster &cluster) : indices(cluster.indices), points(cluster.points) {}
};

struct MergeStep
{
    int cluster_1;
    int cluster_2;
    float distance;
    int size;

    MergeStep(int c1, int c2, float d, int s)
        : cluster_1(c1), cluster_2(c2), distance(d), size(s) {}
};

class AHC
{
private:
    std::vector<std::vector<float>> data_points;
    std::vector<Cluster> clusters;
    std::vector<MergeStep> merge_history;
    int clusters_size;

    // Functions
    void initializeClusters();
    float calculateEuclideanDistance(const std::vector<float> &a, const std::vector<float> &b);
    void displayDistanceMatrix(const std::vector<std::vector<float>> &linkage_matrix);

public:
    // Constructor
    AHC(std::vector<std::vector<float>> points);

    // Functions
    void mergeStep(bool print_matrix = true);
    void merge(bool print_clusters = false, bool print_matrix = false);

    // Getters
    std::vector<std::vector<float>> getPoints() const { return data_points; }
    std::vector<Cluster> getClusters() const { return clusters; }
    std::vector<MergeStep> getMergeHistory() const { return merge_history; }

    // Setters
    void setPoints(std::vector<std::vector<float>> points) { this->data_points = points; }

    // Prints
    void displayClusters();
};

#endif // AHC_C