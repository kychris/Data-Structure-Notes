#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
  string data;
  Node* left;
  Node* right;
  Node(string d) : data(d), left(nullptr), right(nullptr) { };
};

Node* ParsePrefix(const vector<string>& expr, int& ind);

void PrintPrefix(Node* t);

void PrintPostfix(Node* t);

void PrintInfix(Node* t);

int main() {
  vector<string> expr = { "+", "-", "3", "2", "/", "*", "5", "7", "8" };
  int index = 0;
  Node* t = ParsePrefix(expr, index);
  PrintPrefix(t);
  cout << endl;
  PrintPostfix(t);
  cout << endl;
  PrintInfix(t);
  cout << endl;
  return 0;
}

/*
+ - 3 2 / * 5 7 8
3 2 - 5 7 * 8 / +
( ( 3 - 2 ) + ( ( 5 * 7 ) / 8 ) )
 */
