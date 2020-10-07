// File name: CalTest.cpp
// Date: 2019
// Description: This program will test the Calendar class

#include <iostream>
#include <string>
#include <stdexcept>
#include "Calendar.h"

int main(void) {


/********************************************************************************/
/* TESTING Default Constructor */

//test:
    Calendar cal1;   // create an empty Calendar object via default ctor

    if (cal1.getNumRem() != 0) {  // test getNumRem()
        std::cout << "Default ctor failed to create an empty calendar" << std::endl;
        std::cout << "Reported that " << cal1.getNumRem() << " reminders exist"
                  << std::endl;
    }

    if (cal1.displayRem() != "") {  // test displayRem()
        std::cout << "Default ctor should produce an empty calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: " << cal1.displayRem()
                  << std::endl;
    }

/********************************************************************************/
/* TESTING addRem(const Reminder &r) */


//test:
    Date d1("01/08/2018");
    Reminder rem1(d1, "First day of classes");

    size_t index = cal1.addRem(rem1);   // test addRem(); Calendar now has one Reminder




//Edge cases:
// In case of the array being empty: insert as the first element
//test:

    if (index != 0) {
        std::cout << "addRem failed to return index 0 for first insertion" << std::endl;
        std::cout << "Returned index == " << index << std::endl;
    }

    if (cal1.getNumRem() != 1) {
        std::cout << "addRem/getNumRem failed after inserting one reminder" << std::endl;
        std::cout << "Reported that " << cal1.getNumRem() << " reminders exist"
                  << std::endl;
    }

    if (cal1.displayRem() != "On 01/08/2018: First day of classes\n") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: (addRem1) " << cal1.displayRem()
                  << std::endl;
    }

    if (cal1.displayRem(index) != "On 01/08/2018: First day of classes") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: (addRem 2) "
                  << cal1.displayRem(index) << std::endl;
    }


// In case of a non-empty array with space available: insert Reminder in sorted
//      order, shifting other items up to make space
//test:
    Date d2("01/09/2018");
    Reminder rem2(d2, "Second day of classes");

    size_t index2 = cal1.addRem(rem2);   // test addRem(); Calendar now has two reminders

    if (index2 != 1) {
        std::cout << "addRem failed to return index 0 for second insertion" << std::endl;
        std::cout << "Returned index == " << index2 << std::endl;
    }



//In case of already existing Reminder with same date: insert new reminder
//      before (ahead of) the existing one.
//test:
    Date d3("01/09/2018");
    Reminder rem3(d3, "Second day of classes");

    size_t index3 = cal1.addRem(rem3);   // test addRem(); Calendar now has two reminders

    if (index3 != 1) {
        std::cout << "addRem failed to return index 0 for second insertion" << std::endl;
        std::cout << "Returned index == " << index3 << std::endl;
    }



// tests grow
//test:
    try {
        for (int i = 0; i < 100; i++) { // attempt to insert 100 reminders (max is 50)
            cal1.addRem(rem1);
        }
        std::cout << "\ngrow works!" << std::endl;
    }
    catch (std::overflow_error &excpt) {
        std::cout << "Exception successfully thrown & caught:: " << excpt.what()
                  << std::endl;
    }


/********************************************************************************/
/* TESTING getNumRem */

//test:
    Calendar cal2;   // create an empty Calendar w 0 reminders via default ctor

    if (cal2.getNumRem() != 0) {  // test getNumRem()
        std::cout << "getNumRem failed to correctly count" << std::endl;
        std::cout << "Reported that " << cal2.getNumRem() << " reminders exist"
                  << std::endl;
    }


/********************************************************************************/
/* TESTING getRem(size_t index) */


//test:
    Date date("01/08/2018");
    Reminder reminder(date, "First day of classes");

    cal2.addRem(reminder);
    if (cal2.getRem(0) != reminder) {  // test getRem()
        std::cout << "getRem() messed up :(r" << std::endl;
        std::cout << "getRem() returned the following reminders: " << cal2.getRem(0)
                  << std::endl;
    }


    cal2.deleteRem();

//Edge cases:
//If the index is invalid, throw an std::invalid_argument exception
//test:
    try {
        cal2.getRem(5);
        std::cout << "\nTHIS MESSAGE SHOULD NOT BE SEEN."
                  << "\nAn overflow exception was not thrown!!" << std::endl;
    }
    catch (std::invalid_argument &excpt) {
        std::cout << "Exception successfully thrown & caught:: " << excpt.what()
                  << std::endl;
    }



/********************************************************************************/
/* TESTING displayRem() */
//

//test:
    if (cal2.displayRem() != "") {  // test displayRem()
        std::cout << "Default ctor should produce an empty calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: " << cal2.displayRem()
                  << std::endl;
    }

/********************************************************************************/
/* TESTING displayRem(size_t index)*/

