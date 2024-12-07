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

#endif
