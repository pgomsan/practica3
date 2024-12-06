#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../practica1/listlinked.h"  // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	int h(std::string key){
		
		int sum;
		int resto;
		int a;
		char c;
		for(int i=0; i<key.length(); i++){
			c=key.at(i);
			a= int(c);
			sum+=a;
		}
		resto= sum%max;

		return resto;
	}

    public:
        HashTable(int size){
		max = size;                 
        	n = 0;                     
        	table = new ListLinked<TableEntry<V>>[max];       
        	for (int i = 0; i < max; ++i) {
            		table[i] = nullptr;   
        	}	
	}
        ~HashTable(){
		delete[] table;
	}
	int capacity(){
		return max;
	}
	friend std::ostream& operator << (std::ostream &out, const HashTable <V> &th){
	        for (int i = 0; i < th.max; ++i) {
            out << "Cubeta " << i << ": ";
            if (th.table[i].empty()) {
                out << "vacía";
            } else {
                th.table[i].first();  // Apunta al primer elemento de la lista
                while (!th.table[i].finished()) {
                    out << th.table[i].retrieve() << " ";  // Imprime el valor del nodo actual
                    th.table[i].next();  // Mueve al siguiente nodo
                }
            }
            out << std::endl;
        }
        return out;
	}
	V operator [] (std::string key){
	int index = h(key);  // Obtener el índice de la cubeta
        ListLinked<TableEntry<V>> &cubeta = table[index];  // Acceder a la lista enlazada correspondiente

        // Buscar la clave en la cubeta
        cubeta.first();  // Apuntar al primer nodo
        while (!cubeta.finished()) {
            TableEntry<V> entry = bucket.retrieve();
            if (entry.getKey() == key) {
                return entry.getValue();  // Devolver el valor asociado si se encuentra la clave
            }
            bucket.next();  // Moverse al siguiente nodo
        }

        // Si no se encuentra la clave, lanzar excepción
        throw std::runtime_error("Clave no encontrada en la tabla hash.");
	}

        
};

#endif
