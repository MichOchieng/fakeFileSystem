#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "headers/diskSim.h"

int disk[maxSize];
char *fileNames[nInodes];
char *directories[nInodes];
char *currentDir;
bool inRoot = true;

void diskInit(){
    formatDisk();    
    createSuperblock();   
    createRoot();    
}

void diskRead(char *filename){
    // Get inode index
    int inodeIndex  = inodeOffset(getFile(filename));    
    if (inodeIndex != -1)
    {       
        // Get number of data blocks
        int numBlocks  = disk[inodeIndex]/128;   
        printf("%s: ",currentDir);    
        for (int i = 0; i < numBlocks; i++) // Loops over blocks
        {
            // Print data blocks
            int j = 0;
            int blockStart = disk[inodeIndex + (i+1)];
            while (disk[blockStart + j] != 0)
            {                
                printf("%c",disk[blockStart + j]);                
                j++;
            }            
        }
        printf("\n");
    }   
}

void formatDisk(){
    for (int i = 0; i < maxSize; i++)
    {
        disk[i] = 0;
    }   
    for (int i = 0; i < nInodes; i++)
    {
        directories[i] = "";
    }  
}

void makeFile(int index,char *filename){ 
    nFiles++;
    fileNames[index] = filename;   
    int inodeIndex   = getFreeInode();
    createInode(inodeOffset(inodeIndex));    
}
void writeFile(char *filename,char *str){  
    // Find corresponding inode
    int inodeIndex = inodeOffset(getFile(filename));   
    if (inodeIndex != -1)
    {       
        // Empty file
        if(disk[inodeIndex] == 0){
            int i = 0;
            // Increase file size            
            disk[inodeIndex] = 128;            
            // Find next free block
            int blockIndex = blockOffser(getFreeBlock());            
            // Set first block
            disk[inodeIndex + 1] = blockIndex;
            // Set current byte
            disk[inodeIndex + 6] = blockIndex;
            // End of block
            int EOB = blockIndex + 127;
            while (str[i]!= '\0')
            {                                
                disk[blockIndex + i] = str[i];
                if ((blockIndex + i) == EOB)// If end of block is reached
                {                   
                    // Save remaining portion of string
                    unsigned int n = 1;
                    char *temp = (char*) malloc(sizeof(char) * pow(2,n));
                    while (str[i]!= '\0')
                    {   
                        int j = 0;
                        temp[j] = str[i];                     
                        // If the memory block is too small for temp str
                        if(j == pow(2,n)){
                            // Increase the size of the alloted memory                            
                            n++;
                            temp = realloc(temp, pow(2,n)*sizeof(char));                            
                        }
                        i++;
                        j++;
                    }
                    // Call write Recursively
                    writeFile(filename,temp);
                    break;
                }
                //Increase index of current byte
                disk[inodeIndex + 6] += 1;
                i++;               
            }
            // Set last block index
            disk[inodeIndex + 6] = blockIndex + i; 
        }       
        else
        {           
            if (disk[inodeIndex] < 513) // Check to see if file is already full
            {               
                // Determines how many blocks have been used
                int numBlocks = disk[inodeIndex]/128;
                // Index of current block
                int currentBlock = disk[inodeIndex + numBlocks];                
                // End of current block
                int EOB = currentBlock + 127;
                // Current position in block
                int currentPos = disk[inodeIndex + 6];   

                // Checks to see if at the end of the block
                if(currentBlock == EOB)
                {
                    int i = 0;
                    disk[currentPos] = str[i];
                    if (numBlocks == 4)
                    {
                        printf("File %s is full!",filename);
                    }
                    else // Get a new block
                    {                        
                        // Set next block indexes
                        disk[inodeIndex + numBlocks + 1] = blockOffser(getFreeBlock());
                        disk[inodeIndex + 6] = (disk[inodeIndex + numBlocks + 1]) - 1;
                        
                        disk[inodeIndex] += 128;

                        // Save remaining portion of string
                        unsigned int n = 1;
                        char *temp = (char*) malloc(sizeof(char) * pow(2,n));
                        while (str[i]!= '\0')
                        {   
                            int j = 0;
                            temp[j] = str[i];                     
                            // If the memory block is too small for temp str
                            if(j == pow(2,n)){
                                // Increase the size of the alloted memory                            
                                n++;
                                temp = realloc(temp, pow(2,n)*sizeof(char));                            
                            }
                            i++;
                            j++;
                        }
                        // Call write Recursively
                        writeFile(filename,temp);                        
                    }                   
                    
                }
                else // Wrtite to block until at EOB
                {   
                    int i = 0;
                    while (str[i]!= '\0')
                    {
                        disk[currentPos + i] = str[i];                        
                        if ((currentPos + i) == EOB) // If end of block is reached
                        {                   
                            // Save remaining portion of string
                            unsigned int n = 1;
                            char *temp = (char*) malloc(sizeof(char) * pow(2,n));
                            while (str[i]!= '\0')
                            {   
                                int j = 0;
                                temp[j] = str[i];                     
                                // If the memory block is too small for temp str
                                if(j == pow(2,n)){
                                    // Increase the size of the alloted memory                            
                                    n++;
                                    temp = realloc(temp, pow(2,n)*sizeof(char));                            
                                }
                                i++;
                                j++;
                            }
                            // Call write Recursively
                            writeFile(filename,temp);
                            break;
                        }
                        i++;                                  
                    }
                    // Set last block index
                    disk[inodeIndex + 6] = currentPos + i;      
                }               
            }
            else
            {
                printf("File %s is full!",filename);
            }           
        }        
    }        
}
void deleteFile(char *fileName){
    // Get inode
    int inodeIndex  = inodeOffset(getFile(fileName)); 
    int fileIndex   = getFile(fileName);
    fileNames[fileIndex] = "";
    if (inodeIndex != -1)
    {
        // Clear bitmap  
        int bitMapIndex    = inodeBitmapStart + ((inodeIndex-inodesStart)/blockSize);
        disk[bitMapIndex]  = 0; 
        // Clear Data group bitmap
        int dataGroupIndex   = dataBitmapStart + ((inodeIndex-inodesStart)/blockSize); 
        disk[dataGroupIndex] = 0; 
        // Clear data blocks
        int numBlocks  = disk[inodeIndex]/128;
        for (int i = 0; i < numBlocks; i++) // Loops over blocks
        {            
            int j = 0;
            int blockStart = disk[inodeIndex + (i+1)];
            while (disk[blockStart + j] != 0)
            {    
                // Resets block to default value            
                disk[blockStart + j] = 0;                
                j++;
            }            
        }
        // Clear inode
        for (int i = inodeIndex; i < (inodeIndex + 128); i++)
        {
            disk[i] = 0;
        }        
    }
    else
    {
        printf("The file %s does not exist.",fileName);
    }

}
void createRoot(){
    makeFile(0,"");     
    currentDir = ""; 
}
void mkDir(int index,char *dirName){
    nFiles++;
    directories[index] = dirName;   
    int inodeIndex   = getFreeInode();
    createInode(inodeOffset(inodeIndex));

    int dataBlock1 = blockOffser(getFreeBlock());
    int dataBlock2 = blockOffser(getFreeBlock());
    int dataBlock3 = blockOffser(getFreeBlock());
    int dataBlock4 = blockOffser(getFreeBlock());
    // Give max file size
    disk[inodeIndex] = 512;
    // Set data blocks indexes
    disk[inodeIndex + 1] = dataBlock1;
    disk[inodeIndex + 2] = dataBlock2;
    disk[inodeIndex + 3] = dataBlock3;
    disk[inodeIndex + 4] = dataBlock4;    
}
void changeDir(char *dir){
    bool dirFound = false;
    char *goBack = "..";
    int cmp1 = strcmp(dir,goBack);
    if (cmp1 == 0)
    {
        // Go back to the root folder
        dirFound = true;
        inRoot = true;
        currentDir = "";
    }else
    {
        // Check to see if directort exists
        int i = 0;
        while (i<nInodes)
        {
            // If the directory exits enter it            
            if (strcmp(directories[i],dir) == 0)
            {
                dirFound = true;
                inRoot = false;                
                currentDir = NULL;          
                currentDir = dir;    
                break;
            } 
            i++;
        }
        
        if (!dirFound)
        {
            printf("The folder '%s' doesn't exist.\n", dir);
        }
    }
    
        
}


