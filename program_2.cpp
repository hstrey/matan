#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include <new>

using namespace std;

template <typename T>
class SimpleList{
private:
    
    string name;
    struct node{
        T data;
        node* next;
    };

    node *head, *tail;

public:
    
    SimpleList(string n){
        name = n;
        head = new struct node;
        head->next = nullptr;
        tail = head;
    }
    string getname(){
        return name;
    }

    void insert_end(T value){
        struct node* newnode = new struct node;
        tail->next = newnode;
        newnode->next = nullptr;
        newnode->data = value;
        tail = newnode;

    }

    void insert_begin(T value){
        struct node* newnode = new struct node;
        head->data = value;
        newnode->next = head;
        head = newnode;
    }

    T pop(){
        struct node* temp = head;
        head = head->next;
        delete temp;
        return head->data;
    }
    
};




template <typename T>
class Stack : public SimpleList<T>{
public:
    Stack (string name) : SimpleList<T>(name) {}
    
    void push(T value){
        this->insert_begin(value);
    }
};

template <typename T>
class Queue : public SimpleList<T>{
public:
    Queue (string name) : SimpleList<T>(name) {}
    
    void push(T value){
        this->insert_end(value);
    }

};

template<typename T>
SimpleList<T>* search(list<SimpleList<T> *> &listSL, string list_name){
    for (auto i = listSL.begin(); i != listSL.end(); i++){
        if ((*i)->getname() == list_name){
            return *i;
        }
    }
    return nullptr;
    
}




int main(){

    list<SimpleList<int> *> listSLi;
    list<SimpleList<double> *> listSLd;
    list<SimpleList<string> *> listSLs;

    string myText;

    ifstream MyReadFile("commands1.txt");

    string command, name, value;

    string command_temp, name_temp, value_temp;

    while (getline (MyReadFile, myText)) {
        stringstream ss(myText);
        ss >> command >> name >> value;
        char type = name[0];
        cout << myText << endl;

        if (command == "create"){
            if (type == 'i'){
                if (search(listSLi, name) == nullptr){
                    cout << "PROCESSING COMMAND: " << myText << endl;
                    SimpleList<int> *pSLi;
                    if (value == "stack"){
                        pSLi = new Stack<int>(name);
                    }
                    else{
                        pSLi = new Queue<int>(name);
                    }
                }
                else{
                    cout << "this list is empty!" << endl;
                }
            }
            else if (type == 'd'){
                if (search(listSLd, name) == nullptr){
                    cout << "PROCESSING COMMAND: " << myText << endl;
                    SimpleList<double> *pSLd;
                    if (value == "stack"){
                        pSLd = new Stack<double>(name);
                    }
                    else{
                        pSLd = new Queue<double>(name);
                    }
                }
            }
            else if (type == 's'){
                if (search(listSLs, name) == nullptr){
                    cout << "PROCESSING COMMAND: " << myText << endl;
                    SimpleList<string> *pSLs;
                    if (value == "stack"){
                        pSLs = new Stack<string>(name);
                    }
                    else{
                        pSLs = new Queue<string>(name);
                    }
                }
            }
            else{
                cout << "LIST ALREADY EXISTS" << endl;
            }
        }
    }


    
    MyReadFile.close();

}    