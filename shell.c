#include "diskSim.c"
#include "headers/shell.h"

int main(int argc, char ** argv){   
    if (argc > 1)
    {
        printString(argv);
    }else{
        diskInit();
        shell();
    }     
    return 0;
}

void shell(){   
    bool on = true;
    // Will always run at very least once
    do{        
       execute(parser(reader()));  
       input = NULL;
       parseArray = NULL;
       free(input);
       free(parseArray);          
    }while(on); 
}

// Returns pointer to users input
char * reader(){
    unsigned int n = 1; // Size of the input string
    unsigned int i = 0; // Used for looping through char array
    // Allocate memory
    input = (char*) malloc(sizeof(char) * pow(2,n)); // Allocates memory, char type pointer
    // Fill memory with input
    if(input !=NULL){ // Wont take in any loose pointers
        // While the user is inputing and hasn't hit enter
        char nextChar;
        while ((nextChar = getchar()) != '\n')
        {           
            // Add their input to the allocated memory block            
            input[i] = nextChar;                     
            // If the memory block is too small for their input
            if(i == pow(2,n)){
                // Increase the size of the alloted memory
                n++;
                input = realloc(input, pow(2,n)*sizeof(char));
            }
            i++;
        }        
    }
    return input;
}

// Returns a command and argument
char ** parser(char * input){
    unsigned int n = 1; // Size of the parse array  
    unsigned int i = 0; // Used for looping through parse array  
    // Will contain tokens from the input array for later use
    parseArray = malloc(sizeof(char) * pow(2,n));
    // Regular delimeters for strtok method
    const char delims[] = " \n\t\r\v\f";
    // Temperary holder for input string tokens
    char * token = strtok(input,delims);   

    while (token != NULL)
        {           
            // Add token to parse array                  
            parseArray[i] = token;            
            // If the memory block is too small for their input
            if(i == pow(2,n)){
                // Increase the size of the alloted memory
                n++;
                parseArray = realloc(parseArray, pow(2,n)*sizeof(char*));
            }
            i++;
            token = strtok(NULL,delims);
        }  
    parseArray[i] = NULL;     
    return parseArray;
}

void execute(char ** args){
    char *touch = "touch";
    char *rm    = "rm";
    char *write = "write";
    char *cd    = "cd";    
    char *exitt = "exit";

    char *arg0;
    char *arg1;
    char *arg2 = "";

    int i = 0;  
    // Gets arguments
    while (args[i] != NULL)
    {
        if (i == 0)
        {
            arg0 = args[i];
            
        }
        else if (i == 1)
        {
             arg1 = args[i];
             
        }
        else
        {
            strcat(arg2,args[i]);
            
        }
        i++;
    }
    
    // Redirects
    if (strcmp(arg0,touch) == 0)
    {        
        makeFile(nFiles,arg1);
    }
    else if(strcmp(arg0,rm) == 0)
    {
        printf("rm\n");
        // delete file
    }
    else if(strcmp(arg0,write) == 0)
    {
        writeFile(arg1,arg2);
    }
    else if(strcmp(arg0,cd) == 0)
    {
        printf("cd\n");
        // cd
    }
    else if(strcmp(arg0,exitt) == 0)
    {
        terminate();
    }
    

        
}

int terminate(){    
    char c;
    printf("Are you sure you want to exit? [y/n]\n");
    c = getchar();
    if (c == 'y'){
        exit(0);
    }
    else if(c == 'n'){
        printf("Returning to shell...\n");
        shell();
    }
    else{
        printf(": is not an option, try again.\n");
    }   
}

// Takes command line arguments and prints them
void printString(char ** args){
    int i = 1;    
    while (args[i] != NULL){        
        printf("%s",args[i]);
        printf(" ");
        i++;
    }
    printf("\n");
}
