//
// Created by juan on 30/10/20.
//

#include "paginateObserver.h"

void PaginateSubject::attach(IObserver *observer) {
    listObserver.push_back(observer);
}

void PaginateSubject::detach(IObserver *observer) {
    listObserver.remove(observer);
}

void PaginateSubject::notify() {
    list<IObserver*>::iterator iterator = listObserver.begin();
    while (iterator != listObserver.end()){
        (*iterator) -> update(message);
        ++iterator;
    }
}

void PaginateSubject::createMessage(string message) {
    this->message = message;
    notify();
}