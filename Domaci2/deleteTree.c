#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void deleteTree(TreeNode* root)
{

    if (root == NULL)
        return;

    StackElement* s1 = NULL, * s2 = NULL;

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
        free(node);
    }
    deleteStack(s1);
    deleteStack(s2);
}