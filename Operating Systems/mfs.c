// The MIT License (MIT)
// 
// Copyright (c) 2020 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/*
 *
 *  Name: Richard Nguyen
 *  ID: 1001360247
 *
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_NUM_ARGUMENTS 4

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size


struct __attribute__((__packed__)) DirectoryEntry{
  char DIR_Name[11];
  uint8_t DIR_Attr;
  uint8_t Unused1[8];
  uint16_t DIR_FirstClusterHigh;
  uint8_t Unused2[4];
  uint16_t DIR_FirstClusterLow;
  uint32_t DIR_FileSize;
};

struct DirectoryEntry dir[16];

int16_t BPB_BytesPerSec;
int8_t BPB_SecPerClus;
int16_t BPB_RsvdSecCnt;
int8_t BPB_NumFATS;
int32_t BPB_FATSz32;

FILE * fp;

int LBAToOffset(int32_t sector);
int16_t NextLB(uint32_t sector);
int compare(char* input);

int main()
{

  
  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
  bool isOpen = false;

  while( 1 )
  {
    // Print out the mfs prompt
    printf ("mfs> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *arg_ptr;                                         
                                                           
    char *working_str  = strdup( cmd_str );                

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input stringswith whitespace used as the delimiter
    while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    /* Now print the tokenized input as a debug check

    int token_index  = 0;
    for( token_index = 0; token_index < token_count; token_index ++ ) 
    {
      printf("token[%d] = %s\n", token_index, token[token_index] );  
    }

    */

    // Fat32 Functionality

    if(token[0] == NULL){
	continue;
    }

    // open command
    if(strncmp(token[0], "open", 4) == 0){
	if(isOpen){
	   perror("Error: File system image already open. ");
	   continue;
	}


	fp = fopen(token[1],"r");

	if(fp==NULL){
	   perror("Error: File system image not found. ");
	   continue;
	}
	isOpen = true;

	// BytesPerSec
	fseek(fp,11,SEEK_SET);
	fread(&BPB_BytesPerSec,2,1,fp);
	// SecPerClus
	fseek(fp,13,SEEK_SET);
	fread(&BPB_SecPerClus,1,1,fp);
	// RsvdSecCnt
	fseek(fp,14,SEEK_SET);
	fread(&BPB_RsvdSecCnt,2,1,fp);
	// NumFATS
	fseek(fp,16,SEEK_SET);
	fread(&BPB_NumFATS,1,1,fp);
	// FATSz32
	fseek(fp,36,SEEK_SET);
	fread(&BPB_FATSz32,4,1,fp);

	int root = (BPB_NumFATS * BPB_FATSz32 * BPB_BytesPerSec) + (BPB_RsvdSecCnt * BPB_BytesPerSec);

	fseek(fp,root,SEEK_SET);
	fread(&dir,sizeof(struct DirectoryEntry),16,fp);

	
    }

    // close command
    if(strncmp(token[0],"close",5) == 0){
	if(isOpen){
	   isOpen = false;
	   fclose(fp);
	   printf("File closed.\n");
	}
	else{
	   perror("Error: File system not open. ");
	}
    }


   // info command
   if(strncmp(token[0],"info",4) == 0){
	if(isOpen==false){
	   perror("Error: File system image must be opened first. ");
	   continue;
	}

	printf("BPB_BytesPerSec: %d %x\n", BPB_BytesPerSec, BPB_BytesPerSec);

	printf("BPB_SecPerClus: %d %x\n", BPB_SecPerClus, BPB_SecPerClus);

	printf("BPB_RsvdSecCnt: %d %x\n", BPB_RsvdSecCnt, BPB_RsvdSecCnt);

	printf("BPB_NumFATS: %d %x\n", BPB_NumFATS, BPB_NumFATS);

	printf("BPB_FATSz32: %d %x\n", BPB_FATSz32, BPB_FATSz32);
   }


   // stat command
   if(strncmp(token[0],"stat",4) == 0){
	if(isOpen==false){
	   perror("Error: File system image must be opened first. ");
	   continue;
	}
	if(token[1] == NULL){
	   perror("Error: invalid arguments. ");
	   continue;
	}

	int i = compare(token[1]);
	printf("File Size: %d\n", dir[i].DIR_FileSize);
	printf("First Cluster Low: %x\n", dir[i].DIR_FirstClusterLow);
	printf("DIR_ATTR: %x\n", dir[i].DIR_Attr);
	printf("First Cluster High: %x\n", dir[i].DIR_FirstClusterHigh);
   }

   // get command
   if(strncmp(token[0],"get",3) == 0){
	if(isOpen==false){
	   perror("Error: File system image must be opened first. ");
	   continue;
	}
	if(token[1] == NULL){
	   perror("Error: Invalid arguments");
	   continue;
	}
	int i = compare(token[1]);
	if(i == 99){
	   perror("Error: File not found ");
	   continue;
	}
	int nLB = 0;
	unsigned char buffer[512];
	int bytesRemaining = dir[i].DIR_FileSize;
	int cluster = dir[i].DIR_FirstClusterLow;
	int offset = 0;
	FILE *newFile = fopen(token[1], "w");
	while(true){
	   offset = LBAToOffset(cluster);
	   fseek(fp,offset,SEEK_SET);
	   fread(&buffer,512,1,fp);
	   fwrite(&buffer,512,1,newFile);
	   cluster = NextLB(cluster);
	   if(cluster == -1){
	      break;
	   }
	}


   }

   // cd command
   if(strncmp(token[0],"cd",2) == 0){
      if(isOpen==false){
	perror("Error: File system image must be opened first. ");
	continue;
      }
      if(token[1] == NULL){
	perror("Error: Invalid arguments ");
	continue;
      }
      int i = compare(token[1]);
      if(i == 99){
	perror("Error: File not found ");
	continue;
      }
      int cluster = dir[i].DIR_FirstClusterLow;
      int offset = LBAToOffset(cluster);
      fseek(fp,offset,SEEK_SET);
      fread(&dir,sizeof(struct DirectoryEntry),16,fp);
   }

   // ls command
   if(strncmp(token[0],"ls",2) == 0){
	if(isOpen==false){
	   perror("Error: File system image must be opened first. ");
	   continue;
	}

	int i;
	for(i = 0; i < 16; i++){
	   if(dir[i].DIR_Name[0] != (char)0xe5) {
	      if(dir[i].DIR_Attr == 0x01 || dir[i].DIR_Attr == 0x10 || dir[i].DIR_Attr == 0x20){
	         char filename[12];
	         strncpy(&filename[0], &dir[i].DIR_Name[0],11);
	         filename[11] = '\0';
	         printf("%s\n",filename);
	      }
	   }
	}
	
   }

   // read command
   if(strncmp(token[0],"read",4) == 0){
	if(isOpen==false){
		perror("Error: File system image must be opened first. ");
		continue;
	}
	if(token[2] == NULL || token[3] == NULL){
		perror("Error: Invalid Arguments ");
		continue;
	}
	int i = compare(token[1]);
	if(i == 99){
	   perror("Error: File not found ");
	   continue;
	}

	int buffer = 0;
	int cluster = dir[i].DIR_FirstClusterLow;
	int offset = LBAToOffset(cluster);

	fseek(fp,offset+atoi(token[2]),SEEK_SET);
	int j;
	for(j = 0; j < atoi(token[3]); j++){
	   fread(&buffer,1,1,fp);
	   printf("%x ", buffer); 
	}
	printf("\n");
	
   }




    free( working_root );

  }
  return 0;
}


/*
 * Function     : LBAToOffset
 * Parameters   : The current sector number that points to a block of data
 * Returns      : The value of the address for that block of data
 * Description  : Finds the starting address of a block of data given the sector number
 * corresponding to that data block.
 */
int LBAToOffset(int32_t sector){
   if(sector == 0){
      sector = 2;
   }

   return ((sector-2)*BPB_BytesPerSec) + (BPB_BytesPerSec*BPB_RsvdSecCnt) + (BPB_NumFATS * BPB_FATSz32 * BPB_BytesPerSec);
}


/*
 * Name   : NextLB
 * Purpose: Given a logical block address, look up into the first FAT and return the logical block address of the block in the file. If there is no further blocks then return -1
 */
int16_t NextLB(uint32_t sector){
   uint32_t FATAddress = (BPB_BytesPerSec * BPB_RsvdSecCnt) + (sector*4);
   int16_t val;
   fseek(fp, FATAddress, SEEK_SET);
   fread(&val,2,1,fp);
   return val;
}


int compare(char* input){
   char expanded_name[12];
   char dirName[12];

   

   //COPYING input into expanded name
   //Puts spaces
   memset(expanded_name, ' ',11);
   if(strncmp(input,"..",2) == 0){
      strncpy(expanded_name,input,strlen(input));
   }
   else{
      char *token = strtok(input, ".");
      //Copies first half before .
      strncpy(expanded_name,token,strlen(token));
      token = strtok(NULL,".");

      //Second half after the .
      if(token){
         strncpy((char*)(expanded_name+8), token, strlen(token));
      }

      //Turns it all into upper case
      int i;
      for(i = 0; i < 11; i++){
         expanded_name[i] = toupper(expanded_name[i]);
      }

   }


   expanded_name[11] = '\0';

   int i;
   for(i = 0; i < 16; i++){
      strncpy(&dirName[0], &dir[i].DIR_Name[0],11);
      dirName[11] = '\0';
      if(strncmp(expanded_name,dirName,11) == 0){
	return i;
      }
   }

   return 99;


}



