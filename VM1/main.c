#include <stdio.h>
#include <stdlib.h> //for malloc
#include <string.h> //for strlen
#include <math.h> //for pow(x,y) where x is raised to y power

char* breakAfter(char* string, char symbol);
char* breakBefore(char* string, char symbol);
void push(char* memorySecment, char* value, FILE* outputfile);
void add(FILE* outputfile);
void sub(FILE* outputfile);
void infiniteLoop(FILE* outputFile);
char* mSecment(char* string);
char* command(char* string);
char* value(char* string);

int main()
{
    FILE* inputFile = NULL;
    FILE* outputFile = NULL;

    const int bufferSize = 256;
    char inputFileName[bufferSize];

    //user input; file name
    printf("Please enter an input filename: ");
    fgets(inputFileName, bufferSize, stdin);
    inputFileName[strcspn(inputFileName, "\n")] = 0; //removes the \n

    //opening files
    inputFile = fopen(inputFileName, "r"); //read only
    outputFile = fopen("local.asm", "w"); //write only

    //reading the file lines
    char buffer[bufferSize];
    while(fgets(buffer, bufferSize, inputFile) != NULL){ // reading lines in file
        buffer[strcspn(buffer, "\r\n")] = 0;

        //splitting the lines to get commands
        char* sCommand = command(buffer);
        char* sMemorySec = mSecment(buffer);
        char* sValue = value(buffer);

        if(strcmp(sCommand,"push")==0){
            printf("inside if stament PUSH\n");
            push(sMemorySec,sValue,outputFile);
        }
        else if(strcmp(sCommand,"add")==0){
            add(outputFile);
        }
        else if(strcmp(sCommand,"sub")==0){
            sub(outputFile);
        }

      //free(sCommand);
      //free(sMemorySec);
      //free(sValue);

    }
    infiniteLoop(outputFile);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

char* command(char* string){
    char* command = malloc(sizeof (char));
    command = breakBefore(string,' ');
    return command;
}


char* mSecment(char* string){
    char* slicing = breakAfter(string, ' ');
    char* memorySec = malloc(sizeof (char));
    memorySec = breakBefore(slicing,' ');
    return memorySec;
}

char* value(char* string){
    char* slicing = breakAfter(string, ' ');
    char* value = malloc(sizeof (char));
    value = breakAfter(slicing,' ');
    return value;
}

void infiniteLoop(FILE* outputFile){
    char* assembly = malloc(sizeof(char));
    char* loop = "(END)\n@END\n0;JMP\n";
    strcpy(assembly, loop);
    fputs(assembly,outputFile);
}

void push(char* memorySecment, char* value, FILE* outputFile){
    char* pushCommand = "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    int valLen = strlen(value);
    int mSize = 37 + valLen;

    if(strcmp(memorySecment, "constant")==0){
        char* assembly = malloc(sizeof (char) *mSize);
        strcpy(assembly,"@");
        strcat(assembly,value);
        strcat(assembly,pushCommand);
        printf("PUSHING\n");
        fputs(assembly, outputFile);
    }
    else if (strcmp(memorySecment, "local")==0){
        if(strcmp(value,"0")==0){
            char* assembly = malloc(64);
            strcpy(assembly,"@LCL\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
            fputs(assembly, outputFile);
            printf("PUSHING local");
            return;
        }
        char* assembly = malloc(64);
        strcpy(assembly,"@LCL\nA=M\nM=M+1\n");
        strcat(assembly,"@LCL\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
        printf("PUSHING local");
        fputs(assembly, outputFile);
    }
}

void add(FILE* outputfile){
    char* addCommand = "@SP\nA=M-1\nD=M\nA=A-1\nA=M\nD=D+A\n";
    char* assembly = malloc(sizeof(char));
    strcpy(assembly, addCommand);
    strcat(assembly,"@SP\nM=M-1\nA=M-1\nM=D\n");
    fputs(assembly,outputfile);
    printf("ADDING");
}

void sub(FILE* outputFile){
    char* addCommand = "@SP\nA=M-1\nA=A-1\nD=M\n@SP\nA=M-1\n";
    char* assembly = malloc(sizeof(char));
    strcpy(assembly, addCommand);
    strcat(assembly,"A=M\nD=D-A\n@SP\nM=M-1\nA=M-1\nM=D\n");
    fputs(assembly,outputFile);
    printf("Subtrac");
}

char* breakAfter(char* string, char symbol){
    int len = strlen(string);
    int newStrLen = 1;
    char* newString = malloc(sizeof (char) * newStrLen );
    for(int i = 0; i <= len;i++){
        if (string[i] == symbol && string[i+1] != symbol){
            int index = 0;
            for(int j = i ; j <= len;j++){
                newString[index] = string[j+1];
                newStrLen++;
                index++;
            }
         break;
        }
      }
    return (char*)newString;
}

char* breakBefore(char* string, char symbol){
    int len = strlen(string);
    int newStrLen = 1;

    char* newString = (char*)calloc(newStrLen, sizeof (char));
    for(int i = 0; i <= len;i++){
        if (string[i] == symbol){
            newString[i] = '\0';
            break;
        }
        newStrLen++;
        newString[i] = string[i];
    }
    return newString;
}
