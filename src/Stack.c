//
// Created by emre on 20.01.2024.
//

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Data.c"

typedef struct Stack{
   type* real;
   size_t size;
} Stack;

Stack newStack() {
     Stack stack = {
            .real = NULL,
            .size = 0
     };
     return stack;
}

void push(Stack* stack, type val) {

    stack->size++;

    type* newReal = (type*)realloc(stack->real,stack->size*sizeof(type));

    if(newReal == NULL) {
        perror("Stack couldn't allocated (PUSH) ");
        exit(EXIT_FAILURE);
    }

    stack->real = newReal;

    stack->real[stack->size-1] = val;

}

type pop(Stack* stack) {

    stack->size--;

    type popVal = stack->real[stack->size];

    type* newReal = (type*)realloc(stack->real,stack->size*sizeof(type));

    if(newReal == NULL && stack->size) {
        perror("Stack couldn't allocated (POP) ");
        exit(EXIT_FAILURE);
    }

    stack->real = newReal;

    return popVal;

}

type peek(Stack* stack) {
    return stack->real[stack->size-1];
}

void stackRealFlush(Stack* stack) {
    for(size_t i = 0;i<stack->size;i++) {
        free(stack->real[i].data);
    }
    free(stack->real);
}

// For debugging the stack

void printStack(Stack* stack) {

    printf("\n[");

    for(size_t i = 0;i<stack->size;i++) {
        if(stack->real[i].isNumOrOperation) {
            printf("%c",((operation*)(stack->real[i].data))->val);
        }
        else {
            printf("%lf",((number*)(stack->real[i].data))->val);
        }

        if(i<stack->size-1) printf(",");

    }

    printf("]");

}
