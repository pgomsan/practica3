#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
private:
    int nelem;
    BSNode<T>* root;
    
    BSNode<T>* search(BSNode<T>* n, T e) const;
    BSNode<T>* insert(BSNode<T>* n, T e);
    BSNode<T>* remove(BSNode<T>* n, const T& e);
    T max(BSNode<T>* n) const;
    BSNode<T>* remove_max(BSNode<T>* n);
    void print_inorder(std::ostream& out, BSNode<T>* n) const;
    void delete_cascade(BSNode<T>* n);       

public:
    // Constructor
    BSTree() : root(nullptr), nelem(0) {}

    // Destructor
    ~BSTree() {
        delete_cascade(root);
    }

    // Tamaño del árbol
    int size() const {
        return nelem;
    }

    // Búsqueda
    T search(T e) const {
        BSNode<T>* result = search(root, e);
        return result->elem;
    }

    // Insertar
    void insert(T e) {
        root = insert(root, e);
    }

    // Eliminar
    void remove(T e) {
        root = remove(root, e);
    }

    // Sobrecarga operador <<
    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }

    T operator[](T e) const {
        return search(e);
    }
};

// Implementación de los métodos
template<typename T>
BSNode<T>* BSTree<T>::search(BSNode<T>* n, T e) const {
    if (n == nullptr) {
        throw std::runtime_error("Elemento no encontrado en el árbol");
    } else if (e < n->elem) {
        return search(n->left, e);
    } else if (e > n->elem) {
        return search(n->right, e);
    } else {
        return n;
    }
}

template<typename T>
BSNode<T>* BSTree<T>::insert(BSNode<T>* n, T e) {
    if (n == nullptr) {
        ++nelem;
        return new BSNode<T>(e);
    } else if (e == n->elem) {
        throw std::runtime_error("Elemento duplicado en el árbol");
    } else if (e > n->elem) {
        n->right = insert(n->right, e);
    } else if (e < n->elem) {
        n->left = insert(n->left, e);
    }
    return n;
}

template<typename T>
void BSTree<T>::print_inorder(std::ostream& out, BSNode<T>* n) const {
    if (n != nullptr) {
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }
}

template<typename T>
BSNode<T>* BSTree<T>::remove(BSNode<T>* n, const T& e) {
    if (n == nullptr) {
        throw std::runtime_error("Elemento no encontrado");
    }
    if (e < n->elem) {
        n->left = remove(n->left, e);
    } else if (e > n->elem) {
        n->right = remove(n->right, e);
    } else {
        if (n->left == nullptr && n->right == nullptr) {
            delete n;
            --nelem;
            return nullptr;
        } else if (n->left == nullptr) {
            BSNode<T>* temp = n->right;
            delete n;
            --nelem;
            return temp;
        } else if (n->right == nullptr) {
            BSNode<T>* temp = n->left;
            delete n;
            --nelem;
            return temp;
        } else {
            n->elem = max(n->left);
            n->left = remove_max(n->left);
        }
    }
    return n;
}

template <typename T>
T BSTree<T>::max(BSNode<T>* n) const {
    if (n->right == nullptr) {
        return n->elem;
    }
    return max(n->right);
}

template <typename T>
BSNode<T>* BSTree<T>::remove_max(BSNode<T>* n) {
    if (n->right == nullptr) {
        BSNode<T>* temp = n->left;
        delete n;
        --nelem;
        return temp;
    }
    n->right = remove_max(n->right);
    return n;
}

template <typename T>
void BSTree<T>::delete_cascade(BSNode<T>* n) {
    if (n != nullptr) {
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }
}
/*
void print_postorder(std::ostream &out, BSNode<T>* node) const {
    if (node == nullptr) return; // Caso base
    print_postorder(out, node->left); // Recorre subárbol izquierdo
    print_postorder(out, node->right); // Recorre subárbol derecho
    out << node->elem << " "; // Imprime el nodo actual
}

void print_postorder(std::ostream &out) const {
    print_postorder(out, root); // Llama a la versión privada
}
*/

/*
int depth(BSNode<T>* node) const {
    if (node == nullptr) return 0; // Caso base
    return 1 + std::max(depth(node->left), depth(node->right)); // Calcula la profundidad recursivamente
}

int depth() const {
    return depth(root); // Llama a la versión privada
}
*/

/*
// Cálculo de la altura del árbol
template <typename T>
int BSTree<T>::height(BSNode<T>* n) const {
    if (n == nullptr) {
        return -1; // Un árbol vacío tiene altura -1
    }
    int leftHeight = height(n->left);
    int rightHeight = height(n->right);
    return 1 + std::max(leftHeight, rightHeight);
}

int height() const {
    return height(root);
}
Implementa un método `loadFactor()` en `HashTable` que calcule el factor de carga de la tabla.

**Respuesta:**
```cpp
// Factor de carga
// Formula: loadFactor = número de elementos / número de cubetas

double loadFactor() const {
    return static_cast<double>(n) / max;
}

// Verifica si el árbol está balanceado
// Un árbol está balanceado si la diferencia de alturas entre
// los subárboles izquierdo y derecho de cada nodo es como máximo 1

template <typename T>
bool BSTree<T>::isBalanced(BSNode<T>* n) const {
    if (n == nullptr) return true;

    int leftHeight = height(n->left);
    int rightHeight = height(n->right);

    return std::abs(leftHeight - rightHeight) <= 1
        && isBalanced(n->left)
        && isBalanced(n->right);
}

bool isBalanced() const {
    return isBalanced(root);
}

// Obtiene las claves en orden ascendente

// Método privado recursivo
template <typename T>
void BSTree<T>::getKeysInOrder(BSNode<T>* n, std::vector<T>& keys) const {
    if (n != nullptr) {
        getKeysInOrder(n->left, keys);
        keys.push_back(n->elem);
        getKeysInOrder(n->right, keys);
    }
}

2. Implementa esta funcionalidad en `BSTreeDict`:
```cpp
std::vector<std::string> getKeysInOrder() {
    std::vector<TableEntry<V>> entries = tree->getKeysInOrder();
    std::vector<std::string> keys;
    for (const auto& entry : entries) {
        keys.push_back(entry.key);
    }
    return keys;
}
```

#### **5. Integración y análisis en `BSTreeDict`**
**Pregunta:**
Implementa una función llamada `merge` en `BSTreeDict` que tome como parámetro otro diccionario de tipo `BSTreeDict` y combine sus elementos con el diccionario actual. Si hay claves duplicadas, debe prevalecer el valor del diccionario que invocó el método.

**Respuesta:**
```cpp
// Fusiona dos BSTreeDict
// En caso de conflicto de claves, prevalece el valor del diccionario original

void merge(const BSTreeDict<V>& other) {
    std::vector<TableEntry<V>> otherEntries = other.tree->getKeysInOrder();

    for (const auto& entry : otherEntries) {
        try {
            this->insert(entry.key, entry.value);
        } catch (...) {
            // Si la clave ya existe, ignorar
        }
    }
}
```




*/

#endif
