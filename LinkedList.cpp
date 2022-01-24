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
        int length;
    public:
        List();                     // default constructor
        List(const List &list);     // copy constructor
        // add and delete methods
        void append(int val);       // add-last
        void enqueue(int val);      // add-first
        int pop();                  // delete-last
        int dequeue();              // delete-first
        // helper methods
        Node* findV(int val);       // find a node with value = val
        Node* findN(int n);         // find the n-th node
        int getNVal(int n);         // get the value of the n-th node
        int getLength();            // get the length of the linked list
        void delV(int val);         // delete a node with value = val
        void delN(int n);           // delete n-th node
        // misc methods
        void traverse();            // traverse the linked list
        void concat(List &list);    // concatenate the lists, and deallocate the added list
    };

    // List constructor
    List::List() {
        this->head = NULL;
        this->tail = NULL;
        this->length = 0;
    }

    // List copy constructor
    List::List(const List &list) {
        this->head = NULL;
        this->tail = NULL;
        this->length = list.length;
        Node* walk = list.head;
        for (int i = 0; i < list.length; i++) {
            this->append(walk->getValue());
            walk = walk->getNext();
        }
    }

    // append - add a Node at the end of the list
    void List::append(int val) {
        Node *node = new Node(val, NULL, this->tail);
        if (this->tail != NULL) this->tail->setNext(node);
        else this->head = node;
        this->tail = node;
        this->length = this->length + 1;
    }

    // enqueue - add a Node at the front of the list
    void List::enqueue(int val) {
        Node *node = new Node(val, this->head, NULL);
        if (this->head != NULL) this->head->setPrev(node);
        else this->tail = node; // when this is an empty linked list    
        this->head = node;
        this->length = this->length + 1;
    }

    // pop - remove a Node at the last of the list
    int List::pop() {
        int v = this->tail->getValue();
        Node* ptail = this->tail->getPrev();
        delete this->tail;        // remove the memory from the heap
        ptail->setNext(NULL);
        this->tail = ptail;
        this->length = this->length - 1;
        return v;
    }

    // dequeue - remove a Node at the first of the list
    int List::dequeue() {
        int v = this->head->getValue();
        Node* nhead = this->head->getNext();
        delete this->head;
        nhead->setPrev(NULL);
        this->head = nhead;
        this->length = this->length - 1;
        return v;
    }

    // findV - find a node with a value = val, return NULL if there's none
    Node* List::findV(int val) {
        Node* walk = this->head;
        while(walk->getValue() != val) {
            if (walk == this->tail) break;
            walk = walk -> getNext();
        }
        if (walk->getValue() != val) return NULL;
        return walk;
    }

    // findN - find a n-th Node
    Node* List::findN(int n) {
        if (n >= this->length) return NULL;
        Node* walk = this->head;
        for (int i = 0; i < n; i++) {
            walk = walk->getNext();
        }
        return walk;
    }

    // getNVal - get the value of the n-th node
    int List::getNVal(int n) {
        Node* temp = this->findN(n);
        if (temp == NULL) return 1<<31;
        return temp->getValue();
    }

    // getLength - get the length of the linked list
    int List::getLength() {
        return this->length;
    }

    // delV - delete the node with value = val
    void List::delV(int val) {
        Node* temp = this->findV(val);
        if (temp == NULL) return;
        Node* tprv = temp->getPrev();
        Node* tnxt = temp->getNext();
        if (tprv != NULL) tprv->setNext(tnxt);
        else tnxt = this->head;
        if (tnxt != NULL) tnxt->setPrev(tprv);
        else tprv = this->tail;
        this->length -= 1;
        delete temp;
    }

    // delN - delete the n-th node
    void List::delN(int n) {
        Node* temp = this->findN(n);
        if (temp == NULL) return;
        Node* tprv = temp->getPrev();
        Node* tnxt = temp->getNext();
        if (tprv != NULL) tprv->setNext(tnxt);
        else tnxt = this->head;
        if (tnxt != NULL) tnxt->setPrev(tprv);
        else tprv = this->tail;
        this->length -= 1;
        delete temp;
    }

    // traverse - traverse the linked list from the head to the tail
    void List::traverse() {
        if (this == NULL) {
            printf("This list does not exist.\n");
            return;
        }
        int cnt = 0;
        Node* walk = this->head;
        do {
            if (cnt == 0) {
                printf(">> [Head %d] ", cnt++);
            } 
            else {
                printf(">> [Node %d] ", cnt++);
            }
            printf("value: %d\n", walk->getValue());
            walk = walk->getNext();
        } while(walk != this->tail);
        printf(">> [Tail %d] ", cnt);
        printf("value: %d\n", walk->getValue());
    }

    // concat - concatenate a list to this list
    void List::concat(List &list) {
        this->tail->setNext(list.head);
        list.head->setPrev(this->tail);
        this->tail = list.tail;
        this->length += list.length;
        delete &list;
    }
}

