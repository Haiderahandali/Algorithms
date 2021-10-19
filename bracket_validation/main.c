#include "stack.h"
#include "validbracket.h"
#define STACK_MAX_SIZE 100

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage:\nProvide a single argument as a string for bracket matching "
           " program\n");
    return 0;
  }

  mystack_t *st = CreateStack(STACK_MAX_SIZE);
  IsValid(st, argv[1]) ? printf("Valid\n") : printf("not valid\n");

  Close(&st);
}