#include "arithmeticExpression.h"

// helper -> returns an int according to priority of given operator
int arithmeticExpression::priority(char op) const {
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

// helper -> returns postfix notation equivalent to given infix expression
string arithmeticExpression::infix_to_postfix() const {
    stack<char> charStack;
    ostringstream oss;
    char curr;
    for (unsigned i = 0; i < infixExpression.size(); ++i) { // iterate through string
        curr = infixExpression.at(i);
        if (curr == ' ') {
            continue; // to next iteration
        }
        // if curr is an operator
        if (curr == '+' || curr == '-' || curr == '*' || curr == '/' || curr == '(' || curr == ')') {
            if (curr == '(') {
                charStack.push(curr);
            }
            else if (curr == ')') {
                // takes expression in parenthesees from stack and adds to oss
                while (charStack.top() != '(') {
                    oss << charStack.top();
                    charStack.pop();
                }
                charStack.pop();
            }
            else {
                // iterate through rest of stack
                while (!charStack.empty() && priority(curr) <= priority(charStack.top())){
                    // no added elements in current part of expression yet
                    if (charStack.top() == '(') {
                        break;
                    }
                    oss << charStack.top();
                    charStack.pop();
                }
                charStack.push(curr);
            }
        }
        else { // curr is an operand
            oss << curr;
        }
    }
    while (!charStack.empty()) { // move rest of stack to oss
        oss << charStack.top();
        charStack.pop();
    }
    return oss.str();
}

// converts infixExpression to postfix string -> then generates tree and assigns root
void arithmeticExpression::buildTree() {
    if (infixExpression == "") return;
    string postStr = infix_to_postfix();
    stack<TreeNode*> treeStack;
    char curr;
    TreeNode* currNode = nullptr;
    TreeNode* currLeft = nullptr;
    TreeNode* currRight = nullptr;
    for (unsigned i = 0; i < postStr.size(); ++i) { // iterate through string
        curr = postStr.at(i);
        currNode = new TreeNode(curr, i);
        if (priority(curr) > 0) { // if curr is an operator
            // would normally throw error -> wrong format
            if (treeStack.empty()) return;
            currRight = treeStack.top();
            treeStack.pop();
            currLeft = treeStack.top();
            treeStack.pop();
            currNode->left = currLeft;
            currNode->right = currRight;
        }
        treeStack.push(currNode);
    }
    root = currNode; // set root to last char (generally operator)
}

// calls recursive infix helper
void arithmeticExpression::infix() const {
    infix(root); // no newline
}

// calls recursive prefix helper
void arithmeticExpression::prefix() const {
    prefix(root); // no newline
}

// calls recursive postfix helper
void arithmeticExpression::postfix() const {
    postfix(root); // no newline
}

// helper -> outputs infix notation of tree by performing inorder traversal of tree
void arithmeticExpression::infix(TreeNode* tree) const {
    // do left, print data, do right
    if (tree == nullptr) return;
    if (tree->left != nullptr) cout << '('; // only if left exists
    infix(tree->left);
    cout << tree->data;
    infix(tree->right);
    if (tree->right != nullptr) cout << ')'; // only if right exists
}

// helper -> outputs prefix notation of tree by performing preorder traversal of tree
void arithmeticExpression::prefix(TreeNode* tree) const {
    // print data, do left, do right
    if (tree == nullptr) return;
    cout << tree->data;
    prefix(tree->left);
    prefix(tree->right);
}

// helper -> outputs postfix notation of tree by performing postorder traversal of tree
void arithmeticExpression::postfix(TreeNode *tree) const {
    // do left, do right, print data
    if (tree == nullptr) return;
    postfix(tree->left);
    postfix(tree->right);
    cout << tree->data;
}