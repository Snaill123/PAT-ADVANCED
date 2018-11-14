#include<iostream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

int N;
int M;
int INF = 1000000000;
int lenGraph[510][510];
int timeGraph[510][510];
int source;
int destination;
int dLen[510];
set<int> preLen[510];
vector<int> tempPathLen;
vector<int> pathLen;
int minTime = INF;
bool inqLen[510] = {false};
int countInqLen[510] = {0};
int dTime[510];
set<int> preTime[510];
vector<int> tempPathTime;
vector<int> pathTime;
int minCross = INF;
bool inqTime[510] = {false};
int countInqTime[510] = {0};

bool spfaLen(int s);
void dfsLen(int nowVisit);

bool spfaTime(int s);
void dfsTime(int nowVisit);

int main() {
	cin >> N >> M;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			lenGraph[i][j] = timeGraph[i][j] = INF;
		}
	}
	int V1, V2, one_way, length, time;
	for(int i = 0; i < M; i++) {
		cin >> V1 >> V2 >> one_way >> length >> time;
		lenGraph[V1][V2] = length;
		timeGraph[V1][V2] = time;
		if(one_way != 1) {
			lenGraph[V2][V1] = length;
			timeGraph[V2][V1] = time;
		}
	}
	cin >> source >> destination;
	spfaLen(source);
	dfsLen(destination);
	spfaTime(source);
	dfsTime(destination);
	if(pathLen == pathTime) {
		printf("Distance = %d; Time = %d:", dLen[destination], dTime[destination]);
		for(int i = pathLen.size() - 1; i >= 0; i--) {
			printf(" %d", pathLen[i]);
			if(i != 0) {
				printf(" ->");
			}
		}
		printf("\n");
	} else {
		printf("Distance = %d:", dLen[destination]);
		for(int i = pathLen.size() - 1; i >= 0; i--) {
			printf(" %d", pathLen[i]);
			if(i != 0) {
				printf(" ->");
			}
		}
		printf("\n");
		printf("Time = %d:", dTime[destination]);
		for(int i = pathTime.size() - 1; i >= 0; i--) {
			printf(" %d", pathTime[i]);
			if(i != 0) {
				printf(" ->");
			}
		}
		printf("\n");
	}

}

bool spfaLen(int s) {
	for(int i = 0; i < N; i++) {
		dLen[i] = INF;
	}
	dLen[s] = 0;
	queue<int> q;
	q.push(s);
	inqLen[s] = true;
	countInqLen[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inqLen[u] = false;
		for(int v = 0; v < N; v++) {
			if(lenGraph[u][v] != INF) {
				if(dLen[u] + lenGraph[u][v] < dLen[v]) {
					dLen[v] = dLen[u] + lenGraph[u][v];
					preLen[v].clear();
					preLen[v].insert(u);
					if(!inqLen[v]){
						q.push(v);
						inqLen[v] = true;
						countInqLen[v]++;
						if(countInqLen[v] >= N){
							return false;
						}
					}
				}else if(dLen[u] + lenGraph[u][v] == dLen[v]) {
					preLen[v].insert(u);
					if(!inqLen[v]){
						q.push(v);
						inqLen[v] = true;
						countInqLen[v]++;
						if(countInqLen[v] >= N){
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

void dfsLen(int nowVisit) {
	tempPathLen.push_back(nowVisit);
	if(nowVisit == source) {
		int time = 0;
		for(int i = tempPathLen.size() - 1; i > 0; i--) {
			time += timeGraph[tempPathLen[i]][tempPathLen[i - 1]];
		}
		if(time < minTime) {
			pathLen = tempPathLen;
			minTime = time;
		}
		tempPathLen.pop_back();
		return;
	}
	set<int>::iterator it;
	for(it = preLen[nowVisit].begin(); it != preLen[nowVisit].end(); it++) {
		dfsLen(*it);
	}
	tempPathLen.pop_back();
}

bool spfaTime(int s) {
	for(int i = 0; i < N; i++) {
		dTime[i] = INF;
	}
	dTime[s] = 0;
	queue<int> q;
	q.push(s);
	inqTime[s] = true;
	countInqTime[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inqTime[u] = false;
		for(int v = 0; v < N; v++) {
			if(timeGraph[u][v] != INF) {
				if(dTime[u] + timeGraph[u][v] < dTime[v]) {
					dTime[v] = dTime[u] + timeGraph[u][v];
					preTime[v].clear();
					preTime[v].insert(u);
					if(!inqTime[v]){
						q.push(v);
						inqTime[v] = true;
						countInqTime[v]++;
						if(countInqTime[v] >= N){
							return false;
						}
					}
				}else if(dTime[u] + timeGraph[u][v] == dTime[v]) {
					preTime[v].insert(u);
					if(!inqTime[v]){
						q.push(v);
						inqTime[v] = true;
						countInqTime[v]++;
						if(countInqTime[v] >= N){
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

void dfsTime(int nowVisit) {
	tempPathTime.push_back(nowVisit);
	if(nowVisit == source) {
		if(tempPathTime.size() < minCross) {
			pathTime = tempPathTime;
			minCross = tempPathTime.size();
		}
		tempPathTime.pop_back();
		return;
	}
	set<int>::iterator it;
	for(it = preTime[nowVisit].begin(); it != preTime[nowVisit].end(); it++) {
		dfsTime(*it);
	}
	tempPathTime.pop_back();
}