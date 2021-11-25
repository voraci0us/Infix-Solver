#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define MAX_CHARS 100

int preced(char c){
    if(c == '+' || c == '-')
	    return 1;
    if(c == '*' || c == '/')
	    return 2;
    if(c == '^')
	    return 3;
    return 0;
}

void infixToPostfix(char * str){
    Stack * stack = createStack();

    // create a string to store the postfix conversion
    // (will be at most the size of the infix expression)
    int length = 0;
    while(str[length])
        length++;
    char out[length];

    int i, outIndex;
    i = outIndex = 0;
    while(str[i]){
        // if it's an integer, output it
        if(str[i] >= '0' && str[i] <= '9'){
            out[outIndex] = str[i];
            outIndex++;
        }
        // if it's an opening parenthesis, push it to the stack
        else if(str[i] == '('){
            push(stack, str[i]);
        }
        // if it's a closing parenthesis, pop all operands up to the next opening parenthesis
        else if(str[i] == ')'){
            char tmp = top(stack);
            while(tmp != '('){
                out[outIndex] = pop(stack);
                fprintf(stderr, "To close parentheses, copied over %c\n", out[outIndex]);
                outIndex++;
                tmp = top(stack);
            }
        }
        // otherwise it's an operator
        else{
            // print everything of higher or equal precedence
            while(stack->size > 0 && preced(str[i]) <= preced(top(stack))){
                out[outIndex] = pop(stack);
                fprintf(stderr, "Copied over %c\n", out[outIndex]);
                if(out[outIndex] != ')' && out[outIndex != '('])
                    outIndex++;
            }
            // then push it to the stack
            fprintf(stderr, "Pushing %c\n", str[i]);
            push(stack, str[i]);
        }
	    i++;
    }

    // when we finish iterating over the input string,
    // output any operands that are left in the stack
    char tmp = top(stack);
    while(stack->size > 0){
        tmp = top(stack);
        if(tmp == ')' || tmp == '('){
            pop(stack);
            continue;
        }
        out[outIndex] = pop(stack);
        fprintf(stderr, "At the end, copied over %c\n", out[outIndex]);
        outIndex++;
    }

    // copy the postfix expression to the original array the infix expression
    // was stored in and append a null terminator
    i = 0;
    while(i < outIndex){
        str[i] = out[i];
        i++;
    }
    str[outIndex] = '\0';
}

void sanitize(char * str){
    int length = 0;
    while(str[length])
        length++;
    char out[length];
    fprintf(stderr,"Sanitizing a string of length %d...\n", length);

    int i = 0;
    int outIndex = 0;
    while(str[i]){
        if((str[i] >= '0' && str[i] <= '9')
            || str[i] == '(' || str[i] == ')'
            || str[i] == '+' || str[i] == '-'
            || str[i] == '*' || str[i] == '/'
            || str[i] == '^'){
            out[outIndex] = str[i];
            outIndex++;
        }
        i++;
    }

    i = 0;
    while(i < outIndex){
        str[i] = out[i];
        i++;
    }
    str[outIndex] = '\0';
}

int power(int a, int b){
    if(b == 0)
        return 1;
    int ret = a;
    while(b > 1){
        ret *= a;
        b--;
    }
    return ret;
}

int evaluateOperator(char op, char a, char b){
    if(op == '+')
        return (a + b);
    else if(op == '-')
        return (b - a);
    else if(op == '*')
        return (a * b);
    else if(op == '^')
        return power(b, a);
}

int evaluatePostfix(char * str){
    Stack * stack = createStack();

    int i = 0;
    while(str[i]){
        int a, b;
        if(str[i] >= '0' && str[i] <= '9'){
            push(stack, str[i] - '0');
        }
        else{
            a = pop(stack);
            b = pop(stack);
            push(stack, evaluateOperator(str[i], a, b));
        }
        i++;
    }
    return pop(stack);
}

int main(){
    // input the infix expression
    char str[MAX_CHARS];
    fgets(str, MAX_CHARS, stdin);
    printf("\nYou inputed:\n");
    printf("%s\n", str);

    // sanitize the input
    sanitize(str);
    printf("After sanitization:\n");
    printf("%s\n\n", str);

    // convert to postfix notation
    infixToPostfix(str);
    printf("After conversion to postfix:\n");
    printf("%s\n\n", str);

    printf("Value of the expression:\n");
    printf("%d\n", evaluatePostfix(str));
    return 0;
}
