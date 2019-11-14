#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const long long int INF = LLONG_MAX;

struct Graph
{
    std::vector<std::vector< std::pair<int,int> > > nodes;
    int number_of_nodes;
    int number_of_edge;
};

void CreateGraph(Graph &graph, int &start, int &finish);
long long int Dijkstra(Graph &graph, int start, int finish);

int main()
{
    int start;
    int finish;
    long long int res;
    Graph graph;

    CreateGraph(graph, start, finish);

    res = graph.number_of_nodes > 0 ? Dijkstra(graph, start - 1, finish - 1) : -1;
    if(res < 0) {
        std::cout << "No solution" << std::endl;
    } else {
        std::cout << res << std::endl;
    }
    return 0;
}

long long int Dijkstra(Graph &graph, int start, int finish)
{
    std::vector<long long int> distance(graph.number_of_nodes);

    std::priority_queue<std::pair<long long int, int>, std::vector<std::pair<long long int, int> >, std::greater<std::pair<long long int, int> > > PQ;

    for(int i = 0; i < graph.number_of_nodes; ++i) {
        distance[i] = INF;
    }
    distance[start] = 0;
    PQ.push(std::make_pair(0, start));

    while(!PQ.empty()) {
        int active = PQ.top().second;
        PQ.pop();

        std::vector<std::pair<int, int> >::iterator i;
        for (i = graph.nodes[active].begin(); i != graph.nodes[active].end(); ++i) {
            int tmp = (*i).first;
            int weight = (*i).second;

            if (distance[tmp] > distance[active] + weight) {
                distance[tmp] = distance[active] + weight;
                PQ.push(std::make_pair(distance[tmp], tmp));
            }
        }
    }
    if(distance[finish] == INF) {
        return -1;
    }
    return distance[finish];
}

void CreateGraph(Graph &graph, int &start, int &finish) {
    int first;
    int second;
    int weight;
    std::cin >> graph.number_of_nodes
             >> graph.number_of_edge
             >> start
             >> finish;
    graph.nodes.resize(graph.number_of_nodes);
    while(std::cin >> first
                   >> second
                   >> weight) {
        graph.nodes[first - 1].push_back(std::make_pair(second - 1, weight));
        graph.nodes[second - 1].push_back(std::make_pair(first - 1, weight));
    }
}
