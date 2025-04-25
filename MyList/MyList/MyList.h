#pragma once
#include <cstddef>

struct Node {
    void* data;
    Node* next;
    Node* prev;
    
    Node(void* data);
};

class MyList {
private:
    Node* head;
    Node* tail;
    int size;
public:
    //Конструктор и деструктор
    MyList();
    ~MyList();
    
    //Методы добавления
    void push_front(void* data);
    void push_back(void* data);
    
    //Методы удаления
    bool pop_front();
    bool pop_back();
    
    //Методы для получения элементов
    void* get_front() const;
    void* get_back() const;
    
    //Методы для получения информации о списке
    bool empty() const;
    size_t get_size() const;
    
    //Метод для очищения списка
    void clear();
    
    //Методы вставки
    bool insert_after(Node* node, void* data);
    bool remove_after(Node* node, void* data);
    
    //Метод поиска
    Node* find(void* data);
    
    //Доп методы доступа
    Node* get_head() const;
    
    //Метод вывода
    void print(void (*printData)(void* data));
};
