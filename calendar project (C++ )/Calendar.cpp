// File name: Calendar.cpp
// Date: 2019


#include <string>
#include <stdexcept>
#include <cassert>
#include "Calendar.h"


// Default Constructor
// Create an empty Calendar (one with zero Reminders)
Calendar::Calendar() : numRem(0), remList(nullptr) {
}


// Copy ctor
Calendar::Calendar(const Calendar &rhs) : numRem(rhs.numRem), remList(nullptr) {
    if (rhs.remList == nullptr) {
        return;
    }
    RemNodePtr origPtr = rhs.remList;
    remList = new RemNode;
    remList->rem = origPtr->rem;
    RemNodePtr newPtr = remList;
    for (origPtr = rhs.remList->next; origPtr != nullptr; origPtr = origPtr->next) {
        newPtr->next = new RemNode;
        newPtr = newPtr->next;
        newPtr->rem = origPtr->rem;
    }
    newPtr->next = nullptr;
}


// Destructor
Calendar::~Calendar() {
    RemNodePtr temp;
    while (remList != nullptr) {
        temp = remList;
        remList = remList->next;
        delete temp;
    }
    numRem = 0;
}


// Assignment operator
const Calendar &Calendar::operator=(const Calendar &rhs) {
    if (this != &rhs) {
        Calendar temp(rhs);
        std::swap(remList, temp.remList);
        std::swap(numRem, temp.numRem);
    }
    return *this;
}


// getNumRem
// Return the total number of Reminders in the Calendar
size_t Calendar::getNumRem() const {
    return numRem;
}


//addRem(const Reminder &r)
//
//Purpose: add/insert a reminder in the list of reminder objects
//Parameters: Reminder r - the reminder to be added
//Returns: size_t - the index position of the inserted reminder
//
//Behavior:
//1. In case of the list being empty: insert as the first element
//2. In case of a non-empty Calendar: insert Reminder in sorted order
//3. In case of already existing Reminder with same date: insert new reminder
//   before (ahead of) the existing one
//4. Return the index of the inserted reminder, using zero-based indexing
size_t Calendar::addRem(const Reminder &r) {
    size_t count = 0;
    RemNodePtr prev = nullptr;
    RemNodePtr cur = remList;
    RemNodePtr newNode = new RemNode;

    while (cur != nullptr && (cur->rem < r)) {
        prev = cur;
        cur = cur->next;
        count++;
    }
    newNode->rem = r;

    if (prev == nullptr) {
        remList = newNode;
    } else {
        prev->next = newNode;
    }
    newNode->next = cur;
    numRem++;
    return count;
}


