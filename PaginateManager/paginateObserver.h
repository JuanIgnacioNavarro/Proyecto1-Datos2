//
// Created by juan on 30/10/20.
//

#pragma once

#include "iostream"
#include "vector"
#include "list"
using namespace std;

class IObserver {
public:
    virtual void update(const string messageFromSubject) = 0;
};

class PaginateSubject {
public:
    void attach(IObserver* observer);
    void detach(IObserver* observer);
    void notify();
    void createMessage(string message);

private:
    list<IObserver*> listObserver;
    string message;
};


