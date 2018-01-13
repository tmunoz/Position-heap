#include <iostream>
#include "heap.h"
#include "node.h"
#include "childtable.h"

int main() {
    auto *h = new heap();
    int choice = 1;
    while (choice != 0) {
        cout << "\n";
        cout << "0. Quit\n";
        cout << "1. Insert String\n";
        cout << "2. Delete String\n";
        cout << "3. Find positions of a pattern in the strings\n";
        cout << "4. Print nodes of the heap\n";
        cout << "5. Graph heap\n";

        cin >> choice;
        switch (choice) {
            default:
                cout << "Enter a valid number\n";
                break;

            case 0:
                cout << "Goodbye";
                break;

            case 1: {
                string str_toInsert;
                cout << "Enter the string: ";
                cin >> str_toInsert;
                cout << "Inserted with ID: "<<h->insert_str(str_toInsert)<<"\n";
            }
                break;

            case 2: {
                int str_number;
                cout << "Enter the number of the string (From 1 to n): ";
                cin >> str_number;
                h->delete_str(str_number);
                cout << "Deleted !\n";
            }
                break;

            case 3: {
                string pattern;
                cout << "Enter the pattern: ";
                cin >> pattern;
                auto res_nodes = h->search(pattern);
                if (res_nodes.size() == 1 && !res_nodes[0]) {
                    cout << "Not Found !\n";
                } else {
                    int i = 0;
                    cout << "The strings in the heap are:\n";
                    for (auto &elem : h->getText()) cout << ++i << ". " << elem << "\n";
                    cout << "\nThe positions of the pattern are: \n";
                    for (auto &elem : res_nodes) cout << elem->getStr() + 1 << ", " << elem->getIndex() << endl;
                }
            }
                break;

            case 4:
                h->print(h->getRoot());
                break;

            case 5:
                h->GraphTree();
                cout << "Please check the file \"tree.txt\"\n";
                break;
        }
    }
    h->~heap();
    return 0;
}