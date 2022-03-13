#include "binary-search-tree.h"
#include <iostream>
#include <queue>
#include <iostream>
#include <stack>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    left = NULL;
    right = NULL;

    val = newval;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    int count = 0;

    // Counting the height of the left subtree if it exists
    if (n->left != NULL)
    {
        count++;
        count = count + getNodeDepth(n->left);
    }
    else if(n->right != NULL)  // Counting the height of right subtree if left does not exist
    {
        count++;
        count = count + getNodeDepth(n->right);
    }

    return count;
}

BinarySearchTree::BinarySearchTree()
{
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
}
unsigned int BinarySearchTree::size() const
{
    return size_;
}

DataType BinarySearchTree::max() const
{
    Node* cur = root_;
    while (cur->right != NULL)   // Iterating until we find the rightmost node (the max)
    {
        cur = cur->right;
    }

    return (cur->val);
}

DataType BinarySearchTree::min() const
{
    Node* cur = root_;

    while (cur->left != NULL)  // Iterating until we find the leftmost node (the min)
    {
        cur = cur->left;
    }

    return (cur->val);
}

unsigned int BinarySearchTree::depth() const
{
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const
{
    // Pre-Order Printing
    stack< Node* > stack;
    if (root_)
        stack.push(root_);

    while (!stack.empty())
    {
        Node* cur = stack.top();

        stack.pop();

        cout << cur->val << " ";

        if (cur->right) stack.push(cur->right);

        if (cur->left) stack.push(cur->left);
    }

    cout << endl;
    return;

}

bool BinarySearchTree::exists(DataType val) const
{
    Node* cur = root_;

    // Traversing the binary tree until we find our value if it exists

    while (cur != NULL)
    {
        if ( val > cur->val)
        {
            cur = cur->right;
        }
        else if (val < cur->val)
        {
            cur = cur->left;
        }
        else return true;
    }
    return false;
}

Node* BinarySearchTree::getRootNode()
{
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    Node* newNode = new Node(val);
    Node* cur = root_;

    // Base case 1: Tree is empty
    if( root_ == NULL )
    {
        root_ = newNode;
        size_++;
        return true;
    }

    // Base case 2: Val does not exist
    if( exists(val) ) return false;

    while( cur != NULL )
    {
        if( val < cur->val )  // Checking the left subtree
        {
            if (cur->left == NULL)   // If the left subtree is empty, we can insert the node
            {
                cur->left = newNode;
                size_++;
                return true;
            }
            else cur = cur->left;   // If left is not empty, then we traverse the current node to the left
        }
        else     // Checking the right subtree
        {
            if( cur->right == NULL )   // If the right subtree is empty, it is safe to insert the node
            {
                cur->right = newNode;
                size_++;
                return true;
            }
            else
            {
                cur = cur->right;   // If the right subtree is not empty, traverse the current node one to the right
            }
        }
    }
    return false;
}

Node* findPredecessor(Node* ptr)   // Helper function
{
    while( ptr->right != NULL ) ptr = ptr->right;
    return ptr;
}

bool BinarySearchTree::remove(DataType val)
{
    // Base case 1: The value to remove does not exist
    if( !exists(val) ) return false;

    // Case 1: The tree only has a root
    if( size_ == 1 )
    {
        root_ = NULL;
        size_--;
        return true;
    }

    Node* cur = root_;

    // Pointers to keep track of cur's parent nodes
    Node* prevLeft = NULL;
    Node* prevRight = NULL;

    while( cur != NULL )
    {
        if(val < cur->val && cur->left != NULL)  // Check to see if we can move to the left subtree
        {
            prevLeft = cur;
            prevRight = NULL;

            cur = cur->left;
        }
        else if(val > cur->val && cur->right != NULL) // Check to see if we can move to the right subtree
        {
            prevRight = cur;
            prevLeft = NULL;

            cur = cur->right;
        }
        else break;
    }


    if(cur->left == NULL || cur->right == NULL)
    {
        // Case 2: The node has no children
        if(cur->left == NULL && cur->right == NULL)
        {
            if(prevLeft == NULL)  // If prevLeft is null, then we know that node
            {                     // to be removed is to the right of prevRight
                if(prevRight->right != NULL) // Check to see if there is a right node/subtree to remove
                {
                    prevRight->right = NULL;
                }
                    cur = NULL;
                    delete cur;
                    size_--;
                    return true;
            }
            if(prevRight == NULL)  // If prevRight is null, then the node to be removed is to the left of prevLeft
            {
                if(prevLeft->left != NULL)
                {
                    prevLeft->left = NULL;
                }
                cur = NULL;
                delete cur;
                size_--;
                return true;
            }
        }

        // Case 3.1: There is only 1 child in the right subtree
        if (cur->right != NULL)
        {
            cur->val = cur->right->val;
            cur->right = NULL;

            delete cur->right;
            size_--;

            return true;
        }
        // Case 3.2: 1 child in the left subtree
        else if (cur->left != NULL)
        {

            cur->val = cur->left->val;
            cur->left = NULL;

            delete cur->left;
            size_--;

            return true;
        }
    }
  else
  {
      // Case 4: There are 2 children
      Node* pred = cur->left;
      Node* prevPred = NULL;  // Pointer to keep track of the parent node of the predecessor

      // Iterating through the tree to find the predecessor
      while( pred->right != NULL )
      {
          prevPred = pred;
          pred = pred->right;
      }

      int predecessor = pred->val;

      // Case 4.1: Removing the root node
      if( prevPred == NULL )
      {
          pred = NULL;
          delete pred;
          size_--;
          return true;
      }

      // Case 4.2: Pred has no child nodes
      if (pred->left == NULL)
      {
          cur->val = predecessor;  // Copying the value of the predecessor into our current node
          prevPred->right = NULL;  // Removing the link between the parent of the predecessor and the predecessor itself

          pred = NULL;
          delete pred;
          size_--;

          return true;
      }
      else if (pred->left != NULL)  // Case 4.3: Pred has a left child
      {
          cur->val = predecessor;
          prevPred->right = pred->left;

          pred = NULL;
          delete pred;
          size_--;

          return true;
      }
  }
  return false;
}