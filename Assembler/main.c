#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> //for malloc
#include <string.h> //for strlen
#include <math.h> //for pow(x,y) where x is raised to y power

struct Node{
    char* symbol;
    int location;
    struct Node* next;
};

struct LinkedList{
    struct Node* head;
};

char* breakBefore(char[], char);
char* breakAfter(char[], char);
int validateCommand(char buffer[]);
void dest(char line[], char output[]);
void jump(char line[], char output[]);
void comp(char line[], char output[], char);
void setAbit(char line[], char output[]);
void printArray (char array[]);
void translating(char[], char[]);
char* intToBinary(int num);
int charToDigit(char digit);
int stringToInt(char* string);
void translate(FILE* inputFile, FILE* outputFile);
void firstPass(FILE* inputFile,struct LinkedList* list);
void insertAtEnd(struct LinkedList* list, int location, char* symbol);
void printList(struct LinkedList* list);

void symbolTable(struct LinkedList* myList){

    insertAtEnd(myList,0,"SP"); insertAtEnd(myList,1,"LCL"); insertAtEnd(myList,2,"ARG");insertAtEnd(myList,3,"THIS");
    insertAtEnd(myList,4,"THAT"); insertAtEnd(myList,0,"RO");insertAtEnd(myList,1,"R1");insertAtEnd(myList,2,"R2");
    insertAtEnd(myList,3,"R3"); insertAtEnd(myList,4,"R4");insertAtEnd(myList,5,"R5");insertAtEnd(myList,6,"R6");
    insertAtEnd(myList,7,"R7"); insertAtEnd(myList,8,"R8");insertAtEnd(myList,9,"R9");insertAtEnd(myList,10,"R10");
    insertAtEnd(myList,11,"R11");insertAtEnd(myList,12,"R12");insertAtEnd(myList,13,"R13");insertAtEnd(myList,14,"R14");
    insertAtEnd(myList,15,"R15"); insertAtEnd(myList,16384,"SCREEN");insertAtEnd(myList,24576,"KBD");
}

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
    outputFile = fopen("out.txt", "w"); //write only

    struct LinkedList myList;
    myList.head = NULL;
    symbolTable(&myList);
    printList(&myList);

    translate(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
 }

//void firstPass(FILE* inputFile, struct LinkedList* list){

  //  const int bufferSize = 256;
    //char buffer[bufferSize];
    //int lineCounter = 0;

    //while(fgets(buffer, bufferSize, inputFile) != NULL){ // reading lines in file
     //   buffer[strcspn(buffer, "\r\n")] = 0;
       // lineCounter++;

        //if(strcmp(buffer,"(")){
          //  char* inlabel = breakAfter(buffer,'(');
            //char* outlabel = breakBefore(inlabel,')');
            //insertAtEnd(list, lineCounter,outlabel);
       // }
    //}
//}


void translate(FILE* inputFile, FILE* outputFile){

    const int bufferSize = 256;
    char buffer[bufferSize];
    while(fgets(buffer, bufferSize, inputFile) != NULL){ // reading lines in file
        buffer[strcspn(buffer, "\r\n")] = 0;

        //output data array
        char binaryInstruc[17];
        binaryInstruc[16] = '\0';

        //stripping off comment lines and empty spaces
        if(buffer[0] == '/' || strlen(buffer) == 0){
            continue;
        }

        char* line;
        // cleaning line of comments
        for(int i = 0; i < (int)(strlen(buffer));i++){
            if(buffer[i] == '/'){
                line = breakBefore(buffer,'/');
                break;
            }
             line = breakBefore(buffer,' ');
         }

        //A instructions

        if(line[0] == '@'){
           char* number = breakAfter(line,'@');
           strcpy(line,"0");
           strcat(line,intToBinary(stringToInt(number)));
           fputs(line, outputFile);
           fputs("\n", outputFile);
           continue;
        }

        // setting C instruction values
        binaryInstruc[0] = '1';
        binaryInstruc[1] = '1';
        binaryInstruc[2] = '1';

        //translates commands to binary
        translating(line, binaryInstruc);
        fputs(binaryInstruc, outputFile);
        fputs("\n", outputFile);
    }
}




