#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
int binary(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/' || op == 'l' || op == '^')
        return 1;
    return 0;
}
TreeNode* copyTree(TreeNode* root)
{
    if (root == NULL)
        return;

    StackElement* s1 = NULL, * s2 = NULL, *copyStack = NULL;

    // koren na s1 
    s1 = push(s1, root);
    TreeNode* node;

    // dok s1 nije prazan 
    while (!isStackEmpty(s1)) {
        // pop sa s1 i push na s2 
        node = top(s1);
        s1 = pop(s1);
        s2 = push(s2, node);

        // push left i right sinove
        // ili izbacenog iz s1
        if (node->left)
            s1 = push(s1, node->left);
        if (node->right)
            s1 = push(s1, node->right);
    }

    // printovanje elemenata drugog steka (tj. postfiks) 
    while (!isStackEmpty(s2)) {
        node = top(s2);
        s2 = pop(s2);
        if ((node->data >= 'A' && node->data <= 'Z') || node->data =='0' || node->data=='1') {
            TreeNode* newNode = formNode(node->data);
            copyStack = push(copyStack, newNode);
        }
        else
        {
            TreeNode* newNode = formNode(node->data);
            if (binary(node->data)) {
                TreeNode* right, * left;
                right = top(copyStack);
                copyStack = pop(copyStack);
                left = top(copyStack);
                copyStack = pop(copyStack);
                newNode->left = left;
                newNode->right = right;
                copyStack = push(copyStack, newNode);
            }
            else
            {
                TreeNode* left;
                left = top(copyStack);
                copyStack = pop(copyStack);
                newNode->left = left;
                copyStack = push(copyStack, newNode);
            }
        }
    }
    deleteStack(s1);
    deleteStack(s2);
    TreeNode* copy = top(copyStack);
    
    deleteStack(copyStack);
    return copy;
}
