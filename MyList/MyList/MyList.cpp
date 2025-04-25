#include "MyList.h"
#include <iostream>

using namespace std;

//Конструктор узла
Node::Node(void* data) : data(data), next(nullptr), prev(nullptr) {}

//Конуструктор
MyList::MyList() : head(nullptr), tail(nullptr), size(0) {}

//Деструктор
MyList::~MyList(){
    clear();
}

//Проверка на пустоту
bool MyList::empty() const{
    return head == nullptr;
}

//Метод очистки списка
void MyList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

//Метод добавления в начало
void MyList::push_front(void* data) {
    Node* newNode = new Node(data);
    
    if(empty()){
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

//Метод добавления в конец
void MyList::push_back(void* data) {
    Node* newNode = new Node(data);
    
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

//Метод удаление первого узла
bool MyList::pop_front() {
    if (empty()){
        return false;
    }
    
    Node* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    size--;
    return true;
}

//Метод удаления последнего узла
bool MyList::pop_back() {
    if (empty()){
        return false;
    }
    
    Node* temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    size--;
    return true;
}

//Метод получения первого элемента
void* MyList::get_front() const {
    if (empty()){
        return nullptr;
    }
    return head->data;
}

//Метод получения последнего элемента
void* MyList::get_back() const {
    if (empty()) {
        return nullptr;
    }
    return tail->data;
}

//Метод получения размера списка
size_t MyList::get_size() const {
    return size;
}

//Метод вставки после узла
bool MyList::insert_after(Node *node, void *data) {
    Node* newNode = new Node(data);
    
    if (node == nullptr) {
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
        return true;
    }
    
    Node* current = head;
    while (current != nullptr && current != node) {
        current = current->next;
    }
    
    if (current == nullptr) {
        return false;
    }
    
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != nullptr) {
        current->next->prev = newNode;
    } else {
        tail = newNode;
    }
    current->next = newNode;
    size++;
    return true;
}

//Метод удаления после узла
bool MyList::remove_after(Node *node, void *data) {
    if (empty()) {
        return false;
    }
    
    Node* toRemove;
    
    if (node == nullptr) {
        toRemove = head;
        if (toRemove == nullptr) return false;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
    } else {
        Node* current = head;
        while (current != nullptr && current != node) {
            current = current->next;
        }
        
        if (current == nullptr || current->next == nullptr) {
            return false;
        }
        
        toRemove = current->next;
        current->next = toRemove->next;
        
        if (toRemove->next != nullptr) {
            toRemove->next->prev = current;
        } else {
            tail = current;
        }
    }
    
    delete toRemove;
    size--;
    return true;
}

//Метод поиска
Node* MyList::find(void *data) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

//Получение значения head
Node* MyList::get_head() const {
    return head;
}

void MyList::print(void (*printData)(void *)) {
    Node* current = head;
    
    cout << "[";
    
    while (current != nullptr) {
        printData(current->data);
        current = current->next;
        if (current != nullptr) {
            cout << " ";
        }
    }
    cout << "]" << endl;
}
