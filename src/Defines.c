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

#define IS_IT_NUM(BASE,val) (IS_IT_##BASE(val) || val == '.')
#define IS_IT_BIN(val) (val == '0' || val == '1')
#define IS_IT_OCT(val) ('0' <= val && val <= '7')
#define IS_IT_DEC(val) ('0' <= val && val <= '9')
#define IS_IT_HEX(val) (IS_IT_DEC(val) || 'A' <= val && val <= 'F' || 'a' <= val && val <= 'f')

#define IS_IT_OPERATOR(val) (val == '+' || val == '-' || val == '*' || val == '/' || val == '^' || val == 'v')
#define IS_IT_PARENTHESIS(val) (val == '(' || val == ')')

#define PRECEDENCE_LVL1_CHECK (*peek_char(&oppStack) == '^' || *peek_char(&oppStack) == 'v')
#define PRECEDENCE_LVL2_CHECK (*peek_char(&oppStack) == '*' || PRECEDENCE_LVL1_CHECK)
typedef double solution_t;

#define NUM_FLOATER (nummode == 3 ? 16.0 : nummode == 2 ? 10.0 : nummode == 1 ? 8.0 : 2.0)

