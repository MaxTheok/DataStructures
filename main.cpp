//
//  main.cpp
//  P11
//
//  Created by Maxime Theokritoff on 14/02/2018.
//  Copyright © 2018 Maxime Theokritoff. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "ItemType.hpp"

using namespace std;

int menuSelection(void);


const char * menu[]={
    "1.    Add new item",
    "2.    Print phone number based on name",
    "3.    Print items",
    "4.    Quit"
};
//Creates the different options of the menu to be displayed

int main() {
    ItemType myTree;
    myTree.readInvInfo();
    
    int sel;
    do{
        sel = menuSelection();
        //prints menu and asks for a choice.
        switch(sel){
            case 1:
                myTree.putItem();
                //Add item to the list in a sorted way
                break;
            case 2:
                myTree.getName();
                //From name returns phone num info
                break;
            case 3:
                myTree.printAll();
                // Print the  sorted tree
                break;
            case 4:
                return 0;
            default:
                cout << "Error: Command unknown. Pease try again." << endl;
        }
    }while (sel != 4);
    //Menu selection. If selection is not a selectable value will print an error and prompt menu again.
}

int menuSelection(void){
    int sel;
    cout << "\n\t\t Inventory Selection Menu" << endl;
    for(int i=0; i <(int)(sizeof(menu)/sizeof(menu[0])); i++ )
        cout <<menu[i] << endl;
    cout <<"Select: ";
    cin >> ws >> sel;
    return sel;
};
//Function to ask for the menue input



