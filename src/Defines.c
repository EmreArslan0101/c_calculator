//
// Created by emre on 25.01.2024.
//
#define printArray(UNIT_FORMAT,ARRAY,SIZE) \
    printf("["); \
    for (size_t i = 0; i < SIZE; i++) { \
        printf(UNIT_FORMAT, ARRAY[i]); \
            if (i < SIZE - 1) { \
                printf(","); \
            } \
        } \
    printf("]\n");

#define printStack(UNIT_FORMAT,STACK) printArray(UNIT_FORMAT,STACK.real,STACK.size)

#define IS_IT_NUM(val) (47 < val && val < 58)
