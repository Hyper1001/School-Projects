#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
int main()
{
    char * user_name = getenv("USER");
    if (!user_name)
    {
        user_name = getenv("USERNAME");
    }
    cout<<"Hello, "<< user_name <<"!"<<endl;
}
