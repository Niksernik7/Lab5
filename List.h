#ifndef TEACHER
#define TEACHER
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
// 30.05.2022
typedef struct Item {
    size_t data;
    struct Item* next;
} Item;
// 30.05.2022
typedef struct List {
    Item* head;
    Item* tail;
} List;
// 30.05.2022
List* list_new();
// 30.05.2022
void list_delete(List* list);
// 30.05.2022
void list_print(const List* list);
// 30.05.2022
int list_push_back(List* list, int data);
// 30.05.2022
int list_insert(List* list, int data);
// 30.05.2022
void list_remove(List* list, int data);
// 30.05.2022
int list_pop_front(List* list);
// 30.05.2022
int list_set(List* list, int index, int data);
// 30.05.2022
int list_get(List* list, int index);
// 30.05.2022
int list_size(List* list);
// 30.05.2022
void list_resize(List* list, int newSize, int fill);
#endif
