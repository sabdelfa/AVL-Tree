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
}

bool AVLTree::singleLeftRotation(Node *parentNode, bool isLeftChild)
{
}

bool AVLTree::singleRightRotation(Node *parentNode, bool isLeftChild)
{
}

bool AVLTree::leftRightRotation(Node *parentNode, bool isLeftChild)
{
}

bool AVLTree::rightLeftRotation(Node *parentNode, bool isLeftChild)
{
}

// stack of path to inserted/deleted Node
std::stack<BinarySearchTree::Node*> *AVLTree::pathToNodeStack(DataType val)
{
}

// generic function to updated tree balance of insertion/deletion
bool AVLTree::updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val)
{
}

bool AVLTree::insert(DataType val)
{
}

bool AVLTree::remove(DataType val)
{
}
