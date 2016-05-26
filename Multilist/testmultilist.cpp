//  File testmultilist.cpp

#include <iostream>
#include "multilist.h"

using namespace std;

//  Interactive program useful for experimenting with the
//  Multilist 3-way, doubly-linked list class.

int main() {
    Multilist list;
    bool done = false;
    int id, age;
    char command;
    string name;
    while (!done) {
			cout <<	"COMMANDS:\n'+' = insert new person data\n";
			cout << "'-' = remove a person by ID number\n";
			cout << "'n' =   Print contents in name order\n";
			cout << "'N' =   Print contents in reverse name order\n";
			cout << "'i' =   Print contents in ID number order\n";
			cout << "'I' =   Print contents in reverse ID number order\n";
			cout << "'a' =   Print contents in age order\n";
			cout << "'A' =   Print contents in reverse age order\n";
			cout << "'Q'/'q' = quit program\n";
        cin >> command;
        switch (command) {
           case '+':   //  Insert new person data
			   cout << "INPUT DATA: ID, NAME, AGE\n";
               cin >> id >> name >> age;
               cout << "Inserting " << id << ", " << name
                    << ", " << age << endl;
               if ( !list.insert(id, name, age) )
                   cout << "Cannot insert " << name << endl;
               break;
           case '-':   //  Remove a person by ID number
               cin >> id;
               cout << "Removing " << id << endl;
               if ( !list.remove(id) )
                   cout << "Cannot remove " << id << endl;
               break;
           case 'n':  //  Print contents in name order
               cout << "Printing by name " << endl;
               list.print_by_name();
               break;
           case 'N':  //  Print contents in reverse name order
               cout << "Printing by name reverse " << endl;
               list.print_by_name_reverse();
               break;
           case 'i':  //  Print contents in ID number order 
               cout << "Printing by ID number " << endl;
               list.print_by_ID();
               break;
           case 'I':  //  Print contents in reverse ID number order
               cout << "Printing by ID number reverse " << endl;
               list.print_by_ID_reverse();
               break;
           case 'a':  //  Print contents, youngest to oldest
               cout << "Printing youngest to oldest " << endl;
               list.print_by_age();
               break;
           case 'A':  //  Print contents, oldest to youngest
               cout << "Printing oldest to youngest " << endl;
               list.print_by_age_reverse();
               break;
           case 'Q':  //  Quit the program
           case 'q':
               done = true;
               break;
           default:   //  Unknown command, flush input stream
               cout << "Unknown command" << endl;
               cin.ignore(100, '\n');
        }
    }
}
