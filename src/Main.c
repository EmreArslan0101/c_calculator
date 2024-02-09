//
// Created by emre on 20.01.2024.
//

#pragma pack(1)
#pragma GCC optimize("unroll-loops","O3")

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "Stack.c"
#include "Defines.c"

typedef char nummode_t;

double miniSolve(double val1,double val2,char opperand) {
    switch(opperand) {
        case '+':
            return val1+val2;
        case '-':
            return val1-val2;
        case '*':
            return val1*val2;
        case '/':
            return val1/val2;
        case '^':
            return pow(val1,val2);
        case 'v':
            return pow(val1,1/val2);
        default:
            perror("Invalid opperand has been detected");
            exit(EXIT_FAILURE);
    }
}

void errorAt(size_t i,char* buffer,size_t bufferRealSize) {
    printf("\x1b[31m""Invalid character in operation string at %ld\n",i);

    for(size_t j = 0;j<bufferRealSize-1;j++){
        if(j == i) {
            printf("\033[4m""%c""\033[0m""\x1b[31m",buffer[j]);
        }
        else {
            printf("%c",buffer[j]);
        }
    }

    printf("%c""\x1b[0m",buffer[bufferRealSize-1]);

    exit(EXIT_FAILURE);

};

char* bufferHandler(char* buffer) {

    size_t bufferRealSize = strlen(buffer);

    //INVALID CHARACTER CHECK

    if(buffer[0] == '/' || buffer[0] == '*' || buffer[0] == '^') {
        printf("\x1b[31m""Invalid character in operation string at 0 , \"/\", \"*\" or \"^\" cannot be used as the initial character of operation\n");
        printf("%s""\x1b[0m",buffer);
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0;i<bufferRealSize-1;i++) {

        if(IS_IT_OPERATOR(buffer[i])) {

            if(IS_IT_OPERATOR(buffer[i+1]))
                errorAt(i+1,buffer,bufferRealSize);

            if(buffer[i+1] == 10)
                errorAt(i,buffer,bufferRealSize);

        }
        else {
            switch(buffer[i]) {
                case '0':
                    break;
                case 'x': {
                        //HEXADECIMAL NUMBER CHECK
                        if(buffer[i-1] != '0')
                            errorAt(i, buffer,bufferRealSize);

                        while(IS_IT_NUM(HEX,buffer[i+1]))
                            i++;

                        i++;

                        if(!IS_IT_OPERATOR(buffer[i]) && buffer[i] != 10)
                            errorAt(i,buffer,bufferRealSize);

                    }
                    break;
                case 'b': {
                        //BINARY NUMBER CHECK
                        if(buffer[i-1] != '0')
                            errorAt(i, buffer,bufferRealSize);

                        while(IS_IT_NUM(BIN,buffer[i+1]))
                            i++;

                        i++;

                        if(!IS_IT_OPERATOR(buffer[i]) && buffer[i] != 10)
                            errorAt(i,buffer,bufferRealSize);

                    }
                    break;
                case 'o': {
                        //OCTAL NUMBER CHECK
                        if(buffer[i-1] != '0')
                            errorAt(i, buffer,bufferRealSize);

                        while(IS_IT_NUM(OCT,buffer[i+1]))
                            i++;

                        i++;

                        if(!IS_IT_OPERATOR(buffer[i]) && buffer[i] != 10)
                            errorAt(i,buffer,bufferRealSize);

                    }
                    break;
                default: {
                        while(IS_IT_NUM(DEC,buffer[i]))
                            i++;
                    }
                    break;
            }

        }

    }

    //INVALID CHARACTER CHECK

    //PARENTHESIS CHECK

    int parenthesisCount = 0;

    for(size_t i = 0;i<bufferRealSize;i++) {
        if(buffer[i] == '(') {
            if(i != 0 && (buffer[i-1] == ')' || IS_IT_HEX(buffer[i-1]))) {
                errorAt(i-1,buffer,bufferRealSize);
            }
            if(i != bufferRealSize && IS_IT_OPERATOR(buffer[i+1])) {
                errorAt(i+1,buffer,bufferRealSize);
            }
            parenthesisCount++;
        }
        if(buffer[i] == ')') {
            if(i != 0 && IS_IT_OPERATOR(buffer[i-1])) {
                errorAt(i-1,buffer,bufferRealSize);
            }
            if(i != bufferRealSize && (buffer[i+1] == '(' || IS_IT_HEX(buffer[i+1]))) {
                errorAt(i+1,buffer,bufferRealSize);
            }
            parenthesisCount--;
        };
    }

    if(parenthesisCount > 0) {
        perror("Less parenthesis must be used");
        exit(EXIT_FAILURE);
    }

    if (parenthesisCount < 0){
        perror("More parenthesis must be used");
        exit(EXIT_FAILURE);
    }

    //PARENTHESIS CHECK

    //SPECIAL CONDITION CHECK

    if(buffer[0] == '-' || buffer[0] == '+') {

        char *newBuffer = (char *)malloc(1 + bufferRealSize + 1);
        newBuffer[0] = '0';
        newBuffer = strcat(newBuffer, buffer);
        newBuffer[bufferRealSize+1] = 0;
        free(buffer);
        return newBuffer;

    }

    //SPECIAL CONDITION CHECK

    return buffer;

}

