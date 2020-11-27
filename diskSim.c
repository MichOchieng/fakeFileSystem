#include <stdio.h>
#include <stdlib.h>
#include "headers/diskSim.h"

const int superblockStart = 0;
const int inodeStart      = 0;
const int dataGroupStart  = 0;

const int superblockEnd   = 0;
const int inodeGroupEnd   = 0;
const int dataGroupEnd    = 0;

unsigned char disk[maxSize];
char *test = "test";

int main(){
    diskInit();    
    diskWrite(0,test);
    diskRead(0);

    return 0;
}

void diskInit(){
    // Format the disk
    formatDisk();    
    // Create superblock
    createSuperBlock();
    // Create Inode bitmap
    createInodeBitmap();
    // Create Inodes 
    createInode();
    // Create Data groups
    createBlockGroup();
}

void diskRead(int index){
    if (index > maxBlocks) // Outside the range of blocks
    {
        printf("The index entered is too large.");
        exit(0);
    }
    else
    {
        int blockStart = index * 128;
        int blockEnd   = blockStart + 128;
        for (int i = blockStart; i < blockEnd; i++)
        {
            printf("%c\n",disk[i]);
        }  
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

void createSuperBlock(){
    disk[superblockStart]     = magicNum;
    disk[superblockStart + 1] = maxBlocks;
    disk[superblockStart + 2] = maxInodes;
}

void createInodeBitmap(){

}

void createInode(){

}

void createBlockGroup(){

}