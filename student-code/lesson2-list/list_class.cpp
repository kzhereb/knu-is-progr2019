#include <iostream>

using namespace std;

namespace k19lesson2std2{
class Node
{
private:
    Node* next;
public:
    Node() { data=0; next=nullptr;}

    int data;

    void print();

    void add(int);
};

void Node::add(int newData)
{
    Node* current_node = this;
    while(current_node->next)
    {
        current_node = current_node->next;
    }

    current_node->next = new Node;
    current_node->next->data = newData;
    current_node->next->next = nullptr;
}

void Node::print()
{
    Node* current_node = this;
//    do
//    {
//        cout << current_node->data << ' ';
//        current_node = current_node->next;
//    }
//    while(current_node->next != nullptr);

    while(current_node) {
    	cout << current_node->data << ' ';
    	current_node = current_node->next;
    }
}


int main_k19lesson2std2()
{
	cout<< "test"<<endl;
    Node* myList = new Node;
    myList->add(5);
    myList->add(10);
    myList->print();

    return 0;
}
}
