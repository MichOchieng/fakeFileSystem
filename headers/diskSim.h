#define maxSize 1280000
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

void  diskInit();
void  diskRead(int index);
void  diskWrite(int index,char *input);
void  formatDisk();
void  createSuperblock();
void  createInode();