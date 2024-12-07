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
	
	BSNode<T>* search(BSNode<T>* n, T e)const;
	BSNode<T>* insert(BSNode<T>* n, T e);
	BSNode<T>* remove(BSNode<T>* n, const T& e);
	T max(BSNode<T>* n) const;
	BSNode<T>*remove_max(BSNode<T>* n);
	void print_inorder(std::ostream& out, BSNode<T>* n)const;
	void delete_cascade(BSNode<T>* n);       


    public:
        //Constructor
       BSTree() : root(nullptr), nelem(0) {}

       //Destructor
       ~BSTree(){
	       delete_cascade(root);
       }

       // Tamaño del arbol
       int size() const{
	       return nelem;
       }

       //Busqueda
       T search(T e)const{
	       BSNode<T>* result = search(root, e);
	       return result.elem;
       }

       //Insertar
       void insert(T e){
	       root = insert(root, e);
       }

       //Quitar
       void remove(T e){
	       root = remove(root, e);

       }

       // Sobrecarga operador <<
       friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst){
	       bst.print_inorder(out, bst.root);
	       return out;
       }

       T operator[](T e)const{
	       return search(e);
	      }
    
};


	//Busqueda
	template<typename T>
	BSNode<T>* BSTree<T>::search(BSNode<T>* n, T e) const{
		if(n == nullptr){
			throw std::runtime_error("Elemento no encontrado en el árbol");
		}
		else if (e < n.elem) {
			return search(n.left, e);
		}
		else if (e > n.elem){
			return search(n.right, e);
		}
		else{
			return n;
		}
	}
	
	//Añadir
	template<typename T>
	BSNode<T>* BSTree<T>::insert(BSNode<T>* n, T e){
		if(n==NULL){
			++nelem;
			return new BSNode<T>(e);
		}
		 else if (e == n.elem) {
			throw std::runtime_error("Elemento duplicado en el árbol");
                }
                else if (e > n.elem){
                        n.right = insert(n.right, e);
                }
		else if (e < n.elem){
                        n.left = insert(n.left, e);
                }
		
		return n;
	
	}

	//Impresion en orden
	template<typename T>
	void BSTree<T>::print_inorder(std::ostream &out, BSNode<T>* n) const{
		if(n != NULL){
			print_inorder(out, n.left);
        		out << n.elem << " ";
        		print_inorder(out, n.right);
		}
	}

	//Eliminacion
	template<typename T>
	BSNode<T>* BSTree<T>::remove(BSNode<T>* n, const T& e){
			if(n==NULL){
				throw std::runtime_error("Elemento no encontrado");
			}
			if (e < n.elem) {
       				n.left = remove(n.left, e);
    			} else if (e > n.elem) {
        			n.right = remove(n.right, e);
    			} else {
        			// Nodo encontrado
        			if (n.left == NULL && n.right == NULL) {
            				delete n;
            				--nelem;
            				return NULL;
        			} else if (n.left == NULL) {
            				BSNode<T>* temp = n.right;
            				delete n;
            				--nelem;
            				return temp;
        			} else if (n.right == NULL) {
         	   			BSNode<T>* temp = n.left;
            				delete n;
            				--nelem;
            				return temp;
        			} else {
            				n.elem = max(n.left);
            				n.left = remove_max(n.left);
        			}
    			}	
   			return n;	
		}

	//Maximo de una rama
	template <typename T>
	T BSTree<T>::max(BSNode<T>* n) const {
    		if (n.right == NULL) {
        		return n.elem;
    		}
    			return max(n.right);
		}


	//Elimina el máximo en el subarbol

	template <typename T>
	BSNode<T>* BSTree<T>::remove_max(BSNode<T>* n) {
    		if (n->right == NULL) {
        		BSNode<T>* temp = n.left;
        		delete n;
        		--nelem;
        		return temp;
    		}
    			n.right = remove_max(n.right);
    			return n;
	}

	//Destruccion
	template <typename T>
	void BSTree<T>::delete_cascade(BSNode<T>* n) {
    		if (n != NULL) {
        		delete_cascade(n.left);
        		delete_cascade(n.right);
        		delete n;
    		}
	}











#endif
