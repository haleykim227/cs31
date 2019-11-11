//
//  rental.cpp
//  CS31
//
//  Created by Seungwon Kim on 10/13/18.
//  Copyright © 2018 CS31. All rights reserved.
//
//  Code for Project 2
//  Yentl's Rentals

#include <iostream>
using namespace std;

int main()
{
    // The Setup of the Program Interface
    // Declaration of Variables
    int startodometer;
    int endodometer;
    int rentaldays;
    string customername;
    string luxurycar;
    int month;
    
    // Input, Output, and Checking for Errors
    cout << "Odometer at start: ";
    cin >> startodometer;
    if (startodometer < 0)
        cout << "---" << '\n' << "The starting odometer reading must be nonnegative." << endl;
    
    cout << "Odometer at end: ";
    cin >> endodometer;
    if (endodometer < startodometer)
        cout << "---" << '\n' << "The final odometer reading must be at least as large as the starting reading." << endl;
    
    cout << "Rental days: ";
    cin >> rentaldays;
    if (rentaldays < 0)
        cout << "---" << '\n' << "The number of rental days must be positive." << endl;
    cin.ignore(10000, '\n');
    
    cout << "Customer name: ";
    getline(cin,customername);
    if (customername == "")
        cout << "---" << '\n' << "You must enter a customer name." << endl;
    
    cout << "Luxury car? (y/n): ";
    getline(cin,luxurycar);
    if ((luxurycar != "y") && (luxurycar != "n"))
        cout << "---" << '\n' << "You must enter y or n." << endl;
    
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    if ((month < 1) || (month > 12))
        cout << "---" << '\n' << "The month number must be in the range 1 through 12. " << endl;
    
    cout << "---" << endl;
    
    // Finally, The Math Part!!
    cout.setf(ios::fixed);
    cout.precision(2);

    // Declaration of Variables
    int basecharge;
    int milesdriven;
    double extracharge = 0.00;
    double totalcharge;
    
    // Base Charge
    if (luxurycar == "y")
        basecharge = 61 * rentaldays;
    else
        basecharge = 31 * rentaldays;
    
    // Miles Driven
    milesdriven = endodometer - startodometer;
    
    // Extra Charges Based on Miles Driven
    // If Under 100 Miles
    if (milesdriven <= 100)
        extracharge = 100 * 0.27;
    // If Between 100 and 400 Miles
    if ((milesdriven > 100) && (milesdriven <= 400))
    {
        if (month == 1)
            extracharge = milesdriven * 0.27;
        if (month == 2)
            extracharge = milesdriven * 0.27;
        if (month == 3)
            extracharge = milesdriven * 0.27;
        if (month == 12)
            extracharge = milesdriven * 0.27;
        if ((month >= 4) && (month <= 11))
            extracharge = (100 * 0.27) + ((milesdriven - 100) * 0.21);
    }
    // If Over 400 Miles
    if (milesdriven > 400)
        extracharge = (100 * 0.27) + (300 * 0.21) + ((milesdriven - 400) * 0.19);
    
    // Total Charge Calculation
    totalcharge = basecharge + extracharge;
    
    // Final Statement on Interface
    cout << "The rental charge for ";
    cout << customername;
    cout << " is $";
    cout << totalcharge;
}
