#define maxSize 1280000
#define nInodes 1024
const int blockSize = 128;
const int maxBlocks = 10000;
const int maxInodes = 1024;
const int magicNum = 0xf0f03410;

// Block starting positions
const int superblockStart  = 0;
#define inodeBitmapStart blockSize
#define inodesStart      blockSize*9
#define dataBitmapStart  blockSize*maxInodes
#define dataGroupStart   (blockSize*32) + dataBitmapStart
// Block Ending positions 
#define superblockEnd    blockSize-1
#define inodeBitmapEnd   (blockSize*8)-1
#define inodesEnd        dataBitmapStart-1
#define dataBitmapEnd    dataGroupStart-1
#define dataGroupEnd     maxSize

int nFiles = 0;

void  diskInit();
void  diskRead(char *filename);
void  formatDisk();
void  createSuperblock();
void  createInode(int index);
void  createRoot();
void  makeFile(int index,char *filename);
void  writeFile(char *filename,char *str);
void  deleteFile(char *fileName);

int   blockOffser(int index);
int   inodeOffset(int index);
int   findFile(char *filename);
int   getFile(char *fileName);
int   getFreeInode();
int   getFreeBlock();