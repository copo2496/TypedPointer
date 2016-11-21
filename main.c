#include <stdlib.h>
#include <stdio.h>

typedef enum types {
  INT = 1,
  CHAR = 2,
} type_t;

union gentype {
  int i;
  char c;
};

typedef unsigned long int ptr_64;

static inline ptr_64 pack_ptr(void * ptr, type_t type) {
  return (ptr_64)type << 48 | (ptr_64)ptr;
}

static inline void unpack_ptr(void * ptr, ptr_64 tptr, type_t * type) {
  *type = (ptr_64)(tptr & 0xffff000000000000);
  ptr = (void*)(tptr & 0x0000ffffffffffff);
}

/**
Attempts to have macros which define variables to store
data from typed pointers.
Difficulties:
  1 - We need to use an if statement because the type is evaluated at runtime... but then the variable is in that scope
  2 - ...
Currently trying to find a way for this to work. It goes against the grain
of how C works in general, so this is more experimental. Probably won't work.
**/

#define GET_INT(var, ptr) {             \
  int var = *(int*)ptr;                 \
}                                       \

#define GET_ELEMENT(var, tptr) {        \
  void * ptr;                           \
  type_t type = INT;                    \
  unpack_ptr(ptr, tptr, &type);         \
                                        \
}                                       \

int main(int argc, char * argv[]) {
}
