#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<set>
#include<queue>

using namespace std;

int N;	//��������
int K;	//��·����
int INF = 1000000000;
string start;	//��ʼ����
int graph[201][201];
map<string, int> stringToInt;	//��������->���б��
map<int, string> intToString;	//���б��->��������
int happy[201];	//ÿ�����еĿ�����
int d[201];
set<int> pre[201];
vector<int> tempPath;
vector<int> path;
int optValue1 = 0;
double optValue2 = 0;
int count = 0;
bool inq[201] = {false};
int countInq[201] = {0};

bool spfa(int s);
void dfs(int nowVisit);

int main() {
	cin >> N >> K >> start;
	stringToInt[start] = 0;	//��ʼ���б��Ϊ0
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
	spfa(0);
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

bool spfa(int s) {
	for(int i = 0; i < N; i++) {
		d[i] = INF;
	}
	d[s] = 0;
	queue<int> q;
	q.push(s);
	inq[s] = true;
	countInq[s]++;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int v = 0; v < N; v++){
			if(graph[u][v] != INF){
				if(d[u] + graph[u][v] < d[v]){
					d[v] = d[u] + graph[u][v];
					pre[v].clear();
					pre[v].insert(u);
					if(!inq[v]){
						q.push(v);
						inq[v] = true;
						countInq[v]++;
						if(countInq[v] >= N){
							return false;
						}
					}
				}else if(d[u] + graph[u][v] == d[v]){
					pre[v].insert(u);
					if(!inq[v]){
						q.push(v);
						inq[v] = true;
						countInq[v]++;
						if(countInq[v] >= N){
							return false;
						}
					}
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