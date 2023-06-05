#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

class Graph 
{
private:
    int numVertic;
    int numDig;
    std::vector<int> weights;
    std::vector<std::vector<int>> hammingMatrix;

public:
    Graph(int vertices, int dig): numVertic(vertices),
                         numDig(dig),
                         weights(vertices),
                         hammingMatrix(vertices, std::vector<int>(vertices)) {}
    int hammingDist(int x, int y)
    {
        int dist = 0;
        int val = x ^ y;
        while(val != 0)
        {
            dist += val % numDig;
            val /= numDig;
        }
        return dist;
    }

    void createGraph() 
    {
        for (int i = 0; i < numVertic; ++i)
            weights[i] = i;

        for (int i = 0; i < numVertic; ++i)
            for (int j = 0; j < numVertic; ++j){
                if (i != j)
                {
                    int dist = hammingDist(weights[i], weights[j]);
                    hammingMatrix[i][j] = dist;
                } else {
                    hammingMatrix[i][j] = 0;
                }
            }
    }

    void printSelf()
    {
        std::cout << "Графф весов Хэмминга: " << std::endl;
        for (int i = 0; i < numVertic; ++i){
            for(int j = 0; j < numVertic; ++j){
                std::cout << hammingMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<int>> findConnectedSubgraphs(int minWeight) {
        std::vector<std::vector<int>> subgraphs;
        std::vector<bool> visited(numVertic, false);

        for (int i = 0; i < numVertic; i++) {
            if (!visited[i]) {
                std::vector<int> subgraph;
                std::queue<int> queue;
                queue.push(i);
                visited[i] = true;
                while (!queue.empty()) {
                    int vertex = queue.front();
                    queue.pop();

                    subgraph.push_back(vertex);

                    for (int j = 0; j < numVertic; j++) {
                        if (hammingMatrix[vertex][j] >= minWeight && !visited[j]) {
                            queue.push(j);
                            visited[j] = true;
                        }
                    }
                }

                subgraphs.push_back(subgraph);
            }
        }

        return subgraphs;
    }
};

int main() {
    int numVertices = 8;
    int minWeight = 3;
    int systemDig = 2;
    Graph graph(numVertices, systemDig);
    graph.createGraph();
    graph.printSelf();
    std::vector<std::vector<int>> connectedSubgraphs = graph.findConnectedSubgraphs(minWeight);
    std::cout << "Связанные подграфы с весом ребер >= " << minWeight << " при системе счисения ="<< systemDig <<":" << std::endl;
    for (const auto& subgraph : connectedSubgraphs) {
        for (const auto& vertex : subgraph) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}