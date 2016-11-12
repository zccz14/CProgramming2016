#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30
#define MAXM 8
#define STUIDLEN 10
#define STUNAMELEN 20

struct Student {
  char id[STUIDLEN + 1];
  char name[STUNAMELEN + 1];
  float grade[MAXM];
  int gradeCnt;
  //
  float totGrade;
  float avgGrade;
};

struct Class {
  struct Student students[MAXN];
  int studentCnt;
};

void loadFromFile(FILE *file, struct Class *class) {
  fscanf(file, "%d", &(class->studentCnt));
  int i, j;
  for (i = 0; i < class->studentCnt; i++) {
    struct Student *stu = &(class->students[i]);
    stu->totGrade = 0;
    fscanf(file, "%s%s%d", stu->id, stu->name, &(stu->gradeCnt));
    for (j = 0; j < stu->gradeCnt; j++) {
      fscanf(file, "%f", &(stu->grade[j]));
      stu->totGrade += stu->grade[j];
    }
    stu->avgGrade = stu->totGrade / stu->gradeCnt;
  }
}

void saveToFile(FILE *file, struct Class *class) {
  fprintf(file, "%d\n", class->studentCnt);
  int i, j;
  for (i = 0; i < class->studentCnt; i++) {
    struct Student *stu = &(class->students[i]);
    fprintf(file, "%s\t%s\t%d\t", stu->id, stu->name, stu->gradeCnt);
    for (j = 0; j < stu->gradeCnt; j++) {
      fprintf(file, "%.2f\t", stu->grade[j]);
    }
    fprintf(file, "\n");
  }
}

int cmp(const void *a, const void *b) {
  return (((struct Student*)b)->totGrade - ((struct Student*)a)->totGrade);
}

void sort(struct Class *class) {
  qsort(class->students, class->studentCnt, sizeof(struct Student), cmp);
}

void printStu(FILE *file, struct Student *stu) {
  if (stu) {
    fprintf(file, "%s\t%s\t%.2f\t%.2f\t", stu->id, stu->name, stu->totGrade, stu->avgGrade);
    int j;
    for (j = 0; j < stu->gradeCnt; j++) {
      fprintf(file, "%.2f\t", stu->grade[j]);
    }
    fprintf(file, "\n");
  } else {
    fprintf(file, "Student Not Available\n");
  }
}

void print(FILE *file, struct Class *class, char *displayName) {
  fprintf(file, "class %s has %d student(s)\n", displayName, class->studentCnt);
  int i;
  fprintf(file, "Student ID\tName\tTotal\tAverage\tGrades\n");
  for (i = 0; i < class->studentCnt; i++) {
    printStu(file, &(class->students[i]));
  }
}

struct Student *search(struct Class *class, char *keyword) {
  for (int i = 0; i < class->studentCnt; i++) {
    struct Student *stu = &(class->students[i]);
    if (strcmp(keyword, stu->id) == 0 || strcmp(keyword, stu->name) == 0) {
      return stu;
    }
  }
  return 0;
}

struct Class A;

int main() {
  FILE *file;
  file = fopen("score.in", "r");
  loadFromFile(file, &A);
  fclose(file);
  // sort in desending order by total grade
  sort(&A);
  // print class
  print(stdout, &A, "SE 42");
  // search student by Stu.ID or Name
  printStu(stdout, search(&A, "CZ"));
  printStu(stdout, search(&A, "2141601025"));
  printStu(stdout, search(&A, "2161601001"));
  // save to t.out
  file = fopen("t.out", "w");
  print(file, &A, "SE 42");
  fclose(file);

  return 0;
}
