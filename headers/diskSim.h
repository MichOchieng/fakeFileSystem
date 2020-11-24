#define blockSize 128
#define maxSize 1280000
#define maxBlocks 1000

typedef struct superblock
{
    
};

typedef struct inBitmap
{
    /* data */
};

typedef struct inode
{
    int fileSize;
    // direct pointers
    // indirect pointers
};

typedef struct dataGroup
{
    /* data */
};



void  diskInit();
void  diskRead(int index);
void  diskWrite(int index);