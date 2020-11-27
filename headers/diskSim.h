#define blockSize 128
#define maxSize   1280000
#define maxBlocks 1000
#define maxInodes 100
#define magicNum  0xf0f03410

void  diskInit();
void  diskRead(int index);
void  diskWrite(int index,char *input);
void  formatDisk();
void  createSuperblock();
void  createInodeBitmap();
void  createInode();
void  createBlockGroup();