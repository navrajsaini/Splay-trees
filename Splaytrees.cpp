//*************************************
// Navraj Saini & Bhupinder Gill
// Due: 2018, 11,
// Description: Implement Splay trees
//              in a language of out
//              choice (c++)
//************************************

#include "Splay.h"
#include <iostream>

using namespace std;

int main()
{
   splayt a;
   
   int val;
   char exit = 'n';
   while (exit == 'n')
   {
      cout << "please insert a int into the splay tree: ";
      cin >> val;
      a.insert(val);
      cout << "print here: " << endl;
      a.print();
      cout << endl << "done printing" << endl;
   }
   return 0;
}
