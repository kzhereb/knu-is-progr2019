#include <iostream>

using namespace std;

class Node
{
private:
    Node* next;
public:

    int data;

    void print();

    void add(int);
};

void Node::add(int newData)
{
    Node* current_node = this;
    while(current_node->next != nullptr)
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
    do
    {
        cout << current_node->data << ' ';
        current_node = current_node->next;
    }
    while(current_node->next != nullptr);
}


int main()
{
    Node* myList = new Node;
    myList->add(5);
    myList->add(10);
    myList->print();

    return 0;
}
