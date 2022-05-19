//
// Created by gcode on 5/18/22.
//

#include "Book.h"

#include <utility>

Book::Book() = default;

Book::Book(std::string author, std::string title) : mAuthor(std::move(author)), mTitle(std::move(title)) {
//Empty
}
