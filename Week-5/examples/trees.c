typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node

void print_tree(node *root);
void free_tree(node *root);

int main(void)
{
    // Tree of size 0
    node *tree = NULL;
  
    // Add number to list
    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free_tree(tree);
        return 1;
    }

    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    // Print tree
    print_tree(tree);

    // Free tree
    free_tree(tree);
    return 0;
}

void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

bool search(node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number);
    }
    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    else if (number == tree->number)
    {
        return true;
    }
}
