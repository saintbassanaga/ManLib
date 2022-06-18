//
// Created by gcode on 6/18/22.
//

#include "Library.h"

std::map<int ,Book>Library::sBookMap;
std::map<int ,Customer>Library::sCustomerMap;

[[maybe_unused]] std::string Library::sBinaryPath("Library.bin");

Library::Library() {
    load();

    bool quit =false;
    while(!quit){
        std::cout<<"1. Add Book"<<std::endl;
        std::cout<<"2. Delete Book"<<std::endl;
        std::cout<<"3. List Books"<<std::endl;
        std::cout<<"4. Add Customer"<<std::endl;
        std::cout<<"5. Delete Customer"<<std::endl;
        std::cout<<"6. List Customer"<<std::endl;
        std::cout<<"7. Borrow Book"<<std::endl;
        std::cout<<"8. Reserve Book"<<std::endl;
        std::cout<<"9. Return Book"<<std::endl;
        std::cout<<"0. Quit"<<std::endl;
        std::cout<<" : ";

        int choice;
        std::cin>>choice;

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
                quit=true;
                break;
        }
        std::cout<<std::endl;
    }
    save();
}