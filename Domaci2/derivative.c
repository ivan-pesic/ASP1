#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
TreeNode* natLog(TreeNode* node)
{
    TreeNode* log = formNode('l'), * exp = formNode('e');
    exp->left = formNode('1');
    log->left = exp;
    log->right = copyTree(node);

    return log;
}

TreeNode* derivate(TreeNode* root)
{
    char c;
    getchar();
    printf("Uneti promenljivu po kojoj se diferencira: ");
    scanf("%c", &c);

    if (root == NULL)
        return;
    TreeNode* root2, *node1, *node2, *newnode;
    StackElement* s1 = NULL, * s2 = NULL, *derivateStack = NULL, *operatorStack = NULL;
    
    s1 = push(s1, root);
    TreeNode* node;
    while (!isStackEmpty(s1)) {
        node = top(s1);
        s1 = pop(s1);
        s2 = push(s2, node);
        if (node->left)
            s1 = push(s1, node->left);
        if (node->right)
            s1 = push(s1, node->right);
    }
     
    while (!isStackEmpty(s2)) {
        node = top(s2);
        s2 = pop(s2);
        if ((node->data >= 'A' && node->data <= 'Z') || node->data =='1' || node->data =='0') {
            char tmp;
            if (c == node->data)
                tmp = '1';
            else
                tmp = '0';

            derivateStack = push(derivateStack, formNode(tmp));
        }
        else
        {
            if (node->data == '+' || node->data == '-') 
            {
                node2 = top(derivateStack);
                derivateStack = pop(derivateStack);
                node1 = top(derivateStack);
                derivateStack = pop(derivateStack);

                if (node1->data != '0' || node2->data != '0') {
                    if (node1->data == '0')
                    {
                        if (node->data == '-') 
                        {
                            TreeNode* unmin = formNode('@');
                            unmin->left = node2;
                            derivateStack = push(derivateStack, unmin);
                        }
                        else
                             derivateStack = push(derivateStack, node2);
                    }
                    else if (node2->data == '0')
                    {
                        derivateStack = push(derivateStack, node1);
                    }
                    else
                    {
                        newnode = formNode(node->data);
                        newnode->left = node1;
                        newnode->right = node2;

                        derivateStack = push(derivateStack, newnode);

                    }
                    
                }
                else 
                {
                    derivateStack = push(derivateStack, node1);
                    deleteTree(node2);
                }
                    
            }
            else if (node->data == '*') {
                node2 = top(derivateStack);
                derivateStack = pop(derivateStack);
                node1 = top(derivateStack);
                derivateStack = pop(derivateStack);

                if (node1->data != '0' || node2->data != '0')
                {
                    if (node1->data == '0') {
                        deleteTree(node1);
                        TreeNode* first = copyTree(node->left), *mul = formNode('*');
                        mul->left = first;
                        mul->right = node2;

                        derivateStack = push(derivateStack, mul);
                    }
                    else if (node2->data == '0') {
                        deleteTree(node2);
                        TreeNode* second = copyTree(node->right), * mul = formNode('*');
                        mul->left = node1;
                        mul->right = second;

                        derivateStack = push(derivateStack, mul);
                    }
                    else {
                        TreeNode* first = copyTree(node->left), * second = copyTree(node->right), * mul1 = formNode('*'), * mul2 = formNode('*'), * plus = formNode('+');
                        mul1->left = node1;
                        mul1->right = second;

                        mul2->left = first;
                        mul2->right = node2;

                        plus->left = mul1;
                        plus->right = mul2;

                        derivateStack = push(derivateStack, plus);
                    }
                }
                else
                {
                    derivateStack = push(derivateStack, node1);
                    deleteTree(node2);
                }
            }
        
            else if (node->data == '/') {
                node2 = top(derivateStack);
                derivateStack = pop(derivateStack);
                node1 = top(derivateStack);
                derivateStack = pop(derivateStack);
                
                if (node1->data != '0' || node2->data != '0') {

                    if (node1->data == '0') {
                        deleteTree(node1);

                        TreeNode* cons = copyTree(node->left), * div = formNode('/'), * mul = formNode('*'), * unmin = formNode('@');

                        mul->left = copyTree(node->right);
                        mul->right = copyTree(node->right);
                        div->right = mul;
                        div->left = cons;

                        if (node2->data == '1') {
                            deleteTree(node2);
                            unmin->left = div;
                            derivateStack = push(derivateStack, unmin);
                        }
                        else
                        {
                            TreeNode* mul2 = formNode('*');
                            mul2->left = node2;
                            mul2->right = div;
                            unmin->left = mul2;
                            derivateStack = push(derivateStack, unmin);
                        }
                    }
                    else if (node2->data == '0') {
                        deleteTree(node2);

                        TreeNode* cons = copyTree(node->right), *div = formNode('/');

                        div->right = cons;
                        div->left = node1;

                        derivateStack = push(derivateStack, div);
                    }
                    else {
                        TreeNode* first = copyTree(node->left), * second = copyTree(node->right), * mul1 = formNode('*'), * mul2 = formNode('*'), * min = formNode('-'), * div = formNode('/');
                        
                        TreeNode* mul = formNode('*');
                        mul->left = copyTree(second);
                        mul->right = copyTree(second);

                        div->right = mul;

                        mul1->left = node1;
                        mul1->right = second;
                        
                        mul2->left = first;
                        mul2->right = node2;

                        min->left = mul1;
                        min->right = mul2;

                        div->left = min;

                        derivateStack = push(derivateStack, div);
                    }

                }
                else
                {
                    derivateStack = push(derivateStack, node1);
                    deleteTree(node2);
                }
            }

            else if (node->data == '@')
            {
                node1 = top(derivateStack);
                derivateStack = pop(derivateStack);

                if (node1->data == '0') 
                {
                    derivateStack = push(derivateStack, node1);
                }
                else
                {
                    TreeNode* unmin = formNode('@');
                    unmin->left = node1;
                    derivateStack = push(derivateStack, unmin);
                }
            }
            else if (node->data == 'a')
            {
                node1 = top(derivateStack);
                derivateStack = pop(derivateStack);

                if (node1->data == '0')
                {
                    derivateStack = push(derivateStack, node1);
                }
                else if (node1->data == '1')
                {
                    deleteTree(node1);
                    TreeNode* abs = formNode('a'), * div = formNode('/'), * node11 = copyTree(node->left), * node22 = copyTree(node->left);
                    abs->left = node11;
                    div->left = node22;
                    div->right = abs;
                    derivateStack = push(derivateStack, div);
                }
                else
                {
                    TreeNode* abs = formNode('a'), *mul2 = formNode('*'), * div = formNode('/'), * node11 = copyTree(node->left), * node22 = copyTree(node->left);
                    abs->left = node11;
                    div->right = abs;
                    div->left = node22;
                    mul2->left = div;
                    mul2->right = node1;
                    derivateStack = push(derivateStack, mul2);
                }
            }

            else if (node->data == '^')
            {
                node2 = top(derivateStack);
                derivateStack = pop(derivateStack);
                node1 = top(derivateStack);
                derivateStack = pop(derivateStack);

                if (node1->data != '0' || node2->data != '0') {
                    
                    if (node2->data == '0') 
                    {
                        TreeNode* mul = formNode('*'), * deg = formNode('^'), * min = formNode('-');

                        deg->left = copyTree(node->left);
                        min->left = copyTree(node->right);
                        min->right = formNode('1');
                        deg->right = min;
                        mul->left = copyTree(node->right);
                        mul->right = deg;

                        if (node1->data == '1')
                        {
                            derivateStack = push(derivateStack, mul);
                        }
                        else
                        {
                            TreeNode* mul2 = formNode('*');
                            mul2->left = mul;
                            mul2->right = node1;
                            derivateStack = push(derivateStack, mul2);
                        }
                    }
                    else
                    {
                        TreeNode* log = natLog(node->left), *mul = formNode('*');
                        mul->left = copyTree(node);
                        mul->right = log;
                        
                        if (node2->data == '1') 
                        {
                            deleteTree(node2);
                            derivateStack = push(derivateStack, mul);
                        }
                        else
                        {
                            TreeNode* mul2 = formNode('*');
                            mul2->left = mul;
                            mul2->right = node2;
                            derivateStack = push(derivateStack, mul2);
                        }
                        
                    }
                }
                else
                {
                    deleteTree(node2);
                    derivateStack = push(derivateStack, node1);
                }
            }

            else if (node->data == 'e')
            {
                 node1 = top(derivateStack);
                 derivateStack = pop(derivateStack);

                 if (node1->data == '0') {
                     derivateStack = push(derivateStack, node1);
                 }
                 else if (node1->data == '1') {
                     deleteTree(node1);
                     derivateStack = push(derivateStack, copyTree(node));
                 }
                 else
                 {
                     TreeNode* mul = formNode('*');
                     mul->left = copyTree(node);
                     mul->right = node1;

                     derivateStack = push(derivateStack, mul);
                 }
            }

            else if (node->data == 'l')
            {
                node2 = top(derivateStack);
                derivateStack = pop(derivateStack);
                node1 = top(derivateStack);
                derivateStack = pop(derivateStack);

                if (node1->data != '0' || node2->data != '0') 
                {
                    if (node1->data == '1' && node2->data == '1')
                    {
                        deleteTree(node1);
                        deleteTree(node2);
                        derivateStack = push(derivateStack, formNode('0'));
                    }

                    else if (node1->data == '0') 
                    {
                        TreeNode* mul = formNode('*'), * div = formNode('/'), * ln = natLog(node->left), *one = formNode('1');
                        div->left = one;
                        mul->left = copyTree(node->right);
                        mul->right = ln;
                        div->right = mul;
                        if (node2->data != '1') {
                            TreeNode* mul2 = formNode('*');
                            mul2->left = div;
                            mul2->right = node2;
                            derivateStack = push(derivateStack, mul2);
                        }
                        else
                        {
                            deleteTree(node2);
                            derivateStack = push(derivateStack, div);
                        }
                            
                    }
                    else
                    {
                        
                            TreeNode* unmin = formNode('@'), * mul1 = formNode('*'), * mul2 = formNode('*'), * div1 = formNode('/'), * div2 = formNode('/'), * one = formNode('1');
                            div1->left = natLog(node->right);

                            mul1->left = natLog(node->left);
                            mul1->right = natLog(node->left);

                            div1->right = mul1;
                            div2->left = one;
                            div2->right = copyTree(node->right);

                            mul2->left = div1;
                            mul2->right = div2;

                            if (node2->data != '1')
                            {
                                TreeNode* mul3 = formNode('*');
                                mul3->left = mul2;
                                mul3->right = node2;
                                unmin->left = mul3;
                                derivateStack = push(derivateStack, unmin);
                            }
                            else
                            {
                                deleteTree(node2);
                                derivateStack = push(derivateStack, mul2);
                            }
                        
                        
                    }
                }

                else 
                {
                    deleteTree(node1);
                    derivateStack = push(derivateStack, node2);
                }
            }
        }
    }

    deleteStack(s1);
    deleteStack(s2);
    TreeNode* newRoot = top(derivateStack);
    deleteStack(derivateStack);
    return newRoot;
}