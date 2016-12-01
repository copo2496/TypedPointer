#ifndef LISTS_H
#define LISTS_H

#define INT (type_t)1
#define STR (type_t)2

typedef unsigned int long ptr_64, type_t;
typedef ptr_64 listhead;
typedef ptr_64 * list_t;

#define pack_node(ptr, type) (type << 52 & 0xfff000000000000) | (ptr & 0x0000ffffffffffff)
#define unpack_node(ptr) (ptr & 0x0000ffffffffffff)
#define mark_node(ptr) ptr = (ptr | 0x0001000000000000);
#define check_node_mark(ptr) ( (ptr & 0x0001000000000000) >> 48)
#define check_node_type(ptr) ( (ptr & 0xfff000000000000) >> 52)

#define for_each_element(head, i) {   \
  list_t list = lists.get_list(head); \
  int size = lists.get_size(head);    \
  for (int i = 0; i < size; i++)      \
}                                     \

listhead __list_new(int size) {
  list_t list = (list_t)malloc(size*sizeof(list_t));
  listhead head = (ptr_64)size << 48 | (ptr_64)list;
  return head;
}

list_t __list_get_list(listhead head) {
  return (list_t)(head & 0x0000ffffffffffff);
}

int __list_get_size(listhead head) {
  return (int)((head & 0xffff000000000000) >> 48);
}

void __list_add(listhead head, void * element, type_t type) {
  list_t list = __list_get_list(head);
  int size = __list_get_size(head);
  int i = 0;
  while (check_node_mark(list[i++]));
  list[i - 1] = mark_node(list[i - 1]);
  if (i == size - 1) {
    listhead next_head = __list_new(10);
    __list_add(next_head, element, type);
    list[i] = next_head;
  } else {
    list[i] = pack_node((ptr_64)element, type);
  }
}

void __list_print(listhead head) {
  list_t list = __list_get_list(head);
  int size = __list_get_size(head);
  int i = 0;
  do {
    if (i == size - 1) {
      __list_print(list[i]);
    }
    if (check_node_type(list[i]) == 1) {
      printf("%i\n", *(int*)unpack_node(list[i]));
    } else if (check_node_type(list[i]) == 2) {
      printf("%s\n", (char*)unpack_node(list[i]));
    }
  } while (check_node_mark(list[i++]));
}

struct list_toolbox {
  listhead (*new)(int);
  list_t (*get_list)(listhead);
  int (*get_size)(listhead);
  void (*add)(listhead, void*, type_t);
  void (*print)(listhead);
} lists = {&__list_new,
  &__list_get_list,
  &__list_get_size,
  &__list_add,
  &__list_print};

#endif
