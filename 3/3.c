#include <stdio.h>
#include <stdlib.h>


struct List{
  int val;
  struct List *next;
};

// insertion
void insert(struct List **list, int value) {
  // construct the new node
  struct List *newNode = (struct List*)malloc(sizeof(struct List));
  newNode->val = value;
  newNode->next = 0;

  if (*list == 0) {
    // if the list is a empty list
    // insert directly
    *list = newNode;
    return;
  }
  if ((*list)->val >= value) {
    // insert before head
    newNode->next = *list;
    *list = newNode;
    return;
  }
  // travel the list
  struct List *cur; // mark current node
  for (cur = *list; cur; cur = cur->next) {
    if (cur->next) {
      // if cur has next
      if (cur->val < value && cur->next->val >= value) {
        // insert newNode after cur
        newNode->next = cur->next;
        cur->next = newNode;
        return;
      }
    } else {
      // if cur has not next node
      // let newNode to be cur's next
      cur->next = newNode;
      return;
    }
  }
}

int findIntersectionFirst(struct List *a, struct List *b, int *ret) {
  // just run alternatively
  while (a && b) {
    if (a->val > b->val) {
      b = b->next;
    } else if (a->val < b->val) {
      a = a->next;
    } else {
      *ret = a->val;
      return 1; // find, the result stored in ret
    }
  }
  return 0; // not found
}


struct List *list1, *list2;
int main() {
  insert(&list1, 5);
  insert(&list1, 5);
  insert(&list1, 3);
  // list1: 3 -> 5 -> 5
  insert(&list2, 2);
  insert(&list2, 4);
  insert(&list2, 5);
  insert(&list2, 3);
  // list2: 2 -> 3 -> 4 -> 5
  int ret;
  if (findIntersectionFirst(list1, list2, &ret) == 1) {
    printf("the first same element is %d\n", ret);
  } else {
    printf("not found same element\n");
  }
  return 0;
}
