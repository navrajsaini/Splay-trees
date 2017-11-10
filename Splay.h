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
      double data;
      node *left, *right, *parent;
      node()
      {
	 left = NULL;
	 right = NULL;
	 parent = NULL;
	 data = 0;
      }
      node (double a)
      {
	 left = NULL;
	 right = NULL;
	 parent = NULL;
	 data = a;
      }
      ~node(){}

      void print()
      {
	 cout << data << endl;
      }
      
   } *root;
   splayt() : root(NULL), size(0) { }

   //size of the tree
   int size;

   // minimum subtree
   node* mini(node *a)
   {
      //cout << "in mini..." << endl;

      if (!a -> left)
	 return a;
	 return mini(a -> left);

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
      //cout << "entering the while loop in splay" << endl;
      while (x -> parent)
      {
	 if( !x -> parent -> parent )
	 {
	    //cout << "in the first if" << endl;
	    if( x->parent->left == x )
	       RRotate( x->parent );
	    else
	       LRotate( x->parent );
	 }
	 else if( x->parent->left == x &&
		  x->parent->parent->left == x->parent )
	 {
	    //cout << "in the first else if" << endl;
	    RRotate( x->parent->parent );
	    RRotate( x->parent );
	 }
	 else if( x->parent->right == x &&
		    x->parent->parent->right == x->parent )
	 {
	    //cout << "in the 2nd else if" << endl;
	    LRotate( x->parent->parent );
	    LRotate( x->parent );
	 }
	 else if( x->parent->left == x &&
		    x->parent->parent->right == x->parent )
	 {
	    //cout << "in the 3rd else if" << endl;
	    RRotate( x -> parent );
	    LRotate( x -> parent );
	 }
	 else
	 {
	    //cout << "last, entering the LR" << endl;
	    LRotate( x -> parent );
	    //cout << "entering the RR" << endl;
	    RRotate( x -> parent );
	    //cout << "out of the RR?" << endl;
	 }
      }
      //cout << "end of the while loop" << endl;
    }

   void swap (node *a, node *b)
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
   void insert (double d)
   {
      node *a = root;
      node *b = NULL;

      while (a)
      {
	 b = a;
	 //cout << "in the while loop FML" << endl;
	 if (a -> data < d)
	 {
	    //cout << " in the if loop: " <<endl;
	    a = a -> right;
	    //cout << "out of the loop" <<endl;
	    
	 }
	 else
	    a = a -> left;
	 //cout << "out of the if/else in the while" << endl;
      }

      //cout << "out of the while loop" << endl;
      a = new node (d);
      a -> parent = b;
      
      if(!b)
	 root = a;
      else if (b -> data < a -> data)
	 b -> right = a;
      else
	 b -> left = a;
      //cout << "about to splay: " << endl;
      splay(a);
      size++;
   }

   node* find (double d)
   {
      node *a = root;
      // if the data is < than or > than or == to
      while (a)
      {
	 if (a -> data < d)
	    a = a -> right;
	 else if (a -> data > d)
	    a = a -> left;
	 else if (a -> data == d)
	    return a;
	 else
	    return NULL;
      }
      return NULL;
   }

   void del (double d)
   {
      node *a = find (d);
      if (!a)
	 return;
      //cout << "about to splay in del." << endl;
      splay(a);
      //cout << "done splaying....." << endl;
      if (!a -> right)
      {
	 //cout << "about to swap" << endl;
	 swap (a, a -> left);
	 //cout << "done the swap" << endl;
      }
      else if (!a -> left)
      {
	 //cout << "about to swap in else if..." << endl;
	 swap (a, a -> right);
	 //cout << "done" << endl;
      }
      else
      {
	 //cout << "in the else... in del" << endl;
	 node *b = mini(b -> right);
	 //cout << "done making a node..." << endl;
	 if (b -> parent != a)
	 {
	    //cout << "seg fault?" << endl;
	    swap (b, b -> right);
	    b -> right = a -> right;
	    b -> right -> parent = b;
	 }
	 //cout << "seg Fault?" << endl;
	 swap (a, b);
	 b -> left = a -> left;
	 b -> left -> parent = b;
      }
      delete a;
      size--;
   }

   void print()
   {
      //cout << "print seg fault?" << endl;
      cout << root->data << endl;
   }
};

#endif
