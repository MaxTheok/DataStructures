//
//  ItemType.cpp
//  P11
//
//  Created by Maxime Theokritoff on 14/02/2018.
//  Copyright © 2018 Maxime Theokritoff. All rights reserved.
//

#include "ItemType.hpp"

ItemType::ItemType(){
    struct node * header;
    header = new(struct node);
    root = header;
    header -> left = header;
    header -> right = header;
    header -> name = "zzzzz";
    header -> leftTH= true;
    header -> rightTH= true;
};

void ItemType::readInvInfo(){
    string  name, phoneNum;
    node *follow, *find, *parent;
    bool ThisSpot;
    
    ifstream in("raceUnordered.txt");
    if(in.is_open()){
        for(;;){
            getline(in>>ws,name,'.');
            getline(in>>ws,phoneNum);
            if(in.good()){
                struct node *temp;
                temp = new(struct node);
                
                temp -> name = name;
                temp -> number = phoneNum;
                temp -> count = 1;
                temp -> leftTH = true;
                temp -> rightTH = true;
                //sets our temp list item to user entry
                follow = root;
                find = root -> left;
                ThisSpot = root -> leftTH;

                while( !ThisSpot  ){
                    if (name.compare(find -> name)< 0 ){
                        follow = find;
                        find = find -> left;
                        ThisSpot = follow -> leftTH;
                    }
                    else{
                        follow = find;
                        find = find -> right;
                        ThisSpot = follow -> rightTH;
                    }
                    follow -> count +=1;
                }
                parent = follow;
                if (name.compare(parent -> name)< 0){
                    temp -> left = parent -> left;
                    parent ->leftTH = false;
                    temp -> right = parent;
                    parent -> left = temp;
                }
                else{
                    temp -> right = parent -> right;
                    parent ->rightTH = false;
                    temp -> left = parent;
                    parent -> right = temp;
                }
                routCount(parent);
                rebalance(parent);
            }else if(in.eof()){
                break;
                //exits the loop if we reache the end of file
            }else{
                string temp;
                in.clear();
                getline(in,temp);
                cout<<"Corrupted record:"<<temp<<endl;
                //Informes that the data is corrupted
            }
            
            routCount(root->left);
            rebalance(root->left);
        }
        in.close();
    }
    else{
        cout << "Error file not found" << endl;
        //informes user that file is not found
    }
};
//Creates a stream to read data from a file.
//If the file exist, will go and add every line to a linked list with the put function
//Will print an error message for corrupted data and clear the line


void ItemType::putItem(){
    string name, phone;
    struct node *temp;
    node *follow, *find, *parent;
    bool ThisSpot;
    
    temp = new(struct node);
    //Creates the pointers we need and a new structure.
    //Temp will be the new Item we want to add to the list
    //cur points to an item we are interested by
    //prevCur points to the item before cur exept when initialized
    
    cout<<"Enter contact name: ";
    getline(cin >> ws, name);
    cout<<"Enter contact phone: ";
    getline(cin >> ws, phone);
    //Asks user to input new Item information
    
    temp -> name = name;
    temp -> number = phone;
    temp -> count = 1;
    temp -> leftTH = true;
    temp -> rightTH = true;
    //sets our temp list item to user entry
    follow = root;
    find = root -> left;
    ThisSpot = root -> leftTH;
    
    while( !ThisSpot  ){
        if (name.compare(find -> name)< 0 ){
            follow = find;
            find = find -> left;
            ThisSpot = follow -> leftTH;
        }
        else{
            follow = find;
            find = find -> right;
            ThisSpot = follow -> rightTH;
        }
        follow -> count +=1;
    }
    parent = follow;
    if (name.compare(parent -> name)< 0){
        temp -> left = parent -> left;
        parent ->leftTH = false;
        temp -> right = parent;
        parent -> left = temp;
    }
    else{
        temp -> right = parent -> right;
        parent ->rightTH = false;
        temp -> left = parent;
        parent -> right = temp;
    }
    routCount(root->left);
    //launches a routine to weigh the tree
    rebalance(root->left);
    //rebalances if needed
};

void ItemType::printPreOrder(node *myRoot){
    cout << myRoot -> name << ": " << myRoot -> number << endl;
    if (!(myRoot -> leftTH))
        printPreOrder(myRoot -> left);
    if (!(myRoot -> rightTH))
        printPreOrder(myRoot -> right);
};

void ItemType::printPostOrd(node *myRoot){
        if (!(myRoot -> leftTH))
            printPostOrd(myRoot -> left);
        if (!(myRoot -> rightTH))
            printPostOrd(myRoot -> right);
        cout << myRoot -> name << ": "<< myRoot -> number << endl;
};

void ItemType::printAll(){
    node * temp;
    temp = root -> left;
    cout << temp -> name << endl;
    cout << "Pre-Order Tree print: " << endl;
    printPreOrder(temp);
    cout << "\nIn Order Tree print: " << endl;
    InOrdIterative(temp);
    cout << "\nPost-Order Tree print: " << endl;
    printPostOrd(temp);
};