// getRem(size_t index)
//
// Purpose:    returns the reminder at the specified index in the Calendar,
//             throw exception if index is bad
// Parameters: size_t index - the index of the desired reminder;
//                            using zero-based indexing
// Returns:    Reminder     - the reminder at the specified index
//
// Behavior:
// 1. If the index is invalid, throw an std::invalid_argument exception
// 2. Otherwise, return the reminder at the specified index
Reminder Calendar::getRem(size_t index) const {
    if (index >= numRem) {
        throw std::invalid_argument("Index is invalid.");
    }
    RemNodePtr cur = remList;
    for (size_t i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->rem;
}


// displayRem()
//
// Purpose:    Return a string of all reminders
// Parameters: None
// Returns:    string - containing all the reminders in sorted order with each
//             reminder followed immediately by a newline character.
//             Returns an empty string if the Calendar is empty
std::string Calendar::displayRem() const {
    if (remList == nullptr) {
        return "";
    }
    std::string tempStr = "";
    for (RemNodePtr cur = remList; cur != nullptr; cur = cur->next) {
        tempStr += cur->rem.toString();
        tempStr += "\n";
    }
    return tempStr;
}


// displayRem(size_t index)
//
// Purpose:    Return a string of the reminder at a particular index in the Calendar
// Parameters: size_t index
// Return:     string - containing the reminder
//
// Behavior:
// 1. Returns string containing the reminder at the given index
//    (no newline character added)
// 2. Follows 0-indexing
// 3. If list is empty or the index is invalid, returns an empty string
std::string Calendar::displayRem(size_t index) const {
    if (numRem == 0) {
        return "";
    } else if (index >= numRem) {
        return "";
    }

    std::string str = "";
    size_t count = 0;
    RemNodePtr cur = remList;
    while (cur != nullptr) {
        if (count == index) {
            str += cur->rem.toString();
            break;
        }
        cur = cur->next;
        count++;
    }
    return str;
}


// displayRem(const string& str)
//
// Purpose:    Return a string of all reminders whose message matches the provided
//             string
// Parameters: string str - the string we are supposed to check for match
// Returns:    string     - containing all the matching reminders, in sorted order,
//                          each reminder followed immediately by a newline character.
//
// Behavior:
// 1. Finds any reminders having its message same as the provided string (in a case
//    sensitive manner)
// 2. If no match is found, returns an empty string
// 3. If matches are found, append them on the return string in sorted order each
//    followed by a newline character.
std::string Calendar::displayRem(const std::string &str) const {
    std::string string = "";
    RemNodePtr cur = remList;
    while (cur != nullptr) {
        if (str == cur->rem.getMsg()) {
            string += cur->rem.toString();
            string += "\n";
        }
        cur = cur->next;
    }
    return string;
}


// displayRem(const Date& d)
//
// Purpose:    Return a string of all reminders for a given date
// Parameters: Date d - the date we are supposed to check for match
// Return:     string - containing all the matching reminders, in sorted order,
//             each reminder followed immediately by a newline character.
//
// Behavior:
// 1. Finds any reminders on the provided date
// 2. If no match is found, returns an empty string
// 3. If matches are found, append them on the return string in sorted order each
//    followed by a newline character.
//
// Note: see addRem() for the definition of sorted order of Reminders with
//       the same date.
std::string Calendar::displayRem(const Date &d) const    // searches reminders by date
{
    return displayRem(d, d);
}


// displayRem(const Date& d1, const Date& d2)
//
// Purpose:    Displays reminders in a range of two given dates
// Parameters: Date d1, Date d2 (the range of Dates)
// Return:     string containing all the matching reminders, in sorted order,
//             each reminder followed immediately by a newline character.
//
// Behavior:
// 1. If the Calendar contains no dates in the given range, return an empty string
// 2. Create a string containing all the reminders, in sorted order, which are later
//    than or equal to the smaller of the two dates and are earlier than or equal to
//    the larger of the two dates, with each reminder followed immediately by a
//    newline character.
std::string Calendar::displayRem(const Date &d1, const Date &d2) const {
    Date greater;
    Date smaller;
    std::string str = "";
    if (d2 > d1) {
        greater.setDate(d2);
        smaller.setDate(d1);
    } else {
        greater.setDate(d1);
        smaller.setDate(d2);
    }
    RemNodePtr cur = remList;
    while (cur != nullptr) {
        if (cur->rem.getDate() >= smaller && cur->rem.getDate() <= greater) {
            str += cur->rem.toString();
            str += "\n";
        }
        cur = cur->next;
    }
    return str;
}


// findRem(const Date& d)
//
// Purpose:    Find first reminder for the given date and return its index
// Parameters: Date d - the date to search for
// Return:     int    - value containing the index of the first reminder with
//                      the specified date or -1 if no reminders with that date exist
int Calendar::findRem(const Date &d) const {
    RemNodePtr cur = remList;
    int count = 0;
    while (cur != nullptr && !(cur->rem.getDate() > d)) {
        if (d == cur->rem.getDate()) {
            return count;
        }
        cur = cur->next; count++;
    }
    return -1;
}


//findRem(const std::string& str)
//
//Purpose: Find first reminder with the given message and return its index
//Parameters: string str, the message to search for
//Return: int value containing the index of the first reminder with the specified
//        message, or -1 if no reminders with that message exist
int Calendar::findRem(const std::string &str) const {
    RemNodePtr cur = remList;
    int count = 0;
    while (cur != nullptr) {
        if (str == cur->rem.getMsg()) {
            return count;
        }
        cur = cur->next;
        count++;
    }
    return -1;
}


// deleteRem()
//
// Purpose:    Deletes all reminders earlier than today’s date
// Parameters: None
// Return:     size_t - the number of reminders deleted (a size_t value)
//
// Implementation Notes:
// 1. The default constructor of the Date class initializes a Date object to
//    today's date.
size_t Calendar::deleteRem() {
    Date d1;
    size_t count = 0;
    if (numRem <= 0) {//checks that num rem is not going out of bounds and greater than 0
        return 0;
    }
    RemNodePtr nodeToDeletePtr = remList;
    while (remList != nullptr && remList->rem < d1) {
        remList = remList->next;
        delete nodeToDeletePtr;
        nodeToDeletePtr = remList;
        count++;
    }
    numRem -= count;
    return count;
}


// deleteRem(size_t index)
//
// Purpose:    Deletes reminder object at a provided index position
// Parameters: size_t index
// Return:     size_t - the number of reminders deleted (a size_t value)
//
// Notes:
// 1. If the index is invalid, no deletions will be performed and zero is returned
size_t Calendar::deleteRem(size_t index) {
    if (index >= numRem) {
        return 0;
    }
    RemNodePtr cur = remList;
    RemNodePtr prev = nullptr;
    for (size_t count = 0; count != index; count++) {
        prev = cur;
        cur = cur->next;
    }
    if (prev == nullptr) {
        remList = cur->next;
        delete cur;
        numRem--;
        return 1;
    }
    prev->next = cur->next;
    delete cur;
    numRem--;
    return 1;
}


// deleteRem(const string& str)
//
// Purpose:    Delete all reminders whose message matches a given string
// Parameters: string str - (whose match we want to find, case sensitive)
// Return:     size_t - number of reminders deleted (size_t value)
size_t Calendar::deleteRem(const std::string &str) {
    size_t count = 0;
    RemNodePtr cur = remList;
    RemNodePtr prev = nullptr;
    while (cur != nullptr) {
        if (str == cur->rem.getMsg() && (remList == cur)) {
            remList = cur->next;
            delete cur;
            cur = remList;
            count++;
        } else if (str == cur->rem.getMsg()) {
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
            count++;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    numRem -= count;
    return count;

}


// deleteRem(const Date& d)
//
// Purpose:    Deletes all reminders on a particular date
// Parameters: Date d
// Return:     size_t - number of reminders deleted (size_t value)
size_t Calendar::deleteRem(const Date &d) {
    return deleteRem(d, d);
}


// deleteRem(const Date& d1, const Date& d2)
//
// Purpose:    Deletes all reminders between a range of two given dates
// Parameters: Date d1, Date d2 (the range of Dates)
// Return:     size_t - number of reminders deleted (size_t value)
//
// Behavior:
// 1. If the Calendar contains no dates in the given range, perform no deletions
//    and return zero
// 2. Delete all Reminders which are later than or equal to the smaller of the two
//    dates and are earlier than or equal to the larger of the two dates.
//    Return the number deleted.
size_t Calendar::deleteRem(const Date &d1, const Date &d2) {
    size_t count = 0;
    RemNodePtr cur = remList;
    RemNodePtr prev = nullptr;
    Date greater;
    Date smaller;
    if (d2 > d1) {
        greater.setDate(d2);
        smaller.setDate(d1);
    } else {
        greater.setDate(d1);
        smaller.setDate(d2);
    }
    while (cur != nullptr) {
        if (cur->rem.getDate() >= smaller && cur->rem.getDate() <= greater && (remList == cur)) {
            remList = cur->next;
            delete cur;
            cur = remList;
            count++;
        } else if (cur->rem.getDate() >= smaller && cur->rem.getDate() <= greater) {
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
            count++;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    numRem -= count;
    return count;
}
