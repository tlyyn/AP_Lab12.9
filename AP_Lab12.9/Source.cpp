#include <iostream>
#include <windows.h>

using namespace std;

typedef int Info;

struct Node
{
    Info info;
    Node* left;
    Node* right;
};

Node* CreateTree(int nodeCount)
{
    if (nodeCount == 0)
        return NULL;
    else
    {
        Node* newNode = new Node;
        cout << "Enter node value: ";
        cin >> newNode->info;
        int leftCount = nodeCount / 2;
        int rightCount = nodeCount - leftCount - 1;
        newNode->left = CreateTree(leftCount);
        newNode->right = CreateTree(rightCount);
        return newNode;
    }
}

void PrintTree(Node* root, int level)
{
    if (root != NULL)
    {
        PrintTree(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << " ";
        cout << root->info << endl;
        PrintTree(root->left, level + 1);
    }
}

Node* BinarySearchInsert(Node*& root, Info value, bool& found)
{
    if (root == NULL)
    {
        root = new Node;
        root->info = value;
        root->left = NULL;
        root->right = NULL;
        found = false;
        return root;
    }
    else if (value == root->info)
    {
        found = true;
        return root;
    }
    else if (value < root->info)
        return BinarySearchInsert(root->left, value, found);
    else
        return BinarySearchInsert(root->right, value, found);
}

int Count(Node* root)
{
    if (root == NULL)
        return 0;
    else
        return 1 + Count(root->left) + Count(root->right);
}

void RotateRight(Node*& root)
{
    if (root == NULL || root->left == NULL)
        return;

    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    root = newRoot;
}

void RotateLeft(Node*& root)
{
    if (root == NULL || root->right == NULL)
        return;

    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    root = newRoot;
}

void BalanceCount(Node*& root)
{
    if (root == NULL)
        return;

    while (Count(root->left) > Count(root->right) + 1)
    {
        RotateRight(root);
    }

    while (Count(root->left) + 1 < Count(root->right))
    {
        RotateLeft(root);
    }

    BalanceCount(root->left);
    BalanceCount(root->right);
}
Node* FindMax(Node* root)
{
    if (root->right != NULL)
        return FindMax(root->right);
    else
        return root;
}
void RightRotation(Node*& root)
{
    Node* tmp1 = root->left;
    Node* tmp2 = tmp1->right;
    tmp1->right = root;
    root->left = tmp2;
    root = tmp1;
}
void LeftRotation(Node*& root)
{
    Node* tmp1 = root->right;
    Node* tmp2 = tmp1->left;
    tmp1->left = root;
    root->right = tmp2;
    root = tmp1;
}
int Height(Node* root)
{
    if (root == NULL)
        return 0;
    int hL = Height(root->left);
    int hR = Height(root->right);
    return (hL > hR ? hL : hR) + 1;
}
int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
}
void BalanceHeight(Node*& root)
{
    if (root != NULL)
    {
        while (BFactor(root) >= 2)
        {
            if (BFactor(root->right) < 0)
                RightRotation(root->right);
            LeftRotation(root);
        }
        while (BFactor(root) <= -2)
        {
            if (BFactor(root->left) > 0)
                LeftRotation(root->left);
            RightRotation(root);
        }
        BalanceHeight(root->left);
        BalanceHeight(root->right);
    }
}
Node* BinarySearchDelete(Node* root, Info value)
{
    if (NULL == root) return NULL;
    if (root->info == value)
    {
        if (NULL == root->left && NULL == root->right)
        {
            delete root;
            return NULL;
        }
        if (NULL == root->right && root->left != NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        if (NULL == root->left && root->right != NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (root->left != NULL && root->right != NULL)
        {
            Node* temp = root->right;
            Node* temp2 = root->left;
            delete root;
            return temp;
        }
        root->info = FindMax(root->left)->info;
        root->left = BinarySearchDelete(root->left, root->info);
        return root;
    }
    if (value < root->info)
    {
        root->left = BinarySearchDelete(root->left, value);
        return root;
    }
    if (value > root->info)
    {
        root->right = BinarySearchDelete(root->right, value);
        return root;
    }
    return root;
}
int countNodesWithBothChildren(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    int count = 0;
    if (node->left != nullptr && node->right != nullptr) {
        count = 1;
    }

    count += countNodesWithBothChildren(node->left) + countNodesWithBothChildren(node->right);

    return count;
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Node* root = NULL;
    int choice, nodeCount, value;
    bool found;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Create a binary tree with the specified number of elements" << endl;
        cout << "2. Display binary tree" << endl;
        cout << "3. Create a binary search tree with the specified number of items" << endl;
        cout << "4. Add new item to binary search tree" << endl;
        cout << "5. Balance binary search tree" << endl;
        cout << "6. Remove item from binary/search binary tree (no child nodes)" << endl;
        cout << "7. Remove element from binary/search binary tree (with one child node)" << endl;
        cout << "8. Remove element from binary tree/binary search tree (with two child nodes)" << endl;
        cout << "9. Delete item from binary/search binary tree (delete branch)" << endl;
        cout << "10. Perform additional task" << endl;
        cout << "0. Exit the program" << endl;
        cout << "Choose an action: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the number of items: ";
            cin >> nodeCount;
            root = CreateTree(nodeCount);
            cout << "The binary tree was created." << endl;
            break;
        case 2:
            if (root == nullptr) {
                cout << "The binary tree is empty." << endl;
            }
            else {
                cout << "Binary tree:" << endl;
                PrintTree(root, 0);
                cout << endl;
            }
            break;
        case 3:
            cout << "Enter the number of items: ";
            cin >> nodeCount;
            root = NULL;
            for (int i = 0; i < nodeCount; i++) {
                cout << "Enter an item value " << i + 1 << ": ";
                cin >> value;
                BinarySearchInsert(root, value, found);
                if (found)
                    cout << "Element " << value << " already exists in the binary search tree." << endl;
                else
                    cout << "Element" << value << " was successfully added to the binary search tree." << endl;
            }
            break;
        case 4:
            cout << "Enter element value: ";
            cin >> value;
            BinarySearchInsert(root, value, found);
            if (found)
                cout << "The item already exists in the binary search tree." << endl;
            else
                cout << "The item was successfully added to the binary search tree." << endl;
            break;
        case 5:
            BalanceCount(root);
            cout << "The binary search tree was balanced." << endl;
            break;
        case 6:
            cout << "Enter the value of the item you want to delete: ";
            cin >> value;
            root = BinarySearchDelete(root, value);
            cout << "The item was successfully removed from the binary tree." << endl;
            break;
        case 7:
            cout << "Enter the value of the item you want to delete: ";
            cin >> value;
            root = BinarySearchDelete(root, value);
            cout << "The item was successfully removed from the binary tree." << endl;
            break;
        case 8:
            cout << "Enter the value of the item you want to delete: ";
            cin >> value;
            root = BinarySearchDelete(root, value);
            cout << "The item was successfully removed from the binary tree." << endl;
            break;
        case 9:
            cout << "Enter the value of the item you want to delete: ";
            cin >> value;
            root = BinarySearchDelete(root, value);
            cout << "The item was successfully removed from the binary tree." << endl;
            break;
        case 10:
            if (root == nullptr) {
                cout << "The binary tree is empty." << endl;
            }
            else {
                cout << "Count Nodes With Both Children: " << countNodesWithBothChildren(root) << endl;
            }
            break;
        case 0:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid selection. Try again." << endl;
        }
    }
    return 0;
}

