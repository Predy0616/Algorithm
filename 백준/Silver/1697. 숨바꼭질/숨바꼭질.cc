#include<iostream>
#include<queue>
using namespace std;

#define endl "\n"
#define MAX 100001

queue<int> q;
int visited[MAX];
int start, target;

void bfs() {
	while (!q.empty()) {
		int now = q.front();
		if (now == target) break;
		q.pop();
		if (visited[now * 2] == 0 && now * 2 >= 0 && now * 2 < MAX) {
			visited[now * 2] = visited[now]+1;
			q.push(now * 2);
		}
		if (visited[now + 1] == 0 && now + 1 >= 0 && now + 1 < MAX) {
			visited[now + 1] = visited[now] + 1;
			q.push(now + 1);
		}
		if (visited[now-1]==0 && now - 1 >= 0 && now - 1 < MAX) {
			visited[now - 1] = visited[now] + 1;
			q.push(now - 1);
		}
	}
	return;
}

int main() {
	cin >> start >> target;
	q.push(start);
	visited[start] = 1;
	bfs();
	cout << visited[target] - 1;
}