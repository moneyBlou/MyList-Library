#include <iostream>
#include <string>
#include "MyList.h"

using namespace std;

// Структура для хранения информации о студенте
struct Student {
    string lastName;  // Фамилия студента
};

// Структура для хранения информации о группе
struct Group {
    string groupName; // Название группы
    MyList students;  // Список студентов в группе
};

// Функция для вывода информации о студенте
void printStudent(void* data) {
    Student* student = static_cast<Student*>(data);
    cout << student->lastName << " "; // Выводим фамилию студента
}

// Функция для вывода информации о группе
void printGroup(void* data) {
    Group* group = static_cast<Group*>(data);
    cout << "Группа " << group->groupName << ": "; // Выводим название группы
    group->students.print(printStudent);           // Выводим список студентов в группе
    cout << endl;
}

// Функция для поиска группы по имени (вспомогательная)
Group* findGroup(MyList& groupList, const string& groupName) {
    Node* current = nullptr;
    if (!groupList.empty())
         current = static_cast<Node*>(groupList.get_front()); // Получаем первый узел
    while (current != nullptr) {
        Group* group = static_cast<Group*>(current->data); // Получаем данные группы из узла
        if (group->groupName == groupName) {              // Сравниваем названия групп
            return group;                                 // Группа найдена
        }
        current = current->next;                         // Переходим к следующему узлу
    }
    return nullptr;                                     // Группа не найдена
}

int main() {
    MyList groupList; // Список групп
    char addMore;      // Переменная для управления циклом ввода

    do {
        string groupName, lastName; // Переменные для ввода названия группы и фамилии студента
        cout << "Введите название группы: ";    // Запрос на ввод названия группы
        cin >> groupName;                          // Чтение названия группы
        cout << "Введите фамилию студента: "; // Запрос на ввод фамилии студента
        cin >> lastName;                          // Чтение фамилии студента

        Group* group = findGroup(groupList, groupName); // Поиск группы в списке

        if (group == nullptr) {
            // Группа не найдена, создаем новую
            group = new Group;              // Создаем новую группу
            group->groupName = groupName;   // Устанавливаем название группы
            groupList.push_back(group);      // Добавляем группу в список
        }

        // Создаем студента и добавляем его в группу
        Student* student = new Student;    // Создаем нового студента
        student->lastName = lastName;     // Устанавливаем фамилию студента
        group->students.push_back(student); // Добавляем студента в список группы

        cout << "Добавить еще студентов? (y/n): "; // Запрос на добавление еще студентов
        cin >> addMore;                             // Чтение ответа пользователя
    } while (addMore == 'y' || addMore == 'Y');       // Цикл продолжается, пока пользователь вводит 'y' или 'Y'

    cout << "Группы и студенты:" << endl; // Вывод заголовка
    Node* current = nullptr;
    if(groupList.get_front() != nullptr)
        current = static_cast<Node*>(groupList.get_front());

    while (current != nullptr) {
        printGroup(current->data);         // Вывод информации о группе
        current = current->next;            // Переход к следующему узлу
    }


    // Освобождение памяти (упрощенное, без использования find)
    while (!groupList.empty()) {
        Node* nodeToDelete = static_cast<Node*>(groupList.get_front()); // explicit cast
        Group* group = static_cast<Group*>(nodeToDelete->data);

        while (!group->students.empty()) {
            Student* student = static_cast<Student*>(group->students.get_front());
            group->students.pop_front();
            delete student;
        }

        groupList.pop_front();
        delete group;
    }

    return 0;
}
