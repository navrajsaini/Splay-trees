//**********************************
// Splay tree .h file
//**********************************
#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <new>
using namespace std;

class splayt
{
  public:
   friend class node;
   // nodes for the splay tree, points to left, right and parent
   // of the node the user is at....
   
   struct node
   {
   public:
      int data;
      node *left, *right, *parent;
      node()
      {
	 left = NULL;
	 right = NULL;
	 parent = NULL;
	 data = 0;
      }
      node (int a)
      {
	 left = NULL;
	 right = NULL;
	 parent = NULL;
	 data = a;
      }
      ~node(){}
      
   } *root;
   splayt() : root(NULL), size(0) { }

   //size of the tree
   int size;

   // minimum subtree
   node* mini(node *a)
   {
      if (!a -> left)
	 return a;
      mini(a -> left);
   }

   //maximum subtree
   node* maxi(node *a)
   {
      if (!a -> right)
	 return a;
      maxi(a -> right);
   }
   
   //right rotate if needed
   void RRotate(node *x)
   {
      // new nodes point to root node's left sub tree
      node *a = x -> left;
      
      // if the right side of x exits:

      // make x's left point to it's left's right sub tree

      //  if x's left's right subtree exists, point x's left's right's
      //     parent point to x
      //    make a's right (x's left's right) parent x

      //  point a's parent (x's left's parent) to x's parent
      if(a)
      {
	 x -> left = a -> right;
	 if(a -> right)
	    a -> right -> parent = x;
	 a -> parent = x -> parent;
      }
      if( !x -> parent)
	 root = a;
      else if (x == x -> parent -> left)
	 x -> parent -> left = a;

      else
	 x -> parent -> right = a;
      
      if (a)
	 a -> right = x;
      x -> parent = a;
   }

   // same as right rotate but the left and right swap
   void LRotate(node *x)
   {
      node *a = x -> right;
      


      if(a)
      {
	 x -> right = a -> left;
	 if(a -> left)
	    a -> left -> parent = x;
	 a -> parent = x -> parent;
      }
      if (! x -> parent)
	 root = a;
      else if (x == x -> parent -> left)
	 x -> parent -> left = a;

      else
	 x -> parent -> right = a;
      
      if (a)
	 a -> left = x;
      x -> parent = a;
   }

   // now for the actual splay....
   void splay (node *x)
   {
      cout << "entering the while loop in splay" << endl;
      while (x -> parent)
      {
	 if( !x -> parent -> parent )
	 {
	    cout << "in the first if" << endl;
	    if( x->parent->left == x )
	       RRotate( x->parent );
	    else
	       LRotate( x->parent );
	 }
	 else if( x->parent->left == x &&
		  x->parent->parent->left == x->parent )
	 {
	    cout << "in the first else if" << endl;
	    RRotate( x->parent->parent );
	    RRotate( x->parent );
	 }
	 else if( x->parent->right == x &&
		    x->parent->parent->right == x->parent )
	 {
	    cout << "in the 2nd else if" << endl;
	    LRotate( x->parent->parent );
	    LRotate( x->parent );
	 }
	 else if( x->parent->left == x &&
		    x->parent->parent->right == x->parent )
	 {
	    cout << "in the 3rd else if" << endl;
	    RRotate( x -> parent );
	    LRotate( x -> parent );
	 }
	 else
	 {
	    cout << "last, entering the LR" << endl;
	    LRotate( x -> parent );
	    cout << "entering the RR" << endl;
	    RRotate( x -> parent );
	    cout << "out of the RR?" << endl;
	 }
      }
      	 cout << "end of the while loop" << endl;
    }

   void replace (node *a, node *b)
   {
      if (a == a -> parent -> left)
	 a -> parent -> left = b;
      else if (!a -> parent)
	 root = b;
      else
	 a -> parent -> right = b;
      if (b)
	 b -> parent = a -> parent;
   }
   //insert a key into the splay tree
   void insert (int d)
   {
      node *a = root;
      node *b = NULL;

      while (a)
      {
	 b = a;
	 cout << "in the while loop FML" << endl;
	 if (a -> data < d)
	 {
	    cout << " in the if loop: " <<endl;
	    a = a -> right;
	    cout << "out of the loop" <<endl;
	    
	 }
	 else
	    a = a -> left;
	 cout << "out of the if/else in the while" << endl;
      }

      cout << "out of the while loop" << endl;
      a = new node (d);
      a -> parent = b;
      
      if(!b)
	 root = a;
      else if (b -> data < a -> data)
	 b -> right = a;
      else
	 b -> left = a;
      cout << "about to splay: " << endl;
      splay(a);
      size++;
   }

   node* find (int d)
   {
      node *a = root;
      while (a)
      {
	 if (a -> data < d)
	    a = a -> right;
	 else if (a -> data > d)
	    a = a -> left;
	 else
	    return a;
      }
      return NULL;
   }

   void del (int d)
   {
      node *a = find (d);
      if (!a)
	 return;
      splay(a);

      if (!a -> right)
	 replace (a, a -> left);
      else if (!a -> left)
	 replace (a, a -> right);
      else
      {
	 node *b = mini (b -> right);
	 if (b -> parent != a)
	 {
	    replace (b, b -> right);
	    b -> right = a -> right;
	    b -> right -> parent = b;
	 }
	 replace (a, b);
	 b -> left = a -> left;
	 b -> left -> parent = b;
      }
      delete a;
      size--;
   }

   void print()
   {
      cout << "print seg fault?" << endl;
      cout << root->data<< endl;
   }
};

#endif
