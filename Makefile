bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: testHashtable.cpp HashTable.h Dict.h TableEntry.h
	mkdir -p bin
	g++ -o bin/testHashtable testHashtable.cpp

clean:
	rm -rf *.o *.gch bin
