//  File test_hashtable.cpp

#include <iostream>
#include "hashtable.h"

//using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;

//  Adjust as you like
const int TABLE_SIZE = 13;

//  NOT a good hash function!
int hash(const string& s) {
    return s.length() % TABLE_SIZE;
}

int f(int i) {
    return i;  //  Linear probing
}

int main() {
    HashTable ht(TABLE_SIZE, hash, f);
    bool done = false;
    string key;
    char command;
    int data;
    cout << "I)nsert F)ind H)elp Q)uit" << endl;
    while (!done) {
        cin >> command;
        switch (command) {
           case 'I':
           case 'i':
               cin >> key >> data;
               if (!ht.insert(key, data))
                   cout << "Could NOT insert <" 
                        << key << "," 
                        << data << ">" << endl;
               break;
           case 'F':
           case 'f':
               cin >> key;
               data = ht.find(key);
               if (data != -1)
                   cout << data << endl;
               else
                   cout << "Not found" << endl;
               break;
           case 'D':
           case 'd':
               ht.dump();
               break;
           case 'H':
           case 'h':
           case '?':
               cout << "I)nsert F)ind H)elp Q)uit";
               break;
           case 'Q':
           case 'q':
               done = true;
               break;
        }
    }
}
