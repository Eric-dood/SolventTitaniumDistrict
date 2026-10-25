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
int select_goat(list<Goat> trip, int);
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

    //Read & populate arrays for names and colors
    //First do so for names
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    //Use a while loop to add all entries
    while (fin >> names[i++]);
    //Close the file
    fin.close();

    //Then for the colors
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    //Use a while loop to add all entries
    while (fin1 >> colors[i++]);
    //Close the file
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;

    //Declarations
    list<Goat> trip;
    int age;
    string name, color;

    //Set up the trip list
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    //Do a while loop for all options (except for 12, which quits the program)
    while (sel != 12) {
        switch (sel) {
            case 1: //Adding
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2: //Removing
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3: //Printing data
                if (trip.empty()) cout << "Goat data empty.\n";
                else
                {
                    cout << "Displaying goat data.\n";
                    display_trip(trip);
                }
                break;
            case 4: //Clearing data
                trip.clear();
                cout << "Clearing the goat data. New trip size: " << trip.size() << endl;
                break;
            case 5: //Shuffling
                shuffle_goats(trip);
                break;
            case 6: //Sorting
                cout << "Sorting the goat list by name..." << endl;
                trip.sort();
                break;
            case 7: //Removing duplicates
                remove_dups(trip);
                break;
            case 8: //Reversing
                cout << "Reversing the goat list..." << endl;
                trip.reverse();
                break;
            case 9: //Adding after an index 
                cout << "Adding a goat after an index." << endl;
                add_goat_specific(trip, names, colors);
                break;
            case 10: //Increase ages
                cout << "Increasing the goats' ages." << endl;
                modify_age(trip);
                break;
            case 11: //Finding goat
                cout << "Finding a goat by name." << endl;
                find_goat(trip);
                break;
            default: //N/A
                cout << "Invalid selection.\n";
                break;
        }
        //Print out the menu & define sel as a choice
        sel = main_menu();
    }

    //Return 0...
    return 0;
}

//Define main_menu()
int main_menu() {
    //Print out the entire menu
    cout << "*** GOAT MANAGER 3100 ***\n";
    cout << "[1] Add a goat | [2] Delete a goat | [3] List goats\n";
    cout << "[4] Clear the goat list | [5] Shuffle the goats | [6] Sort the goats \n";
    cout << "[7] Remove duplicates | [8] Reverse list | [9] Insert before a specific location \n";
    cout << "[10] Increase Age | [11] Find a goat | [12] Quit\n";
    cout << "Choice --> ";
    //Ask the user to enter a choice
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

//Define delete_goat()
void delete_goat(list<Goat> &trip) {
    //Check if the list is empty
    if (trip.empty())
        cout << "No goats left to delete." << endl;
    //Otherwise perform as usual
    else
    {
        cout << "DELETE A GOAT\n";
        //Use select_goat() to find a certain goat
        int index = select_goat(trip, 1);
        //Use a iterator to go to a position
        auto it = trip.begin();
        advance(it, index-1);
        //Erase the element
        trip.erase(it);
        cout << "Goat deleted. New trip size: " << trip.size() << endl;
    }
}

//Define add_goat()
void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    //Define the goat elements
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    //Use a constructor
    Goat tmp(nm, age, cl);
    //Push the goat into the list
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

//Define display_trip()
void display_trip(list<Goat> trp)
{
    //i is for the goat number
    int i = 1;
    //Use a range-based loop to print all of the goats
    for (auto gt : trp)
        cout << "\t" << "[" << i++ << "] " << gt.get_name() << " (" << gt.get_age() << ", "
        << gt.get_color() << ")\n";
}

//Define select_goat()
int select_goat(list<Goat> trp, int min = 1) {
    //This will be used for the choice
    int input;
    //Tell the user to make a selection & print the list
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    //If the choice is below min or above the trip size, print out a error message
    //And ask them to try again; validation loop
    while (input < min or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    //Return the input
    return input;
}

//Define shuffle_goats()
void shuffle_goats(list<Goat> &trp)
{
    //If the list isn't empty, shuffle as usual
    if (!trp.empty())
    {
        cout << "Shuffling goats..." << endl;
        //Use a temporary vector to avoid errors
        vector<Goat> temp(trp.begin(), trp.end());
        shuffle(temp.begin(), temp.end(), default_random_engine());
        //Then assign the vector to the 
        trp.assign(temp.begin(), temp.end());
    }
    else //Otherwise print out a message
        cout << "No goats to shuffle..." << endl;
}

//Define remove_dups()
void remove_dups(list<Goat> &trp)
{
    //oldSize will be used for comparing the new size and the old size
    auto oldSize = trp.size();
    //Use a temporary list
    list<Goat> temp = trp;
    cout << "Removing goat duplicates by name..." << endl;
    //Sort the temp list
    temp.sort();
    //Remove all duplicates by using .unique()
    temp.unique();
    //If the new size is different than the old size, successfully change the list
    if (temp.size() != oldSize)
    {
        cout << "New list size: " << temp.size() << endl;
        trp.assign(temp.begin(), temp.end());
    }
    //Otherwise print out a message
    else cout << "No duplicates found." << endl;
}

//Define add_goat_specific()
void add_goat_specific(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT AFTER SPECIFIC POSITION\n(0 = Beginning of the list)\n";
    //Use select_goat() to define a position
    int index = select_goat(trip, 0);
    //Use an iterator to go through the list until a certain position
    auto it = trip.begin();
    advance(it, index);

    //Add the goat elements as usual
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    //Constructor
    Goat tmp(nm, age, cl);
    //Then insert it at this certain position
    trip.insert(it, tmp);

    cout << "Goat added. New trip size: " << trip.size() << endl;
}

//Define modify_age()
void modify_age(list<Goat> &trip) {
    //Use a temporary vector to avoid errors
    vector<Goat> temp(trip.begin(), trip.end());
    //Use for_each to go through every element
    for_each(temp.begin(), temp.end(), [](Goat &g)
    {
        //Increase the goats' ages until they reach 20 (MAX_AGE)
        if (g.get_age() < MAX_AGE)
            g.set_age(g.get_age() + 1);
    } );
    //Assign those values to the list
    trip.assign(temp.begin(), temp.end());
}

//Define find_goat()
void find_goat(list<Goat> trip)
{
    //This'll be used as the target for searching
    string search;

    //Ask the user to enter the villager's name
    cout << "Which goat do you want to find?" << endl << "Name --> ";
    //Use cin.ignore() in order for it to not skip inputting the target name
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