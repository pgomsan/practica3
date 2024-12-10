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
		int sum = 0;
       	 	for (char c : key) {
            		sum += static_cast<int>(c);
        	}

        	return sum % max;
	}

    public:
        HashTable(int size){
		max = size;                 
        	n = 0;                     
        	table = new ListLinked<TableEntry<V>>[max];       	
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
                out << th.table[i];
            }
            out << std::endl;
        }
        return out;
	}

// Implementación del método insert
    void insert(std::string key, V value) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];

        for (int i = 0; i < bucket.size(); ++i) {
            TableEntry<V> entry = bucket.get(i);
            if (entry.key == key) {
                throw std::runtime_error("Clave ya existente en la tabla hash.");
            }
        }

        bucket.append(TableEntry<V>(key, value));
        ++n;
    }

    // Implementación del método search
    V search(std::string key) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];

        for (int i = 0; i < bucket.size(); ++i) {
            TableEntry<V> entry = bucket.get(i);
            if (entry.key == key) {
                return entry.value;
            }
        }

        throw std::runtime_error("Clave no encontrada en la tabla hash.");
    }

    // Implementación del método remove
    V remove(std::string key) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];

        for (int i = 0; i < bucket.size(); ++i) {
            TableEntry<V> entry = bucket.get(i);
            if (entry.key == key) {
                V value = entry.value;
                bucket.remove(i);
                --n;
                return value;
            }
        }

        throw std::runtime_error("Clave no encontrada en la tabla hash.");
    }

    // Devuelve el número de entradas en la tabla
    int entries() override {
        return n;
    }

	V operator [] (std::string key){
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];

        for (int i = 0; i < bucket.size(); ++i) {
            TableEntry<V> entry = bucket.get(i);
            if (entry.key == key) {
                return entry.value;
            }
        }

        throw std::runtime_error("Clave no encontrada en la tabla hash.");
	}

        
};

/*
// Devuelve todas las claves almacenadas en la tabla
std::vector<std::string> export_keys() {
    std::vector<std::string> keys; // Vector para almacenar las claves
    for (int i = 0; i < max; ++i) { // Recorre todas las cubetas
        for (int j = 0; j < table[i].size(); ++j) { // Recorre cada lista enlazada
            keys.push_back(table[i].get(j).key); // Obtiene la clave y la añade al vector
        }
    }
    return keys; // Devuelve el vector de claves
}

// Calcula y devuelve el factor de carga
double load_factor() {
    return static_cast<double>(n) / max; // n = número de elementos, max = número de cubetas
}


*/




#endif
