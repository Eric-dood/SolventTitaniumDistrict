//COMSC-210 | Lab 28 | Eric-Giulio Hedes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <string>
#include <random>
#include "Goat.h"
using namespace std;

//Global constants for names & colors
const int SZ_NAMES = 200, SZ_COLORS = 25;

//Prototype functions
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void shuffle_goats(list<Goat> &trip);
void remove_dups(list<Goat> &trip);
void add_goat_specific(list<Goat> &trip, string [], string []);
void modify_age(list<Goat> &trip);
void find_goat(list<Goat> trip);
int main_menu();

//Start of main()
int main() {
    //Use a random seed generator
    srand(time(0));

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                if (trip.empty()) cout << "Goat data empty.\n";
                else
                {
                    cout << "Displaying goat data.\n";
                    display_trip(trip);
                }
                break;
            case 4:
                trip.clear();
                cout << "Clearing the goat data. New trip size: " << trip.size() << endl;
                break;
            case 5:
                shuffle_goats(trip);
                break;
            case 6:
                cout << "Sorting the goat list by name..." << endl;
                trip.sort();
                break;
            case 7:
                remove_dups(trip);
                break;
            case 8:
                cout << "Reversing the goat list..." << endl;
                trip.reverse();
                break;
            case 9:
                cout << "Adding a goat after an index." << endl;
                add_goat_specific(trip, names, colors);
                break;
            case 10:
                cout << "Increasing the goats' ages." << endl;
                modify_age(trip);
                break;
            case 11:
                cout << "Finding a goat by name." << endl;
                find_goat(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3100 ***\n";
    cout << "[1] Add a goat | [2] Delete a goat | [3] List goats\n";
    cout << "[4] Clear the goat list | [5] Shuffle the goats | [6] Sort the goats \n";
    cout << "[7] Remove duplicates | [8] Reverse list | [9] Insert before a specific location \n";
    cout << "[10] Increase Age | [11] Find a goat | [12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp)
{
    int i = 1;
    for (auto gt : trp)
        cout << "\t" << "[" << i++ << "] " << gt.get_name() << " (" << gt.get_age() << ", "
        << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void shuffle_goats(list<Goat> &trp)
{
    if (trp.size() > 0)
    {
        cout << "Shuffling goats..." << endl;
        vector<Goat> temp(trp.begin(), trp.end());
        shuffle(temp.begin(), temp.end(), default_random_engine());
        trp.assign(temp.begin(), temp.end());
    }
    else
        cout << "No goats to shuffle..." << endl;
}

void remove_dups(list<Goat> &trp)
{
    auto oldSize = trp.size();
    list<Goat> temp = trp;
    cout << "Removing goat duplicates by name..." << endl;
    temp.sort();
    temp.unique();
    if (temp.size() != oldSize)
    {
        cout << "New list size: " << temp.size() << endl;
        trp.assign(temp.begin(), temp.end());
    }
    else cout << "No duplicates found." << endl;
}

void add_goat_specific(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT BEFORE SPECIFIC POSITION\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);

    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.insert(it, tmp);

    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void modify_age(list<Goat> &trip) {
    vector<Goat> temp(trip.begin(), trip.end());
    for_each(temp.begin(), temp.end(), [](Goat &g)
    {
        if (g.get_age() < MAX_AGE)
            g.set_age(g.get_age() + 1);
    } );
    trip.assign(temp.begin(), temp.end());
}

void find_goat(list<Goat> trip)
{
    string search;

    //Ask the user to enter the villager's name
    cout << "Which goat do you want to find?" << endl << "Name --> ";
    cin.ignore();
    getline(cin, search);

    //Use a iterator & .find() to find the villager (using .find() avoids errors)
    auto it = find(trip.begin(), trip.end(), search);
    if (it != trip.end())
    {  // the iterator points to beyond the end of the map
        cout << "\nFound: " << search;
        cout << " (" << it->get_age() << ", " << it->get_color() << ")\n" << endl;
    }
    else //If the goat's name is not found, print a message
        cout << endl << search << " not found.\n" << endl;
}