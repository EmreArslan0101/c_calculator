//
// Created by emre on 20.01.2024.
//

typedef struct number{
    double val;
}number;

typedef struct operation{
    char val;
}operation;

typedef struct type{
    char isNumOrOperation;
    void* data;
}type;

number* newNum(int val) {
    number* _number = (number*)malloc(sizeof(number));
    _number->val = val;
    return _number;
}

operation* newOpp(char val) {
    operation* _operation = (operation*)malloc(sizeof(operation));
    _operation->val = val;
    return _operation;
}

type* newType(void* data, char isNumOrOperation) {
    type* _type = (type*)malloc(sizeof(type));
    _type->data = data;
    _type->isNumOrOperation = isNumOrOperation;
    return _type;
}