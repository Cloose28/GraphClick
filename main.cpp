#include <iostream>
#include "Graph.cpp"

void printTriangles(std::vector<Triangle> vector) {
    for (int i = 0; i < vector.size(); ++i) {
        Triangle triangle = vector[i];
        std::cout << "Triangle: " << triangle.onePoint << " " << triangle.twoPoint << " "
                  << triangle.threePoint << "\n";
    }
}

int main() {
    int size = 5;
    int graph[][size] = {{0, 1, 0, 1, 1},
                         {1, 0, 1, 0, 0},
                         {0, 1, 0, 0, 0},
                         {1, 0, 0, 0, 1},
                         {1, 0, 0, 1, 0}};

    int **a = new int *[size];
    for (int i = 0; i < size; i++)
        a[i] = new int[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = graph[i][j];
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    GraphAdjacency graphAdjacency(size, a);
    const std::vector<Triangle> vector = graphAdjacency.getTriangles();
    printTriangles(vector);
    return 0;
}

