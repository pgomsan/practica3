#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
       BSTreeDict(){
       	tree = new BSTree<TableEntry<V>>[];
       }

       ~BSTreeDict(){
       	delete[] tree;
       }

       friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
	        for (int i = 0; i < bs.nelem; ++i) {
                out << bs.tree[i];
            }
            out << std::endl;
        }
        return out;
	}
       }

       V operator[](std::string key){
       		return search(key);
       }
       
       void insert(std::string key, V value) override {

       }

	V search(std::string key) override {
	
	}

	V remove(std::string key) override {
	
	}

	int entries() override {
	}
};	

#endif
