#include<bits/stdc++.h>

using namespace std;

class DisjointSet {
public:
	vector<int>size, parent;

	DisjointSet(int n) {
		parent.resize(n, 0);
		size.resize(n, 1);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}

	int findParent(int node) {
		if (node == parent[node]) {
			return node;
		}
		return parent[node] = findParent(parent[node]);
	}

	void unionBySize(int u, int v) {
		int pu = findParent(u);
		int pv = findParent(v);
		if (pu == pv)	return ;
		if (size[pv] > size[pu]) {
			// pv is bigger
			parent[pu] = pv;
			// smaller gets attached to bigger

			size[pv] += size[pu];
		}
		else {
			parent[pv] = pu;
			size[pu] += size[pv];
		}
	}

};




int solve(vector<pair<int, int>>&v) {
	int n = v.size();
	vector<pair<int, pair<int, int>>>edges;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int weight = abs(v[i].first - v[j].first) + abs(v[i].second - v[j].second);
			edges.push_back({weight, {i, j}});
		}
	}
	//O(N2)

	sort(edges.begin(), edges.end());//O(NLOGN)
	DisjointSet ds(n);
	int sum = 0;
	for (int i = 0; i < edges.size(); i++) {
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		int weight = edges[i].first;
		if (ds.findParent(u) != ds.findParent(v)) {// O(4Alpha)
			ds.unionBySize(u, v);
			sum += weight;
		}
	}
	return sum;
}
// total tc is o(n2)
int main() {

	vector<pair<int, int>>v = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};

	cout << solve(v) << endl;
}
