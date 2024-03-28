#include <stdio.h>
#include <queue>
#include <time.h>

//#define RUN

// 41654
using namespace std;

typedef unsigned int uint;


uint A[502][502], D[3][502][502];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

enum Player {
	John, Cloyee, Festival
};

struct point {
	unsigned int x, y, w;
	point() {};
	point(uint _x, uint _y, uint _who) : x(_x), y(_y), w(_who) {};
} now;

int main(int argc, char** argv) {

	freopen("input.txt", "r", stdin);

#ifndef RUN
	time_t start = clock();
#endif // !RUN


	uint TC, S, C, i, j, tmp;
	
	scanf("%u", &TC);
	for (uint tc = 1; tc <= TC; tc++) {
		uint jX, jY, cX, cY, eX, eY;
		scanf("%u %u %u %u %u %u %u %u", &S, &C, &jX, &jY, &cX, &cY, &eX, &eY);

		for (i = 1; i <= S; i++) {
			for (j = 1; j <= C; j++) {
				scanf("%u", &A[i][j]);
				D[0][i][j] = D[1][i][j] = D[2][i][j] = -1;
			}
		}

		for (i = 0; i < C + 2; i++) {
			A[0][i] = D[0][0][i] = D[1][0][i] = D[2][0][i] = 0;
			A[S + 1][i] = D[0][S + 1][i] = D[1][S + 1][i] = D[2][S + 1][i] = 0;
		}
		for (i = 1; i < S + 2; i++) {
			A[i][0] = D[0][i][0] = D[1][i][0] = D[2][i][0] = 0;
			A[i][C + 1] = D[0][i][C + 1] = D[1][i][C + 1] = D[2][i][C + 1] = 0;
		}

		queue<point> q;
		q.push(point(jX, jY, John));	// 존의 위치
		q.push(point(cX, cY, Cloyee));	// 클로이의 위치
		q.push(point(eX, eY, Festival));	// 축제의 위치
		D[0][jX][jY] = D[1][cX][cY] = D[2][eX][eY] = 0;

		while (!q.empty()) {
			now = q.front(); 	q.pop();
			uint xx = now.x;
			uint yy = now.y;
			uint me = now.w;

			for (uint k = 0; k < 4; k++) {
				uint nX = xx + dx[k];
				uint nY = yy + dy[k];

				if (me == Festival)
					tmp = D[Festival][xx][yy] + A[nX][nY];
				else
					tmp = D[me][xx][yy] + A[xx][yy];

				if (D[me][nX][nY] > tmp) {
					D[me][nX][nY] = tmp;
					q.push(point(nX, nY, me));
				}
			}
		}

		// 존과 클로이가 따로 이동할 때의 경비
		uint result = D[John][eX][eY] + D[Cloyee][eX][eY];
		for (i = 1; i <= S; i++) {
			for (j = 1; j <= C; j++) {	// i,j 지점에서 만나 이동하는 경우
				tmp = D[John][i][j] + D[Cloyee][i][j] + D[Festival][i][j];
				if (result > tmp) result = tmp;
			}
		}

		printf("#%u %u \n", tc, result);
	}

#ifndef RUN
	time_t end = clock();
	printf("time : %f\n", (double)(end - start));
#endif // !RUN


	return 0;
}