// It checks if destination or jump command
void translating(char reading[], char output[]){

    int command = validateCommand(reading);
    if (command == 1){                     // 1 = destination command

       setAbit(reading, output);
       dest(reading, output);
       comp(reading, output, '=');
       printArray(output);

    }
    else{                                 // 0 = jump command
       setAbit(reading, output);
       comp(reading, output, ';');
       jump(reading,output);
       printArray(output);
    }

}

// set a bit to; 0 if 'A' in command ; 1 IF 'M' in command
void setAbit(char line[], char output[]){
    int len = strlen(line);
    for(int i=0; i <= len; i++){
        if(line[i] == 'A'){
            output[3] = '0';
        }
        if(line[i] =='M'){
            output[3] = '1';
        }
    }
    output[3] = '0';
}

//set destiantion values
void dest(char line[], char output[]){
    //setting jump indexes to zero
    for(int i=13; i <= 15; i++){
        output[i] = '0';
    }
    //set the comp to 000 for now
    for(int i=4; i <= 9; i++){
        output[i] = '0';
    }

    char* dest = breakBefore(line, '=');
    printf("isnde function");

    if(strcmp(dest,"null") == 0){
        output[10] = '0';
        output[11] = '0';
        output[12] = '0';

    }
    if (strcmp(dest,"M") == 0){
        output[10] = '0';
        output[11] = '0';
        output[12] = '1';

    }
    if (strcmp(dest,"D") == 0){
        printf("insisde the if loop""\n");
        output[10] = '0';
        output[11] = '1';
        output[12] = '0';

    }
    if (strcmp(dest,"MD") == 0){
        output[10] = '0';
        output[11] = '1';
        output[12] = '1';

    }
    if (strcmp(dest,"A") == 0){
        output[10] = '1';
        output[11] = '0';
        output[12] = '0';

    }
    if (strcmp(dest,"AM") == 0){
        output[10] = '1';
        output[11] = '0';
        output[12] = '1';

    }
    if (strcmp(dest,"AD") == 0){
        output[10] = '1';
        output[11] = '1';
        output[12] = '0';

    }
    if (strcmp(dest,"AMD") == 0){
        output[10] = '1';
        output[11] = '1';
        output[12] = '1';

    }
    free(dest);

}

