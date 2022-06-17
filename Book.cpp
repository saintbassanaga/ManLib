//
// Created by gcode on 5/18/22.
//

#include "Book.h"

#include <utility>

int Book::MaxBookId;

Book::Book() = default;

Book::Book(std::string author, std::string title) : mAuthor(std::move(author)), mTitle(std::move(title)) {
    //Empty
}

void Book::write(std::ofstream &outStream) const {
    outStream.write((char*) &mBookId , sizeof mBookId);
    outStream<<mAuthor<<endl;
    outStream<<mAuthor<<endl;

    outStream.write((char*) &mBorrowed, sizeof mBorrowed);
    outStream.write((char*) &mCustomerId, sizeof mCustomerId);

    // Nous ecrivons le nombre de reseration en premier puis puis nous le l'identite apres .

    {
        int reservationListSize = mReservationList.size();
        outStream.write((char*) &reservationListSize , sizeof reservationListSize);
        for (int customerId:mReservationList) {
            outStream.write((char*) &customerId,sizeof customerId);
        }
    }
}



