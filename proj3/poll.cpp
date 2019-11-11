//
//  poll.cpp
//  poll
//
//  Created by Haley Kim on 10/28/18.
//  Copyright © 2018 CS31. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cctype>
#include <string>
#include <cmath>
using namespace std;

// Function for hasProperSyntax
// Whether the string pollData only contains digits, letters, and commas
bool digitsalphacomma(string pollData)
{
    // Checking through every character
    for (size_t k = 0; k != pollData.length(); k++)
    {
        // if every character is a digit, or a letter, or a comma, return true
        if ((!isdigit(pollData[k])) && (!isalpha(pollData[k])) && (pollData[k] != ','))
            return false;
    }
    // if not, return false
    return true;
}

// Function for hasProperSyntax
// Whether the state codes are valid
// Returns true if the argument is a two-uppercase-letter state code, or false otherwise.
bool isValidUppercaseStateCode(string statecode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (statecode.size() == 2  &&
            statecode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(statecode) != string::npos);  // match found
}

// Function for hasProperSyntax
// Whether the state forecasts are valid
bool stateforecast(string pollData)
{
    // Checking through every character until the second to last one
    for (size_t k = 0; k != (pollData.length()-1); k++)
    {
        // set statecode as an empty string
        string statecode = "";
        // if the character is a letter
        if ((isalpha(pollData[k])) && (isalpha(pollData[k+1])))
        {
            // add uppercase version of character to empty string
            statecode += toupper(pollData[k]);
            // add uppercase version of character to string with one letter already in it
            statecode += toupper(pollData[k+1]);
            // if the string does not fit the isValidUppercaseState function, return false
            if (!isValidUppercaseStateCode(statecode)){
                return false;
            }
        }
    }
    if (pollData.length() > 2)
    {
        // Checking through every character until the third to last one
        for (size_t k = 0; k != (pollData.length()-2); k++)
        {
            // set votes as an empty string
            // if the character is a digit
            if ((isdigit(pollData[k])) && (isdigit(pollData[k+1])) && (isdigit(pollData[k+2])))
                return false;
        }
    }
    if (pollData.length() > 2)
    {
        // Checking through every character until third to last one
        for (size_t k = 1; k != (pollData.length()-2); k++)
        {
            // if the character is a comma
            if (pollData[k] == ',')
            {
                // if the character before the comma is not a letter, false
                if (!isalpha(pollData[k-1]))
                    return false;
                // if the character after the comma is not a letter, false
                if (!isalpha(pollData[k+1]))
                    return false;
                // if the character after the letter after the comma is not a letter, false
                if (isalpha(pollData[k+1]))
                {
                    if (!isalpha(pollData[k+2]))
                    {
                        return false;
                    }
                }
            }
        }
    }
    // Checking through every character until third to last one
    if (pollData.length() > 2)
    {
        for (size_t k = 0; k != (pollData.length()-2); k++)
        {
            // if character is a digit
            if (isdigit(pollData[k]))
            {
                // if neither the character after the digit nor the one after is a letter, false
                if (!isalpha(pollData[k+1]) && (!isalpha(pollData[k+2])))
                {
                    return false;
                }
                // if both characters behind the digit are letters, false
                if ((isalpha(pollData[k+1])) && (isalpha(pollData[k+2])))
                {
                    return false;
                }
            }
        }
    }
    // Checking through every character until third to last one
    if (pollData.length() > 2)
    {
        for (size_t k = 0; k != (pollData.length()-2); k++)
        {
            // if character is a letter
            if ((isalpha(pollData[k])) && (isalpha(pollData[k+1])) &&(isalpha(pollData[k+2])))
                return false;
        }
    }
    // if none of the conditions are false, return true
    return true;
}

// Declaring function hasProperSyntax with string polldata
bool hasProperSyntax(string pollData)
{
    // if the string is empty, true
    if (pollData.length() == 0)
        return true;
    // if the string has one character, false
    if (pollData.length() == 1)
        return false;
    // if neither the first or second character are letters
    if ((!isalpha(pollData[0])) || (!isalpha(pollData[1])))
        return false;
    // if the string contains characters that are not digits, letters, or commas, function returns false
    if (digitsalphacomma(pollData) == false)
        return false;
    // if the string does not begin or end with a letter, function returns false
    if ((!isalpha(pollData[0])) || (!isalpha(pollData[pollData.size()-1])))
        return false;
    // if it is not a valid state, returns false
    if (stateforecast(pollData) == false)
        return false;
    else
        return true;
}

