//
// Created by gcode on 6/18/22.
//

#include "Library.h"

std::map<int, Book>Library::sBookMap;
std::map<int, Customer>Library::sCustomerMap;

[[maybe_unused]] std::string Library::sBinaryPath("Library.bin");

Library::Library() {
    load();

    bool quit = false;
    while (!quit) {
        std::cout << "1. Add Book" << std::endl;
        std::cout << "2. Delete Book" << std::endl;
        std::cout << "3. List Books" << std::endl;
        std::cout << "4. Add Customer" << std::endl;
        std::cout << "5. Delete Customer" << std::endl;
        std::cout << "6. List Customer" << std::endl;
        std::cout << "7. Borrow Book" << std::endl;
        std::cout << "8. Reserve Book" << std::endl;
        std::cout << "9. Return Book" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cout << " : ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                listBook();
                break;
            case 4:
                addCustomer();
                break;
            case 5:
                deleteBook();
                break;
            case 6:
                listCustomer();
                break;
            case 7:
                borrowBook();
                break;
            case 8:
                reservedBook();
                break;
            case 9:
                returnBook();
                break;
            case 0:
                quit = true;
                break;
            default:
                std::cout << "Wrong choice please try again" << std::endl;
        }
        std::cout << std::endl;
    }
    save();
}

bool Library::lookUpBook(const std::string &author, const std::string &title, Book *bookPtr) {
    for ( std::pair<const int, Book> &entry: sBookMap) {
        const Book &book = entry.second;
        if ((book.author() == author) && (book.title() == title)) {
            if (bookPtr != nullptr)
                *bookPtr = book;
            return true;
        }
    }
    return false;
}

bool Library::lookUpCustomer(const std::string &name, const std::string &address, Customer *customerPtr) {
    for (std::pair<const int, Customer> &entry: sCustomerMap) {
        const Customer &customer = entry.second;
        if ((customer.name() == name) && (customer.address() == address)) {
            if (customerPtr != nullptr) { *customerPtr = customer; }
            return false;
        }
    }
    return true;
}

void Library::addBook() {
    std::string author;
    std::cout << " Author : ";
    std::cin >> author;

    std::string title;
    std::cout << " Title : ";
    std::cin >> title;

    if (!lookUpBook(author, title)) {
        std::cout << std::endl << " The Book " << title << " By " << author << " already Exits" << std::endl;
        return;
    }
    Book book(author, title);
    sBookMap[book.bookId()] = book;
    std::cout << std::endl << " Added: " << book << std::endl;
}

void Library::deleteBook() {
    std::string author;
    std::cout << " Author: ";
    std::cin >> author;

    std::string title;
    std::cout << " Title: ";
    std::cin >> title;

    Book book;
    if (!lookUpBook(author, title, &book)) {
        std::cout << std::endl << "There is no book " << title << " by "
                  << "author " << author << "." << std::endl;
        return;
    }
    for (std::pair<const int, Customer> entry: sCustomerMap) {
        Customer &customer = entry.second;
        customer.returnBook(book.bookId());
        customer.unreserveBook(book.bookId());
        sCustomerMap[customer.Id()] = customer;
    }
    sBookMap.erase(book.bookId());
    std::cout << std::endl << "Deleted." << std::endl;
}

void Library::listCustomer() {
    if (sCustomerMap.empty()) {
        std::cout << "No customers." << std::endl;
        return;
    }
    for (const std::pair<const int, Customer> &entry: sCustomerMap) {
        const Customer &customer = entry.second;
        std::cout << customer << std::endl;
    }
}

void Library::listBook() {
    if (sBookMap.empty()) {
        std::cout << " No Books. " << std::endl;
        return;
    }
    for (const std::pair<const int, Book> &entry: sBookMap) {
        const Book &book = entry.second;
        std::cout << book << std::endl;
    }
}


void Library::addCustomer() {
    std::string name;
    std::cout << " Name ";
    std::cin >> name;

    std::string address;
    std::cout << " Address ";
    std::cin >> address;

    if (lookUpCustomer(name, address)) {
        std::cout << std::endl << " A customer with name " << name
                  << " and address " << address << " already exists. "
                  << std::endl;
        return;
    }
    Customer customer(name, address);
    sCustomerMap[customer.Id()] = customer;
    std::cout << std::endl << " Added. " << std::endl;
}

[[maybe_unused]] void Library::deleteCustomer() {
    std::string name;
    std::cout << " Name: ";
    std::cin >> name;

    std::string address;
    std::cout << " Address: ";
    std::cin >> address;

    Customer customer;
    if (!lookUpCustomer(name, address, &customer)) {
        std::cout << " Customer " << name << " Has borrowed at least "
                  << " One book and cannot be deleted. " << std::endl;
        return;
    }
    for (const std::pair<const int, Book> &entry: sBookMap) {
        Book book = entry.second;
        book.unreserveBook(customer.Id());
        sBookMap[book.bookId()] = book;
    }
    std::cout << std::endl << " Deleted. " << std::endl;
    sCustomerMap.erase(customer.Id());
}

