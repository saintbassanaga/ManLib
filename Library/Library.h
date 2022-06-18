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

    static void addBook();

    static void deleteBook();

    static void listBook();

    static void addCustomer();

    [[maybe_unused]] static void deleteCustomer();

    static void listCustomer();

    static void borrowBook();

    static void reservedBook();

    static void returnBook();

    static void load();

    static void save();

public:
    static std::map<int, Book> sBookMap;
    static std::map<int, Customer> sCustomerMap;

};


#endif //MANLIB_LIBRARY_H
