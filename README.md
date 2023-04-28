# Part 1: Binary Search Tree Implementation

# Purpose of this assignment

In this assignment, you will practice your knowledge about tree by implementing a data type
called binary search tree. The header file binary-search-tree.h, which is explained
below, provides the structure of the BinarySearchTree class with declarations of member
functions. Do not modify the signatures of any of these functions. You need to implement
all of the public member functions listed in binary-search-tree.cpp. Note that the tree
does not have to be balanced for this part of the assignment.

# Description
The details of the header file binary-search-tree.h are as follows:
DataType defines the kind of data that the tree will contain. Being public, it can be accessed
directly as BinarySearchTree::DataType.

# Member variables:

Node: This is a structure declaration. Node contains the following member function and
variables:
Node(DataType newval): Sets the left and right children to NULL, and initializes val.
val: Value of the node.
left: Pointer to the left node.
right: Pointer to the right node.
avlBalance: As introduced in the class, the balance value of each node refers to the absolute value of difference in heights between the left and right subtrees of the node. You may
implement updateNodeBalance function to update avlBalance. It is not necessary for Part
1 about binary search tree, but it may help you when you implement AVL tree in Part 2.
Note that there are other methods to implement AVL tree properly without the need to use
this variable, so it is optional.
root : Pointer to the root node of the tree.
size : Number of nodes in the tree.
Member functions:
BinarySearchTree(): Constructor to initialize an empty tree with no node.
~BinarySearchTree(): Deallocates the memory space allocated for the binary search tree
nodes, if any.
int size() const: Returns the number of nodes in the tree.
DataType max() const: Returns the maximum value of a node in the tree among all the
nodes. You can assume that this function will never be called on an empty tree.
DataType min() const: Returns the minimum value of a node in the tree among all the
nodes. You can assume that this function will never be called on an empty tree.
unsigned int depth() const: Returns the maximum depth of all nodes in the tree. Since
the root node has a depth of 0, a tree with only the root node will have 0 as the return value
here. You can assume that this function will never be called on an empty tree.
void print() const: You can print the tree in whatever order you prefer. However, methods such as in-order or level-order traversal could be the most useful for debugging. Note:
2
this function will not be used for grading purposes, so the printing format does not matter.
bool exists(DataType val) const: Returns true if a node with the value val exists in
the tree; otherwise, it returns false.
Node* getRootNode(): Returns a pointer to the root node.
Node** getRootNodeAddress(): Returns the address of the root node pointer.
bool insert(DataType val): Inserts the value val into the tree as a new node. Returns
false if val already exists in the tree, and true otherwise.
bool remove(DataType val): Removes the node with the value val from the tree. Returns true if successful, and false otherwise. Note: when the to-be-removed node has
two child nodes, replace the value with the predecessor (rather than successor). This implementation will be different from the demo code used in the lecture, which used the successor.
void updateNodeBalance(Node* n): Optional. This function is not necessary for Part 1
about binary search tree, but it may help you when you implement AVL tree in Part 2. Given
Node* n that is a pointer pointing to a node in the tree, this function calculates the balance
value of Node* n and repeat this for all the ancestors of Node* n. Note that there are other
methods to implement AVL tree properly without the need to implement this function, so
it is optional.


# Part 2: AVL Tree Implementation

# Purpose of this assignment

In this project, you practice your knowledge about tree by implementing a data
type called AVL tree. The header file avl-tree.h, which is explained below, provides the
structure of the AVLTree class with declarations of member functions.

# Description
You need to implement the new AVL versions of insert and remove operations that keep
the tree balanced. Place your code into avl-tree.cpp. The pseudocode for them has been
introduced in the lectures. When defining the AVL version of them, you may want to call
the Binary Search Tree version of insert and remove inherited from your Binary Search
Tree class, using BinarySearchTree::insert or BinarySearchTree::remove, to insert or
remove the node from the tree, respectively. After that, you need to ensure that the tree is
kept balanced by applying the appropriate AVL tree rotations.

Do not modify the signatures of the insert and remove functions to ensure that the test
cases pass. The AVL tree should be kept balanced after calling just insert or remove, so any
re-balancing operations should happen within these functions rather than outside of them.

You may create additional functions and/or attributes in the .h and .cpp files to help complete the tasks, if needed.

# Brief Notes:
Assume that all rotation functions do not need to check the balance of the final tree.
Recall from lectures that an inbalanced node is a node whose subtrees are not balanced. i.e.
a node for which (HrHl) is greater than 1, where Hr and Hl represent the depths of the left
and right subtrees for this given node.

For all rotation functions:

The parentNode parameter is the parent of the node that is imbalanced. In the case that
the root of the tree is unbalanced, this node is NULL (since the root does not have a parent).
The isLeftChild parameter is true when the inbalanced node is the left child of the parent
node; else this value is false. This function returns true for a successful left rotation.

# Member functions:
depthBelow(Node *n): Computes the maximum depth of the tree from the root node n.
This function follows the convention that a single node has depth equals to 1. Thus, if the
root node is a leaf node, the expected output would be 1.
singleLeftRotation(Node *parentNode, bool isLeftChild): Carries out a single left
rotation on the subtree. Returns true on success. Assume that no balance-checking needs
to be carried out.
singleRightRotation(Node *parentNode, bool isLeftChild): Carries out a single right
rotation on the subtree. Returns true on success. Assume that no balance-checking needs
to be carried out.
leftRightRotation(Node *parentNode, bool isLeftChild): Carries out a left-right rotation on the subtree. Returns true on success. Assume that no balance-checking needs to
be carried out.
2
rightLeftRotation(Node *parentNode, bool isLeftChild): Carries out a right-left rotation on the subtree. Returns true on success. Assume that no balance-checking needs to
be carried out.
pathToNodeStack(DataType val): Computes a stack that contains all nodes that are traversed in a tree, in order to reach the node with the given value. The last inserted element
of the returned stack should be the parent of the node that you are trying to reach. You can
assume that this function will always be called on a valid val.
updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val):
A generic function that is called by every insert and delete operation to rebalance the tree.
This function determines which of the rotation functions to call. The pathToNode parameter
is the output of the pathToNodeStack function and the val is the value of the node that was
either inserted or deleted. This function returns true if the balancing was successful.
insert(DataType val): Inserts a node with value equals to val into the avl tree. Returns
the output of updateNodeBalance.
remove(DataType val): Removes a node with value equals to val into the avl tree. Returns
the output of updateNodeBalance.
