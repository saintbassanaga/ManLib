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
    [[maybe_unused]] Book(std::string author, std::string title);

    Book();

    [[maybe_unused]] void read(std::ifstream &inStream);

    [[maybe_unused]] void write(std::ofstream &outStream) const;

    [[nodiscard]] int bookId() const { return mBookId; }

    [[nodiscard]] const std::string &author() const { return mAuthor; }

    [[nodiscard]] const std::string &title() const { return mTitle; }

    std::list<int> &reservationList() { return mReservationList; }

    void borrowBook(int customerId);

    void returnBook(int customerId);

    unsigned int reserveBook(int customerId);

    [[maybe_unused]] void unreserveBook(int customerId);

    [[nodiscard]] bool borrowed() const { return mBorrowed; }

    [[nodiscard]] int customerId() const { return mCustomerId; }

    [[maybe_unused]] static int MaxBookId;

   friend std::ostream& operator<<(std::ostream& outStream, const Book& book);
};


#endif //MANLIB_BOOK_H
