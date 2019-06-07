#include <iostream>

using namespace std;

class Node {
public:
  int data;
  Node* left;
  Node* right;
  Node(int n) : data(n), left(nullptr), right(nullptr) {};
};

void Insert(Node*& tree, int n) {
  if (tree == nullptr) {
    tree = new Node(n);
    return;
  } else if (tree->data == n) {
    return;
  } else if (tree->data < n) {
    Insert(tree->right, n);
    return;
  } else {
    Insert(tree->left, n);
    return;
  }
}

int RemoveLargest(Node*& tree) {
  if (tree->right == nullptr) {
    int d = tree->data;
    tree = tree->left;
    return d;
  } else {
    return RemoveLargest(tree->right);
  }
}

int RemoveSmallest(Node*& tree) {
  if (tree->left == nullptr) {
    int d = tree->data;
    tree = tree->right;
    return d;
  } else {
    return RemoveSmallest(tree->left);
  }
}

void Remove(Node*& tree, int n) {
  if (tree == nullptr) {
    return;
  } else if (tree->data == n) {
    if (tree->left == nullptr) {
      cout << "left is null" << endl;
      Node* todelete = tree;
      tree = tree->right;
      delete todelete;
    } else if (tree->right == nullptr) {
      cout << "right is null" << endl;
      Node* todelete = tree;
      tree = tree->left;
      delete todelete;
    } else {
      cout << "need to remove largest" << endl;
      int i = RemoveLargest(tree->left);
      tree->data = i;
    }
    return;
  } else if (tree->data < n) {
    Remove(tree->right, n);
    return;
  } else {
    Remove(tree->left, n);
    return;
  }
}

void Print(Node* tree) {
  if (tree == nullptr) return;
  Print(tree->left);
  cout << tree->data << " ";
  Print(tree->right);
}

bool Find(Node* tree, int n) {
  if (tree == nullptr) {
    return false;
  } else if (tree->data == n) {
    return true;
  } else if (tree->data < n) {
    return Find(tree->right, n);
  } else {
    return Find(tree->left, n);
  }
}

Node* BalancedTreeFromArray(int arr[], int first, int last) {
  if (first > last) {
    return nullptr;
  } else {
    int mid = (first + last) / 2;
    Node* newnode = new Node(arr[mid]);
    newnode->left = BalancedTreeFromArray(arr, first, mid - 1);
    newnode->right = BalancedTreeFromArray(arr, mid + 1, last);
    return newnode;
  }
}

int FindDepth(Node* tree) {
  if (tree == nullptr) return 0;
  int L = FindDepth(tree->left);
  int R = FindDepth(tree->right);
  if (L > R) {
    return L + 1;
  } else {
    return R + 1;
  }
}

bool IsBalanced(Node* tree) {
  if (tree == nullptr) return true;
  int L = FindDepth(tree->left);
  int R = FindDepth(tree->right);
  if ((L > R + 1) || (R > L + 1)) return false;
  if (!IsBalanced(tree->left)) return false;
  if (!IsBalanced(tree->right)) return false;
  return true;
}

int NumNodes(Node* tree) {
  if (tree == nullptr) return 0;
  return 1 + NumNodes(tree->left) + NumNodes(tree->right);
}

void BalanceTree(Node*& tree) {
  if (tree == nullptr) return;
  while (NumNodes(tree->left) > (NumNodes(tree->right) + 1)) {
    int val = RemoveLargest(tree->left);
    int rootval = tree->data;
    tree->data = val;
    Insert(tree, rootval);
  }
  while (NumNodes(tree->right) > (NumNodes(tree->left) + 1)) {
    int val = RemoveSmallest(tree->right);
    int rootval = tree->data;
    tree->data = val;
    Insert(tree, rootval);
  }
  BalanceTree(tree->left);
  BalanceTree(tree->right);
}

// This has only two test cases. You may want to test more exhaustively.
int main() {

  int arr[] = { 2, 5, 7, 9, 10, 11, 16, 18 };
  Node* tree1 = BalancedTreeFromArray(arr, 0, 7);
  Print(tree1);
  cout << endl;
  if (IsBalanced(tree1)) {
    cout << "Tree is balanced" << endl;
  }

  Node* tree = nullptr;
  Insert(tree, 13);
  Insert(tree, 12);
  Insert(tree, 6);
  Insert(tree, 7);
  Insert(tree, 8);
  Insert(tree, 5);
  Insert(tree, 6);
  Insert(tree, 4);
  Insert(tree, 3);

  if (IsBalanced(tree)) {
    cout << "Tree is balanced." << endl;
  } else {
    cout << "Tree is not balanced." << endl;
  }

  BalanceTree(tree);

  if (IsBalanced(tree)) {
    cout << "Tree is balanced." << endl;
  } else {
    cout << "Tree is not balanced." << endl;
  }

  Print(tree);

  return 0;
}

/*

2 5 7 9 10 11 16 18
Tree is balanced
Tree is not balanced.
Tree is balanced.
3 4 5 6 7 8 12 13

*/
