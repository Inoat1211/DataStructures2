#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

class HashMapChaining
{
private:
    vector<list<pair<int, string>>> table;
    int capacity;
    int hashFunction(int key)
    {
        return (key % capacity + capacity) % capacity;
    }

public:
    HashMapChaining(int m)
    {
        capacity = m;
        table.resize(capacity);
    }

    void insert(int key, string value)
    {
        int index = hashFunction(key);
        for (auto &item : table[index])
        {
            if (item.first == key)
            {
                item.second = value;
                return;
            }
        }

        table[index].push_back({key, value});
    }

    bool search(int key)
    {
        int index = hashFunction(key);
        for (auto item : table[index])
        {
            if (item.first == key)
                return true;
        }
        return false;
    }
};

struct BSTNode
{
    int key;
    BSTNode *left;
    BSTNode *right;

    BSTNode(int value)
    {
        key = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
private:
    BSTNode *root;
    BSTNode *insertNode(BSTNode *node, int key)
    {
        if (node == nullptr)
            return new BSTNode(key);
        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        return node;
    }
    bool searchNode(BSTNode *node, int key)
    {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return searchNode(node->left, key);
        return searchNode(node->right, key);
    }

public:
    BST()
    {
        root = nullptr;
    }
    void insert(int key)
    {
        root = insertNode(root, key);
    }
    bool search(int key)
    {
        return searchNode(root, key);
    }
};

struct AVLNode
{
    int key;
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(int value)
    {
        key = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVL
{
private:
    AVLNode *root;
    int getHeight(AVLNode *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    int getBalance(AVLNode *node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    void updateHeight(AVLNode *node)
    {
        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));
    }

    AVLNode *rotateRight(AVLNode *y)
    {
        AVLNode *x = y->left;
        AVLNode *temp = x->right;
        x->right = y;
        y->left = temp;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode *rotateLeft(AVLNode *x)
    {
        AVLNode *y = x->right;
        AVLNode *temp = y->left;
        y->left = x;
        x->right = temp;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode *insertNode(AVLNode *node, int key)
    {
        if (node == nullptr)
            return new AVLNode(key);
        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;
        updateHeight(node);
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    bool searchNode(AVLNode *node, int key)
    {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return searchNode(node->left, key);
        return searchNode(node->right, key);
    }

public:
    AVL()
    {
        root = nullptr;
    }

    void insert(int key)
    {
        root = insertNode(root, key);
    }

    bool search(int key)
    {
        return searchNode(root, key);
    }
};

double doThoiGianChenHash(vector<int> keys, int capacity)
{
    HashMapChaining hashTable(capacity);
    auto batDau = high_resolution_clock::now();
    for (int i = 0; i < keys.size(); i++)
    {
        hashTable.insert(keys[i], "");
    }
    auto ketThuc = high_resolution_clock::now();
    double thoiGian =
        duration<double, milli>(ketThuc - batDau).count();
    return thoiGian;
}

double doThoiGianChenBST(vector<int> keys)
{
    BST tree;
    auto batDau = high_resolution_clock::now();
    for (int i = 0; i < keys.size(); i++)
    {
        tree.insert(keys[i]);
    }
    auto ketThuc = high_resolution_clock::now();
    double thoiGian =
        duration<double, milli>(ketThuc - batDau).count();
    return thoiGian;
}

double doThoiGianChenAVL(vector<int> keys)
{
    AVL tree;
    auto batDau = high_resolution_clock::now();
    for (int i = 0; i < keys.size(); i++)
    {
        tree.insert(keys[i]);
    }
    auto ketThuc = high_resolution_clock::now();
    double thoiGian =
        duration<double, milli>(ketThuc - batDau).count();
    return thoiGian;
}

double doThoiGianTimHash(vector<int> keys,
                         vector<int> queries,
                         int capacity)
{
    HashMapChaining hashTable(capacity);
    for (int i = 0; i < keys.size(); i++)
    {
        hashTable.insert(keys[i], "");
    }
    int dem = 0;
    auto batDau = high_resolution_clock::now();

    for (int i = 0; i < queries.size(); i++)
    {
        if (hashTable.search(queries[i]))
        {
            dem++;
        }
    }
    auto ketThuc = high_resolution_clock::now();
    double thoiGian =
        duration<double, milli>(ketThuc - batDau).count();
    return thoiGian;
}

double doThoiGianTimBST(vector<int> keys,
                        vector<int> queries)
{
    BST tree;
    for (int i = 0; i < keys.size(); i++)
    {
        tree.insert(keys[i]);
    }
    int dem = 0;
    auto batDau = high_resolution_clock::now();
    for (int i = 0; i < queries.size(); i++)
    {
        if (tree.search(queries[i]))
        {
            dem++;
        }
    }
    auto ketThuc = high_resolution_clock::now();
    double thoiGian =
        duration<double, milli>(ketThuc - batDau).count();
    return thoiGian;
}

double doThoiGianTimAVL(vector<int> keys,
                        vector<int> queries)
{
    AVL tree;
    for (int i = 0; i < keys.size(); i++)
    {
        tree.insert(keys[i]);
    }
    int dem = 0;
    auto batDau = high_resolution_clock::now();
    for (int i = 0; i < queries.size(); i++)
    {
        if (tree.search(queries[i]))
        {
            dem++;
        }
    }
    auto ketThuc = high_resolution_clock::now();
    double thoiGian =
        duration<double, milli>(ketThuc - batDau).count();
    return thoiGian;
}

int main()
{
    vector<int> sizes = {10000, 100000, 500000};
    mt19937 rng(42);

    cout << "n\tHash Chen\tBST Chen\tAVL Chen\t"
         << "Hash Tim\tBST Tim\tAVL Tim\n";

    for (int i = 0; i < sizes.size(); i++)
    {
        int n = sizes[i];
        vector<int> keys;
        for (int j = 1; j <= n; j++)
        {
            keys.push_back(j);
        }
        shuffle(keys.begin(), keys.end(), rng);
        vector<int> queries;
        uniform_int_distribution<int> randomIndex(0, n - 1);
        for (int j = 0; j < 100000; j++)
        {
            int viTri = randomIndex(rng);
            queries.push_back(keys[viTri]);
        }
        int capacity = n * 2 + 1;
        double hashInsert =
            doThoiGianChenHash(keys, capacity);

        double bstInsert =
            doThoiGianChenBST(keys);

        double avlInsert =
            doThoiGianChenAVL(keys);
            
        double hashSearch =
            doThoiGianTimHash(keys, queries, capacity);

        double bstSearch =
            doThoiGianTimBST(keys, queries);

        double avlSearch =
            doThoiGianTimAVL(keys, queries);

        cout << n << "\t"
             << hashInsert << "\t"
             << bstInsert << "\t"
             << avlInsert << "\t"
             << hashSearch << "\t"
             << bstSearch << "\t"
             << avlSearch << "\n";
    }
    return 0;
}