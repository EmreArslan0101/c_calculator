//
// Created by emre on 20.01.2024.
//

#pragma pack(1)
#pragma GCC optimize("unroll-loops","O3")

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "Stack.c"
#include "Defines.c"

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
        default:
            perror("Invalid opperand has been detected");
            exit(EXIT_FAILURE);
    }
}

char* bufferHandler(char* buffer) {

    size_t bufferRealSize = strlen(buffer);

    //INVALID CHARACTER CHECK

    if(buffer[0] == '/' || buffer[0] == '*') {
        printf("\x1b[31m""Invalid character in operation string at 0 , \"/\" or \"*\" cannot be used as initial characters of operation\n");
        printf("%s""\x1b[0m",buffer);
        exit(EXIT_FAILURE);
    }

   for(size_t i = 0;i<bufferRealSize-1;i++) {
        if(
            buffer[i] < 40 ||
            buffer[i] > 57 ||
            buffer[i] == '.' || //Just the integers and opperrands are accepted in input formula, not the floats
            buffer[i] == ','  //Floats are just available at in output
        ) {

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
        }
    }

    //INVALID CHARACTER CHECK

    //PARENTHESIS CHECK

    int parenthesisCount = 0;

    for(size_t i = 0;i<bufferRealSize;i++) {
        if(buffer[i] == '(') parenthesisCount++;
        if(buffer[i] == ')') parenthesisCount--;
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

    for(size_t i = 0;i<strlen(data)-1;i++) {

        if(IS_IT_NUM(data[i])) {

            double currNum = 0;

            while(IS_IT_NUM(data[i])) {
                currNum = currNum*10 + data[i++]-48;
            }
            i--;

            char *currOpp = oppStack.size ? (peek_char(&oppStack)) : 0;

            if(currOpp != NULL && (*currOpp == '*' || *currOpp == '/')) {

                double *topVal = peek_double(&finalStack);

                *topVal = miniSolve(*topVal,currNum,pop_char(&oppStack));

            }
            else {
                push_double(&finalStack,currNum);
            }

        }
        else {

            if(data[i] != ')')
                push_char(&oppStack,data[i]);
            else {

                while(*peek_char(&oppStack) != '(') {
                    double val1 = pop_double(&finalStack),
                          *val2 = peek_double(&finalStack);
                    *val2 = miniSolve(*val2,val1, pop_char(&oppStack));
                }

                pop_char(&oppStack);

                char *checkChar = peek_char(&oppStack);

                if(checkChar != NULL && (*checkChar == '*' || *checkChar == '/')) {
                    double val1 = pop_double(&finalStack),
                            *val2 = peek_double(&finalStack);
                    *val2 = miniSolve(*val2,val1, pop_char(&oppStack));
                }

            }

        }

    }

//    printStack("%lf",finalStack);
//    printStack("%c",oppStack);

    double output = finalStack.real[0];

    for(size_t i = 1;i<oppStack.size+1;i++) {
        output = miniSolve(output, finalStack.real[i], oppStack.real[i - 1]);
    }

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

    printf(">>> %lf\n", solver(buffer));

    return 0;

}
