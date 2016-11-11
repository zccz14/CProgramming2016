#include <stdio.h>
#define N 20
int data[N];
#define R(x, y) ((x) < (y))
int main() {
  scanf("%d", data);
  for (int i = 1; i < N; i++) {
    int newComing;
    scanf("%d", &newComing);
    int j;
    for (j = i - 1; j >= 0 && R(newComing, data[j]); j--) {
      data[j + 1] = data[j];
    }
    data[j + 1] = newComing;
  }
  for (int i = 0; i < N; i++) {
    printf("%d ", data[i]);
  }
  return 0;
}
