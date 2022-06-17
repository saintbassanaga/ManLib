//
// Created by gcode on 5/18/22.
//

#include "Book.h"
#include <utility>
#include <fstream>

[[maybe_unused]] int Book::MaxBookId;

Book::Book() = default;

[[maybe_unused]] Book::Book(std::string author, std::string title) : mAuthor(std::move(author)), mTitle(std::move(title)) {
    //Empty
}

[[maybe_unused]] void Book::write(std::ofstream &outStream) const {
    outStream.write((char*) &mBookId , sizeof mBookId);
    outStream<<mAuthor<<std::endl;
    outStream<<mAuthor<<std::endl;

    outStream.write((char*) &mBorrowed, sizeof mBorrowed);
    outStream.write((char*) &mCustomerId, sizeof mCustomerId);

    // Nous ecrivons le nombre de reseration en premier puis puis nous le l'identite apres .

    {
       unsigned int reservationListSize = mReservationList.size();
        outStream.write((char*) &reservationListSize , sizeof reservationListSize);
        for (int customerId:mReservationList) {
            outStream.write((char*) &customerId,sizeof customerId);
        }
    }
}

[[maybe_unused]] void Book::read(std::ifstream &inStream) {
    inStream.read((char*) &mBookId, sizeof mBookId);
    getline(inStream, mAuthor);
    getline(inStream, mTitle);

    inStream.read((char*) &mBorrowed, sizeof mBorrowed);
    inStream.read((char*) &mCustomerId,sizeof mCustomerId);

    // Comme sur l'ecriture nous lisons d'abord le numbre de reservation puis l'identite de la reservation.

    {
        int reservationListSize;
        inStream.read((char*) &reservationListSize, sizeof reservationListSize);
        for (int count = 0; count < reservationListSize; ++count) {
            int customerId;
            inStream.read((char*) &customerId , sizeof customerId);
            mReservationList.push_back(customerId);
        }
    }
}

void Book::borrowBook(int customerId) {
    mBorrowed = true;
    mCustomerId = customerId;
}

unsigned int Book::reserveBook(int customerId) {
    mReservationList.push_back(customerId);
    return mReservationList.size();
}

void Book::returnBook(int customerId) {
    mBorrowed = false;
}

[[maybe_unused]] void Book::unreserveBook(int customerId) {
    mReservationList.remove(customerId);
}

std::ostream &operator<<(std::ostream& outStream, const Book& book){
    outStream<<" "<<book.mTitle<<" By " <<book.mAuthor;
    if (book.borrowed()){
        outStream<<std::endl<<" Borrowed by: "
                            <<Library::sCustomerMap[book.mCustomerId].name();
    }
    if (!book.mReservationList.empty()){
        outStream<<std::endl<<"Reserved by : ";
        bool  first = true;
        for (int customerId : book.mReservationList) {
            outStream<<(first ? " " : ",")<<Library::sCustomerMap[customerId].name();
            first= false;
        }
        outStream<<" . ";
    }
    return outStream;
}