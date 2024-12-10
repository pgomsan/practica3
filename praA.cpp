#include<iostream>
#include "HashTable.h"

int main()
{
	HashTable<int> tabla_hash = HashTable<int>(3);
	std::cout << "-HASH TABLE created, capacity: " << tabla_hash.capacity() << std::endl;
	
	std::cout << "\n\n-INSERTS:" << std::endl; 
	std::string s_key = "aaa";
	int val = 0;
	try
	{
		tabla_hash.insert(s_key, val);
		std::cout << "  Key " << s_key << " -> " << val << " inserted" << std::endl;
	} catch(std::runtime_error &e)
	{
		std::cout << "	Wrong insertion of aaa, 0" << std::endl;
	}
	s_key = "aba";
	val = 1;
 	try
	{
		tabla_hash.insert(s_key, val);
		std::cout << "  Key " << s_key << " -> " << val << " inserted" << std::endl;
	} catch(std::runtime_error &e)
	{
                std::cout << "	Wrong insertion of aba, 0" << std::endl;
	}
	s_key = "aab";
        val = 2;
        try
	{
		tabla_hash.insert(s_key, val);
		std::cout << "  Key " << s_key << " -> " << val << " inserted" << std::endl;
	} catch(std::runtime_error &e)
	{
                std::cout << "	Wrong insertion of aab, 0" << std::endl;
	}
	
	std::cout << "\n\n-PRINT HASH:" << std::endl;
	std::cout << " *Tabla Hash: " << std::endl;
	std::cout << tabla_hash;
	std::cout << " *Number of reg: " << tabla_hash.entries() << std::endl;

	std::cout << "\n\n-SEARCH:" << std::endl;
	s_key = "aaa";
	try
	{
        	val = tabla_hash.search(s_key);
		std::cout << "  Key " << s_key << " FOUND: " << val << std::endl;
	} catch(std::runtime_error &e)
	{
		std::cout << "  Key "<< s_key << " NOT FOUND" << std::endl;
	}
	s_key = "aab";
	try
	{
		val = tabla_hash.search(s_key);
		std::cout << "  Key " << s_key << " FOUND: " << val << std::endl;
	} catch(std::runtime_error &e)
	{
		std::cout << "  Key "<< s_key << " NOT FOUND" << std::endl;
	}
	s_key = "aba";
        try
	{
		val = tabla_hash.search(s_key);
		std::cout << "  Key " << s_key << " FOUND: " << val << std::endl;
	} catch(std::runtime_error &e)
	{
		std::cout << "  Key "<< s_key << " NOT FOUND" << std::endl;
	}

	std::cout << "\n\n-REMOVE:\n\n" << std::endl;
	s_key = "aab";
        try
	{
		val = tabla_hash.remove(s_key);
		std::cout << "  Key " << s_key << " REMOVED: " << val << std::endl;
	} catch(std::runtime_error &e)
	{
		std::cout << "  Key "<< s_key << " NOT FOUND" << std::endl;
	}

	std::cout << "\n\n-PRINT HASH:" << std::endl;
        std::cout << " *Tabla Hash: " << std::endl;
        std::cout << tabla_hash;
        std::cout << " *Number of reg: " << tabla_hash.entries() << std::endl;

	s_key = "aaa";
        try
	{
		val = tabla_hash.remove(s_key);
		std::cout << "  \n\nKey " << s_key << " REMOVED: " << val << std::endl;
	} catch(std::runtime_error &e)
	{
		std::cout << "  \n\nKey "<< s_key << " NOT FOUND" << std::endl;
	}
	std::cout << "\n\n-PRINT HASH:" << std::endl;
	std::cout << " *Tabla Hash: " << std::endl;
	std::cout << tabla_hash;
	std::cout << " *Number of reg: " << tabla_hash.entries() << std::endl;

	s_key = "aba";
	try
	{
		val = tabla_hash.remove(s_key);
		std::cout << "  \n\nKey " << s_key << " REMOVED: " << val << std::endl;
	} catch(std::runtime_error &e)
	{
		std::cout << "  \n\nKey "<< s_key << " NOT FOUND" << std::endl;
	}
	std::cout << "\n\n-PRINT HASH:" << std::endl;
	std::cout << " *Tabla Hash: " << std::endl;
	std::cout << tabla_hash;
	std::cout << " *Number of reg: " << tabla_hash.entries() << std::endl;

	return 0;
}
