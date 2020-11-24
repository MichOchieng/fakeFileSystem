#include <stdio.h>
#include "headers/diskSim.h"

unsigned char disk[maxSize];

int main(){
    diskInit();
    diskRead(0);
    diskWrite(0);
    diskRead(0);

    return 0;
}

void diskInit(){
    for (size_t i = 0; i < maxSize; i++)
    {
        disk[i] = 0;
    }    
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
        for (size_t i = blockStart; i < blockEnd; i++)
        {
            printf("%02x\n",disk[i]);
        }  
    }   
      
}

void diskWrite(int index){
    if (index > maxBlocks)
    {
        printf("The index entered is too large.");
        exit(0);
    }
    else
    {
        int blockStart = index * 128;
        int blockEnd   = blockStart + 128;
        for (size_t i = blockStart; i < blockEnd; i++)
        {
            disk[i] = 0xA;        
        }    
    }
    
}