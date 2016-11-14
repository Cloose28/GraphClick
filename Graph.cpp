#include <vector>
#include <iostream>

struct Triangle {
    int onePoint;
    int twoPoint;
    int threePoint;
};

class Graph {
private:
    int originalNode;
    std::vector<int> clicks;
    std::vector<Triangle> triangles;
protected:
    int n;
public:
    virtual std::vector<int> getLinks(int node) = 0;

    Graph(int n) : n(n) {}

    std::vector<Triangle> getTriangles() {
        triangles.clear();
        for (int i = 0; i < n; ++i) {
            originalNode = i;
            findClick(clicks, 0, i);
        }
        return triangles;
    }

    bool triangleExist(std::vector<int> clicks){
        if (triangles.size() == 0) return false;
        for (int i = 0; i < triangles.size(); ++i) {
            Triangle triangle = triangles[i];
            if (triangle.onePoint == clicks[0] && triangle.twoPoint == clicks[1] && triangle.threePoint == clicks[2]) {
                return true;
            }
        }
        return false;
    }

    std::vector<int>  sort(std::vector<int> clicks) {
        for (int i = 0; i < 2; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                if (clicks[i] > clicks[j]) {
                    int tmp = clicks[i];
                    clicks[i] = clicks[j];
                    clicks[j] = tmp;
                }
            }
        }
        return clicks;
    }

    void addTriangle(std::vector<int> clicks){
        clicks = sort(clicks);
        if (triangleExist(clicks)) {
            return;
        }
        Triangle triangle;
        triangle.onePoint = clicks[0];
        triangle.twoPoint = clicks[1];
        triangle.threePoint = clicks[2];
        triangles.push_back(triangle);
    }

    void findClick(std::vector<int> clicks, int level, int currentNode) {
        if (level == 3) {
            if (currentNode == originalNode) {
                addTriangle(clicks);
            } else {
                clicks.pop_back();
            }
            return;
        }
        clicks.push_back(currentNode);

        const std::vector<int> &links = getLinks(currentNode);
        for (int j = 0; j < links.size(); ++j) {
            findClick(clicks, level + 1, links[j]);
        }
        clicks.pop_back();
    }
};

class GraphAdjacency : public Graph {
public:
    GraphAdjacency(int n, int **graph) : Graph(n) {
        matrix = graph;
    }

    virtual std::vector<int> getLinks(int node) override {
        std::vector<int> links;
        for (int i = 0; i < n; ++i) {
            if (matrix[node][i] == 1) {
                links.push_back(i);
            }
        }
        return links;
    }

private:
    int **matrix;
};

class ListGraph : public Graph {
private:
    struct ListLink {
        int link;
        ListLink *next;
    };

    ListLink **listLinks;
public:
    ListGraph(int n) : Graph(n) {
        listLinks = new ListLink *[n];
        for (int i = 0; i < n; ++i) {
            ListLink *listLink = getEmptyLink();
            listLinks[i] = listLink;
        }
    }

    virtual std::vector<int> getLinks(int node) override {
        std::vector<int> links;
        ListLink *pListLink = listLinks[node];
        while (pListLink->link != -1) {
            links.push_back(pListLink->link);
            pListLink = pListLink->next;
        }
        return links;
    }

    void addLink(int n1, int n2) {
        ListLink *link = listLinks[n1];
        while (link->link != -1) {
            link = link->next;
        }
        link->link = n2;
        link->next = getEmptyLink();
    }

    ListLink *getEmptyLink() {
        ListLink *nextEmpty = new ListLink;
        nextEmpty->link = -1;
        return nextEmpty;
    }
};