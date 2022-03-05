#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
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
}

DataType BinarySearchTree::max() const
{
}

DataType BinarySearchTree::min() const
{
}

unsigned int BinarySearchTree::depth() const
{
}

void BinarySearchTree::print() const
{
}

bool BinarySearchTree::exists(DataType val) const
{
}

Node* BinarySearchTree::getRootNode()
{
}

Node** BinarySearchTree::getRootNodeAddress()
{
}

bool BinarySearchTree::insert(DataType val)
{
}

Node* findPredecessor(Node* ptr)
{
}

bool BinarySearchTree::remove(DataType val)
{
}