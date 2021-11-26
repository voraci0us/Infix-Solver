#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// stack functions
Stack * createStack(){
    Stack * ret = (Stack *) malloc(sizeof(Stack));
    ret->size = 0;
    ret->cap = DEFAULT_CAP;
    ret->arr = (char *) malloc(ret->cap * sizeof(char));
    return ret;
}

// expand the stack by reallocating the array
Stack * expandStack(Stack * stack){
    stack->cap = stack->cap * 2;
    char * newArr = (char *) realloc(stack->arr, stack->cap * sizeof(char));
    if(newArr == NULL)
	    return NULL;
    stack->arr = newArr;
    return stack;
}

// remove the top element and return it
char pop(Stack * stack){
    if(stack->size == 0)
	    return IMPOSSIBLE;
    stack->size--;
    return stack->arr[stack->size];
}

// return the top element
char top(Stack * stack){
    if(stack->size == 0)
	    return IMPOSSIBLE;
    return stack->arr[stack->size-1];
}

// add an element to the top of the stack
void push(Stack * stack, char c){
    if(stack->size == stack->cap)
	    expandStack(stack);

    stack->arr[stack->size] = c;
    stack->size++;
}

// print the contents of the entire stack
void printStack(Stack * stack)
{
  printf("-----STACK CONTENTS----\n");
  for (int i = 0; i < stack->size; i++)
  {
    if (stack->arr[i] >= 0 && stack->arr[i] <= 9)
      printf("%d", stack->arr[i]);
    else
      printf("%c", stack->arr[i]);
    if (i != stack->size)
      printf(" ");
  }
  printf("\n");
  printf("-----END STACK CONTENTS----\n");
}
