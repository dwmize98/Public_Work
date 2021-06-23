#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "parser.hpp"
#define true_clause 1
#define false_clause 0
#define unknown_clause 2

using namespace std;

typedef unordered_map<string, bool> MODEL;                    

//Function declarations

bool DPLL(vector<Expr*> clauses, vector<string>* symbols, MODEL* model); 
bool DPLL_Satisfiable(vector<Expr*> clauses, MODEL* model);
void expr_parse(Expr* clause, vector<string>* symbols);
int eval(Expr* clause, MODEL* model);
int unit_heuristic(Expr* clause, MODEL* model, MODEL* clean_model);
static bool heuristic = true;

static int counter = 0;

bool DPLL(vector<Expr*> clauses, vector<string> symbols, MODEL* model) {
    counter++;
    int num_satisified = 0;
    bool all_true = true;
    int clause_value = -1;
    //Checking values of the models with the clauses
    for (int i = 0; i < clauses.size(); i++) {
        clause_value = eval(clauses.at(i), model);
        if (clause_value == false_clause) {
            cout << "backtracking..." << endl;
            return false;
        }
        else if (clause_value == unknown_clause) {
            all_true = false;
        }
        else {
            num_satisified++;
        }
    }
    //printing tracing information
    cout << endl << "model: ";
    for (auto& i: *model) {
        cout << i.first << "=" << ((i.second) ? "T" : "F") << " ";
    }
    for (int i = 0; i < symbols.size(); i++) {
        cout << symbols.at(i) << "=? ";
    }
    cout << endl << "num clauses satisfied: " << num_satisified << " out of " << clauses.size() << endl;;

    //return true if all clauses are true
    if(all_true){
        return true;
    }

    
    if(heuristic) {
        for (int i = 0; i < clauses.size(); i++) {
            MODEL* clean_model = new MODEL; //empty model that will be loaded with heuristic information
            unit_heuristic(clauses.at(i), model, clean_model); //call to heuristic function
            if (clean_model->size() == 1) { //if only one thing is placed into the new model, then it is forceable
                string new_symbol;
                for (auto& i: *clean_model) { //inserts it and removes it from symbols
                    new_symbol = i.first;
                    model->insert({i.first, i.second});
                    cout << "forcing " << i.first << "=" << i.second << endl;
                    for (int j = 0; j < symbols.size(); j++) {
                        if (symbols.at(j) == i.first) {
                            symbols.erase(symbols.begin() + j);
                        }
                    }
                }
                if (DPLL(clauses, symbols, model)) {
                    return true;
                }
                else {
                    model->erase(new_symbol);
                    return false;
                }
            } 
        }
    }

    //update symbols
    string curr_symbol = symbols.at(0);
    symbols.erase(symbols.begin());

    
    //recursive call
    model->insert({curr_symbol, true});
    cout << "trying " << curr_symbol << "=1" << endl;
    if (DPLL(clauses, symbols, model)) {
        return true;
    }
    

    model->at(curr_symbol) = false;

    cout << "trying " << curr_symbol << "=0" << endl;
    if (DPLL(clauses, symbols, model)) {
        return true;
    }

    else {
        model->erase(curr_symbol);
        return false;
    }

}

bool DPLL_Satisfiable(vector<Expr*> clauses, MODEL* model) {

    //builds the symbol vector
    vector<string>* symbols = new vector<string>;
    for (int i = 0; i < clauses.size(); i++) {
       expr_parse(clauses.at(i), symbols); 
    }

    //calls DPLL, outputs as appropriate
    if(DPLL(clauses, *symbols, model)) {
        cout << endl << "Success!" << endl;
        cout << "Number of DPLL calls=" << counter;
        cout << ((heuristic) ? " (WITH unit-clause heuristic)" : " (WITHOUT unit-clause heuristic)") << endl;
        cout << "Here is the model: " << endl;
        vector<pair<string, bool>> sorted_model(model->begin(), model->end());
        sort(sorted_model.begin(), sorted_model.end());
        for (auto& i : sorted_model) {
            cout << i.first << " : " << i.second << endl;
        }
        return true;
    }
    else {
        cout << "Unsatisfiable" << endl;
        return false;
    }

}

