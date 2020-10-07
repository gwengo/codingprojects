

#ifndef REMINDER_H
#define REMINDER_H

#include "Date.h"
#include <string>



class Reminder : public Date {
private:
    std::string msg;

public:
    Reminder();  //default constructor set date to today's date and message to empty string
    Reminder(const Date &d, const std::string &m);   //alt constructor

    void setMsg(const std::string &msgStr);  //set the message of a Reminder

    std::string getMsg() const;  //get the message of a Reminder
    Date getDate() const;   //get the Date of a Reminder
    std::string toString() const; //get a string version of a Reminder

    // must override these operators so that they operate correctly for Reminders
    Reminder operator+(int add) const;       // add days to a Reminder
    Reminder operator-(int sub) const;       // subtract days from a Reminder
    bool operator==(const Reminder &rhs) const;  // determine equality of two Reminders


    virtual void print(std::ostream &out = std::cout) const;
};

std::ostream &operator<< (std::ostream &os, const Reminder &rem);

#endif
