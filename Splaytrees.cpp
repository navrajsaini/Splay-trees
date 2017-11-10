//*************************************
// Navraj Saini & Bhupinder Gill
// Due: 2018, 11,
// Description: Implement Splay trees
//              in a language of out
//              choice (c++)
// resources: http://www.cs.uleth.ca/~gaur/post/splay/
//************************************

#include "Splay.h"
#include <iostream>

using namespace std;

int main()
{
   splayt a;
   
   double val;
   char exit = 'y';
   char func;
   while (exit == 'y')
   {
      cout << "Insert (I), Find (F), or Delete(D): ";
      cin >> func;
      switch (func)
      {
	 case 'I':
	 case 'i':
	 {
	    cout << "enter the number you would like to insert: ";
	    cin >> val;
	    a.insert(val);
	    break;
	 }
	 case 'F':
	 case'f':
	 {
	    cout << "enter the number you would like to find: ";
	    cin >> val;
	    splayt::node* b = a.find(val);
	    b->print();
	    break;
	 }
	 case 'D':
	 case 'd':
	 {
	    cout << "enter the number you would like to delete: ";
	    cin >> val;
	    a.del(val);
	    break;
	 }
      }
      cout << "would you like to continue? y = yes, n = no: ";
      cin >> exit;
   }
   return 0;
}
