// File name: Calendar.h
// Date: 2019
// Description: This is the declaration of the Calendar class, which supports a collection of Reminders




#ifndef CALENDAR_H
#define CALENDAR_H


#include "Date.h"
#include "Reminder.h"
#include "RemNode.h"


class Calendar {

private:
    size_t numRem;        //number of reminders in list
    RemNodePtr remList;   //pointer to head of linked list; RemNodePtr declared in RemNode.h


public:
    // Default Constructor
    // Create an empty Calendar (one with zero Reminders)
    Calendar();

    // Copy ctor
    Calendar(const Calendar &rhs);

    // Assignment operator
    const Calendar &operator=(const Calendar &rhs);

    // Destructor
    ~Calendar();


    // getNumRem
    // Return the total number of Reminders in the Calendar
    size_t getNumRem() const;


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
    size_t addRem(const Reminder &r);


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
    Reminder getRem(size_t index) const;


    // displayRem()
    //
    // Purpose:    Return a string of all reminders
    // Parameters: None
    // Returns:    string - containing all the reminders in sorted order with each
    //             reminder followed immediately by a newline character.
    //             Returns an empty string if the Calendar is empty
    std::string displayRem() const;


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
    std::string displayRem(size_t index) const;


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
    std::string displayRem(const std::string &str) const;


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
    std::string displayRem(const Date &d) const;


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
    std::string displayRem(const Date &d1, const Date &d2) const;


    // findRem(const Date& d)
    //
    // Purpose:    Find first reminder for the given date and return its index
    // Parameters: Date d - the date to search for
    // Return:     int    - value containing the index of the first reminder with
    //                      the specified date or -1 if no reminders with that date exist
    int findRem(const Date &d) const;


    //findRem(const std::string& str)
    //
    //Purpose: Find first reminder with the given message and return its index
    //Parameters: string str, the message to search for
    //Return: int value containing the index of the first reminder with the specified
    //        message, or -1 if no reminders with that message exist
    int findRem(const std::string &str) const;


    // deleteRem()
    //
    // Purpose:    Deletes all reminders earlier than today’s date
    // Parameters: None
    // Return:     size_t - the number of reminders deleted (a size_t value)
    //
    // Implementation Notes:
    // 1. The default constructor of the Date class initializes a Date object to
    //    today's date.
    size_t deleteRem();


    // deleteRem(size_t index)
    //
    // Purpose:    Deletes reminder object at a provided index position
    // Parameters: size_t index
    // Return:     size_t - the number of reminders deleted (a size_t value)
    //
    // Notes:
    // 1. If the index is invalid, no deletions will be performed and zero is returned
    size_t deleteRem(size_t index);


    // deleteRem(const string& str)
    //
    // Purpose:    Delete all reminders whose message matches a given string
    // Parameters: string str - (whose match we want to find, case sensitive)
    // Return:     size_t - number of reminders deleted (size_t value)
    size_t deleteRem(const std::string &str);


    // deleteRem(const Date& d)
    //
    // Purpose:    Deletes all reminders on a particular date
    // Parameters: Date d
    // Return:     size_t - number of reminders deleted (size_t value)
    size_t deleteRem(const Date &d);


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
    size_t deleteRem(const Date &d1, const Date &d2);



};


#endif