void ItemType::getName(){
    //Finds and returns name and phone based on name
    node *find, *parent, *first, *last, *prev, *next;
    //sets a pointer to the begining of the list
    string name;
    cout << "Entre the name you are looking for: " << endl;
    getline(cin >> ws, name);
    //gets the name from user
    parent = root;
    find = root -> left;
    first = findFirst(find);
    last = findLast(find);
    while(!(find -> leftTH and find -> rightTH) and (find -> name).substr(0,name.length()) != name){
        if (name.compare((find -> name).substr(0,name.length()))<0){
            parent = find;
            find = find -> left;
        }
        else if (name.compare((find -> name).substr(0,name.length()))>0){
            parent = find;
            find = find -> right;
        }
    }
    //itterates until the name is found or we reach the end of the tree
    if ((find -> name).substr(0,name.length()) == name ) {
        cout << find -> name << ": " << find -> number << endl;
        prev = find;
        next = find;
        while (name.compare((inOrdPred(prev) -> name).substr(0,name.length()))==0 and prev != first){
            prev = inOrdPred(prev);
            cout << prev -> name << ": " << prev -> number << endl;
        }
        while (name.compare((inOrdSucc(next) -> name).substr(0,name.length()))==0 and next != last){
            next = inOrdSucc(next);
            cout << next -> name << ": " << next -> number << endl;
        }
    }
    else {
        cout << "Name not found." << endl;
    }
    //return the name and phone number or not found.
}


void ItemType::routCount(node * myRoot){
    if (!(myRoot -> leftTH) and !(myRoot -> rightTH)){
        myRoot -> count = myRoot -> left -> count + myRoot -> right -> count +1;
    }
    else if (myRoot -> rightTH and !(myRoot -> leftTH) ){
        myRoot -> count = myRoot -> left -> count + 1;
    }
    else if (!(myRoot -> rightTH) and myRoot -> left ){
        myRoot -> count = myRoot -> right -> count + 1;
    }
    // calculates the weight of a myRoot based on its left and right neighbor, verifying if the neighbor is null to avoid issues.
};


float ItemType::bigness(node* myRoot){
    if (myRoot -> name == "zzzzz")
        return 0;
    else
        return myRoot -> count;
};
// How big is the tree?

bool ItemType::heavyRight(node *myRoot){
    if (bigness(myRoot->left)<0.237*bigness(myRoot))
        return true;
    else
        return false;
};
// Is the tree heavy on the right?

bool ItemType::heavyLeft(node *myRoot){
    if (bigness(myRoot->right)<0.237*bigness(myRoot))
        return true;
    else
        return false;
};
// Is the tree heavy on the left?

void ItemType::singleRotateLeft(node * myRoot){
    node *top, *thisRight, *orphan;
    bool thread;

    //assigning the pointers
    top = myRoot;
    thisRight = myRoot -> right;
    if ( thisRight -> left != top)
        orphan = thisRight -> left;
    else
        orphan = thisRight;
    
    //exchanging nodes
    top -> right = orphan;
    thisRight -> left = top;
    root -> left = thisRight;
    
    // exchanging threads
    thread = thisRight -> leftTH;
    thisRight -> leftTH = top -> rightTH;
    top -> rightTH  = thread;
    
    //Routine to update the counts of both nodes as they have changed place
    routCount(top);
    routCount(thisRight);
};

void ItemType::singleRotateRight(node * myRoot){
    node *top, *thisLeft, *orphan;
    bool thread;
    
    //assigning the pointers
    top = myRoot;
    thisLeft = myRoot -> left;
    if ( thisLeft -> right != top)
        orphan = thisLeft -> right;
    else
        orphan = thisLeft;
    
    //exchanging nodes
    top -> left = orphan;
    thisLeft -> right = top;
    root -> left = thisLeft;
    
    // exchanging threads
    thread = thisLeft -> rightTH;
    thisLeft -> rightTH = top -> leftTH;
    top -> leftTH  = thread;

    //Routine to update the counts of both nodes as they have changed place
    routCount(top);
    routCount(thisLeft);
};

void ItemType::doubleRotateLeft(node * myRoot){
    singleRotateRight(myRoot ->right);
    singleRotateLeft(myRoot);
};
//Double rotate Left

void ItemType::doubleRotateRight(node * myRoot){
    singleRotateLeft(myRoot ->left);
    singleRotateRight(myRoot);
};
//Double rotate Right

void ItemType::rebalance(node * myRoot){
    if ((myRoot -> count) > 4){
        if (heavyRight(myRoot)){
            if (heavyLeft(myRoot->right)){
                doubleRotateLeft(myRoot);
            }
            else{
                singleRotateLeft(myRoot);
            }
        }
        else if (heavyLeft(myRoot)){
            if (heavyRight(myRoot->left)){
                doubleRotateRight(myRoot);
            }
            else{
                singleRotateRight(myRoot);
            }
        }
    }
};
// routine to rebalance the tree

node* ItemType::inOrdPred(node * myRoot){
    node * pred;
    if (myRoot -> leftTH)
        return myRoot -> left;
    else {
        pred = myRoot -> left;
        while( !(pred ->rightTH))
            pred = pred -> right;
        return pred;
    }
};
//Finds the In Order Predecessor of a node


node* ItemType::inOrdSucc(node * myRoot){
    node * succ;
    if (myRoot -> rightTH)
        return myRoot -> right;
    else {
        succ = myRoot -> right;
        while( !(succ ->leftTH))
            succ = succ -> left;
        return succ;
    }
};
//Finds the In Order Successor of a node

node* ItemType::findFirst(node * myRoot){
    node * first = myRoot;
    while (!(first -> leftTH) )
        first = first -> left;
    return first;
};
//  Finds the first, leftmost node of the tree

node* ItemType::findLast(node * myRoot){
    node * last = myRoot;
    while (!(last -> rightTH)){
        last = last -> right;
    }
    return last;
};
//  Finds the last, rightmost node of the tree


void ItemType::InOrdIterative(node * myRoot){
    node *first, *last, *node;
    first = findFirst(myRoot);
    last = findLast(myRoot);
    node = first;
    cout << node -> name << ": " << node -> number << endl;
    while (node  != last){
        node = inOrdSucc(node);
        cout << node -> name << ": " << node -> number << endl;
    }
};
// Iterates and prints the In Order transversale 
