#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>

// Shell methods
void shell();
int terminate();
char * reader();
char ** parser();
void printString();
void execute(char ** args);
char * input;
char ** parseArray;
// File system methods
void makeFile();
void writeFile();
void deleteFile();