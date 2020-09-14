#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char* searchWord(FILE* file){
    char *result, *tempWord, currChar, quotCount = 0;
    int minLength = 512, fileLength = 0, tempWordLen = 0, wordFlag = 1;

    result = (char*)malloc(1 * sizeof(char));
    tempWord = (char*)malloc(0 * sizeof(char));
    result[0] = '0';

    // Getting char number in file:
    while (fscanf(file, "%c", &currChar) == 1){  // The number of elements количество элементов в строке
        fileLength ++;
    }
    fseek(file, 0, 0);  // Getting the pointer to the beginning of file

    // Cheking file correctness:
    if (fileLength < 3){
        printf("Error: incorrect input!!!");
        exit(-1);
    }

    // Main cycle body:
    for (int i = 0; i < fileLength; i++){
        fscanf(file, "%c", &currChar);
        // If current symbol is a quot:
        if (currChar == '"'){
            if (quotCount % 2 == 1){  // If got into openned quote then
                // Checking word:
                // I. Checking englishness:
                for (int j = 0; j < tempWordLen; j++){
                    if ((tempWord[j] >= 'A' && tempWord[j] <= 'Z') || (tempWord[j] >= 'a' && tempWord[j] <= 'z')){
                        // It`s Ok
                        wordFlag = 1;
                    }
                    else {
                        wordFlag = 0;  // Wrong word
                    }
                }
                // II. Checking capitalyze:
                if (tempWord[0] >= 'A' && tempWord[0] <= 'Z'){
                    wordFlag = 1;
                }
                else {
                    wordFlag = 0; // Wrong word
                }
                // Checking if current word is shorter than minimum:
                if (wordFlag == 1){
                    if (tempWordLen <= minLength){
                        minLength = tempWordLen;
                        result = (char*)realloc(result, (tempWordLen + 1)* sizeof(char)); // + 1 including '\0'
                        for (int j = 0; j < tempWordLen; j++){
                            result[j] = tempWord[j];  // Getting the massive of lengthes:)
                        }
                        result[tempWordLen] = '\0';
                    }
                }
                wordFlag = 1;
                tempWordLen = 0;
            }
            quotCount ++; // To understand the word's boundaries
            continue;
        }
        // If current symbol isn`t a quot:
        if (currChar != '"'){
            // If we`re outside any word:
            if (quotCount % 2 == 0){  // If found 2nd quote
                continue;  // Leaving the cycle
            }
            // If we`re now inside some word:
            if (quotCount % 2 == 1){  // If still into word then
                tempWordLen ++;  // Counting the length of a word
                tempWord = (char*)realloc(tempWord, tempWordLen * sizeof(char));  // Allocating memory
                tempWord[tempWordLen - 1] = currChar; // - 1 cuz starting with 0 and remembering the position of cursor(pointer)int the file
            }
        }
    }
    return result;
}

int autotest(void){
    FILE* testFile;
    char* testAnswer;

    testFile = fopen("test.txt", "r");
    if (!testFile){
        printf("Error: cannot open test file!!!");
        exit(-1);
    }

    testAnswer = searchWord(testFile);
    if (testAnswer[0] != 'T'){
        printf("Autotest failed!!!");
        exit(-1);
    }
    else{
        printf("Autotest passed...\n\n");
    }
    return 0;
}

int main(void){
    FILE* fp;
    char* wordPointer;

    // Opening file
    fp = fopen("input.txt", "r");

    // Checking if file wasn`t opened:
    if (!fp){
        printf("Error: cannot open file!!!");
        exit(-1);
    }
    autotest();
    wordPointer = searchWord(fp);
    if (wordPointer[0] == '0'){
        printf("No such words in file!!!\n");
    }
    else{
        printf("Answer is %s\n", wordPointer);
    }

    return 0;
}