//tesT:
    Date d4("01/08/2018");
    Reminder rem4(d4, "First day of classes");

    size_t index4 = cal2.addRem(rem4);

    if (cal2.displayRem(index4) != "On 01/08/2018: First day of classes") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem(index4) << std::endl;
    }

// Edge case:
// If array is empty or the index is invalid, returns an empty string
//test:

    if (cal2.displayRem(5) != "") { //invalid index
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem(5) << std::endl;
    }

    cal2.deleteRem();
    if (cal2.displayRem(0) != "") { //array is empty
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem(5) << std::endl;
    }


/********************************************************************************/
/* TESTING displayRem(const string& str) */
//

//test:

    cal2.addRem(rem4);
    if (cal2.displayRem("First day of classes") != "On 01/08/2018: First day of classes\n") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem("First day of classes") << std::endl;
    }

//Edge cases:
// If no match is found, returns an empty string
//test:
    if (cal2.displayRem("No match should be found!") != "") { //invalid index
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem("No match should be found!") << std::endl;
    }
    // case sensitivity
    // test:
    if (cal2.displayRem("first day of classes") != "") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem("No match should be found!") << std::endl;
    }

//tests displayRem(string) such that more than one matching reminders were found

    cal2.addRem(rem4);
    if (cal2.displayRem("First day of classes") !=
        "On 01/08/2018: First day of classes\nOn 01/08/2018: First day of classes\n") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem("First day of classes") << std::endl;
    }

    cal2.deleteRem(1);
/********************************************************************************/
/* TESTING displayRem(const Date& d) */
//

//test:
    if (cal2.displayRem(d4) != "On 01/08/2018: First day of classes\n") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem(d4) << std::endl;
    }

//Edge cases:
//If no match is found, returns an empty string
//test:
    if (cal2.displayRem("01/09/2018") != "") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem("01/09/2018") << std::endl;
    }

/********************************************************************************/
/* TESTING displayRem(const Date& d1, const Date& d2) */


// If the Calendar contains no dates in the given range, return an empty string
//test:
    Date date2("01/03/2018");
    Date date3("01/04/2018");
    if (cal2.displayRem(date3, date2) != "") {
        std::cout << "Unexpected reminder in calendar!" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem(date3, date2) << std::endl;
    }
//Create a string containing all the reminders, in sorted order, which are later
//    than or equal to the smaller of the two dates and are earlier than or equal to
//    the larger of the two dates, with each reminder followed immediately by a
//    newline character.
//test:
    Date d5("01/09/2018");
    Reminder rem5(d5, "Second day of classes");
    cal2.addRem(rem5);
    if (cal2.displayRem(d4, d5) !=
        "On 01/08/2018: First day of classes\nOn 01/09/2018: Second day of classes\n") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem(d4, d5) << std::endl;
    }

//test  the range of Dates spanning from the middle of the calendar  all the way to the end

    Date testDate("01/11/2018");
    Reminder testRem(testDate, "Second day of classes");
    for (size_t i = 0; i < 2; ++i) {
        cal2.addRem(testRem);
    }
    if (cal2.displayRem(++d5, testRem) !=
        "On 01/11/2018: Second day of classes\nOn 01/11/2018: Second day of classes\n") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem(++d5, testRem) << std::endl;
    }

    //test w the range of Dates starting and ending in the middle of the calendar
    Date testDate2("01/10/2018");
    Reminder testRem2(testDate2, "Second day of classes");
    cal2.addRem(testRem2);
    if (cal2.displayRem(--d5, testRem2) !=
        "On 01/09/2018: Second day of classes\nOn 01/10/2018: Second day of classes\n") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem(d5, testRem2) << std::endl;
    }

//test w the smaller Date parameter being larger than all dates in the calendar
    Date bigDate("01/28/2019");
    Date bigDate2("01/29/2019");
    if (cal2.displayRem(bigDate, bigDate2) !=
        "") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: "
                  << cal2.displayRem(d4, d5) << std::endl;
    }

/********************************************************************************/
/* TESTING findRem(const Date& d) */
//

//test:
    if (cal2.findRem(d4) != (int) index4) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "findRem returned the following reminders1: "
                  << cal2.findRem(d4) << std::endl;
    }

    //return  -1 if no reminders with that date exist
    if (cal2.findRem(date2) != -1) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "findRem returned the following reminders2: "
                  << cal2.findRem(date2) << std::endl;
    }
/********************************************************************************/
/* TESTING findRem(const std::string& str) */
//

//test:
    if (cal2.findRem("First day of classes") != (int) index4) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "findRem returned the following reminders3: "
                  << cal2.findRem("First day of classes") << std::endl;
    }

    //return  -1 if no reminders with that date exist + case sensitivity
    if (cal2.findRem("first day of classes") != -1) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "findRem returned the following reminders4: "
                  << cal2.findRem("first day of classes") << std::endl;
    }
/********************************************************************************/
/* TESTING deleteRem() */
//

