//
// Created by gcode on 6/17/22.
//
#include "Customer.h"
#include "../Library/Library.h"

#include <utility>

int Customer::MaxCustomerId;

Customer::Customer() = default;

Customer::Customer(std::string name, std::string address) : mCustomerId(++MaxCustomerId), mName(std::move(name)),
                                                            mAddress(std::move(address)) {
    //Empty.
}

void Customer::read(std::ifstream &inStream) {
    inStream.read((char *) &mCustomerId, sizeof mCustomerId);

    getline(inStream, mName);
    getline(inStream, mAddress);

    {
        int loanSetSize;
        inStream.read((char *) &loanSetSize, sizeof loanSetSize);
        for (int count = 0; count < loanSetSize; ++count) {
            int bookId;
            inStream.read((char *) &bookId, sizeof bookId);
            mLoanSet.insert(bookId);
        }
    }

    {
        int reservationListSize;
        inStream.read((char *) &reservationListSize, sizeof reservationListSize);
        for (int count = 0; count < reservationListSize; ++count) {
            int bookId;
            inStream.read((char *) &bookId, sizeof bookId);
            mLoanSet.insert(bookId);
        }
    }
}

void Customer::write(std::ofstream &outStream) const {
    outStream.write((char *) &mCustomerId, sizeof mCustomerId);
    outStream << mName << std::endl;
    outStream << mAddress << std::endl;

    {
        unsigned int loanSetSize = mLoanSet.size();
        outStream.write((char *) &loanSetSize, sizeof loanSetSize);
        for (int bookId: mLoanSet) {
            outStream.write((char *) &bookId, sizeof bookId);
        }
    }
    {
        unsigned int reservationListSize = mReservationSet.size();
        outStream.write((char *) &reservationListSize, sizeof reservationListSize);
        for (int bookId: mReservationSet) {
            outStream.write((char *) &bookId, sizeof bookId);
        }
    }
}

void Customer::borrowBook(int bookId) {
    mLoanSet.insert(bookId);
}

void Customer::returnBook(int bookId) {
    mLoanSet.erase(bookId);
}

void Customer::unreserveBook(int bookId) {
    mReservationSet.erase(bookId);
}

std::ostream &operator<<(std::ostream &outStream, const Customer &customer) {
    outStream << customer.mCustomerId << ". " << customer.mAddress << ", " << customer.mAddress << ".";
    if (!customer.mLoanSet.empty()) {
        outStream << std::endl << " Borrowed books: ";
        bool first = true;
        for (int bookId: customer.mLoanSet) {
            outStream << (first ? " " : ",")
                      << Library::sBookMap[bookId].author();
            first = false;
        }
    }
    if (!customer.mReservationSet.empty()) {
        outStream << std::endl << " Reserved books: ";
        bool first = true;
        for (int bookId: customer.mReservationSet) {
            outStream << (first ? "" : ",")
                      << Library::sBookMap[bookId].title();
            first = false;
        }
    }
    return outStream;
}

void Customer::reserveBook(int bookId) {
    mReservationSet.insert(bookId);
}
