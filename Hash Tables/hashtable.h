//  File hashtable.h

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <string>
#include <vector>

using std::string;
using std::vector;


class HashTable {
protected:
    //  Protected data structure used by the hash table
    struct Record {
        string key; //  The key used for uniquely indentifying this record
        int data;   //  The data of interest, here a simple integer
        //  Create a record with the given fields
        Record(const string& k, int d): key(k), data(d) {}
    };

    //  Table of record pointers
    //  Null pointer represents an empty slot
    vector<Record *> table;  

    //  A function intended to be used by insert and find to hash a
    //  string key to a location in the hash table.  This hash
    //  function is initialized by the constructor.  The client
    //  supplies the hash function which must include a collision
    //  resolution strategy.
    int (*hash)(const string&);

    //  A function used to determine which slot to probe next after
    //  each unsuccessful attempt to insert or find an element.
    //  The client supplies this function during construction.
    int (*f)(int);


    //  Locates the position within the table of the record with the
    //  given key.  If the key cannot be found, it probes for the
    //  closest empty slot.  If the key cannot be found and there
    //  are no available slots, the method returns -1.
    //  Clients do not use this protected method
    //  directly.  The insert and find methods use locate
    //  to find the slot they need to process.
    //  Note: This method returns the position of the key, NOT the
    //  key's corresponding data value of interest.
    int locate(const string& s) const;

public:
    //  Creates a hash table of the given size.  
    //  h is a hash function to be used by the insert and find
    //  methods.  
    //  f is a function used to probe for am available slot.
    //  The hash table is initially empty.
    HashTable(unsigned table_size, int (*h)(const string&), int (*f)(int));

    //  Deallocates the space held by the records in 
    //  the hash table.
    virtual ~HashTable();

    //  Inserts the information for a new record into the hash 
    //  table.  If a record with
    //  the same key is already present in the hash table or the
    //  table is full, the method returns false; otherwise, the 
    //  method returns true upon successful insertion.
    //  This function uses the protected locate function to locate
    //  an open position in the hash table.
    bool insert(const string& k, int d);

    //  Returns the data associated with the given key.  If the key
    //  cannot be found, the method returns -1 (valid data will 
    //  be non-negative).
    //  Note: This does NOT return the index of the record within
    //  the table.
    //  This function uses the protected locate function to find
    //  the element within the hash table.
    int find(const string &key) const;

    //  Displays the contents of the hash table for debugging
    //  purposes.
    void dump() const;
};


#endif
