//Made by: Will Mize

#include "coin.h"
#include <iostream>
#include <string>
#include <locale> //needed for tolower()
#include <vector>
#include <math.h>
#include <set>

string cleaner(string input) {                                                   //helper function converts user input to lowercase and removes any spaces
    string clean;
    locale loc;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] != ' ') {
            clean.push_back(tolower(input[i], loc));
        }
    }
    return clean;
}
    

int main () {

    coin q(25);
    coin d(10);
    coin n(5);
    coin p(1);
    vector<coin> collection{q, d, n, p};                                         //stores all denominations

    string input = "";
    string newDenom = "";

    while(true) {
        
        try {
            cout << "Enter a number to get the fewest number of coins required to make change of that value. Or type 'add' to add a new denomination." << endl;
            cin >> input;
            input = cleaner(input);

            if(input == "quit") {
                return 0;
            }

            if (input == "add") {
                cout << "Enter the new denomination: " << endl;
                cin >> newDenom;

                if (stod(newDenom) * 100 < 1) {
                    cout << "Cannot add a denomination for a value less than 0.01" << endl;
                }

                else {

                    coin newCoin(stod(newDenom) * 100);                             //all values are dealt with in int to simplify division

                    vector<coin>::iterator it = collection.begin();

                    for (int i = 0; i < collection.size(); i++) {                   //adds new values to the collection
                        if(newCoin.value == collection.at(i).value) {
                            cout << "That denomination is already in the collection" << endl;
                            break;
                        }
                        if(newCoin.value > collection.at(i).value) {
                            collection.insert(it+i, newCoin);
                            cout << "Added!" << endl;
                            break;
                        }
                        else if (i == collection.size() - 1) {
                            collection.push_back(newCoin);
                            cout << "Added!" << endl;
                            break;
                        }
                    }
                }
            }

            else {                                                              //performs the change calculation 

                int inputAmt = stod(input) * 100;
                if (inputAmt < 1) {
                    cout << "Cannot provide change for a value less than 0.01" << endl;
                }
                else {
                    cout << "Amount of coins needed: " << endl;
                    for (int i = 0; i < collection.size(); i++) {
                        collection.at(i).amount = (inputAmt / collection.at(i).value);
                        inputAmt = inputAmt - (collection.at(i).amount * collection.at(i).value);
                        cout << "(" << (double)(collection.at(i).value)/100 << "): " << collection.at(i).amount << endl;
                    }
                }

            }

        } catch(exception& e) {
            cerr << "Error: " << e.what() << endl;
            cout << "HINT: Make sure you entered a numerical value" << endl;
        
        }

    }

}
