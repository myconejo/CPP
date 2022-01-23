#include <stdlib.h>
#include <stdio.h>

#define VERBOSE 0

namespace linkedlist {

    // Node: an object with pointers and a value
    class Node {
        int value;  // 4B
        Node* next; // 8B
        Node* prev; // 8B
    public:
        Node(int v, Node* n, Node* p);
        int getValue(void);
        void setValue(int v);
        void setPrev(Node* p);
        void setNext(Node* n);
        Node* getPrev();
        Node* getNext();
    };

    // Node constructor
    Node::Node(int v, Node* n, Node* p) {
        this->value = v;
        this->next = n;
        this->prev = p;
    }

    // setValue - set value of the Node
    void Node::setValue(int v) {
        this->value = v;
    }   

    // setNext - set the next pointer of the Node
    void Node::setNext(Node* n) {
        this->next = n;
    }

    // setPrev - set the prev pointer of the Node
    void Node::setPrev(Node* p) {
        this->prev = p;
    }

    // getValue - get the value of the Node
    int Node::getValue(void) {
        return this->value;
    }

    // getNext - get the next pointer of the Node
    Node* Node::getNext() {
        return this->next;
    }

    // getPrev - get the prev pointer of the Node
    Node* Node::getPrev() {
        return this->prev;
    }

    // List: an object with a head and a tail
    class List {
        Node* head;
        Node* tail;
    public:
        List();
        List(const List &list);
        void append(int val);       // add-last
        void enqueue(int val);      // add-first
        int pop();                  // remove-last
        int dequeue();              // remove-first
        void traverse();
        void concat(List &list);
    };

    // List constructor
    List::List() {
        this->head = NULL;
        this->tail = NULL;
    }

    // List copy constructor
    List::List(const List &list) {
        this->head = list.head;
        this->tail = list.tail;
    }

    // append - add a Node at the end of the list
    void List::append(int val) {
        Node *node = new Node(val, NULL, this->tail);
        if (this->tail != NULL) this->tail->setNext(node);
        else this->head = node;
        this->tail = node;
    }

    // enqueue - add a Node at the front of the list
    void List::enqueue(int val) {
        Node *node = new Node(val, this->head, NULL);
        if (this->head != NULL) this->head->setPrev(node);
        else this->tail = node; // when this is an empty linked list    
        this->head = node;
    }

    // pop - remove a Node at the last of the list
    int List::pop() {
        int v = this->tail->getValue();
        Node* ptail = this->tail->getPrev();
        if (VERBOSE) printf("Address of the node to be popped: %p\n", this->tail);
        delete this->tail;        // remove the memory from the heap
        if (VERBOSE) {
            printf("Address of the node to be popped: %p\n", this->tail);
            printf("Accessing the value: %d\n", ptail->getNext()->getValue());
            // if deleted (freed) properly, then the value is not accessible
        }
        ptail->setNext(NULL);
        this->tail = ptail;
        return v;
    }

    // dequeue - remove a Node at the first of the list
    int List::dequeue() {
        int v = this->head->getValue();
        Node* nhead = this->head->getNext();
        delete this->head;
        nhead->setPrev(NULL);
        this->head = nhead;
        return v;
    }

    // traverse - traverse the linked list from the head to the tail
    void List::traverse() {
        int cnt = 0;
        Node* walk = this->head;
        do {
            if (cnt == 0) {
                printf("LinkedList> Traversing the list\n");
                printf(">> [Head %d] ", cnt++);
            } 
            else {
                printf(">> [Node %d] ", cnt++);
            }
            printf("value: %d\n", walk->getValue());
            walk = walk->getNext();
        } while(walk != this->tail);
        printf(">> [Tail %d] ", cnt);
        printf("value: %d\n\n", walk->getValue());
    }

    // concat - concatenate a list to this list
    void List::concat(List &list) {
        printf("LinkedList> concatenating the lists\n\n");
        if (VERBOSE) printf("tail next: %p\n", this->tail->getNext());
        this->tail->setNext(list.head);
        if (VERBOSE) printf("tail next: %p\n", this->tail->getNext());
        list.head->setPrev(this->tail);
        this->tail = list.tail;
    }
}

// main routine
int main() {
    using namespace linkedlist;
    printf("LinkedList> Node size is %d bytes.\n\n", sizeof(Node));
    List list = List();
    List list2 = List();
    
    // list 1 
    for (int i = 2; i < 10; i++) {
        if (i%4 == 1) list.pop();
        else list.append(i);
    }
    list.enqueue(5);
    list.traverse();

    // list 2
    list2.enqueue(8);
    list2.enqueue(4);
    list2.traverse();
    
    // list concatenation
    list.concat(list2);
    list.traverse();

    return 0;
}
