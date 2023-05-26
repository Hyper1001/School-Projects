#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>

#define cores 4
#define MAX 5000000
using namespace std;
  
int total = 0; //total of all substrings found
char *s1,*s2;//s1=text to be scanned, s2=substring to be found
int n1,n2; //n1 = length of s1, n2 = length of s2
FILE *fp;

void* num_substring(void* args)
{
	int threadnum = *(int*)args;
    	int i, j, k;//i and j for for loops, k is for the offset.
    	bool fail;//variable to keep track if substrings are the same.
    	int threadtotal=0;//keep track of totals in thread and prevent it from interfering with other threads.
    	for (i = threadnum; i <= n1-n2; i = i + cores) //will check every "threanum + 4" to see if its a substring
    	{
        	fail = false;
        	k = i;
        	for (j = 0; j < n2-1; j++)//Thiis will actually see if the string and substring are the same by looking at each one character by character.
        	{
            		if (s1[k] != s2[j])//if not the same, then break and do nothing else
            		{
				fail = true;
             		   	break;
            		}
            		else
            		{
            			k++;
            		}
        	}
		if (fail == false) //adds to the total if it didn't fail
        	{
          	  threadtotal += 1;
        	}
    	}
    	total+=threadtotal;//makes sure that threads don't interfere with each other.
}
  
int main()
{
	fp=fopen("string.txt","r");
	s1=(char *)malloc(sizeof(char)*MAX);
	s2=(char *)malloc(sizeof(char)*MAX);
	s1=fgets(s1, MAX, fp);
    	s2=fgets(s2, MAX, fp);
	//n1 = s1.length();
	//n2 = s2.length();
	n1= strlen(s1);
	n2=strlen(s2);
 	pthread_t thread[cores];//create a thread capable of doing 4 tasks simultaneously
  	int i;
  	int foo[cores];
    	for (int a = 0; a < cores; a++)
    	{
        	foo[a] = a;
        }
    	for (i = 0; i < cores; i++)//create a thread for each core
    	{
    		int p =2;
        	pthread_create(&thread[i], NULL, num_substring,(void*)&foo[i]);//will create a thread to cover each core (0,1,2,3)

    	}
    	for (i = 0; i < cores; i++)//run each thread simultaneously
    	{
        	pthread_join(thread[i], NULL);

    	}
    	cout << "The number of substrings is : " << total << endl;

    	return 0;
}
