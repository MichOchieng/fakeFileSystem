#define maxSize 1280000
#define nInodes 1024
const int blockSize = 128;
const int maxBlocks = 10000;
const int maxInodes = 1024;
const unsigned char magicNum = 0xf0f03410;

// Block starting positions
const int superblockStart  = 0;
const int inodeBitmapStart = blockSize;
const int inodesStart      = blockSize*9;
const int dataBitmapStart  = blockSize*maxInodes;
const int dataGroupStart   = (blockSize*32) + dataBitmapStart;
// Block Ending positions 
const int superblockEnd    = blockSize-1;
const int inodeBitmapEnd   = (blockSize*8)-1;
const int inodesEnd        = dataBitmapStart-1;
const int dataBitmapEnd    = dataGroupStart-1;
const int dataGroupEnd     = maxSize;

int nFiles = 0;

void  diskInit();
void  diskRead(int startBlock,int endBlock);
void  diskWrite(int index,char *input);
void  formatDisk();
void  createSuperblock();
void  createInode(int index);
void  makeFile(int index,char *filename);
void  writeFile(char *filename,char *str);
void  deleteFile();

int   blockOffser(int index);
int   inodeOffset(int index);
int   findFile(char *filename);
int   getFile(char *fileName);
int   getFreeInode();
int   getFreeBlock();