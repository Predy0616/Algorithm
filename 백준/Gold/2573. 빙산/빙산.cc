#include<iostream>
#include<queue>
using namespace std;

int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };

int n, m;
int matrix[301][301] = { 0 };
int visited[301][301] = { 0 };
queue<pair<int, int>> q;

int check() {
	int cnt = 0;
	bool isEnd = true;
	int visited[301][301] = { 0 };

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (matrix[i][j] > 0 && visited[i][j] == 0) {
				isEnd = false;
				cnt++;
				q.push({ i, j });
				visited[i][j] = 1;
				while (!q.empty()) {
					int nx=q.front().second, ny=q.front().first;
					q.pop();
					for (int k = 0; k < 4; k++) {
						if (nx+dx[k]>=0 && nx + dx[k] < m && ny + dy[k]>=0 && ny + dy[k]< n && matrix[ny + dy[k]][nx + dx[k]] > 0 && visited[ny + dy[k]][nx + dx[k]] == 0) {
							q.push({ ny + dy[k] , nx + dx[k] });
							visited[ny + dy[k]][nx + dx[k]] = 1;
						}
					}
				}
			}
		}
	}
	if (isEnd) return 0;
	if (cnt > 1) return 1;
	return 2;
}

int main() {
	int year = 0;

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> matrix[i][j];
			if (matrix[i][j] > 0) visited[i][j] = 1;
		}
	}
	while (check() == 2) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (visited[i][j] == 0) {
					for (int k = 0; k < 4; k++) {
						if (j + dx[k] >= 0 && j + dx[k] < m && i + dy[k] >= 0 && i + dy[k] < n && matrix[i + dy[k]][j + dx[k]] > 0) matrix[i + dy[k]][j + dx[k]]--;
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (matrix[i][j] == 0) {
					visited[i][j] = 0;
				}
			}
		}
		year++;
	}

	if (check()) cout << year;
	else cout << 0;

	return 0;
}