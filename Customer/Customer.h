//
// Created by gcode on 6/17/22.
//

#ifndef MANLIB_CUSTOMER_H
#define MANLIB_CUSTOMER_H

#include <iostream>
#include <set>
#include <list>
#include <map>
#include <fstream>
#include "../Book/Book.h"
//#include "../Library/Library.h"

class Customer {
public:
    Customer();

    Customer(std::string name, std::string address);

    void read(std::ifstream &inStream);

    void write(std::ofstream &outStream) const;

    void borrowBook(int bookId);

    void reserveBook(int bookId);

    void returnBook(int bookId);

    void unreserveBook(int bookId);

    bool hasBorrowed() const { return !mLoanSet.empty(); }

    const std::string &name() const { return mName; }

    const std::string &address() const { return mAddress; }

    int Id() const { return mCustomerId; }

    static int MaxCustomerId;

    friend std::ostream &operator<<(std::ostream &outStream, const Customer &customer);

private:
    int mCustomerId{};
    std::string mName;
    std::string mAddress;
    std::set<int> mLoanSet, mReservationSet;
};


#endif //MANLIB_CUSTOMER_H
