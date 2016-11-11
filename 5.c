#include <stdio.h>
#define MAXS 10
char S[MAXS + 1];
char C[MAXS + 1];

int main() {
  // input string
  while (scanf("%s", S) == 1) {
    // status
    int i = 0, cnt = 0;
    int curC = 0;
    char lastCh = 0;
    // travel the string
    do {
      if (S[i] == lastCh) {
        cnt++;
      } else {
        if (cnt > 0) {
          if (cnt > 1) {
            C[curC++] = cnt + '0';
          }
          // copy the character to C
          C[curC++] = lastCh;
        }
        // update last character and set counter = 1
        lastCh = S[i];
        cnt = 1;
      }
    } while (S[i++]);
    C[curC++] = 0; // end the string
    printf("%s\n", C);
  }
  return 0;
}