double solver(char* data) {

    Stack_double finalStack = newStack(double);
    Stack_char oppStack = newStack(char);
    //Alternative modes are for making easier the flattening the input buffer process
    bool isAlternativeModeOn_MINUS = false, isAlternativeModeOn_DIVISON = false;

    for(size_t i = 0;i<strlen(data);i++) {

        if(IS_IT_NUM(DEC,data[i])) {

            double currNum = 0;
            char floatPartCount = 0,isFloat = false;
            nummode_t nummode = 0;

            if(data[i] == '0') {
                i++;
                switch(data[i]) {
                    case 'x': {
                        i++;
                        while(IS_IT_NUM(HEX,data[i])) {
                            if (data[i] == '.') {
                                i++;
                                isFloat = true;
                                continue;
                            }
                            if (isFloat) floatPartCount++;
                            if (IS_IT_DEC(data[i]))
                                currNum = currNum * 16 + data[i++] - 48;
                            if ('A' <= data[i] && data[i] <= 'F')
                                currNum = currNum * 16 + data[i++] - 55;
                            if ('a' <= data[i] && data[i] <= 'f')
                                currNum = currNum * 16 + data[i++] - 87;
                        }
                        nummode = 3;
                    }
                    break;
                    case 'o': {
                        i++;
                        while(IS_IT_NUM(OCT,data[i])) {
                            if (data[i] == '.') {
                                i++;
                                isFloat = true;
                                continue;
                            }
                            if (isFloat) floatPartCount++;
                            currNum = currNum * 8 + data[i++] - 48;
                        }
                        nummode = 1;
                    }
                    break;
                    case 'b': {
                        i++;
                        while(IS_IT_NUM(BIN,data[i])) {
                            if (data[i] == '.') {
                                i++;
                                isFloat = true;
                                continue;
                            }
                            if (isFloat) floatPartCount++;
                            currNum = currNum * 2 + data[i++] - 48;
                        }
                    }
                    break;
                    default: {
                        while(IS_IT_NUM(DEC,data[i])) {
                            if(data[i] == '.') {
                                i++;
                                isFloat = true;
                                continue;
                            }
                            if(isFloat) floatPartCount++;
                            currNum = currNum*10 + data[i++]-48;
                        }
                        nummode = 2;
                    }
                }

            }
            else {
                while(IS_IT_NUM(DEC,data[i])) {
                    if(data[i] == '.') {
                        i++;
                        isFloat = true;
                        continue;
                    }
                    if(isFloat) floatPartCount++;
                    currNum = currNum*10 + data[i++]-48;
                }
                nummode = 2;
            }

            //We should go back one char because in the 'while' loop we move one more char
            i--;

            if(isAlternativeModeOn_MINUS) {
                currNum *= -1;
                isAlternativeModeOn_MINUS = false;
            }


            if (isAlternativeModeOn_DIVISON) {
                currNum = 1/currNum;
                isAlternativeModeOn_DIVISON = false;
            }

            push_double(&finalStack,currNum*pow(NUM_FLOATER,-floatPartCount));

        }
        else {

            //I ordered operands due to their precedence and if they are in parentheses or not
            //For always uprising the precedence of parentheses, I put '(' in the highest precedence
            //and also activate its solution process when it crossed with a ')'

            switch (data[i]) {
                case '(':
                case '^':
                case 'v':
                    push_char(&oppStack,data[i]);
                    break;
                case '*':
                case '/': {
                        while(peek_char(&oppStack) != NULL && PRECEDENCE_LVL1_CHECK) {
                            double val2 = pop_double(&finalStack),
                                    *val1 = peek_double(&finalStack);
                            if(val1 == NULL) {
                                push_double(&finalStack,0);
                                val1 = peek_double(&finalStack);
                            }
                            *val1 = miniSolve(*val1,val2,pop_char(&oppStack));
                        }
                        if(data[i] == '/')
                            isAlternativeModeOn_DIVISON = true;
                        push_char(&oppStack,'*');
                    }
                    break;
                case '+':
                case '-': {
                        while(peek_char(&oppStack) != NULL && PRECEDENCE_LVL2_CHECK){
                            double val2 = pop_double(&finalStack),
                                    *val1 = peek_double(&finalStack);
                            if(val1 == NULL) {
                                push_double(&finalStack,0);
                                val1 = peek_double(&finalStack);
                            }
                            *val1 = miniSolve(*val1,val2,pop_char(&oppStack));
                        }
                        if(data[i] == '-')
                            isAlternativeModeOn_MINUS = true;
                        push_char(&oppStack,'+');
                    }
                    break;
                case ')': {
                        while(peek_char(&oppStack) != NULL && *peek_char(&oppStack) != '(') {
                            double val2 = pop_double(&finalStack),
                                    *val1 = peek_double(&finalStack);
                            if(val1 == NULL) {
                                push_double(&finalStack,0);
                                val1 = peek_double(&finalStack);
                            }
                            *val1 = miniSolve(*val1,val2,pop_char(&oppStack));
                        }
                        pop_char(&oppStack);
                    }
                    break;
                //It takes line break as the end of process
                //In that case we do final flattening
                case '\n': {
                    while(oppStack.size) {
                        double val2 = pop_double(&finalStack),
                                *val1 = peek_double(&finalStack);
                        *val1 = miniSolve(*val1,val2,pop_char(&oppStack));
                    }
                }
                break;
            }

        }

    }

    double output = finalStack.real[0];

    Stack_double_RealFlush(&finalStack);
    Stack_char_RealFlush(&oppStack);

    return output;

}

int main(int argc, char** argv) {

    char *buffer = (char *)malloc(4096);

    if(buffer == NULL) {
        perror("Buffer couldn't allocated initially");
        exit(EXIT_FAILURE);
    }

    printf("Enter operation here:\n>>> ");
    if(fgets(buffer,4096,stdin) == NULL) {
        perror("Bigger data then buffer size has been entered, buffer data is 4096 characters");
        return EXIT_FAILURE;


    }

    buffer = bufferHandler(buffer);
//    printf("%s",buffer); // For showing final operation string while debugging or development

    solution_t solution = solver(buffer);

    printf(">>> %lf\n", solution);

    free(buffer);

    return 0;

}