void expr_parse(Expr* clause, vector<string>* symbols) { //searches the KB for symbols linearly and returns each one
    if (clause->kind == LIST) {
        for (int i = 0; i < clause->sub.size(); i++) {
            expr_parse(clause->sub.at(i), symbols);
        }
    }
    else if (clause->sym != "not" && clause->sym != "and" && clause->sym != "or") {
        bool found = false;
        if (symbols->size() == 0) {
            symbols->push_back(clause->sym);
        }
        else {
            for (int i = 0; i < symbols->size(); i++) {
                if (symbols->at(i) == clause->sym) {
                    found = true;
                }
            }
            if (!found) {
                symbols->push_back(clause->sym);
            }
        }
    }
}

int eval(Expr* clause, MODEL* model) { //walks the clause and returns true, false, or unknown

    //if its a not, flips the value and returns
    if (clause->kind == LIST && clause->sub.at(0)->sym == "not") {
        int first = eval(clause->sub.at(1), model);
        if (first == true_clause) {
            return false_clause;
        } 
        else if (first == false_clause) {
            return true_clause;
        }
        else {
            return unknown_clause;
        }
    }
    
    //walks through or and will return true only if a true is present and all others are set
    else if (clause->kind == LIST && clause->sub.at(0)->sym == "or") {
        int true_count = 0;
        int false_count = 0;
        int curr_atom = 0;
        int num_clauses = clause->sub.size() - 1;
        for (int i = 1; i < clause->sub.size(); i++) {
            curr_atom = eval(clause->sub.at(i), model);
            
            if (curr_atom == true_clause) {
                true_count++;
            }
            
            else if (curr_atom == false_clause) {
                false_count++;
            }
        }
        
        if (false_count == num_clauses) {
            return false_clause;
        }

        else if (true_count == num_clauses || (true_count + false_count) == num_clauses) {
            return true_clause;
        }


        else {
            return unknown_clause;
        }
         
    }

    else { //looks at the model for the value, or returns unknown
        try {
            int modelvalue = model->at(clause->sym);
            return modelvalue;
        }
        catch (out_of_range& e) {
            return unknown_clause;
        }
    }
}

int unit_heuristic(Expr* clause, MODEL* model, MODEL* clean_model) { //walks very similar to eval

    if (clause->kind == LIST && clause->sub.at(0)->sym == "not") {
        int first = unit_heuristic(clause->sub.at(1), model, clean_model);
        if (first == true_clause) {
            return false_clause;
        } 
        else if (first == false_clause) {
            return true_clause;
        }
        else { //if the value is unknown then it is asserted in the clean_model as false
            clean_model->insert({clause->sub.at(1)->sym, false});
            return unknown_clause;
        } 
    }

    else if (clause->kind == LIST && clause->sub.at(0)->sym == "or") {
        int true_count = 0;
        int false_count = 0;
        int curr_atom = 0;
        int num_clauses = clause->sub.size() - 1;
        for (int i = 1; i < clause->sub.size(); i++) {
            curr_atom = unit_heuristic(clause->sub.at(i), model, clean_model);
            if (curr_atom == true_clause) {
                true_count++;
            }
            
            else if (curr_atom == false_clause) {
                false_count++;
            }
            //if a value is uknown and atomic within the or it is inserted into the clean_model as false
            else if (curr_atom == unknown_clause && clause->sub.at(i)->kind == ATOM) {
                clean_model->insert({clause->sub.at(i)->sym, true});
            }
        }
        //if there is more than one unkown then the new model will have more than one entry, and thus nothign is forceable

        //in the event that there is one unknown, but not all other values are false, (or there are no unknowns) 
        //two entries are placed into the model to insure it is not used when it returns
        if(false_count != num_clauses - 1 || true_count != 0) {
            clean_model->insert({"unit", false});
            clean_model->insert({"clause", false});
        }

        if (false_count == num_clauses) {
            return false_clause;
        }

        else if (true_count == num_clauses || (true_count + false_count) == num_clauses) {
            return true_clause;
        }

        else {
            return unknown_clause;
        }
        
    }

    else {
        try {
            int modelvalue = model->at(clause->sym);
            return modelvalue;
        }
        catch (out_of_range& e) {
            return unknown_clause;
        }
    }
}


// main function

int main(int argc, char **argv) {
    
    try {
        if(argc > 2 && (string)(argv[argc - 1]) == "-unit") {
            heuristic = false;
        }
        string filename = argv[1];

        vector<Expr*> KB = load_kb(filename);
        vector<string> keys;
        MODEL* model = new MODEL;
        DPLL_Satisfiable(KB, model);


    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
