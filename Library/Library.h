//
// Created by gcode on 6/18/22.
//

#ifndef MANLIB_LIBRARY_H
#define MANLIB_LIBRARY_H

#include <iostream>
#include <set>
#include <map>
#include <list>
#include <string>
#include "../Library/Library.h"
#include "../Customer/Customer.h"

class Customer;

class Book;

class Library {
public:
    Library();

private:
    [[maybe_unused]] static std::string sBinaryPath;

    static bool lookUpBook(const std::string &author, const std::string &title, Book *bookPtr = nullptr);

    static bool lookUpCustomer(const std::string &name, const std::string &address, Customer *customerPtr = nullptr);

    void addBook();

    void deleteBook();

    void listBook();

    void addCustomer();

    void deleteCustomer();

    void listCustomer();

    void borrowBook();

    void reservedBook();

    void returnBook();

    void load();

    void save();

public:
    static map<int, Book> sBookMap;
    static map<int, Customer> sCustomerMap;

};


#endif //MANLIB_LIBRARY_H
