#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H
#include <iostream>
#include <cstdlib>
#include <stack>
#include <sstream>

// only using specified stds
using std::cout;
using std::string;
using std::stack;
using std::ostringstream;
struct TreeNode{
    char data;
    char key;
    TreeNode* left;
    TreeNode* right;
    // constructor
    TreeNode(char data, char key) : data(data), key(key), left(0), right(0) {}
    ~TreeNode() {   // tears down left and right subtrees
        // delete is safe on nullptr
        delete left;
        delete right;
    }
    // rule of 3
    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode &) = delete;
};

class arithmeticExpression{
  private:
    string infixExpression;
    TreeNode* root;

  public:
    // constructor -> initializes empty tree and sets infixExpression
    arithmeticExpression(const string &param) : infixExpression(param), root(nullptr) {}

    // destructor because uses node pointers
    // deleting root should deallocate all children
    ~arithmeticExpression() { delete root; }

    // rule of 3
    arithmeticExpression(const arithmeticExpression&) = delete;
    arithmeticExpression& operator=(const arithmeticExpression&) = delete;

    // converts infixExpression to equivalent postfix string -> then generates tree and assigns root
    void buildTree();

    // calls recursive infix helper
    void infix() const;

    // calls recursive prefix helper
    void prefix() const;

    // calls recursive postfix helper
    void postfix() const;

 private:
    // helper -> returns an int according to priority of given operator
    int priority(char) const;

    // helper -> returns postfix notation equivalent to given infix expression
    string infix_to_postfix() const;

    // helper -> outputs infix notation of tree by performing inorder traversal of tree
    void infix(TreeNode*) const;

    // helper -> outputs prefix notation of tree by performing preorder traversal of tree
    void prefix(TreeNode*) const;

    // helper -> outputs postfix notation of tree by performing postorder traversal of tree
    void postfix(TreeNode*) const;
};
#endif