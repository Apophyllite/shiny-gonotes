#include <iostream>
#include <vector>
#include <set>

//Dijkstra 算法

int min_cost = -1;

void Search(int cidx, const std::vector<std::vector<int> >& distMap, std::vector<int>& visited, int cost) {
	if (visited.size() == distMap.size()) {
		int lastcost = distMap[visited.back()][0];
		if (min_cost > cost + lastcost) {
			min_cost = cost + lastcost;
		} else if (min_cost < 0) {
			min_cost  = cost + lastcost;
		}
		return ;
	}
	for (int i = 1; i < distMap.size(); i++) {
		if (std::find(visited.begin(), visited.end(), i) != visited.end()) {
			continue;
		}
		cost += distMap[visited.back()][i];
		visited.push_back(i);
		Search(i, distMap, visited, cost);
		visited.pop_back();
		cost -= distMap[visited.back()][i];
	}
}
//找到从idx出发的最短路径
int find_shortest_poi (const std::vector<std::vector<int> >& distMap, int idx) {
	int min = -1, min_idx = idx;
	for (int i = 0; i < distMap[idx].size(); i++) {
		if (i == idx) continue;
		if (min > 0 and distMap[idx][i] > 0 and min > distMap[idx][i]) {
			min_idx = i;
			min = distMap[idx][i];
		}
	}
	return min_idx;
}

int main() {
	int N = 0;
	std::cin >> N;
	std::vector<std::vector<int> > distMap;
	for (int i = 0; i < N; i++) {
		std::vector<int> distmap;
		for (int j = 0; j < N; j++) {
			int d;
			std::cin >> d;
			distmap.push_back(d);
		}
		distMap.push_back(distmap);
	}
	std::vector<int> visited;
	visited.push_back(0);
	int cost = 0;
	Search(0, distMap, visited, cost);
	std::cout << min_cost << std::endl;
	return 0;
}
