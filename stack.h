// default capacity of a stack
#define DEFAULT_CAP 5
// what to return from pop() or top() if there are no values available
#define IMPOSSIBLE -1

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

// stack structure
typedef struct Stack Stack;
struct Stack{
    int size, cap;
    char * arr;
};

// stack prototypes
Stack * createStack();
Stack * expandStack(Stack *);
char pop(Stack *);
char top(Stack * stack);
void push(Stack *, char);
void printStack();

#endif
