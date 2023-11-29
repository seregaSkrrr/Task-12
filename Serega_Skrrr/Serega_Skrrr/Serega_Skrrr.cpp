#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int d) : data{ d }, left{ nullptr }, right{ nullptr } {}
    void print() {
        cout << data;
    }
};

class Tree {
    Node* root = nullptr;
    Node* add(Node*& parent, Node* node);
    void print(Node* Node);
    int countNodes(Node* root);
    int height(Node* root);
    bool isBalanced(Node* root);
    int sum(Node* root);
    bool isFull(Node* root);
    Node* findMin(Node* node);
    Node* findMax(Node* node);
public:
    Node* findNext(Node* root, int data);
    Node* findPrev(Node* root, int data);
    Node* find(int data);
    Node* remove(Node*& parent, int key);
    void addNode(Node* n) {
        add(root, n);
    }
    void removeNum(int key) {
        remove(root, key);
    }
    void print() {
        print(root);
    }
    int countNodes() {
        return countNodes(root);
    }
    int height() {
        return height(root);
    }
    bool isBalanced() {
        return isBalanced(root);
    }
    int sum() {
        return sum(root);
    }
    bool isFull() {
        return isFull(root);
    }
    Node* findMin() {
        return findMin(root);
    }
    Node* findMax() {
        return findMax(root);
    }
};

Node* Tree::add(Node*& parent, Node* node) {

    if (!parent) {
        parent = node;
        return node;
    }
    if (node->data < parent->data) {
        parent->left = add(parent->left, node);
    }
    else if (node->data > parent->data) {
        parent->right = add(parent->right, node);
    }

    return parent;
}
Node* Tree::findMin(Node* node) {
    if (node == nullptr || node->left == nullptr)
        return node;
    return findMin(node->left);
}

Node* Tree::findMax(Node* node) {
    if (node == nullptr || node->right == nullptr)
        return node;
    return findMax(node->right);
}

Node* Tree::find(int data) {
    Node* curr = root;
    while (curr) {
        if (data < curr->data)
            curr = curr->left;
        else if (data > curr->data)
            curr = curr->right;
        else
            return curr;
    }
    return nullptr;
}

Node* Tree::remove(Node*& parent, int key) {
    if (parent == nullptr)
        return parent;

    if (key < parent->data)
        parent->left = remove(parent->left, key);

    else if (key > parent->data)
        parent->right = remove(parent->right, key);

    else {
        if (parent->left == nullptr) {
            Node* temp = parent->right;
            delete parent;
            return temp;
        }
        else if (parent->right == nullptr) {
            Node* temp = parent->left;
            delete parent;
            return temp;
        }

        Node* temp = findMin(parent->right);
        parent->data = temp->data;
        parent->right = remove(parent->right, temp->data);
    }
    return parent;
}

Node* Tree::findNext(Node* root, int data) {
    Node* next = nullptr;
    while (root != nullptr) {
        if (data < root->data) {
            next = root;
            root = root->left;
        }
        else if (data > root->data) {
            root = root->right;
        }
        else {
            if (root->right != nullptr) {
                next = root->right;
                while (next->left != nullptr) {
                    next = next->left;
                }
            }
            return next;
        }
    }
    return next;
}

Node* Tree::findPrev(Node* root, int data) {
    Node* prev = nullptr;
    while (root != nullptr) {
        if (data < root->data) {
            root = root->left;
        }
        else if (data > root->data) {
            prev = root;
            root = root->right;
        }
        else {
            if (root->left != nullptr) {
                prev = root->left;
                while (prev->right != nullptr) {
                    prev = prev->right;
                }
            }
            return prev;
        }
    }
    return prev;
}

void Tree::print(Node* node) {
    if (node != 0) {
        print(node->right);
        node->print();
        print(node->left);
    }
}

int Tree::countNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int Tree::height(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(height(root->left), height(root->right));
}

bool Tree::isBalanced(Node* root) {
    if (root == nullptr) {
        return true;
    }
    return std::abs(height(root->left) - height(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

int Tree::sum(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->data + sum(root->left) + sum(root->right);
}

bool Tree::isFull(Node* root) {
    if (root == nullptr) {
        return true;
    }
    if (root->left == nullptr && root->right != nullptr) {
        return false;
    }
    if (root->left != nullptr && root->right == nullptr) {
        return false;
    }
    return isFull(root->left) && isFull(root->right);
}

int main() {
    setlocale(LC_ALL, "RU");

    Tree t;
    t.addNode(new Node(7));
    t.addNode(new Node(3));
    t.addNode(new Node(9));
    t.addNode(new Node(5));
    t.addNode(new Node(9));

    cout << "Массив после добавления: ";
    t.print();

    t.removeNum(7);
    cout << endl << "Массив после удаления: ";
    t.print();
    cout << "\nВысота дерева " << t.height() << endl;
    cout << "Минимальное значение " << t.findMin()->data << endl;
    cout << "Максимальное значение " << t.findMax()->data << endl;
    cout << "Сумма всех нод " << t.sum() << endl;
    cout << "Количество нод " << t.countNodes() << endl;
    cout << "Сбалансированное? " << (t.isBalanced() ? "Да" : "Не") << endl;
    cout << "Полное? " << (t.isFull() ? "Да" : "Не") << endl;

    return 0;
}