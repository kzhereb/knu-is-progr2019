#include <bits/stdc++.h>
using namespace std;
namespace k18lesson2std1 {
struct Node {
    int data;
    Node *next;
};

using List = Node;
using ListPtr = List*;

ListPtr create_list(int, int, int);
void print_list(ListPtr);
void delete_list(ListPtr);


int main_k18lesson1std1()
{
    ListPtr p;
    p = create_list(1, 2, 3);
    print_list(p);
    return 0;
}

ListPtr create_node(ListPtr top, int data) {
    ListPtr curr = new List;
    curr->data = data;
    curr->next = top;
    return curr;
}

ListPtr create_list(int d1, int d2, int d3) {
    ListPtr p;

    p = create_node(nullptr, d3);

    p = create_node(p, d2);

    p = create_node(p, d1);

    return p;
}

void print_list(ListPtr top) {
    ListPtr p;
    while(p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
}
