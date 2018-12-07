//
//  ItemType.hpp
//  P11
//
//  Created by Maxime Theokritoff on 14/02/2018.
//  Copyright © 2018 Maxime Theokritoff. All rights reserved.
//

#ifndef ItemType_hpp
#define ItemType_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <stack>
#include <fstream>
#include <queue>

using namespace std;

struct node{
    string name;
    string number;
    int count;
    node *left;
    node *right;
    bool leftTH;
    bool rightTH;
};

class ItemType{
public:
    node * root;
    
    ItemType();
    void printAll();
    void putItem();
    void getName();
    void readInvInfo();
    
    void rebalance();
private:
    float bigness(node* myRoot);
    bool heavyRight(node *myRoot);
    bool heavyLeft(node *myRoot);
    void singleRotateLeft(node * myRoot);
    void singleRotateRight(node * myRoot);
    void rebalance(node *myRoot);
    void doubleRotateLeft(node * myRoot);
    void doubleRotateRight(node * myRoot);
    void routCount(node * myRoot);
    void printPreOrder(node *root );
    void printPostOrd(node *root);
    
    node* inOrdPred(node * myRoot);
    node* inOrdSucc(node * myRoot);
    node* findFirst(node * myRoot);
    node* findLast(node * myRoot);
    void InOrdIterative(node * myRoot);
};


#endif /* ItemType_hpp */


