#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<set>

using namespace std;

int N;	//城市数量
int K;	//道路条数
int INF = 1000000000;
string start;	//起始城市
int graph[201][201];
map<string, int> stringToInt;	//城市名称->城市编号
map<int, string> intToString;	//城市编号->城市名称
int happy[201];	//每个城市的快乐数
int d[201];
set<int> pre[201];
vector<int> tempPath;
vector<int> path;
int optValue1 = 0;
double optValue2 = 0;
int count = 0;

bool bellmanFord(int s);
void dfs(int nowVisit);

int main() {
	cin >> N >> K >> start;
	stringToInt[start] = 0;	//起始城市编号为0
	intToString[0] = start;
	string city;
	int happyness;
	for(int i = 1; i < N; i++) {
		cin >> city >> happyness;
		stringToInt[city] = i;
		intToString[i] = city;
		happy[i] = happyness;
	}
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			graph[i][j] = graph[j][i] = INF;
		}
	}
	string city1, city2;
	int cost;
	for(int i = 0; i < K; i++) {
		cin >> city1 >> city2 >> cost;
		int id1 = stringToInt[city1];
		int id2 = stringToInt[city2];
		graph[id1][id2] = graph[id2][id1] = cost;
	}
	bellmanFord(0);
	int destination = stringToInt["ROM"];
	dfs(destination);
	cout << count << " " << d[destination] << " " << optValue1 << " " << (int)optValue2 << endl;
	for(int i = path.size() - 1; i >= 0; i--) {
		cout << intToString[path[i]];
		if(i != 0) {
			cout << "->";
		}
	}
	cout << endl;
	return 0;
}

bool bellmanFord(int s) {
	for(int i = 0; i < N; i++) {
		d[i] = INF;
	}
	d[s] = 0;
	for(int i = 0; i < N - 1; i++) {
		for(int u = 0; u < N; u++) {
			for(int v = 0; v < N; v++) {
				if(graph[u][v] != INF) {
					if(d[u] + graph[u][v] < d[v]) {
						d[v] = d[u] + graph[u][v];
						pre[v].clear();
						pre[v].insert(u);
					} else if(d[u] + graph[u][v] == d[v]) {
						pre[v].insert(u);
					}
				}
			}
		}
	}
	for(int u = 0; u < N; u++) {
		for(int v = 0; v < N; v++) {
			if(graph[u][v] != INF) {
				if(d[u] + graph[u][v] < d[v]) {
					return false;
				}
			}
		}
	}
	return true;
}

void dfs(int nowVisit) {
	tempPath.push_back(nowVisit);
	if(nowVisit == 0) {
		count++;
		int value1 = 0;
		for(int i = tempPath.size() - 2; i >= 0; i--) {
			value1 += happy[tempPath[i]];
		}
		double value2 = value1 * 1.0 / (tempPath.size() - 1);
		if(value1 > optValue1) {
			optValue1 = value1;
			optValue2 = value2;
			path = tempPath;
		} else if(value1 == optValue1 && value2 > optValue2) {
			optValue2 = value2;
			path = tempPath;
		}
		tempPath.pop_back();
		return;
	}
	set<int>::iterator it;
	for(it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++){
		dfs(*it);
	}
	tempPath.pop_back();
}
