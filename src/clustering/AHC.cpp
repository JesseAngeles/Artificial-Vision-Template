#include "clustering/AHC.h"

AHC::AHC(std::vector<std::vector<float>> data_points)
    : data_points(data_points)
{
    initializeClusters();
}

// Functions

void AHC::initializeClusters()
{
    for (int i = 0; i < data_points.size(); i++)
        clusters.push_back(Cluster({i}, {data_points[i]}));
    clusters_size = clusters.size();
}

void AHC::mergeStep(bool display_distance_matrix)
{
    std::vector<std::vector<float>> distance_matrix;

    int closest_cluster_i = -1;
    int closest_cluster_j = -1;
    float minimum_distance = std::numeric_limits<float>::max();

    // Iterate through all clusters in a bubble-like manner
    for (int i = 0; i < clusters.size() - 1; i++)
    {
        std::vector<float> distances;
        for (int j = i + 1; j < clusters.size(); j++)
        {

            // Iterate through all elements of each cluster
            for (const std::vector<float> &point_a : clusters[i].points)
            {
                for (const std::vector<float> &point_b : clusters[j].points)
                {
                    float distance = calculateEuclideanDistance(point_a, point_b);
                    if (distance < minimum_distance)
                    {
                        minimum_distance = distance;
                        closest_cluster_i = i;
                        closest_cluster_j = j;
                    }
                }
            }
            distances.push_back(minimum_distance);
        }
        distance_matrix.push_back(distances);
    }

    if (display_distance_matrix)
        displayDistanceMatrix(distance_matrix);

    Cluster merged_cluster(clusters[closest_cluster_i]);
    merged_cluster.indices.insert(merged_cluster.indices.end(),
                                  clusters[closest_cluster_j].indices.begin(),
                                  clusters[closest_cluster_j].indices.end());

    merged_cluster.points.insert(merged_cluster.points.end(),
                                 clusters[closest_cluster_j].points.begin(),
                                 clusters[closest_cluster_j].points.end());

    merged_cluster.indices.push_back(clusters_size++);

    merge_history.push_back(MergeStep(
        clusters[closest_cluster_i].indices[clusters[closest_cluster_i].indices.size() - 1],
        clusters[closest_cluster_j].indices[clusters[closest_cluster_j].indices.size() - 1],
        minimum_distance,
        clusters[closest_cluster_i].points.size() + clusters[closest_cluster_j].points.size()));

    if (closest_cluster_i > closest_cluster_j)
        std::swap(closest_cluster_i, closest_cluster_j);

    clusters.erase(clusters.begin() + closest_cluster_j);
    clusters.erase(clusters.begin() + closest_cluster_i);

    clusters.push_back(merged_cluster);
}

void AHC::merge(bool print_cluster, bool print_matrix)
{

    while (clusters.size() > 1)
    {
        if (print_cluster)
            displayClusters();
        mergeStep(print_matrix);
    }
}

float AHC::calculateEuclideanDistance(const std::vector<float> &point_a, const std::vector<float> &point_b)
{
    float sum = 0.0f;
    for (size_t i = 0; i < point_a.size(); ++i)
    {
        sum += std::pow(point_a[i] - point_b[i], 2);
    }
    return std::sqrt(sum);
}

void AHC::displayClusters()
{
    for (int i = 0; i < clusters.size(); i++)
    {
        std::cout << "Cluster " << i << " ( ";
        for (const int &index : clusters[i].indices)
            std::cout << index << " ";
        std::cout << "):\n";

        for (const std::vector<float> &point : clusters[i].points)
        {
            for (const float &coordinate : point)
                std::cout << coordinate << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void AHC::displayDistanceMatrix(const std::vector<std::vector<float>> &distance_matrix)
{
    std::cout << "------------------------------------------------------\n";
    std::cout << "Matrix\t";

    for (int i = 1; i < clusters.size(); i++)
    {
        std::cout << i << "( ";
        for (const int &index : clusters[i].indices)
            std::cout << index << " ";
        std::cout << ")\t\t";
    }

    std::cout << std::endl;

    int cluster_index = -1;
    for (const std::vector<float> &distances : distance_matrix)
    {
        std::cout << ++cluster_index << "( ";
        for (const int &index : clusters[cluster_index].indices)
            std::cout << index << " ";
        std::cout << ")\t";

        for (const float &distance : distances)
            std::cout << std::fixed << std::setprecision(1) << distance << "\t\t";
        std::cout << std::endl;
    }
    std::cout << "\n";
}
