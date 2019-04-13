#include <iostream>
#include <stdlib.h>
#include <time.h>
#define TAM 52

#include "Node.h"

using namespace std;

template <class T>
class Pilha{

	private:
		int tam;
		Node<T>* topo;

	public:
		Pilha(T parametro){
			Node<T> *aux = new Node<T>(parametro);
		    this->tam = 1;
		    this->topo = aux;
		};
		Pilha(){
			this->topo = NULL;
		    this->tam = 0;
		}
		bool empilha(T elemento){
			Node<T> *aux = new Node<T>(elemento);
		
		    if(aux == NULL){
		        return false;
		    }else{
		        aux->next = topo;
		        topo = aux;
		        tam++;
		        aux = NULL;
		    }
		}
		bool desempilha(T &elemento){
			if(topo == NULL){
		    	return false;
			}else{
		        Node<T> *aux = topo; 
		        elemento = topo->info; 
		        topo = topo->next; 
		        tam--;
		        delete(aux);
		    }
		}
		bool vazia() const{
			if(this->topo == NULL)
				return true;
			else
				return false;

		}
		bool cheia() const{
			Node<T> *aux = new Node<T>();
		
		    if(aux = NULL){
		        delete(aux);
		        return true;
		    }else{
		        delete(aux);
		        return false;
		    }
		}
		T elementoDoTopo(bool &DeuCerto){
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
		Node<T>* getTopo() const{
			return topo;
		}
		int getTam() const{
			return this->tam;
		}
		bool transfereElementosPara(Pilha &p){
			if(p.cheia() || this->getTam() > p.getTam())
				return false;
			else{
				T elemento;
				while(!this->vazia()){
					this->desempilha(elemento);
					p.empilha(elemento);
				}
				return true;
			}
		}
		bool maisElementosQue(Pilha &p){
			int qtdP1=0,qtdP2=0;
			Pilha <T> pilhaAux1(this->getTam());
			Pilha <T> pilhaAux2(p.getTam());
			T elemento;
		
			while(!this->Vazia()){
				this->desempilha(elemento);
				pilhaAux1.empilha(elemento);
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
		bool temElementoIgual(T elemento){
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
		bool ehIgual(Pilha &p){
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
		Pilha* embaralha(){
			int j = this->getTam();
			
		    T vetor [j] ;
		    int l = j;
		    T temp;
		    Pilha <T> * aux = new Pilha();
		
		    int i=0;
		
		    while (!this->vazia()){
		    	
		        desempilha(temp);
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
		void quantidadeDeElementos(int &num){
			Pilha<T> aux;
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
		void desempilhaTudo(){
			T temp;
			while(!this->vazia()){
				this->desempilha(temp);
			}
		}
};


