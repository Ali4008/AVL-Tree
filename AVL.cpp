// ConsoleApplication182.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

struct node {
    int val;
    node* right;
    node* left;
    int h;
    node(int v) {
        val = v;
        right = left = NULL;
    }
};

class avl {
public:
    node* root;
public:
    avl() {
        root = NULL;
    }
    int height(node* r) {
        if (r == NULL) {
            return -1;
        }
        else {
            int lh = height(r->left);
            int rh = height(r->right);
            if (lh > rh) {
                return (lh + 1);
            }
            else {
                return (rh + 1);
            }
        }
    }

    int getbal(node* r) {
        if (r == NULL) {
            return -1;
        }
        else {
            return height(r->left) - height(r->right);
        }
    }

    node* rightrot(node* y) {
        node* x = y->left;
        node* t2 = x->right;
        x->right = y;
        y->left = t2;
        return x;
    }

    node* leftrot(node* x) {
        node* y = x->right;
        node* t2 = y->left;
        y->left = x;
        x->right = t2;
        return y;
    }

    node* insert(node* r, int v) {
        if (r == NULL) {
            node* temp = new node(v);
            return temp;
        }

        if (r->val > v) {
            r->left = insert(r->left, v);
        }
        else if (r->val < v) {
            r->right = insert(r->right, v);
        }
       
        int bf = getbal(r);
        if (bf > 1 && r->left->val > v) {
            return rightrot(r);
        }
        if (bf > 1 && r->left->val < v) {
            r->left = leftrot(r->left);
            return rightrot(r);
        }

        if (bf < -1 && r->right->val < v) {
            return leftrot(r);
      }

        if (bf<-1 && r->right->val>v) {
            r->right = rightrot(r->right);
            return leftrot(r);
        }
        return r;
    }

    void inorder(node* r) {
        if (r) {
            inorder(r->left);
            cout << r->val<<" ";
            inorder(r->right);
        }
    }
    node* min(node* r) {
        node* temp = r;
        while (r->left != NULL) {
            temp = temp->left;
        }
        return temp;
    }
    node* del(node* r, int v) {
        if (r == NULL) {
            return NULL;
        }
        else if (r->val > v) {
            r->left = del(r->left, v);
        }
        else if (r->val < v) {
            r->right = del(r->right, v);
        }
        else {
            if (r->left == NULL) {
                node* temp = r->right;
                delete r;
                return temp;
            }
            else if (r->right == NULL) {
                node* temp = r->left;
                delete r;
                return temp;
            }
            else {
                node* temp = min(r->right);
                r->val = temp->val;
                r->right = del(r->right, temp->val);
            }
        }

        int bf = getbal(r);
        if (bf == 2 && getbal(r->left) >= 0) {
            return rightrot(r);
        }
        else  if (bf == 2 && getbal(r->left) == -1) {
            r->left = leftrot(r->left);
            return rightrot(r);
        }
        else if (bf == -2 && getbal(r->right) <= 0) {
            return leftrot(r);
        }
        else if (bf == -2 && getbal(r->right) == 1) {
            r->right = rightrot(r->right);
            return leftrot(r);
        }
        return r;
  }
    
};

int main()
{

    avl a;
    a.root=a.insert(a.root, 10);
    a.root=a.insert(a.root, 1);
    a.root = a.insert(a.root, 40);
    a.root = a.insert(a.root, 120);
    a.root = a.insert(a.root, 11);
    a.root = a.insert(a.root, 15);
    a.root = a.del(a.root, 120);
    a.inorder(a.root);




}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
