//
// Created by gcode on 5/18/22.
//

#ifndef MANLIB_BOOK_H
#define MANLIB_BOOK_H

#include <iostream>
#include <list>

class Book {
private:
    int mBookId{}, mCustomerId{};
    bool mBorrowed = false;
    std::list<int> mReservationList;
    std::string mAuthor, mTitle;

public:
    Book(std::string author, std::string title);

    Book();

    void read(std::ifstream &inStream);

    void write(std::ofstream &outStream) const;

    [[nodiscard]] int bookId() const { return mBookId; }

    [[nodiscard]] const std::string &author() const { return mAuthor; }

    [[nodiscard]] const std::string &title() const { return mTitle; }

    std::list<int> &reservationList() { return mReservationList; }

    void borrowBook(int customerId);

    void returnBook(int customerId);

    void reserveBook(int customerId);

    void unreserveBook(int customerId);

    [[nodiscard]] bool borrowed() const { return mBorrowed; }

    int customerId() const { return mCustomerId; }

    static int MaxBookId;

};


#endif //MANLIB_BOOK_H
