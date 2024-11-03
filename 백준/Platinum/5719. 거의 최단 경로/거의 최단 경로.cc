#include<iostream>
#include<vector>
#include<queue>
#include<cstdio>

using namespace std;

#define INF 21e8

struct Compare {
	bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
		return a.second > b.second; // 두 번째 값을 기준으로 오름차순 정렬
	}
};

struct node {
	int now;
	int cost;
};

vector<node> map[501];
priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
int dis[501];
vector<int> route[501];


int N, M, S, D, U, V, P;

void dijk(int s, int d) {
	pq.push({ s, 0 });
	dis[s] = 0;
	while (!pq.empty()) {
		int now = pq.top().first;
		int cost = pq.top().second;
		pq.pop();
		for (int i = 0; i < map[now].size(); i++) {
			int next = map[now][i].now;
			if (dis[next] > cost + map[now][i].cost) {
				route[next].clear();
				route[next].push_back(now);
				dis[next] = cost + map[now][i].cost;
				pq.push({ next, dis[next] });
			}
			else if (dis[next] == cost + map[now][i].cost) {
				route[next].push_back(now);
			}
		}
	}
}

void dijk2(int s, int d) {
	pq.push({ s, 0 });
	dis[s] = 0;
	while (!pq.empty()) {
		int now = pq.top().first;
		int cost = pq.top().second;
		pq.pop();
		if (dis[now] < cost) continue; // 이미 최단 경로가 갱신된 경우 무시
		for (int i = 0; i < map[now].size(); i++) {
			int next = map[now][i].now;
			if (dis[next] > cost + map[now][i].cost) {
				route[next].clear();
				route[next].push_back(now);
				dis[next] = cost + map[now][i].cost;
				pq.push({ next, dis[next] });
			}
			else if (dis[next] == cost + map[now][i].cost) {
				route[next].push_back(now);
			}
		}
	}
}

void remove() {
	queue<int> q;
	vector<bool> visited(N, false); // 방문 체크용 배열
	q.push(D); // 목적지에서 시작하여 역추적
	visited[D] = true; // 시작점 방문 처리

	while (!q.empty()) {
		int n = q.front();
		q.pop();

		// n으로 가는 모든 이전 노드를 통해 최단 경로 간선 삭제
		for (int i = 0; i < route[n].size(); i++) {
			int prev = route[n][i]; // 이전 노드

			// prev 노드에서 n으로 가는 간선을 찾아 삭제
			for (auto it = map[prev].begin(); it != map[prev].end(); ++it) {
				if (it->now == n) {
					map[prev].erase(it); // 간선을 삭제
					break;
				}
			}

			// 이전 노드를 방문하지 않은 경우에만 큐에 추가
			if (!visited[prev]) {
				visited[prev] = true; // 방문 표시
				q.push(prev);
			}
		}
	}
}

int main() {

	while (1) {
		cin >> N >> M >> S >> D;
		if (N == 0 && M == 0) return 0;
		for (int i = 0; i < N; i++) {
			map[i].clear();
			route[i].clear();
		}
		for (int i = 0; i < M; i++) {
			cin >> U >> V >> P;
			map[U].push_back({ V, P });
		}
		for (int i = 0; i < N; i++) dis[i] = INF;
		dijk(S, D);
		remove();
		for (int i = 0; i < N; i++) dis[i] = INF;
		dijk2(S, D);
		if (dis[D] == INF) cout << -1 << endl;
		else cout << dis[D] << endl;
	}
}