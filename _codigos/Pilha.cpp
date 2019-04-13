#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Pilha.h"
#define TAM 52

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

using namespace std;

template <class T>
Pilha<T>::Pilha(unsigned int tam){
	this->tam = tam;
	this->topo = -1;
	pilhaPtr = new T[this->tam];
}

template <class T>
Pilha<T>::Pilha(){
	this->tam = TAM;
	this->topo = -1;
	pilhaPtr = new T[this->tam];
}

template <class T>
Pilha<T>::~Pilha(){
	delete [] pilhaPtr;
}

template <class T>
bool Pilha<T>::empilha(T elemento){
	if(this->cheia())
		return false;
	else{
		this->topo = this->getTopo() + 1;
		this->pilhaPtr[this->getTopo()] = elemento;
		return true;
	}
}

template <class T>
bool Pilha<T>::desempilha(T &elemento){
	if(this->vazia())
		return false;
	else{
		elemento = this->pilhaPtr[this->getTopo()];
		this->topo = this->getTopo() - 1;
		return true;
	}
}

template <class T>
bool Pilha<T>::vazia() const{
	if(this->getTopo() == -1)
		return true;
	else
		return false;
}

template <class T>
bool Pilha<T>::cheia() const{
	if(this->getTopo() == (this->getTam() -1))
		return true;
	else
		return false;
}

template <class T>
T Pilha<T>::elementoDoTopo(bool &DeuCerto){
	if(this->Vazia())
		DeuCerto = false;
	else{
		T elemento;
		this->Desempilha(elemento);
		this->Empilha(elemento);
		DeuCerto = true;
		return elemento;
	}
}

template <class T>
int Pilha<T>::getTopo()const{
	return this->topo;
}

template <class T>
int Pilha<T>::getTam() const{
	return this->tam;
}

template <class T>
bool Pilha<T>::transfereElementosPara(Pilha &p){
	if(p.Cheia() || this->getTam() > p.getTam())
		return false;
	else{
		T elemento;
		while(!this->Vazia()){
			this->Desempilha(elemento);
			p.Empilha(elemento);
		}
		return true;
	}
}

template <class T>
bool Pilha<T>::maisElementosQue(Pilha &p){
	int qtdP1=0,qtdP2=0;
	Pilha <T> pilhaAux1(this->getTam());
	Pilha <T> pilhaAux2(p.getTam());
	T elemento;

	while(!this->Vazia()){
		this->Desempilha(elemento);
		pilhaAux1.Empilha(elemento);
		qtdP1++;
	}

	while(!pilhaAux1.Vazia()){
		pilhaAux1.Desempilha(elemento);
		this->Empilha(elemento);
	}

	while(!p.Vazia()){
		p.Desempilha(elemento);
		pilhaAux2.Empilha(elemento);
		qtdP2++;
	}

	while(!pilhaAux2.Vazia()){
		pilhaAux2.Desempilha(elemento);
		p.Empilha(elemento);
	}

	return qtdP1 > qtdP2;
}

template <class T>
bool Pilha<T>::temElementoIgual(T elemento){
	bool tem = false;
	Pilha<T> pilhaAux(this->getTam());
	T aux;

	while(!this->Vazia() && !tem){
		this->Desempilha(aux);
		pilhaAux.Empilha(aux);

		if(aux == elemento)
			tem = true;

	}

	while(!pilhaAux.Vazia()){
		pilhaAux.Desempilha(aux);
		this->Empilha(aux);
	}

	return tem;

}

template <class T>
bool Pilha<T>::ehIgual(Pilha &p){
	if(this->Vazia() && p.Vazia())
		return true;

	if(this->getTopo() == p.getTopo()){

		Pilha <T> pilhaAux1(this->getTam());
		Pilha <T> pilhaAux2(p.getTam());
		bool igual = true, DeuCerto1,DeuCerto2;
		T elemento;



		while(igual && !this->Vazia() && !p.Vazia()){
			this->Desempilha(elemento);
			pilhaAux1.Empilha(elemento);

			p.Desempilha(elemento);
			pilhaAux2.Empilha(elemento);

			if(pilhaAux1.ElementoDoTopo(DeuCerto1) == pilhaAux2.ElementoDoTopo(DeuCerto2)){
				igual = true;
			}else{
				igual = false;
			}
		}

		while(!pilhaAux1.Vazia()){
			pilhaAux1.Desempilha(elemento);
			this->Empilha(elemento);
		}

		while(!pilhaAux2.Vazia()){
			pilhaAux2.Desempilha(elemento);
			p.Empilha(elemento);
		}

		return igual;
	}else{
		return false;
	}
}

template <class T>
void Pilha <T>::quantidadeDeElementos(int &num){
    Pilha<T> aux(this->getTam());
    T temp;
    int cont;
    num =0;
    while(!this->vazia()){
        this->desempilha(temp);
        aux.empilha(temp);
        num++;
    }

    while(!aux.vazia()){
        aux.desempilha(temp);
        this->empilha(temp);
    }

}


template <class T>
Pilha<T>* Pilha<T>::embaralha(){
	
	int j ;
	this->quantidadeDeElementos(j);
	
    T vetor [j] ;
    int l = j;
    T temp;
    Pilha <T> * aux = new Pilha(this->getTam());

    int i=0;


    while(!this->vazia()){
    	
        this->desempilha(temp);
        vetor [i] = temp;
        i++;
    }
	
	srand(time(NULL));
	
    for(int i=0; i < j; i++){
    	int r= rand() % l;
    	aux->empilha(vetor[r]);
    	
    	vetor[r] = vetor[l-1];
    	l--;
	}

	return aux;
}

template <class T>
void Pilha<T>::desempilhaTudo(){
	T temp;
	while(!this->vazia()){
		this->desempilha(temp);
	}
	
}

