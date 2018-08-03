/*
 Class: CS 211, Spring 2017. Wednesday, 3pm-5pm lab.
 System: OSX El Capitan, Xcode.
 Author: Christian Dominguez
 Assignment: Program 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Defining global variables
#define TRUE 1
#define FALSE 0
#define debugMode 1

//Declaring struct used in program
typedef struct Stack{
    char *arr;
    int arraySize;
    int topIndicator;
}stack;

void initialize(stack *st1){
    st1->arraySize = 2;
    st1->arr = (char *)malloc(sizeof(char) * st1->arraySize);
    st1->topIndicator = 0;
}//End of initialize

int isEmpty(stack *st1){
    if(st1->topIndicator == 0){
        return TRUE;
    }
    return FALSE;
}//End of isEmpty

void pushCharacter(stack *st1, char character){
    char* temp;
    int k;
    
    //Check if there is enough space to add another character and grow if needed
    if(st1->topIndicator+2 >= st1->arraySize){
        st1->arraySize = st1->arraySize + 2;
        temp = (char*)malloc(sizeof(char) *st1->arraySize);
        
        for(k=0; k<st1->arraySize; k++){
            temp[k] = st1->arr[k];
        }
        
        free(st1->arr);
        st1->arr = temp;
    }
    
    //Adding the character and incrementing the top position
    st1->arr[st1->topIndicator] = character;
    st1->topIndicator = st1->topIndicator +2;
    
}//End of push

char topCharacter(stack *st1){
    return (st1->arr[st1->topIndicator-2]);
}//End of topCharacter

void popCharacter(stack *st1){
    st1->topIndicator = st1->topIndicator - 2;
}//End of popCharacter

void resetStack(stack *st1){
    st1->topIndicator = 0;
}//End of resetStack

int isOpenSymbol(char character){
    if(character == '('){
        return TRUE;
    }
    else if(character == '{'){
        return TRUE;
    }
    else if(character == '['){
        return TRUE;
    }
    else if(character == '<'){
        return TRUE;
    }
    return FALSE;
}//End of isOpenSymbol

int isClosingSymbol(char character){
    if(character == ')'){
        return TRUE;
    }
    else if(character == '}'){
        return TRUE;
    }
    else if(character == ']'){
        return TRUE;
    }
    else if(character == '>'){
        return TRUE;
    }
    return FALSE;
}//End of isClosingSymbol

int areMatchingSymbols(char character, char character2){
    if(character2 == '(' && character == ')'){
        return TRUE;
    }
    if(character2 == '{' && character == '}'){
        return TRUE;
    }
    if(character2 == '[' && character == ']'){
        return TRUE;
    }
    if(character2 == '<' && character == '>'){
        return TRUE;
    }
    return FALSE;
}//End of isMatchingSymbols

void oppositeError(char character){
    if(character == ')'){
        printf("\n^missing (");
    }
    if(character == '}'){
        printf("\n^missing {");
    }
    if(character == ']'){
        printf("\n^missing [");
    }
    if(character == '>'){
        printf("\n^missing <");
    }
}//End of oppositeError

int missingOpeningSymbol(stack *st1 ,char c){
    
    if(c == ')' && topCharacter(st1) != '('){
        return TRUE;
    }
    if(c == '}' && topCharacter(st1) != '{'){
        return TRUE;
    }
    if(c == ']' && topCharacter(st1) != '['){
        return TRUE;
    }
    if(c == '>' && topCharacter(st1) != '<'){
        return TRUE;
    }
    
    return FALSE;
}

void displayIdentifyingInformation(){
    printf("Author: Christian Dominguez\n");
    printf("Net-Id: cdomin26\n");
    printf("CS 211: Project 2\n");
    printf("Date: 01/29/17\n\n");

}//End of displayIdentifyingInformation

int main(int argc, char** argv){
    
    //Declaring variables used throughout program
    stack st1;
    int i = 0;
    int j;
    char userInput[300];
    char character;
    char character2;
    
    //Displaying author information
    displayIdentifyingInformation();
    
    //Initialize the array memory
    initialize(&st1);
    
    //Let the user know what to enter if they wish to exit the program
    printf("Enter 'q' or 'Q' if you wish to exit the program.\n");
    
    //Reading in input and using functions
    while(fgets(userInput, 300, stdin)){
        printf("\n");
        
        //Checking if the user entered 'q' or 'Q'
        if(userInput[i] == 'q' || userInput[i] == 'Q'){
            printf("Exiting Program...\n");
            exit(0);
        }

        
        while(userInput[i] != '\0'){
            
        //Printing contents of the array
            printf("%c ", userInput[i]);

        
            character = userInput[i];
            
        //Checking the characters entered by the user
            if(isOpenSymbol(character)){
               // character = userInput[i];
                pushCharacter(&st1, character);
               }
            
            character2 = topCharacter(&st1);
            
            if(isClosingSymbol(character)){
                
                if(missingOpeningSymbol(&st1, character)){
                    printf("Expression is unbalanced.\n");
                    break;
                }
                
                //Checking if stack is empty, if so, there is no need to pop
                if(isEmpty(&st1)){
                    for(j = 0; j<i; j++){
                        printf(" ");
                    }
                    //Calling opposite function to know which character to print for error message
                    oppositeError(character);
                    
                }
                //Checking if there is a matching opening symbol
                if(areMatchingSymbols(character, character2)){
                     popCharacter(&st1);
                }
                else{
                    
                }
                
            }//End of closing symbol if statement
            i++;
            
        }//End of 2nd while loop
        
        //Checking is stack is empty
        if(isEmpty(&st1)){
            printf("Expression is balanced.\n");
        }
        else{
            printf("^missing\n");
        }
        
        //Resetting count to be able to enter multiple lines in sucession
        i=0;
        
   }//End of fgets while loop
    
    
    return 0;
}//End of main
