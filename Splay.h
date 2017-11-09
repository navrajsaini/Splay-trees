//**********************************
// Splay tree .h file
//**********************************
#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>

using namespace std;

class splayt
{
  private:
   // nodes for the splay tree, points to left, right and parent
   // of the node the user is at....
   class node
   {
     public:
      int data;
      node *left, *right, *parent;
     node(int) : left (NULL), right (NULL), parent(NULL), data (0) {}
      ~node(){}
      
   } *root;
   
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

      if (! x -> parent)
	 root = a;
      
      // if the right side of x exits:

      // make x's left point to it's left's right sub tree

      //  if x's left's right subtree exists, point x's left's right's
      //     parent point to x
      //    make a's right (x's left's right) parent x

      //  point a's parent (x's left's parent) to x's parent
      if(x -> left)
      {
	 x -> left = a -> right;
	 if(a -> right)
	    a -> right -> parent = x;
	 a -> parent = x -> parent;
      }

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
      
      if (! x -> parent)
	 root = a;

      if(a)
      {
	 x -> right = a -> left;
	 if(a -> left)
	    a -> left -> parent = x;
	 a -> parent = x -> parent;
      }

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
      while (x -> parent)
      {
	 if (x -> parent -> parent -> left == x -> parent &&
	     x -> parent -> left == x)
	 {
	    RRotate (x -> parent -> parent);
	    RRotate (x -> parent);
	 }
	 else if (!x -> parent -> parent)
	 {
	    if (x -> parent -> left == x)
	       RRotate (x -> parent);
	    else
	       LRotate (x -> parent);
	 }
	 else if (x -> parent -> parent -> right == x -> parent &&
		  x -> parent -> right)
	 {
	    LRotate (x -> parent -> parent);
	    LRotate (x -> parent);
	 }
	 else if(x -> parent -> left == x &&
		 x -> parent -> parent -> right == x -> parent)
	 {
	    RRotate (x -> parent);
	    LRotate (x -> parent);
	 }
	 else
	 {
	    LRotate (x -> parent);
	    RRotate (x -> parent);
	 }
      }
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
  public:
   
   //insert a key into the splay tree
   void insert (int d)
   {
      node *a = root;
      node *b = NULL;

      while (a)
      {
	 b = a;
	 if (a -> data < d)
	    a = a -> right;
	 else
	    a = a -> left;
      }
      
      a = new node (d);
      a -> parent = b;

      if(!b)
	 root = a;
      else if (b -> data < a -> data)
	 b -> right = a;
      else
	 b -> left = a;
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
};

#endif
