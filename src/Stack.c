//
// Created by emre on 20.01.2024.
//

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define StackInitialize(T) \
typedef struct Stack_##T { \
    T *real; \
    size_t size; \
} Stack_##T; \
\
void push_##T(Stack_##T *stack, T val) { \
    stack->size++; \
    T *newReal = (T *)realloc(stack->real, stack->size * sizeof(T)); \
    if (newReal == NULL) { \
        perror("Stack_##T couldn't be allocated (PUSH)"); \
        exit(EXIT_FAILURE); \
    } \
    stack->real = newReal; \
    stack->real[stack->size - 1] = val; \
} \
\
T pop_##T(Stack_##T *stack) { \
    if (stack->size == 0) { \
        exit(EXIT_FAILURE); \
    } \
    T popVal = stack->real[stack->size - 1]; \
    stack->size--; \
    T *newReal = realloc(stack->real, stack->size * sizeof(T)); \
    if (newReal == NULL && stack->size > 0) { \
        perror("Stack_##T couldn't be allocated (POP)"); \
        exit(EXIT_FAILURE); \
    } \
    stack->real = newReal; \
    return popVal; \
} \
\
T* peek_##T(Stack_##T *stack) { \
    return stack->size ? stack->real+(stack->size - 1) : 0; \
} \
\
void Stack_##T##_RealFlush(Stack_##T *stack) { \
    free(stack->real); \
}

#define newStack(T) { .real = (T*)malloc(sizeof(T)) , .size = 0 }

StackInitialize(double);
StackInitialize(char);



