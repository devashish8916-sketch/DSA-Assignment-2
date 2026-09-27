# Expression Tree and Postfix Evaluation

## Problem Statement

Consider the postfix expression:

**8 3 2 * + 6 2 / -**

a) Implement an Expression Tree using the postfix expression. Display the tree and its traversal results.

b) Evaluate the expression using:

* Stack-based postfix evaluation
* Expression Tree evaluation

Prepare a trace showing the important intermediate operations.

c) Compare the two approaches based on:

* Number of operations
* Data structure used
* Time complexity
* Space requirements

Also analyse why the Expression Tree provides additional structural information compared with direct postfix evaluation.

---

# 1. Algorithm

## A. Algorithm to Construct Expression Tree

1. Read the postfix expression from left to right.
2. If the symbol is an operand, create a new tree node and push it onto the stack.
3. If the symbol is an operator:

   * Pop the right operand from the stack.
   * Pop the left operand from the stack.
   * Create a new node containing the operator.
   * Make the left operand the left child.
   * Make the right operand the right child.
   * Push the newly created node onto the stack.
4. After scanning the complete postfix expression, the remaining node in the stack is the root of the Expression Tree.

## B. Algorithm for Inorder Traversal

1. Traverse the left subtree.
2. Visit the root.
3. Traverse the right subtree.

## C. Algorithm for Preorder Traversal

1. Visit the root.
2. Traverse the left subtree.
3. Traverse the right subtree.

## D. Algorithm for Postorder Traversal

1. Traverse the left subtree.
2. Traverse the right subtree.
3. Visit the root.

## E. Algorithm for Expression Tree Evaluation

1. If the node is an operand, return its value.
2. Recursively evaluate the left subtree.
3. Recursively evaluate the right subtree.
4. Apply the operator at the current node.
5. Return the calculated value.

---

# 2. C Program

```c
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
```

---

# 3. Output

```text
Postfix Expression: 8 3 2 * + 6 2 / -

Expression Tree:
             -
           /   \
          +     /
         / \   / \
        8   * 6   2
           / \
          3   2

Inorder Traversal   : 8 + 3 * 2 - 6 / 2
Preorder Traversal  : - + 8 * 3 2 / 6 2
Postorder Traversal : 8 3 2 * + 6 2 / -

Stack-Based Postfix Evaluation = 11
Expression Tree Evaluation      = 11
```

---

# 4. Expression Tree Construction Trace

| Symbol | Action                           | Stack   |
| ------ | -------------------------------- | ------- |
| 8      | Create node and push             | 8       |
| 3      | Create node and push             | 8, 3    |
| 2      | Create node and push             | 8, 3, 2 |
| *      | Pop 2 and 3, create `*` node     | 8, *    |
| +      | Pop `*` and 8, create `+` node   | +       |
| 6      | Create node and push             | +, 6    |
| 2      | Create node and push             | +, 6, 2 |
| /      | Pop 2 and 6, create `/` node     | +, /    |
| -      | Pop `/` and `+`, create `-` node | -       |

The final node `-` becomes the root of the Expression Tree.

---

# 5. Stack-Based Postfix Evaluation Trace

| Step | Symbol | Operation   | Stack    |
| ---- | ------ | ----------- | -------- |
| 1    | 8      | Push 8      | 8        |
| 2    | 3      | Push 3      | 8, 3     |
| 3    | 2      | Push 2      | 8, 3, 2  |
| 4    | *      | 3 × 2 = 6   | 8, 6     |
| 5    | +      | 8 + 6 = 14  | 14       |
| 6    | 6      | Push 6      | 14, 6    |
| 7    | 2      | Push 2      | 14, 6, 2 |
| 8    | /      | 6 ÷ 2 = 3   | 14, 3    |
| 9    | -      | 14 − 3 = 11 | 11       |

Therefore:

**Stack-Based Postfix Evaluation = 11**

---

# 6. Expression Tree Evaluation Trace

The Expression Tree is evaluated from the leaf nodes towards the root.

### Step 1

The `*` node is evaluated:

```text
3 × 2 = 6
```

### Step 2

The `+` node is evaluated:

```text
8 + 6 = 14
```

### Step 3

The `/` node is evaluated:

```text
6 ÷ 2 = 3
```

### Step 4

The root `-` node is evaluated:

```text
14 - 3 = 11
```

Therefore:

**Expression Tree Evaluation = 11**

---

# 7. Comparison of Both Approaches

| Criteria                     | Stack-Based Postfix Evaluation | Expression Tree Evaluation                         |
| ---------------------------- | ------------------------------ | -------------------------------------------------- |
| Number of operations         | Each token is processed once   | Tree construction and tree evaluation are required |
| Data structure               | Stack                          | Binary Expression Tree                             |
| Time complexity              | O(n)                           | O(n)                                               |
| Space requirement            | O(n) worst case                | O(n)                                               |
| Traversal                    | Not applicable                 | Inorder, Preorder, Postorder                       |
| Structure of expression      | Not explicitly maintained      | Completely represented                             |
| Subexpression identification | Difficult                      | Easy                                               |
| Expression modification      | Difficult                      | Easy                                               |
| Expression conversion        | Limited                        | Easy using traversals                              |

Here, **n** represents the number of tokens in the expression.

---

# 8. Analysis of Structural Information

The Expression Tree provides additional structural information because every operator and operand is represented as a node in a hierarchical structure.

For the given expression:

```text
             -
           /   \
          +     /
         / \   / \
        8   * 6   2
           / \
          3   2
```

The tree clearly shows that:

```text
3 * 2
```

is a subexpression.

The result of this subexpression is then used in:

```text
8 + (3 * 2)
```

Similarly,

```text
6 / 2
```

forms another subexpression.

Finally, the complete expression is:

```text
(8 + (3 * 2)) - (6 / 2)
```

The tree therefore preserves the **parent-child relationship between operators and operands**.

It also allows the expression to be represented in different forms:

```text
Infix:
8 + 3 * 2 - 6 / 2

Prefix:
- + 8 * 3 2 / 6 2

Postfix:
8 3 2 * + 6 2 / -
```

In contrast, direct postfix evaluation mainly uses the stack to calculate the final value. Once the calculation is complete, the intermediate structural relationships are not explicitly maintained.

---

# 9. Conclusion

The given postfix expression **8 3 2 * + 6 2 / -** was successfully converted into an Expression Tree.

The three traversals obtained are:

* **Inorder:** `8 + 3 * 2 - 6 / 2`
* **Preorder:** `- + 8 * 3 2 / 6 2`
* **Postorder:** `8 3 2 * + 6 2 / -`

Both evaluation techniques produce the same result:

**Final Result = 11**

Stack-based postfix evaluation is simple and efficient when only the numerical result is required. Expression Tree evaluation requires the construction of a tree, but it provides complete structural information about the expression and supports traversal, conversion, subexpression identification, modification, and further expression processing.
