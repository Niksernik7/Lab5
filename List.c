#include "List.h"
// 30.05.2022 ����� ����
List* list_new() {
    return (List*)calloc(1, sizeof(List));
}
// 30.05.2022 ������� ���� 
void list_delete(List* list) {
    if (list == NULL)
        return;
    Item* ptr = list->head, * ptr_prev;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(list);
}
// 30.05.2022 �������� ���� 
void list_print(const List* list) {
    Item* ptr = list->head;
    while (ptr) {
        printf("%d  ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
// 30.05.2022 �������� �������� � �����
int list_push_back(List* list, int data) {
    Item* ptr = (Item*)malloc(sizeof(Item));
    if (!ptr) {
        return -1;
    }

    ptr->data = data;
    ptr->next = NULL;
    if (!list->head) {
        list->head = ptr;
        list->tail = ptr;
    }
    else {
        list->tail->next = ptr;
        list->tail = ptr;
    }
    return 0;
}
// 30.05.2022 �������� �� ������� 
int list_insert(List* list, int data) {
    Item* ptr = list->head, * ptr_prev = NULL;
    while (ptr && (ptr->data < data)) {
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    Item* new = (Item*)malloc(sizeof(Item));
    if (!new) {
        return -1;
    }
    new->data = data;
    new->next = ptr;
    if (ptr_prev) {
        ptr_prev->next = new;
    }
    else {
        list->head = new;
    }
    if (!ptr) {
        list->tail = new;
    }
    return 0;
}
// 30.05.2022 ������� ���� 
void list_remove(List* list, int data) {
    Item* ptr = list->head, * ptr_prev = NULL;
    while (ptr && ptr->data != data) {
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    if (!ptr) {
        return;
    }
    if (ptr == list->head) {
        list->head = ptr->next;
    }
    if (ptr == list->tail) {
        list->tail = ptr_prev;
    }
    if (ptr_prev) {
        ptr_prev->next = ptr->next;
    }
    free(ptr);
}
// 30.05.2022 ������ ������� � ������
int list_pop_front(List* list)
{
    assert(list != NULL);
    assert(list->head != NULL);

    int res = list->head->data;
    list_remove(list, res);

    return res;
}
// 30.05.2022 ���������� �������� �� �������
int list_set(List* list, int index, int data)
{
    Item* ptr = list->head;
    for (int i = 0; ptr != NULL && i < index; i++)
        ptr = ptr->next;
    if (ptr != NULL)
        ptr->data = data;
    else
        return 1;
    return 0;
}
// 30.05.2022 �������� �������� �� ������� 
int list_get(List* list, int index)
{
    Item* ptr = list->head;
    int res = 0;
    for (int i = 0; ptr != NULL && i < index; i++)
        ptr = ptr->next;
    if (ptr != NULL)
        res = ptr->data;
    else
        assert("index out of size");
    return res;
}
// 30.05.2022 ������� ������ �����
int list_size(List* list)
{
    assert(list != NULL);
    int res = 0;
    Item* ptr = list->head;
    while (ptr != NULL) {
        ptr = ptr->next;
        res++;
    }
    return res;
}
// 30.05.2022 �������� ������ ����� 
void list_resize(List* list, int newSize, int fill)
{
    assert(list != NULL);
    int oldSize = list_size(list);
    for (int i = 0; i < newSize - oldSize; i++)
        list_push_back(list, fill);

}
