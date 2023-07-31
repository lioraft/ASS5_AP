//
// Created by lior on 1/12/23.
//

// this class is for exceptions catching & handling

#ifndef HW5_CPP_POLITICS_ERROR_H
#define HW5_CPP_POLITICS_ERROR_H

#include <iostream>
using namespace std;

// definition of general error. is abstract because all errors will inherit it and throw informative message
class Error {
public:
    Error() {};
    virtual ~Error() {};
    virtual void Handle()=0;
};

// an error will be thrown whenever the user tries to initialize an object with invalid input
class newObjectError : public Error {
public:
    newObjectError() {};
    virtual ~newObjectError() {};
    virtual void Handle() {cout << "Please enter valid details" << endl;};
};

// an error will be thrown whenever the user tries to remove politician by entering invalid id
class removePoliticianError : public Error {
public:
    removePoliticianError() {};
    virtual ~removePoliticianError() {};
    virtual void Handle() {cout << "Please enter valid id" << endl;};
};

// an error will be thrown whenever the user tries to remove party by entering invalid name
class removePartyError : public Error {
public:
    removePartyError() {};
    virtual ~removePartyError() {};
    virtual void Handle() {cout << "Please enter valid name" << endl;};
};


#endif //HW5_CPP_POLITICS_ERROR_H
