#include <stdio.h>
#include <string.h>
#define MAXN 15
// the result matrix (allocate only)
int Mat[MAXN][MAXN];
int n;
// constant direction array
// 'dr' means delta row
// 'dc' means delta column
// here is 'down', 'right', 'up', 'left'
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

char inputBuffer[10];

int isInRange(int r, int c) { return r >= 0 && c >= 0 && r < n && c < n; }

void print() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%3d ", Mat[i][j]);
    }
    printf("\n");
  }
  fflush(stdout);
}

int main() {
  while (scanf("%d", &n) == 1) {
    if (!(4 <= n && n <= 15)) {
      printf("illegal input!\n");
      break;
    }
    int isInDetail = 0;
    printf("Show Detail? (Y for Yes, N for No) (default no): \n");
    fflush(stdout);
    scanf("%s", inputBuffer);
    isInDetail = inputBuffer[0] == 'Y';
    int r = -1, c = 0;     // start point
    int d = 0;             // initialize direction
    int totalStep = n * n; // total step counter
    int i = 0;
    while (i < totalStep) {
      int newR = r + dr[d], newC = c + dc[d];
      if (isInRange(newR, newC) && !Mat[newR][newC]) {
        // if (newR, newC) is in range, and there has been not visited yet,
        // mark counter here.
        Mat[newR][newC] = ++i;
        // update position
        r = newR;
        c = newC;
      } else {
        // next direction
        d = (d + 1) % 4;
      }
      if (isInDetail) {
        printf("step #%d:\n", i);
        print();
        printf("\n");
      }
    }
    // print the final matrix
    if (!isInDetail) {
      print();
    }
    memset(Mat, 0, sizeof(Mat));
  }
  return 0;
}