void Library::borrowBook() {
    std::string author;
    std::cout << " Author: ";
    std::cin >> author;

    std::string title;
    std::cout << " Title: ";
    std::cin >> title;

    Book book;
    if (!lookUpBook(author, title, &book)) {
        std::cout << std::endl << " There book " << title << " by "
                  << " author " << author << " . " << std::endl;
        return;
    }

    std::string name;
    std::cout << " Customer name: ";
    std::cout << name;

    std::string address;
    std::cout << " Address: ";
    std::cin >> address;

    Customer customer;
    if (!lookUpCustomer(name, address, &customer)) {
        std::cout << std::endl << "There is no customer with name " << name
                  << " and address " << address << " . " << std::endl;
        return;
    }
    book.borrowBook(customer.Id());
    customer.borrowBook(book.bookId());
    sBookMap[book.bookId()] = book;
    sCustomerMap[customer.Id()] = customer;
    std::cout << std::endl << " Borrowed. " << std::endl;
}

void Library::reservedBook() {
    std::string author;
    std::cout << " Author: ";
    std::cin >> author;

    std::string title;
    std::cout << " Title: " << std::endl;
    std::cin >> title;

    Book book;
    if (!lookUpBook(author, title, &book)) {
        std::cout << std::endl << "There is no book " << title << " By "
                  << " author " << author << "." << std::endl;
        return;
    }
    if (!book.borrowed()) {
        std::cout << std::endl << "The book with author " << author
                  << " and title " << title << " has not been "
                  << "borrowed. please borrow the book instead. " << std::endl;
        return;
    }
    std::string name;
    std::cout << " Customer name: ";
    std::cin >> name;

    std::string address;
    std::cout << " Address: ";
    std::cin >> address;

    Customer customer;
    if (!lookUpCustomer(name, address, &customer)) {
        std::cout << std::endl << "No customer with name " << name
                  << " and address " << address << " exits. " << std::endl;
        return;
    }
    if (book.customerId() == customer.Id()) {
        std::cout << std::endl << " The book has already been borrowed by "
                  << name << " . " << std::endl;
        return;
    }
    customer.reserveBook(book.bookId());
    unsigned int position = book.reserveBook(customer.Id());

    sBookMap[book.bookId()] = book;
    sCustomerMap[customer.Id()] = customer;

    std::cout << std::endl << position << "nd reserved. " << std::endl;
}

void Library::returnBook() {
    std::string author;
    std::cout << " Author: ";
    std::cin >> author;

    std::string title;
    std::cout << " Title : ";
    std::cin >> title;

    Book book;
    if (!lookUpBook(author, title, &book)) {
        std::cout << std::endl << "No book " << title
                  << " by " << author << " Exits. " << std::endl;
        return;
    }

    if (!book.borrowed()) {
        std::cout << std::endl << " The book " << title
                  << " by " << author
                  << " has not been borrowed " << std::endl;
        return;
    }
    book.returnBook();
    std::cout << std::endl << " Returned. " << std::endl;

    Customer customer = sCustomerMap[book.customerId()];
    customer.returnBook(book.bookId());
    sCustomerMap[customer.Id()] = customer;

    std::list<int> &reservationList = book.reservationList();

    if (!reservationList.empty()) {
        int newCustomerId = reservationList.front();
        reservationList.erase(reservationList.begin());
        book.borrowBook(newCustomerId);
        Customer newCustomer = sCustomerMap[newCustomerId];
        newCustomer.borrowBook(book.bookId());

        sCustomerMap[newCustomerId] = newCustomer;
        std::cout << std::endl << " Borrowed by " << newCustomer.name() << std::endl;
    }
    sBookMap[book.bookId()] = book;
}

void Library::save() {
    std::ofstream outStream(sBinaryPath);

    // D'abord nous ecrivons le nombre  de livres et puis les informations de chacun des livres

    if (outStream) {
        unsigned int numberOfBooks = sBookMap.size();
        outStream.write((char *) &numberOfBooks, sizeof numberOfBooks);
        for (const std::pair<const int, Book> &entry: sBookMap) {
            Book book = entry.second;
            book.write(outStream);
        }

        unsigned int numberOfCustomers = sCustomerMap.size();
        outStream.write((char *) &numberOfCustomers, sizeof numberOfCustomers);

        for (const std::pair<const int, Customer> &entry: sCustomerMap) {
            const Customer &customer = entry.second;
            customer.write(outStream);
        }
    }
}

void Library::load() {
    std::ifstream inStream(sBinaryPath);
    if (inStream) {
        int numberOfBooks;
        inStream.read((char *) &numberOfBooks, sizeof numberOfBooks);
        for (int count = 0; count < numberOfBooks; ++count) {
            Book book;
            book.read(inStream);
            sBookMap[book.bookId()] = book;
            Book::MaxBookId = std::max(Book::MaxBookId, book.bookId());
        }
        int numberOfCustomers;
        inStream.read((char *) &numberOfCustomers, sizeof numberOfCustomers);

        for (int count = 0; count < numberOfCustomers; ++count) {
            Customer customer;
            customer.read(inStream);
            sCustomerMap[customer.Id()] = customer;
            Customer::MaxCustomerId = std::max(Customer::MaxCustomerId, customer.Id());
        }

    }

}
