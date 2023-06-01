#include<iostream>
using namespace std;

struct pos { int x, y, type; };
int N, M, k=0, ans=65;
int map[8][8] = { 0 };
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
pos cctv[8];

void copy(int ar[8][8], int arr[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			ar[i][j] = arr[i][j];
		}
	}
}

void sol(int num, int dir) {
	if (num == k) {
		int answer = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == 0) answer++;
			}
		}
		if (answer < ans) ans = answer;
		/*cout << "num : " << num << "   dir : " << dir << "   answer : " << ans << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << map[i][j];
			}
			cout << endl;
		}
		*/
		return;
	}
	for (int i = 1; i < 8; i++) {	//정면(전부)
		int dtx = cctv[num].x + dx[dir] * i;
		int dty = cctv[num].y + dy[dir] * i;
		if (dtx >= M || dtx < 0 || dty < 0 || dty >= N) break;
		if (map[dty][dtx] == 6) break;
		map[dty][dtx] = 9;
	}
	dir += 2;
	dir %= 4;
	if (cctv[num].type == 2 || cctv[num].type == 4 || cctv[num].type == 5) {
		for (int i = 1; i < 8; i++) {	//후면(2, 4, 5)
			int dtx = cctv[num].x + dx[dir] * i;
			int dty = cctv[num].y + dy[dir] * i;
			if (dtx >= M || dtx < 0 || dty < 0 || dty >= N) break;
			if (map[dty][dtx] == 6) break;
			map[dty][dtx] = 9;
		}
	}
	dir += 1;
	dir %= 4;
	if (cctv[num].type == 3 || cctv[num].type == 4 || cctv[num].type == 5) {
		for (int i = 1; i < 8; i++) {	//왼쪽면(3, 4, 5)
			int dtx = cctv[num].x + dx[dir] * i;
			int dty = cctv[num].y + dy[dir] * i;
			if (dtx >= M || dtx < 0 || dty < 0 || dty >= N) break;
			if (map[dty][dtx] == 6) break;
			map[dty][dtx] = 9;
		}
	}
	dir += 2;
	dir %= 4;
	if (cctv[num].type == 5) {
		for (int i = 1; i < 8; i++) {	//오른쪽면(5)
			int dtx = cctv[num].x + dx[dir] * i;
			int dty = cctv[num].y + dy[dir] * i;
			if (dtx >= M || dtx < 0 || dty < 0 || dty >= N) break;
			if (map[dty][dtx] == 6) break;
			map[dty][dtx] = 9;
		}
	}
	int temp[8][8];
	for (int i = 0; i < 4; i++) {
		copy(temp, map);
		sol(num + 1, i);
		copy(map, temp);
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			cin >> map[i][j];
			if ((map[i][j] > 0) && (map[i][j] < 6)) {
				cctv[k].y = i;
				cctv[k].x = j;
				cctv[k++].type = map[i][j];
			}
		}
	}
	int temp[8][8];
	for (int i = 0; i < 4; i++) {
		copy(temp, map);
		sol(0, i);
		copy(map, temp);
	}
	cout << ans;
}