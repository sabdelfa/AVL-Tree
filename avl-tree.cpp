#include "avl-tree.h";
#include <cmath>
#include <stack>
#include <iostream>

using namespace std;

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

// check height of the node
int AVLTree::depthBelow(Node *n)
{
    /* Compute the max depth of the three from the root node n
       Follows the convention that a single node has depth of 1
       If the root node is the leaf node, return 1
     */
    if(n->right == NULL && n->left == NULL) return 1;

    int count = 0;

    // Counting the height of the left subtree if it exists
    if (n->left != NULL)
    {
        count++;
        count = count + depthBelow(n->left);
    }
    else if(n->right != NULL)  // Counting the height of right subtree if left does not exist
    {
        count++;
        count = count + depthBelow(n->right);
    }

    return count;
}

bool AVLTree::singleLeftRotation(Node *parentNode, bool isLeftChild)
{
    /* Carries out a single left rotation on the subtree
     * Return true on success
     * Assume that no balance-checking needs to be carried out
     */

    /*                10
     *            7          15   <- parentNode
     *                  13       20
     *                               24
     */

    // Case 1: The right child has a right child
 /*   Node* rightChild = parentNode->right;

    if(depthBelow(parentNode->right) > depthBelow(parentNode->left))
    {
        if(rightChild->left == NULL && rightChild->right != NULL)
        {
            Node* temp = parentNode;
            rightChild = parentNode;
            rightChild->left = temp;
        }
    }*/
    if( isLeftChild ) return false;

    Node* s = parentNode->right;
    Node* b = s->left;

    s->left = parentNode;
    parentNode->right = b;

    depthBelow(parentNode);

    return true;

}

bool AVLTree::singleRightRotation(Node *parentNode, bool isLeftChild)
{
    /* Carries out a single right rotation on the subtree
     * Return true on success
     * Assume that no balance-checking needs to be carried out
     */
    if( !isLeftChild ) return false;

    Node *s = parentNode->left;
    Node *b = s->right;
    s->right = parentNode;
    parentNode->left = b;
    return true;
}

bool AVLTree::leftRightRotation(Node *parentNode, bool isLeftChild)
{
    /* Carries out a left-right rotation on the subtree
     * Returns true on success
     * Assume that no balance-checking needs to be carried out
     */
    bool leftChild = isLeftChild;
    Node* s = parentNode->left;
   // parentNode->left = singleLeftRotation(s, leftChild);

}

bool AVLTree::rightLeftRotation(Node *parentNode, bool isLeftChild)
{
    /* Carries out a right-left rotation on the subtree
     * Returns true on success
     * assume that no balance-checking needs to be carried out
     */
}

// stack of path to inserted/deleted Node
std::stack<BinarySearchTree::Node*> *AVLTree::pathToNodeStack(DataType val)
{
    /* Computes a stack that contains all nodes that are traversed in a tree
     * to reach the node with a given value
     * the last inserted element of the returned stack should be the parent
     * of the node that you are trying to reach
     * Assume that this function will always be called on a valid val
     */
}

// generic function to updated tree balance of insertion/deletion
bool AVLTree::updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val)
{
    /* Generic function that is called by every insert and delete operation to rebalance tree
     * Determines which of the rotation functions to call.
     * The parameter is the output of the pathToNodeStack function
     * val is the value of the node that was either inserted or deleted
     * return true if successful
     */
}

bool AVLTree::insert(DataType val)
{
    /* Insert a node with the value = val into the avl tree
     * Return the output of updateNodeBalance
     */


}



bool AVLTree::remove(DataType val)
{
    /* Removes a node with a value = val into the avl tree.
     * Return the output of updateNodeBalance
     */
    // Base case 1: The value to remove does not exist
    Node* root_;

    if( !exists(val) ) return false;

    // Case 1: The tree only has a root
    if( root_->right == NULL && root_->left == NULL )
    {
        root_ = NULL;
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
                return true;
            }
        }

        // Case 3.1: There is only 1 child in the right subtree
        if (cur->right != NULL)
        {
            cur->val = cur->right->val;
            cur->right = NULL;

            delete cur->right;

            return true;
        }
            // Case 3.2: 1 child in the left subtree
        else if (cur->left != NULL)
        {

            cur->val = cur->left->val;
            cur->left = NULL;

            delete cur->left;

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
            return true;
        }

        // Case 4.2: Pred has no child nodes
        if (pred->left == NULL)
        {
            cur->val = predecessor;  // Copying the value of the predecessor into our current node
            prevPred->right = NULL;  // Removing the link between the parent of the predecessor and the predecessor itself

            pred = NULL;
            delete pred;

            return true;
        }
        else if (pred->left != NULL)  // Case 4.3: Pred has a left child
        {
            cur->val = predecessor;
            prevPred->right = pred->left;

            pred = NULL;
            delete pred;

            return true;
        }
    }
    return false;
}
