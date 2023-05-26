#include <iostream>
using namespace std;
int main()
{
    string line;
    cout<<"Please enter your name on the line (including spaces): ";
    getline(cin,line);
	cout<<"Hello, " << line<<"!"<<endl;
}