//test:
    size_t num = cal2.getNumRem();
    if (num != cal2.deleteRem()) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem()1 did not delete all the reminders" << std::endl;
    }

//check not going out of bound, greater than zero, not deleting empty array
    if (0 != cal2.deleteRem()) {
        std::cout << "oops" << std::endl;
        std::cout << "deleteRem() tried to delete an already empty array" << std::endl;
    }

    // test  w/o params such that all dates in the calendar are equal / later than current date
    Date laterTestDate("05/11/2019");
    Reminder laterTestRem(laterTestDate, "Second day of classes");
    for (size_t i = 0; i < 4; ++i) {
        cal2.addRem(laterTestRem); //later than current day
    }
    Date today;
    Reminder oneMoreRem(today, "Second day of classes");
    cal2.addRem(oneMoreRem); //current day
    if (0 != cal2.deleteRem()) {
        std::cout << "oops" << std::endl;
        std::cout << "deleteRem() tried to delete reminders later than current date" << std::endl;
    }


/********************************************************************************/
/* TESTING deleteRem(size_t index) */
//

//test:

    size_t num2 = 1;
    Calendar cal3;
    Date dates0("01/20/2019");
    Date dates1("02/02/2019");
    Date dates2("02/03/2019");
    Date dates3("02/04/2019");
    Date dates4("02/05/2019");
    Date dates5("02/06/2019");
    Date dates6("02/07/2019");
    Reminder remind0(dates0, "day 0");
    Reminder remind1(dates1, "day 1");
    Reminder remind2(dates2, "day 2");
    Reminder remind3(dates3, "day 3");
    Reminder remind4(dates4, "day 4");
    Reminder remind5(dates5, "day 5");
    Reminder remind6(dates6, "day 6");
    cal3.addRem(remind0);
    cal3.addRem(remind1);
    cal3.addRem(remind2);
    cal3.addRem(remind3);
    cal3.addRem(remind4);
    cal3.addRem(remind5);
    cal3.addRem(remind6);

    if (num2 != cal3.deleteRem(6)) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem()2 did not delete all the reminders" << std::endl;
    }

//If the index is invalid, no deletions will be performed and zero is returned
//test:

    if (0 != cal3.deleteRem(6)) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem()3 did not delete all the reminders" << std::endl;
    }

    //test deleteRem(size_t) such that shifting down of reminders is required
    if (1 != cal3.deleteRem(3)) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem()3 did not delete all the reminders" << std::endl;
    }
    cal3.addRem(remind3);
/********************************************************************************/
/* TESTING deleteRem(const string& str) */
//

//test:
    if (num2 != cal3.deleteRem("day 5")) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem()4 did not delete all the reminders" << std::endl;
    }

    Calendar testCal;
    // test  on an empty calendar
    if (0 != testCal.deleteRem("Day 5")) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem()4 did not delete all the reminders" << std::endl;
    }

    // test such that no matches were found/deleted
    testCal.addRem(remind0);
    testCal.addRem(remind1);
    if (0 != testCal.deleteRem("Day 5")) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem()4 did not delete all the reminders" << std::endl;
    }


/********************************************************************************/
/* TESTING  deleteRem(const Date& d) */
//

//test:
    if (num2 != cal3.deleteRem(dates4)) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem()a did not delete all the reminders" << std::endl;
    }
/********************************************************************************/
/* TESTING deleteRem(const Date& d1, const Date& d2) */
//

//test:
    if (++num2 != cal3.deleteRem(dates2, dates3)) {
        std::cout << "Unexpected reminder in calendar!" << std::endl;
        std::cout << "deleteRem()b did not delete all the reminders" << std::endl;
    }

//Edge cases:
// If the Calendar contains no dates in the given range, perform no deletions &
//      return zero
//test:

    Date datesRange1("01/21/2019");
    Date datesRange2("01/22/2019");

    if (0 != cal3.deleteRem(datesRange1, datesRange2)) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem() did not delete all the reminders" << std::endl;
    }


//Reminders are shifted down in the array to fill any vacated entries.
//test:
    if (cal3.displayRem() != "On 01/20/2019: day 0\nOn 02/02/2019: day 1\n") {
        std::cout << "there was an issue shifting array!" << std::endl;
        std::cout << "displayRem returned the following reminders: " << cal3.displayRem()
                  << std::endl;
    }

    // test on an empty calendar
    Calendar testCal2;
    if (0 != testCal2.deleteRem(datesRange1, datesRange2)) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem() did not delete all the reminders" << std::endl;
    }

    //test with the two date parameters out of order(the first one being later than the second one)
    if (2 != cal3.deleteRem(dates1, dates0)) {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "deleteRem() did not delete all the reminders" << std::endl;
    }


/********************************************************************************/


// uncomment the following lines if you are running the program in a
// DOS or terminal window and you want the window to stay open when
// the testing is done.
//	std::cout << "\nEnd of tests. Press enter to exit.";
//	char tt;
//	tt = std::cin.get();


}
