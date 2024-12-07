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

#endif
