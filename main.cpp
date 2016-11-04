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
                         {1, 0, 1, 1, 0},
                         {0, 1, 1, 0, 0},
                         {1, 0, 0, 0, 1},
                         {1, 0, 0, 1, 0}};


    ListGraph listGraph(size);
    int **adjacency = new int *[size];
    for (int i = 0; i < size; i++)
        adjacency[i] = new int[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            int element = graph[i][j];
            adjacency[i][j] = element;
            if (element == 1) {
                listGraph.addLink(i, j);
            }
        }
    }

    GraphAdjacency graphAdjacency(size, adjacency);
    const std::vector<Triangle> vector = graphAdjacency.getTriangles();
    const std::vector<Triangle> vectorList = listGraph.getTriangles();
    std::cout << "AdjacencyGraph\n";
    printTriangles(vector);
    std::cout << "ListGraph\n";
    printTriangles(vectorList);
    return 0;
}

