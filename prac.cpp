// This is the same BST from the last lab, converted into an AVL tree.
#include <iostream>
using namespace std;

class Employee
{
public:
    string name;
    int id;

    void info()
    {
        cout << "Enter ID: ";
        cin >> id;
    }
};

class Node
{
public:
    Employee data;
    Node *left;
    Node *right;
    int height;

    Node(Employee x)
    {
        data = x;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void inorder(Node *root)
{
    if (root != NULL)
    {
        // Traverse left
        inorder(root->left);

        // Traverse root
        cout << root->data.id << " -> ";

        // Traverse right
        inorder(root->right);
    }
}

int height(Node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

void updateHeight(Node *root)
{
    if (root != NULL)
    {
        root->height = 1 + max(height(root->left), height(root->right));
    }
}

int balanceFactor(Node *root)
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

Node *min(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }

    return root;
}

Node *newnode(Employee e)
{
    Node *temp = new Node(e);
    return temp;
}

Node *rotateLeft(Node *a)
{
    Node *b = a->right;
    Node *temp = b->left;

    b->left = a;
    a->right = temp;

    updateHeight(a);
    updateHeight(b);

    return b;
}

Node *rotateRight(Node *a)
{
    Node* b = a->left;
    Node* temp=b->right;

    b->right = a;
    a->left = temp;

    updateHeight(a);
    updateHeight(b);

    return b;
}

Node *insert(Employee x, Node *root)
{
    if (root == nullptr)
    {
        return newnode(x);
    }

    if (x.id < root->data.id)
    {
        root->left = insert(x, root->left);
    }

    else if (x.id > root->data.id)
    {
        root->right = insert(x, root->right);
    }

    else
    {
        cout << "This ID already exists in the BST\n";
        return root;
    }

    updateHeight(root);

    int balance = balanceFactor(root);

    if (balance < -1)
    {
        // Right Right case
        if (root->right->data.id < x.id)
        {
            return rotateLeft(root);
        }
        // Right Left Case
        else
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    else if (balance > 1)
    {
        // Left Left case
        if (root->left->data.id > x.id)
        {
            return rotateRight(root);
        }
        // Left Right Case
        else
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    return root;
}

Node *del(int id, Node *root)
{

    if (root == NULL)
    {
        cout << "Tree is empty\n";
        return NULL;
    }

    if (id < root->data.id)
    {
        root->left = del(id, root->left);
    }

    else if (id > root->data.id)
    {
        root->right = del(id, root->right);
    }

    else
    {
        if (root->left == NULL)
        {
            Node *temp = root;
            root = root->right;
            delete temp;
            return root;
        }
        else if (root->right == NULL)
        {
            Node *temp = root;
            root = root->left;
            delete temp;
            return root;
        }

        root->data = min(root->right)->data;
        root->right = del(root->data.id, root->right);
    }

    return root;
}

int main()
{
    Employee e1;
    Node* root = NULL;

    cout<<"\n\t**Enter Values 1 2 3 4 5 6 7 \n\n";
    /*
        AVL tree for these Values will be 
                             4
                           /   \
                          2     6
                        /  \   / \
                       1    3 5    7
    */
    e1.info();
    root = insert(e1,root);

    e1.info();
    root = insert(e1,root);

    e1.info();
    root = insert(e1,root);

    e1.info();
    root = insert(e1,root);

    e1.info();
    root = insert(e1,root);

    e1.info();
    root = insert(e1,root);

    e1.info();
    root = insert(e1,root);

    cout<< "\n\nID: "<< root->data.id;
    cout<< "\nID: "<< root->left->data.id;
    cout<< "\nID: "<< root->right->data.id;

    cout<<"\n\nInorder: ";
    inorder(root);

    del(7,root);
    del(5,root);
    del(6,root);

    cout<<"\n\nInorder after deleting root node: ";
    inorder(root);

}
// This is the same BST from the last lab, converted into an AVL tree.