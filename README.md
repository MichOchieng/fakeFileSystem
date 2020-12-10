Completely Fake File System (CFFS)
==================================
This is not a working file system, and cannot be mounted.\
This programs simulates the disk and partition and temporarily saves
data in memory.

# Functions

void  diskInit();                                                     // Formats the disk, creates superblock and root directory\
void  diskRead(char *filename);                       // Allows user to read "file" data\
void  formatDisk();                                              // Sets disk values to 0 and fills directory array to empty strings\
void  createSuperblock();                                  // Creates superblock\
void  createInode(int index);                           // Initializes inode with file size of 0\
void  createRoot();                                             // Creates root directory (Makes file)\
void  makeFile(int index,char *filename);   // Creates an inode for a file and saves file name to fileNames array\
void  writeFile(char *filename,char *str);   // Writes data to a given file\
void  deleteFile(char *fileName);                 // Deletes a file\
void  mkDir(int index,char *dirName);      // Makes a new directory on the disk\
void  changeDir(char *dir);                          // Changes directory\
void  shell();                                                    // Runs the shell until user exits\
void  printString();                                       // Prints a string\
void  execute(char ** args);                      // Depending on input will execute disk functions\
int   blockOffser(int index);                      // Used for calculating datablock locations\
int   inodeOffset(int index);                       // Used for calculating inode locations\
int   getFile(char *fileName);                    // Used for getting file index for inode calculations\
int   getDirIndex(char *dir);                     // Used for getting directory index for inode calculations\
int   getFreeInode();                                  // Gets the location of the next free inode\
int   getFreeBlock();                                  // Gets the location of the next data block

# Shell Operations
touch <Filename>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;                 //Creates files\
mkdir <Directory>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;                //Creates folders\
cd    <Directory>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;                //Changes directories\
rm    <Filename>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;                 //Removes files\
write <Filename> <String>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;        //Writes given input to files\
read   <Filename>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;                //Reads from files and prints to terminal
