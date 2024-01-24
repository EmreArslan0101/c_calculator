//
// Created by emre on 20.01.2024.
//

#pragma pack(1)


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "Stack.c"

#define NUM 0
#define OPP 1
#define IS_IT_NUM 47 < data[i] && data[i] < 58

double miniSolve(double val1,double val2,char opperand) {
    switch(opperand) {
        case '+':
            return val1+val2;
        case '-':
            return val2-val1;
        case '*':
            return val1*val2;
        case '/':
            return val2/val1;
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
//        printf("CHAR %ld = %c\n",i,buffer[i]);
        if(buffer[i] < 42 || buffer[i] > 57 || buffer[i] == '.' || buffer[i] == ',') {
            printf("\x1b[31m""Invalid character in operation string at %ld\n",i);
            printf("%s""\x1b[0m",buffer);
            exit(EXIT_FAILURE);
        }
    }

    //INVALID CHARACTER CHECK


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

    Stack finalStack = newStack(), oppStack = newStack();

    for(size_t i = 0;data[i];i++) {

        type* curr;

        if(IS_IT_NUM) {

            number* currNum = newNum(0);

            while(IS_IT_NUM) {
                currNum->val = currNum->val*10 + data[i]-48;
                i++;
            }
            i--;

            curr = newType(currNum,NUM);

            push(&finalStack,*curr);


        }
        else {

            operation* currOpp = newOpp(data[i]);
            curr = newType(currOpp,OPP);

            if(currOpp->val == '*' || currOpp->val == '/') {
                push(&oppStack, *curr);
            }
            else {
                while(oppStack.size) {
                    number *currNum1 = (number*)(pop(&finalStack).data),
                           *currNum2 = (number*)(peek(&finalStack).data);

                    currNum2->val = miniSolve(currNum1->val,currNum2->val,((operation*)(pop(&oppStack).data))->val);
                }
                push(&oppStack,*curr);
            }


        }

    }

    double output = ((number *)(peek(&finalStack).data))->val;

    stackRealFlush(&finalStack);
    stackRealFlush(&oppStack);

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

    printf(">>> %lf",solver(buffer));

    return 0;

}
