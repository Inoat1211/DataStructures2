#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
 int data;
 TreeNode* left;
 TreeNode* right;
 TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

int height(TreeNode* root) {
    if (root == nullptr)
        return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return 1 + leftHeight;
    else
        return 1 + rightHeight;}

void inorderHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr)
        return;
    inorderHelper(root->left, result);
    result.push_back(root->data);
    inorderHelper(root->right, result);
}

vector<int> inorder(TreeNode* root) {
    vector<int> result;
    inorderHelper(root, result);
    return result;
}

void printVector(vector<int>& v) {
    for (int x : v)
        cout << x << " ";
    cout << endl;
}        

TreeNode* insert(TreeNode* root, int key) {
 // TODO: sinh vien cai dat (tham khao lai ly thuyet muc 2.4.2)
     if (root == nullptr)
        return new TreeNode(key);
    if (key < root->data) {
        root->left = insert(root->left, key);
    }
    else if (key > root->data) {
        root->right = insert(root->right, key);
    }
    else {
        cout << "Khoa " << key << " da ton tai, khong chen trung." << endl;
    }
    return root;
}

TreeNode* search(TreeNode* root, int key) {
 // TODO: sinh vien cai dat
    if (root == nullptr)
        return nullptr;
    if (root->data == key)
        return root;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}
TreeNode* findMin(TreeNode* root) {
 // TODO: tim nut nho nhat trong mot cay con - can cho deleteNode()
    if (root == nullptr)
        return nullptr;
    while (root->left != nullptr)
        root = root->left;
    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
 // TODO: xu ly du 3 truong hop (0 con / 1 con / 2 con)
    if (root == nullptr)
        return nullptr;
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }

    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }

    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        
        else if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        else {
            TreeNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;

}
void printMenu() {
 cout << "\n----- MENU QUAN LY BST -----\n";
 cout << "1. Chen khoa\n";
 cout << "2. Tim kiem khoa\n";
 cout << "3. Xoa khoa\n";
 cout << "4. In cay theo Inorder\n";
 cout << "5. In chieu cao cay\n";
 cout << "0. Thoat\n";
 cout << "Lua chon cua ban: ";
}
int main() {
 TreeNode* root = nullptr;
 int choice, key;
 do {
 printMenu();
 cin >> choice;
 switch (choice) {
 case 1:
 cout << "Nhap khoa can chen: "; cin >> key;
 root = insert(root, key);
 break;
 case 2:
 cout << "Nhap khoa can tim: "; cin >> key;
 cout << (search(root, key) ? "Tim thay!" : "Khong thay!") << endl;
 break;
 case 3:
 cout << "Nhap khoa can xoa: "; cin >> key;
 root = deleteNode(root, key);
 break;
 case 4:
 // TODO: goi lai ham inorder() da viet o Bai 2, in ra man hinh
    {vector<int> result = inorder(root);
    cout << "Inorder: ";
    printVector(result);
    break;}
 case 5:
 // TODO: goi lai ham height() da viet o Bai 1, in ra man hinh
cout << "Chieu cao cay: "<< height(root) << endl;
break;

case 0:
cout << "Thoat chuong trinh." << endl;
break;
default:
cout << "Lua chon khong hop le!" << endl; }
 } while (choice != 0);
 return 0;
}

