#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry {
    public:
	    std::string key;
	    V value;

	    TableEntry(std::string key, V value): key(key), value(value){} //constructor

	    TableEntry(std::string key): key(key), value(V{}) {}  //Entrada solo con clave
	
            TableEntry():key(""), value(V{}) {} //Entrada sin clave y sin valor

	    //Sobrecarga del operador ==
	    friend bool operator == (const TableEntry<V> &te1, const TableEntry<V> &te2){
	    	return te1.key == te2.key;
	    } 
	    
	    //Sobrecarga del operador !=
	    friend bool operator !=(const TableEntry<V> &te1, const TableEntry<V> &te2){
	    	return !(te1 == te2);
	    }

	    // Sobrecarga del operador <<
	    friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te){
		out << "('" << te.key << "' =>  " << te.value<<")";
        	return out;
	}
	   //sobrecarga operador <
	   friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){
	   	return te1.key < te2.key;
	   }

	   //sobrecarga operador >
	   friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){
	   	return te1.key > te2.key;
	   }
};

#endif