// main routine
int main() {
    using namespace linkedlist;
    printf("\n");
    printf("LinkedList> Node size is %d bytes.\n", sizeof(Node));
    printf("\n");
    List* list1 = new List();       // allocated at the heap
    List* list2 = new List();       // allocated at the heap
    
    // list 1 
    for (int i = 2; i < 10; i++) {
        if (i%4 == 1) list1->pop();
        else list1->append(i);
    }
    printf("LinkedList> Traversing the list1\n");
    list1->traverse();
    printf("\n");

    // list 2
    list2->enqueue(8);
    list2->enqueue(1);
    list2->enqueue(6);
    list2->dequeue();
    list2->enqueue(4);
    printf("LinkedList> Traversing the list2\n");
    list2->traverse();
    printf("\n");

    // list concatenation
    printf("LinkedList> Concatenating list2 to list1\n");
    list1->concat(*list2);
    printf("\n");

    printf("LinkedList> Traversing the list1\n");
    list1->traverse();
    printf("\n");

    // finding the node with value = val
    printf("LinkedList> Helper Routines\n");
    printf(">> Length of list1 is %d\n", list1->getLength());
    Node* V3 = list1->findV(3);
    Node* V5 = list1->findV(5);
    Node* N0 = list1->findN(0);
    Node* N8 = list1->findN(8);
    printf(">> Node with value 3 is at %p\n", V3);
    printf(">> Node with value 5 is at %p\n", V5);
    printf(">> Node 0 is at %p\n", N0);
    printf(">> Node 8 is at %p\n", N8);
    printf(">> Tail 6's value is %d\n", list1->getNVal(6));
    printf(">> Head 0's value is %d\n", list1->getNVal(0));
    printf(">> Node 9's value is %d\n", list1->getNVal(9));
    printf("\n");

    list1->delV(3);
    list1->delV(7);
    // 2 - 6 - 4 - 1 - 8
    list1->append(5);
    list1->enqueue(9);
    // 9 - 2 - 6 - 4 - 1 - 8 - 5
    list1->delN(1);
    // 9 - 6 - 4 - 1 - 8 - 5
    printf("LinkedList> Traversing the list1\n");
    list1->traverse();
    printf("\n");

    // copy constructor, on heap
    List* list3 = new List(*list1);

    list3->enqueue(3);
    list3->enqueue(7);
    list3->pop();
    list3->pop();
    printf("LinkedList> Address of the list is at %p\n", list1);
    printf("LinkedList> Address of the head if the list is at %p\n", list1->findN(0));
    printf("LinkedList> Traversing the list1\n");
    list1->traverse();
    printf("\n");

    printf("LinkedList> Address of the list3 is at %p\n", list3);
    printf("LinkedList> Address of the head if the list3 is at %p\n", list3->findN(0));
    printf("LinkedList> Traversing the list3\n");
    list3->traverse();
    printf("\n");

    delete list1;               // deallocate from the heap
    delete list3;
    return 0;
}
