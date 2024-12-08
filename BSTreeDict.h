#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:
    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor
    ~BSTreeDict() {
        delete tree;
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
        out << *(bs.tree);
        return out;
    }

    // Sobrecarga del operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Insertar un elemento
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    // Buscar un elemento
    V search(std::string key) override {
        TableEntry<V> entry(key);
        try {
            TableEntry<V> result = tree->search(entry);
            return result.value;
        } catch (const std::runtime_error& e) {
            throw std::runtime_error("Clave no encontrada: " + key);
        }
    }

    // Eliminar un elemento
    V remove(std::string key) override {
        TableEntry<V> entry(key);
        try {
            TableEntry<V> result = tree->search(entry);
            tree->remove(entry);
            return result.value;
        } catch (const std::runtime_error& e) {
            throw std::runtime_error("Clave no encontrada: " + key);
        }
    }

    // Número de entradas
    int entries() override {
        return tree->size();
    }
};

#endif