// tallySeats function to find out how many votes the indicated party will win
int tallySeats(string pollData, char party, int& seatTally)
{
    // if pollData does NOT have proper syntax, return 1
    if (!hasProperSyntax(pollData))
        return 1;
    // if variable party is NOT a letter, return 2
    if (!isalpha(party))
        return 2;
    // set seatTally as 0
    seatTally = 0;
    // if pollData is an empty string, return 0
    if (pollData.length() == 0)
        return 0;
    // set digits as an empty string
    string digits = "";
    // To ensure a pollData string with no digits is still considered a valid entry
    // Checking through every character in string pollData
    for (size_t k = 0; k != (pollData.length()); k++)
    {
        // if character is a digit, add to string digits
        if (isdigit(pollData[k]))
        {
            digits += pollData[k];
        }
    }
    // if string digits is empty, return 0
    if (digits.length() == 0)
        return 0;
    // Checking through every character starting from the fourth character
    for (size_t k = 3; k != (pollData.length()); k++)
    {
        // set strings onedigitvotes and twodigitvotes to empty strings
        string onedigitvotes = "";
        string twodigitvotes = "";
        // if character is a letter and character before is a digit and character before is a digit
        if ((isalpha(pollData[k])) && (isdigit(pollData[k-1])) && (isdigit(pollData[k-2])))
        {
            // if character equals the indicated party code
            if ((toupper(pollData[k])) == (toupper(party)))
            {
                // add first digit to string twodigitvotes and add second digit to string twodigitvotes
                twodigitvotes += pollData[k-2];
                twodigitvotes += pollData[k-1];
                // turn twodigitvotes to an int and store in seatTally
                seatTally += stoi(twodigitvotes);
            }
        }
        // if character is a letter and character before is a digit and character before is a letter
        if ((isalpha(pollData[k])) && (isdigit(pollData[k-1])) && (isalpha(pollData[k-2])))
        {
            // if character equals the indicated party code
            if ((toupper(pollData[k])) == (toupper(party)))
            {
                // add digit to string onedigitvotes
                onedigitvotes += pollData[k-1];
                // turn onedigitvotes into an int and store in seatTally
                seatTally += stoi(onedigitvotes);
            }
        }
    }
    return 0;
}

int main()
{
    // sThese should fucking work
    assert(hasProperSyntax(""));
    assert(hasProperSyntax("ct"));
    assert(hasProperSyntax("ct1d"));
    assert(hasProperSyntax("ct1d1r"));
    assert(hasProperSyntax("ct1d,nv"));
    assert(hasProperSyntax("ct1d,nv,va,nY11g"));
    assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"));
    assert(hasProperSyntax("vt,vt"));
    int seats;
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 22);
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
    assert(tallySeats("va55d,nv,nY3r7D,TX12d", 'D', seats) == 0  &&  seats == 74);
    assert(tallySeats("", 'd', seats) == 0  &&  seats == 0);
    assert(tallySeats("CT", 'i', seats) == 0  &&  seats == 0);
    assert(tallySeats("va55d", '@', seats) == 2  &&  seats == 0);
    assert(tallySeats("va55d@", 'd', seats) == 1  &&  seats == 0);
    assert(tallySeats("va55d3i,nv,nY3r7D2i3r4i,TX12d3i", 'i', seats) == 0  &&  seats == 12);
    // These should not fucking work
    assert(!hasProperSyntax(" "));
    assert(!hasProperSyntax("!"));
    assert(!hasProperSyntax("D"));
    assert(!hasProperSyntax("DP"));
    assert(!hasProperSyntax("vtx"));
    assert(!hasProperSyntax("asdkfhaslfhs"));
    assert(!hasProperSyntax("a,ca"));
    assert(!hasProperSyntax("ct01ny"));
    assert(!hasProperSyntax("ct01,ny"));
    assert(!hasProperSyntax("CT5D,NY9R17D1I,VTx,ne3r00D"));
    assert(!hasProperSyntax("CT!5D,NY9R17D1I,VT,ne3r00D"));
    assert(!hasProperSyntax(",CT5D,NY9R17D1I,VT,ne3r00D"));
    assert(!hasProperSyntax("CT5D, NY9R17D1I,VT,ne3r00D"));
    assert(!hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00DE"));
    assert(!hasProperSyntax("CT5D,NY9R17D1I,VT,,ne3r00D"));
    assert(!hasProperSyntax("CT5D,NY9R17D1I,VT,,ne3r002D"));
    assert(!hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r002D"));
    cerr << "ALL TESTS PASSED" << endl;
}
