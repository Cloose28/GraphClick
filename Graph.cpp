#include <vector>
#include <iostream>

struct Triangle {
    int onePoint;
    int twoPoint;
    int threePoint;
};

class Graph {
private:
    int n;
    int *nodes;
public:
    virtual bool isLink(int n1, int n2) = 0;

    Graph(int n) : n(n) {
        nodes = new int[n];
        for (auto i = 0; i < n; ++i) {
            nodes[i] = i + 1;
        }
    }

    std::vector<Triangle> getTriangles() {
        std::vector<Triangle> triangles;
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if (isLink(i, j) && isLink(i, k) && isLink(j, k)) {
                        Triangle triangle;
                        triangle.onePoint = i + 1;
                        triangle.twoPoint = j + 1;
                        triangle.threePoint = k + 1;
                        triangles.push_back(triangle);
                    }
                }
            }
        }
        return triangles;
    }
};

class GraphAdjacency : public Graph {
public:
    GraphAdjacency(int n, int** graph) : Graph(n) {
        matrix = graph;
    }

private:
    int** matrix;

    virtual bool isLink(int n1, int n2) override {
        return matrix[n1][n2] == 1;
    }
};

class ListGraph : public Graph {
private:
    struct ListLink {
        int link;
        ListLink *next;
    };

    ListLink** listLinks;
public:
    ListGraph(int n) : Graph(n) {
        listLinks = new ListLink*[n];
        for (int i = 0; i < n; ++i) {
            ListLink *listLink = getEmptyLink();
            listLinks[i] = listLink;
        }
    }

    virtual bool isLink(int n1, int n2) override {
        ListLink* link = listLinks[n1];
        while (link->link != -1) {
            if (link->link == n2) {
                return true;
            }
            link = link->next;
        }
        return false;
    }

    void addLink(int n1, int n2) {
        ListLink* link = listLinks[n1];
        while (link->link != -1) {
            link = link->next;
        }
        link->link = n2;
        link->next = getEmptyLink();
    }

    ListLink* getEmptyLink() {
        ListLink* nextEmpty = new ListLink;
        nextEmpty->link = -1;
        return nextEmpty;
    }
};