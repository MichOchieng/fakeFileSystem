#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/diskSim.h"

unsigned char disk[maxSize];
char *fileNames[nInodes];

void diskInit(){
    // Format the disk
    formatDisk();    
    // Create superblock
    createSuperBlock();   
    printf("--Disk created\n");
}

void diskRead(int startBlock,int nBlocks){
    if (startBlock > maxBlocks) // Outside the range of blocks
    {
        printf("--The index entered is too large.");
        exit(0);
    }
    else
    {
        int realStart = startBlock * 128;
        int realEnd = nBlocks * 128;
        for (int i = realStart; i < realEnd; i++)
        {
            printf("%c",disk[i]);
        }  
        printf("\n");
    }      
}

void diskWrite(int index,char *input){
    if (index > maxBlocks)
    {
        printf("The index entered is too large.");
        exit(0);
    }
    else 
    {   
        // Check to see if the block is available
        int blockStart = index * 128;
        int blockEnd   = blockStart + 128;

        // Take in the string
        // Break it down word by word
        // Store each char to one position of the block
        int i = 0;
        while (input[i] != '\0'){     
            disk[blockStart] = input[i];      
            blockStart++;     
            i++;
        }
    }    
}

void formatDisk(){
    for (int i = 0; i < maxSize; i++)
    {
        disk[i] = 0;
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
    // Find next free block
    int blockIndex = blockOffser(getFreeBlock());
    
    if (blockIndex != 0)
    {
        // Set inode pointer to block
        // If block is full -> grab new block
            // If 4 blocks taken -> indirect pointer

        
    }
        
}

void createSuperBlock(){
    disk[superblockStart]     = magicNum;
    disk[superblockStart + 1] = maxBlocks;
    disk[superblockStart + 2] = maxInodes;
}

void createInode(int index){    
    int fileSize   = 0;
    disk[index] = fileSize;
}
int findFile(char *filename){

}

int getFile(char *fileName){
    bool fileFound = false;
    for (int i = 0; i < nFiles; i++)
    {
        int test = strcmp(fileNames[i],fileName);
        if (test == 0)
        {   
            fileFound = true;
            printf("%s is file number %i.\n",fileName,i);
            return i;
        }       
    }    
    if(!fileFound)
    {
        printf("The file %s does not exist.\n",fileName);
    }
}

int getFreeInode(){    
    for (int i = inodeBitmapStart; i <= inodeBitmapEnd; i++)
    {
        if (disk[i] == 0)
        {
            // Free inode found
            disk[i] = 1;
            printf("--Free inode at index: %i\n",i);
            return i;
        }
        else if(i == inodeBitmapEnd && disk[i] == 1)
        {
            printf("--Max files reached.\n");
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
            printf("--Free data block at index: %i\n",i);
            return i;
        }
        else if(i == dataBitmapEnd && disk[i] == 1)
        {
            printf("--Disk is full.\n");
            return 0;
        }       
    }
}

int inodeOffset(int index)
{
    return (index*128) + inodesStart;
}

int blockOffser(int index){
    return (index*128) + dataGroupStart;
}