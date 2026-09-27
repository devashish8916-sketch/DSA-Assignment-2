#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Structure for Expression Tree Node
struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
};

// Stack for tree nodes
struct Node *stack[MAX];
int top = -1;

// Push a node into stack
void push(struct Node *node)
{
    stack[++top] = node;
}

// Pop a node from stack
struct Node *pop()
{
    return stack[top--];
}

// Create a new tree node
struct Node *createNode(char data)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Check whether character is an operator
int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Construct Expression Tree from postfix expression
struct Node *constructTree(char postfix[])
{
    int i;
    struct Node *node;
    struct Node *left;
    struct Node *right;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (postfix[i] == ' ')
            continue;

        node = createNode(postfix[i]);

        if (!isOperator(postfix[i]))
        {
            push(node);
        }
        else
        {
            right = pop();
            left = pop();

            node->left = left;
            node->right = right;

            push(node);
        }
    }

    return pop();
}

// Inorder traversal
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal
void postorder(struct Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

// Evaluate Expression Tree
int evaluateTree(struct Node *root)
{
    int leftValue, rightValue;

    if (root == NULL)
        return 0;

    if (!isOperator(root->data))
        return root->data - '0';

    leftValue = evaluateTree(root->left);
    rightValue = evaluateTree(root->right);

    switch (root->data)
    {
        case '+':
            return leftValue + rightValue;

        case '-':
            return leftValue - rightValue;

        case '*':
            return leftValue * rightValue;

        case '/':
            return leftValue / rightValue;
    }

    return 0;
}

// Stack-based postfix evaluation
int evaluatePostfix(char postfix[])
{
    int valueStack[MAX];
    int valueTop = -1;
    int i;
    int a, b;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (postfix[i] == ' ')
            continue;

        if (isdigit(postfix[i]))
        {
            valueStack[++valueTop] = postfix[i] - '0';
        }
        else
        {
            b = valueStack[valueTop--];
            a = valueStack[valueTop--];

            switch (postfix[i])
            {
                case '+':
                    valueStack[++valueTop] = a + b;
                    break;

                case '-':
                    valueStack[++valueTop] = a - b;
                    break;

                case '*':
                    valueStack[++valueTop] = a * b;
                    break;

                case '/':
                    valueStack[++valueTop] = a / b;
                    break;
            }
        }
    }

    return valueStack[valueTop];
}

int main()
{
    char postfix[] = "8 3 2 * + 6 2 / -";

    struct Node *root;

    root = constructTree(postfix);

    printf("Postfix Expression: %s\n\n", postfix);

    printf("Expression Tree:\n");
    printf("             -\n");
    printf("           /   \\\n");
    printf("          +     /\n");
    printf("         / \\   / \\\n");
    printf("        8   * 6   2\n");
    printf("           / \\\n");
    printf("          3   2\n\n");

    printf("Inorder Traversal   : ");
    inorder(root);

    printf("\nPreorder Traversal  : ");
    preorder(root);

    printf("\nPostorder Traversal : ");
    postorder(root);

    printf("\n\nStack-Based Postfix Evaluation = %d",
           evaluatePostfix(postfix));

    printf("\nExpression Tree Evaluation      = %d",
           evaluateTree(root));

    printf("\n");

    return 0;
}