//set comp values for jumps or destination commands
void comp(char line[], char output[], char symbol){

    char* comp;
    if(symbol == ';'){
       comp = breakBefore(line, ';');
     }
    if(symbol == '='){
        comp = breakAfter(line, '=');
    }


    printf("a inside Comp func, Comp = ""%s\n", comp);
    if(strcmp(comp,"0") == 0){
        output[4] = '1';
        output[5] = '0';
        output[6] = '1';
        output[7] = '0';
        output[8] = '1';
        output[9] = '0';

    }
    if(strcmp(comp,"1") == 0){
        output[4] = '1';
        output[5] = '1';
        output[6] = '1';
        output[7] = '1';
        output[8] = '1';
        output[9] = '1';

    }
    if(strcmp(comp,"-1") == 0){
        output[4] = '1';
        output[5] = '1';
        output[6] = '1';
        output[7] = '0';
        output[8] = '1';
        output[9] = '0';

    }
    if(strcmp(comp,"D") == 0){
        output[4] = '0';
        output[5] = '0';
        output[6] = '1';
        output[7] = '1';
        output[8] = '0';
        output[9] = '0';

    }
    if(strcmp(comp,"A") == 0 || strcmp(comp,"M") == 0){
        output[4] = '1';
        output[5] = '1';
        output[6] = '0';
        output[7] = '0';
        output[8] = '0';
        output[9] = '0';

    }
    if(strcmp(comp,"!D") == 0){
        output[4] = '0';
        output[5] = '0';
        output[6] = '1';
        output[7] = '1';
        output[8] = '0';
        output[9] = '1';

    }
    if(strcmp(comp,"!A") == 0 || strcmp(comp,"!M") == 0){
        output[4] = '1';
        output[5] = '1';
        output[6] = '0';
        output[7] = '0';
        output[8] = '0';
        output[9] = '1';

    }
    if(strcmp(comp,"-D") == 0){
        output[4] = '0';
        output[5] = '0';
        output[6] = '1';
        output[7] = '1';
        output[8] = '1';
        output[9] = '1';

    }
    if(strcmp(comp,"-A") == 0 || strcmp(comp,"-M") == 0){
        output[4] = '1';
        output[5] = '1';
        output[6] = '0';
        output[7] = '0';
        output[8] = '1';
        output[9] = '1';

    }
    if(strcmp(comp,"D+1") == 0){
        output[4] = '0';
        output[5] = '1';
        output[6] = '1';
        output[7] = '1';
        output[8] = '1';
        output[9] = '1';

    }
    if(strcmp(comp,"A+1") == 0 || strcmp(comp,"M+1") == 0){
        output[4] = '1';
        output[5] = '1';
        output[6] = '0';
        output[7] = '1';
        output[8] = '1';
        output[9] = '1';

    }
    if(strcmp(comp,"D-1") == 0){
        output[4] = '0';
        output[5] = '0';
        output[6] = '1';
        output[7] = '1';
        output[8] = '1';
        output[9] = '0';

    }
    if(strcmp(comp,"A-1") == 0 || strcmp(comp,"M-1") == 0){
        output[4] = '1';
        output[5] = '1';
        output[6] = '0';
        output[7] = '0';
        output[8] = '1';
        output[9] = '0';

    }
    if(strcmp(comp,"D+A") == 0 || strcmp(comp,"D+M") == 0){
        output[4] = '0';
        output[5] = '0';
        output[6] = '0';
        output[7] = '0';
        output[8] = '1';
        output[9] = '0';

    }
    if(strcmp(comp,"D-A") == 0 || strcmp(comp,"D-M") == 0){
        output[4] = '0';
        output[5] = '1';
        output[6] = '0';
        output[7] = '0';
        output[8] = '1';
        output[9] = '1';

    }
    if(strcmp(comp,"A-D") == 0 || strcmp(comp,"M-D") == 0){
        output[4] = '0';
        output[5] = '0';
        output[6] = '0';
        output[7] = '1';
        output[8] = '1';
        output[9] = '1';

    }
    if(strcmp(comp,"D&A") == 0 || strcmp(comp,"D&M") == 0){
        output[4] = '0';
        output[5] = '0';
        output[6] = '0';
        output[7] = '0';
        output[8] = '0';
        output[9] = '0';

    }
    if(strcmp(comp,"D|A") == 0 || strcmp(comp,"D|M") == 0){
        output[4] = '0';
        output[5] = '1';
        output[6] = '0';
        output[7] = '1';
        output[8] = '0';
        output[9] = '1';

    }
    free(comp);
}

// sets jump values
void jump(char line[], char output[]){
    //setting dest indexes to zero
    for(int i=10; i <= 12; i++){
        output[i] = '0';
    }

    char* jump = breakAfter(line, ';');
    printf("isnde function JUMP....");
    if(strcmp(jump,"null") == 0){
        output[13] = '0';
        output[14] = '0';
        output[15] = '0';

    }
    if (strcmp(jump,"JGT") == 0){
        output[13] = '0';
        output[14] = '0';
        output[15] = '1';

    }
    if (strcmp(jump,"JEQ") == 0){
        printf("insisde the if loop""\n");
        output[13] = '0';
        output[14] = '1';
        output[15] = '0';

    }
    if (strcmp(jump,"JGE") == 0){
        output[13] = '0';
        output[14] = '1';
        output[15] = '1';

    }
    if (strcmp(jump,"JLT") == 0){
        output[13] = 1;
        output[14] = 0;
        output[15] = 0;
    }
    if (strcmp(jump,"JNE") == 0){
        output[13] = '1';
        output[14] = '0';
        output[15] = '1';

    }
    if (strcmp(jump,"JLE") == 0){
        output[13] = '1';
        output[14] = '1';
        output[15] = '0';

    }
    if (strcmp(jump,"JMP") == 0){
        output[13] = '1';
        output[14] = '1';
        output[15] = '1';

    }
    free(jump);

}