void createSuperblock(){
    disk[superblockStart]     = magicNum;
    disk[superblockStart + 1] = maxBlocks;
    disk[superblockStart + 2] = maxInodes;
}

void createInode(int index){    
    int fileSize   = 0;
    disk[index]    = fileSize;
}

int getFile(char *fileName){
    bool fileFound = false;
    for (int i = 0; i < nFiles; i++)
    {
        int test = strcmp(fileNames[i],fileName);
        if (test == 0)
        {   
            fileFound = true;            
            return i;
        }       
    }    
    if(!fileFound)
    {
        printf("The file '%s' does not exist.\n",fileName);
        return -1;
    }
}

int getFreeInode(){    
    for (int i = inodeBitmapStart; i <= inodeBitmapEnd; i++)
    {
        if (disk[i] == 0)
        {
            // Free inode found
            disk[i] = 1;            
            return i;
        }
        else if(i == inodeBitmapEnd && disk[i] == 1)
        {
            printf("--Max files reached.\n");
            return -1;
        }       
    }    
}

int getFreeBlock(){
    for (int i = dataBitmapStart; i <= dataBitmapEnd; i++)
    {
        if (disk[i] == 0)
        {
            // Free inode found
            disk[i] = 1;            
            return (i-dataBitmapStart);
        }
        else if(i == dataBitmapEnd && disk[i] == 1)
        {
            printf("--Disk is full.\n");
            return -1;
        }       
    }
}

int inodeOffset(int index)
{
    if (index == -1)
    {
        return index;
    } 
    return (index*128) + inodesStart;
}

int blockOffser(int index){
    if (index == -1)
    {
        return index;
    }    
    return (index*128) + dataGroupStart;
}