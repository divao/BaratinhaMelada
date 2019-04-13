#include <iostream>
#include <stdlib.h>
#include <time.h>
#define TAM 52

using namespace std;

template <typename T>
class Node{

        public:
            T info;
            Node* next;


            Node(T info, Node* next){
                this->info = info;
                this->next = next;
            }

            Node(T info){
                this->info = info;
                this->next = NULL;
            }
            Node(){
                this->next = NULL;
            }
};
