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

#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

#define MAX_NUM_ARGUMENTS 3

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size


struct __attribute__((__packed__)) DirectoryEntry
{
	char DIR_Name[11];
	uint8_t DIR_Attr;
	uint8_t unused[8];
	uint16_t ClusterHigh;
	uint8_t unused2[4];
	uint16_t ClusterLow;
	uint32_t size;
};

struct DirectoryEntry dir[16];

int comp(char* in)
{
	char IMG_Name[12];
 	char expanded_name[12];
 	memset( expanded_name, ' ', 11 );
  	char* tok = strtok(in,".");
  	int len = strlen(tok);
	strncpy(expanded_name,tok,len);
	tok = strtok(NULL,".");
	if(tok)
	{
		strncpy((char*)(expanded_name + 8), tok, len);	
	}
	int a;
	for(a=0;a<11;a++)//All upper case
	{
		expanded_name[a] = toupper(expanded_name[a]);
	}
	expanded_name[11] = '\0';
	for(a=0;a<16;a++)
	{
		strncpy(&IMG_Name[0],&dir[a].DIR_Name[0],11);
		IMG_Name[11] = '\0';
		if(strncmp(expanded_name,IMG_Name,11)==0)
		{
			return a;
		}
		
	}
	return -1;
}

int main()
{

	char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
	int isOpened = 0;
	FILE *fp;
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
    		while (((arg_ptr = strsep(&working_str, WHITESPACE))!= NULL)&&(token_count<MAX_NUM_ARGUMENTS))
   		{
      			token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
      			if( strlen( token[token_count] ) == 0 )
      			{
        			token[token_count] = NULL;
      			}
        		token_count++;
    		}

    		// Now print the tokenized input as a debug check
    		// \TODO Remove this code and replace with your FAT32 functionality

    		if(strcmp("open",token[0])==0)
    		{
    			
    			if(isOpened==1)
    			{
    				printf("Error: File system image already opened\n");
    			}
    			else
    			{
    				fp = fopen(token[1],"r");
    				if(fp==NULL)
    				{
    					printf("Error: File system image not found (\"%s\")\n",token[1]);
    					fp=NULL;
    				}
    				else
    				{
    					isOpened=1;
    				}
    			}
    		}
    		else if(strcmp("quit",token[0])==0)
    		{
    			return 0;
    		}
    		else if(isOpened==0)
    		{
    			printf("Error: First system image must be opened first\n");
    		}
    		else if(strcmp("close",token[0])==0)
    		{
    			fclose(fp);
    			isOpened=0;
    		}
    		else if(strcmp("info",token[0])==0)
    		{
    			int placeholder = 0;
    			int16_t BPB_BytsPerSec;
    			fseek(fp,11,SEEK_SET);
    			fread(&BPB_BytsPerSec, 2, 1, fp);
    			int8_t BPB_SecsPerClus;
    			fseek(fp,13,SEEK_SET);
    			fread(&BPB_SecsPerClus, 1, 1, fp);
    			int16_t BPB_RsvdSecCnt;
    			fseek(fp,14,SEEK_SET);
    			fread(&BPB_RsvdSecCnt, 2, 1, fp);
    			int8_t BPB_NumFATs;
    			fseek(fp,16,SEEK_SET);
    			fread(&BPB_NumFATs, 1, 1, fp);
    			int32_t BPB_FATSz32;
    			fseek(fp,36,SEEK_SET);
    			fread(&BPB_FATSz32, 4, 1, fp);
    			printf("BPB_BytesPerSec:\t%d\t%x\n",BPB_BytsPerSec,BPB_BytsPerSec);
    			printf("BPB_SecPerClus:\t\t%d\t%x\n",BPB_SecsPerClus,BPB_SecsPerClus);
    			printf("BPB_RsvdSecCnt:\t\t%d\t%x\n",BPB_RsvdSecCnt,BPB_RsvdSecCnt);
    			printf("BPB_NumFATS:\t\t%d\t%x\n",BPB_NumFATs,BPB_NumFATs);
    			printf("BPB_FATSz32:\t\t%d\t%x\n",BPB_FATSz32,BPB_FATSz32);
    		}
    		else if(strcmp("stat",token[0])==0)
    		{
    			int i = comp(token[1]);
    			if(token[1]==NULL||i==-1)
    			{
    				printf("Error: File not Found\n");
    			}
    	
    				printf("File Size: %d\n", dir[i].size);
    				printf("First Cluster Lower %x\n",dir[i].ClusterLow);
    				printf("DIR_ATTR %x\n",dir[i].DIR_Attr);
    				printf("First Cluster High: %x\n",dir[i].ClusterHigh);
    			
    		}
    		else if(strcmp("cd",token[0])==0)
    		{
    			printf("This is the cd command \n");
    		}
    		else if(strcmp("ls",token[0])==0)
    		{
    			int i;
    			fseek(fp,0x100400,SEEK_SET);
    			fread(&dir, sizeof(struct DirectoryEntry),16,fp);
    			for(i=0;i<16;i++)
    			{
    				if(dir[i].DIR_Attr==0x1||dir[i].DIR_Attr==0x10||dir[i].DIR_Attr==0x20)
    				{
    					char filename[12];
    					strncpy(&filename[0],&dir[i].DIR_Name[0],11);
    					filename[11]='\0';
    					printf("%s\n",filename);
    				}
    			}
    		}
    		else if(strcmp("get",token[0])==0)
    		{
    			printf("This is the get command \n");
    		}
    		else if(strcmp("read",token[0])==0)
    		{
    			printf("This is the read command \n");
    		}
    		else
    		{
    			printf("Error: Command not found.\n");
    		}
    		free( working_root );
  	}
	return 0;
}