// defining if jump or dest command
// dest == 1 , jump == 0
int validateCommand(char buffer[]){

    for(int i = 1; i < (int)strlen(buffer); i++){
        if(buffer[i] == '='){
            return 1;
        }
        else if ( buffer[i] == ';'){
            return 0;
        }
    }
    return 0; // what if i dont find the symbol ?
}


char* breakBefore(char* string, char symbol){

    int len = strlen(string);
    int newStrLen = 1;

    char* newString = (char*)calloc(newStrLen, sizeof (char));
    for(int i = 0; i <= len;i++){
        if (string[i] == symbol){
            break;
        }
        newStrLen++;
        newString[i] = string[i];
    }
    return (char*)newString;
}

char* breakAfter(char* string, char symbol){

    int len = strlen(string);
    int newStrLen = 1;
    char* newString = malloc(sizeof (char) * newStrLen );
    for(int i = 0; i <= len;i++){
        if (string[i] == symbol){
            int index = 0;
            for(int j = i ; j <= len;j++){
                newString[index] = string[j+1];
                newStrLen++;
                index++;
            }
        }
      }
    printf("%s", newString);
    return (char*)newString;
}

void printArray(char array[]){
    for(int i = 0; i < (int)strlen(array); i++){
        printf("%c", array[i]);
    }
}

char* intToBinary(int num){
    char *result = (char*)malloc(16*sizeof(char));
    int dividedNum = num;
    int reminder;

    for(int i = 14; i >=0 ; i--){
        reminder = dividedNum % 2;
        if(reminder == 0){
            result[i] = '0';
        }
        if(reminder == 1){
            result[i] = '1';
        }
        dividedNum = dividedNum / 2;
    }

    result[15] = '\0';
    return result;

}

int stringToInt(char* string){

    unsigned int len = strlen(string);
    int sum = 0;
    int power = 0;
    for (int i = len-1; i >= 0;i--){
        sum = sum + (charToDigit(string[i]) * floor(pow(10,power++)));
    }
    return sum;
}

int charToDigit(char digit){

    char* numberS = NULL;
    numberS = malloc(sizeof(char) * 2); //ten element string
    strcpy(numberS,&digit);

    return (int)*numberS - '0';
}

void insertAtEnd(struct LinkedList* list, int location, char* symbol)
{
    if(list->head == NULL)
    {
        list->head = malloc(sizeof(struct Node));

        list->head->location = location;
        list->head->symbol = symbol;
        list->head->next = NULL;
    }
    else
    {

       if(list->head->next == NULL){

          struct Node* newNode = malloc(sizeof(struct Node));
          list->head->next = newNode;
          newNode->location = location;
          newNode->symbol = symbol;
          newNode->next = NULL;
      }
      else{
           struct Node* current = NULL;

           current = list->head;
           while( current->next != NULL )
           {
               current = current -> next;
           }
           struct Node* newNode = malloc(sizeof(struct Node));
           current->next = newNode;
           newNode->location = location;
           newNode->symbol = symbol;
           newNode->next = NULL;
       }

    }
}

void printList(struct LinkedList* list)
{
    struct Node* temp = NULL;
    temp = list->head;
    while( temp != NULL )
    {
        printf("%i\n", temp->location);
        printf("%s\n", temp->symbol);
        temp = temp -> next;
    }
}
