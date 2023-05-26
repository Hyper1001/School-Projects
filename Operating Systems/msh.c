/*

  Name: George Vo
  ID: 1001360024

*/
// The MIT License (MIT)
//
// Copyright (c) 2016, 2017, 2021 Trevor Bakker
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
// 7f704d5f-9811-4b91-a918-57c1bb646b70
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 5     // Mav shell only supports five arguments

int main()
{
	char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
 	while( 1 )
  	{
    		// Print out the msh prompt
    		printf ("msh> ");

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
    		char*argument_ptr;

		char *working_str  = strdup( cmd_str );

    		// we are going to move the working_str pointer so
   		// keep track of its original value so we can deallocate
  		// the correct amount at the end
   		char *working_root = working_str;

    		// Tokenize the input strings with whitespace used as the delimiter
		while ( ( (argument_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && (token_count<MAX_NUM_ARGUMENTS))
		{
			token[token_count] = strndup( argument_ptr,MAX_COMMAND_SIZE);
			if( strlen( token[token_count] ) == 0 )
			{
				token[token_count] = NULL;
			}
       			token_count++;
    		}

		// Now print the tokenized input as a debug check
    		// \TODO Remove this code and replace with your shell functionality

		int token_index  = 0;
		//Checks to see if input is NULL and just ignore and loop again.
		if(token[0]==NULL)
		{
		}
		//Chekcs ot see if input is exit/quit and will break out of the loop and return 0
		else if(strcmp(token[0],"exit")==0||strcmp(token[0],"quit")==0)
		{
			break;
		}
		//Checks to see if user inputted cd and will change directories.
		else if(strcmp(token[0],"cd")==0)
		{
			chdir(token[1]);
		}
		//Anything that gets past the if statements above.
		else
		{
			pid_t pid = fork();

  			if( pid == 0 )
			{
    				// Runs through all locations to see if there is a command there.
    				char cat1[100000];
  				strcat(cat1,"/usr/local/bin/");
  				strcat(cat1,token[0]);
  				char cat2[100000];
  				strcat(cat2,"/usr/bin/");
  				strcat(cat2,token[0]);
  				char cat3[100000];
  				strcat(cat3,"/bin/");
  				strcat(cat3,token[0]);
    			 	int ret = execl( cat1, token[0], token[1], token[2], token[3], token[4], token[5], token[6], token[7], token[8], token[9], token[10]);
    			 	ret = execl( cat2, token[0], token[1], token[2], token[3], token[4], token[5], token[6], token[7], token[8], token[9], token[10]);
  				ret = execl( cat3, token[0], token[1], token[2], token[3], token[4], token[5], token[6], token[7], token[8], token[9], token[10]);
  				//If it fails, then it will return command not found and break so it doesn't cause issues.
    				if(ret==-1)
    				{
      					printf("%s: Command not found\n",token[0]);
      					break;
    				}
  			}
  			else
  			{
    				int status;
    				wait( & status );

 			}
		}
		free( working_root );
	}
	//Program has finished.
  	return 0;
}
