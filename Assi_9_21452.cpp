#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string keyword;
    string meaning;
    Node *left;
    Node *right;

    Node(const string &key, const string &mean)
        : keyword(key), meaning(mean), left(nullptr), right(nullptr) {}
};

class AVLTree
{
private:
    Node *root;

    int height(Node *node);
    int getBalance(Node *node);
    Node *rightRotate(Node *node);
    Node *leftRotate(Node *node);
    Node *insert(Node *node, const string &keyword, const string &meaning);
    Node *minValueNode(Node *node);
    Node *deleteNode(Node *node, const string &keyword);
    void inorderTraversal(Node *node);
    int maxComparisons(Node *node, const string &keyword, int count);

public:
    AVLTree();
    ~AVLTree();
    void addEntry(const string &keyword, const string &meaning);
    void deleteEntry(const string &keyword);
    void updateEntry(const string &keyword, const string &meaning);
    void displayAscending();
    void displayDescending();
    int getMaxComparisons(const string &keyword);
};

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree()
{
    while (root != nullptr)
    {
        deleteEntry(root->keyword);
    }
}

int AVLTree::height(Node *node)
{
    if (node == nullptr)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

int AVLTree::getBalance(Node *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node *AVLTree::rightRotate(Node *node)
{
    Node *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}

Node *AVLTree::leftRotate(Node *node)
{
    Node *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

Node *AVLTree::insert(Node *node, const string &keyword, const string &meaning)
{
    if (node == nullptr)
        return new Node(keyword, meaning);

    if (keyword < node->keyword)
        node->left = insert(node->left, keyword, meaning);
    else if (keyword > node->keyword)
        node->right = insert(node->right, keyword, meaning);
    else
        node->meaning = meaning;

    int balance = getBalance(node);

    if (balance > 1)
    {
        if (keyword < node->left->keyword)
            return rightRotate(node);
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balance < -1)
    {
        if (keyword > node->right->keyword)
            return leftRotate(node);
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

Node *AVLTree::minValueNode(Node *node)
{
    Node *current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

Node *AVLTree::deleteNode(Node *node, const string &keyword)
{
    if (node == nullptr)
        return nullptr;

    if (keyword < node->keyword)
        node->left = deleteNode(node->left, keyword);
    else if (keyword > node->keyword)
        node->right = deleteNode(node->right, keyword);
    else
    {
        if (node->left == nullptr || node->right == nullptr)
        {
            Node *temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        else
        {
            Node *temp = minValueNode(node->right);
            node->keyword = temp->keyword;
            node->meaning = temp->meaning;
            node->right = deleteNode(node->right, temp->keyword);
        }
    }

    int balance = getBalance(node);

    if (balance > 1)
    {
        if (getBalance(node->left) >= 0)
            return rightRotate(node);
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balance < -1)
    {
        if (getBalance(node->right) <= 0)
            return leftRotate(node);
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

void AVLTree::addEntry(const string &keyword, const string &meaning)
{
    root = insert(root, keyword, meaning);
}

void AVLTree::deleteEntry(const string &keyword)
{
    root = deleteNode(root, keyword);
}

void AVLTree::updateEntry(const string &keyword, const string &meaning)
{
    Node *node = root;
    while (node != nullptr)
    {
        if (keyword == node->keyword)
        {
            node->meaning = meaning;
            break;
        }
        else if (keyword < node->keyword)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
}

void AVLTree::displayAscending()
{
    inorderTraversal(root);
    cout << endl;
}

void AVLTree::displayDescending()
{
    // Reverse inorder traversal for descending order
    cout << "Descending Order: ";
    Node *current = root;
    while (current != nullptr)
    {
        if (current->right == nullptr)
        {
            cout << current->keyword << " ";
            current = current->left;
        }
        else
        {
            Node *predecessor = current->right;
            while (predecessor->left != nullptr && predecessor->left != current)
                predecessor = predecessor->left;

            if (predecessor->left == nullptr)
            {
                predecessor->left = current;
                current = current->right;
            }
            else
            {
                predecessor->left = nullptr;
                cout << current->keyword << " ";
                current = current->left;
            }
        }
    }
    cout << endl;
}

void AVLTree::inorderTraversal(Node *node)
{
    if (node == nullptr)
        return;

    inorderTraversal(node->left);
    cout << node->keyword << ": " << node->meaning << endl;
    inorderTraversal(node->right);
}

int AVLTree::getMaxComparisons(const string &keyword)
{
    return maxComparisons(root, keyword, 1);
}

int AVLTree::maxComparisons(Node *node, const string &keyword, int count)
{
    if (node == nullptr)
        return 0;

    if (keyword == node->keyword)
        return count;

    if (keyword < node->keyword)
        return maxComparisons(node->left, keyword, count + 1);
    else
        return maxComparisons(node->right, keyword, count + 1);
}

void displayMenu()
{
    cout << "========== Dictionary Menu ==========\n";
    cout << "1. Add an entry\n";
    cout << "2. Delete an entry\n";
    cout << "3. Update an entry\n";
    cout << "4. Display entries in ascending order\n";
    cout << "5. Display entries in descending order\n";
    cout << "6. Find maximum comparisons for a keyword\n";
    cout << "7. Exit\n";
    cout << "=====================================\n";
}

int main()
{
    AVLTree dictionary;

    int choice;
    string keyword, meaning;

    do
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice)
        {
        case 1:
            cout << "Enter keyword: ";
            getline(cin, keyword);
            cout << "Enter meaning: ";
            getline(cin, meaning);
            dictionary.addEntry(keyword, meaning);
            cout << "Entry added successfully!\n";
            break;
        case 2:
            cout << "Enter keyword to delete: ";
            getline(cin, keyword);
            dictionary.deleteEntry(keyword);
            cout << "Entry deleted successfully!\n";
            break;
        case 3:
            cout << "Enter keyword to update: ";
            getline(cin, keyword);
            cout << "Enter new meaning: ";
            getline(cin, meaning);
            dictionary.updateEntry(keyword, meaning);
            cout << "Entry updated successfully!\n";
            break;
        case 4:
            cout << "Entries in ascending order:\n";
            dictionary.displayAscending();
            break;
        case 5:
            cout << "Entries in descending order:\n";
            dictionary.displayDescending();
            break;
        case 6:
            cout << "Enter keyword to find maximum comparisons: ";
            getline(cin, keyword);
            cout << "Max comparisons for '" << keyword << "': " << dictionary.getMaxComparisons(keyword) << endl;
            break;
        case 7:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 7.\n";
        }
    } while (choice != 7);

    return 0;
}
