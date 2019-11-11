//
//  array.cpp
//  array
//
//  Created by Haley Kim on 11/6/18.
//  Copyright © 2018 CS31. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cctype>
#include <string>
#include <cmath>
using namespace std;

// function appendToAll, which adds string to end of each element in array
int appendToAll(string a[], int n, string value)
{
    // if n is a negative value, the function will return -1
    if (n < 0)
        return -1;
    // checking through each element in array
    for (int i = 0; i < n; i++)
    {
        // add value to end of existing element
        a[i] += value;
    }
    return n;
}

// function lookup, which looks up where string target is located in array
int lookup(const string a[], int n, string target)
{
    // if n is a negative value, the function will return -1
    if (n < 0)
        return -1;
    // checking through each element in array
    for (int i = 0; i < n; i++)
    {
        // if element in position i in array a is equal to target, return i
        if (a[i] == target)
            return i;
    }
    // if there are no matches, return -1
    return -1;
}

// function positionOfMax, which looks up the position of the largest string in array
int positionOfMax(const string a[], int n)
{
    // if n is a negative value, the function will return -1
    if (n <= 0)
        return -1;
    // set string max to empty string
    string max = "";
    // set int position to zero
    int position = 0;
    // checking through each element in array
    for (int i = 0; i < n; i++)
    {
        // if element in position i is greater than max
        if (a[i] > max)
        {
            // set max to element in position i and position to i
            max = a[i];
            position = i;
        }
    }
    // if max is an empty string, return 0
    if (max == "")
        return 0;
    // return the final position
    else
        return position;
}

// function rotateLeft, which takes the element at position pos and puts it at the end of the array
int rotateLeft(string a[], int n, int pos)
{
    // if n is a negative value, the function will return -1
    if (n <= 0)
        return -1;
    // if position indicated is negative or larger or equal to n, return -1
    if ((pos < 0) || (pos >= n))
        return -1;
    // assign element in position pos to string goaway
    string goaway = a[pos];
    // checking through each element from pos to the one before last
    for (int i = pos; i < n-1; i++)
    {
        // assign the next element to that element
        a[i] = a[i+1];
    }
    // assign string goaway to the last element
    a[n-1] = goaway;
    return pos;
}

// function countRuns, which checks the number of different strings in the array, treats identical arrays as one array
int countRuns(const string a[], int n)
{
    // if n is a negative value, the function will return -1
    if (n < 0)
        return -1;
    int counter = 0;
    // checking through each element
    for (int i = 0; i < n; i++)
    {
        // if it is the first element and it is not an empty string, add 1 to counter
        if ((i == 0) && a[i] != "")
            counter++;
        // if it is not the first element and it does not equal the element before it, add 1 to counter
        if (i != 0)
            if (a[i] != a[i - 1])
                counter++;
    }
    return counter;
}

// function flip, which flips the order of the elements in the array
int flip(string a[], int n)
{
    // if n is a negative value, the function will return -1
    if (n < 0)
        return -1;
    string replace = "";
    // checking through the first half of the array
    for (int i = 0; i < (n / 2); i++)
    {
        // set string replace to element in position i
        replace = a[i];
        // set element in position i to element in position n-1-i
        a[i] = a[n-1-i];
        // set element in position n-1-i to string replace, aka element in i
        a[n-1-i] = replace;
    }
    return n;
}

// function differ, which finds where the two strings differ
int differ(const string a1[], int n1, const string a2[], int n2)
{
    // if either n is negative, return -1
    if ((n1 < 0) || (n2 < 0))
        return -1;
    if ((n1 == 0) || (n2 == 0))
        return 0;
    // checking through each element
    for (int i = 0; ; i++)
    {
        // if element in position i do not equal each other, return i
        if (a1[i] != a2[i])
            return i;
        // if i is greater than or equal to n1, return n1
        if (i >= n1)
            return n1;
        // if i is greater than or equal to n2, return n2
        if (i >= n2)
            return n2;
    }
}

// function subsequence, which finds the position in a1 where the subsequence of a2 begins
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    // if either n is negative, return -1
    if (n1 < 0)
        return -1;
    if (n2 < 0)
        return -1;
    // if n2 is 0, return 0
    if (n2 == 0)
        return 0;
    // checking through every element of a1
    for (int i = 0; i < n1; i++)
    {
        // if an element in a1 is identical to the first element of a2
        if (a1[i] == a2[0])
        {
            // checking through every element of a2
            for (int j = 0; j < n2; j++)
            {
                // if a1 is not long enough to contain all of a2, return -1
                if (i + j > n1)
                    return -1;
                // if every element of a2 does not equal every element of a1 since the subsequence began, break from for loop
                if (a1[i + j] != a2[j])
                    break;
                // if neither upper scenarios occur, and j equals the last position of a2, return i
                if (j == n2 - 1)
                    return i;
            }
        }
    }
    return -1;
}

// function lookupAny, which finds the smallest position in a1 where it equals an element in a2
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    // if either n is negative, return -1
    if (n1 < 0)
        return -1;
    if (n2 < 0)
        return -1;
    // checking through every element of a1
    for (int i = 0; i < n1; i++)
    {
        // checking through every element of a2
        for (int j = 0; j < n2; j++)
        {
            // if element in position i of a1 equals element of position j in a2, return i
            if (a2[j] == a1[i])
                return i;
        }
    }
    return -1;
}

// function divide, which puts everything smaller than divider to the left and greater to the right
int divide(string a[], int n, string divider)
{
    // if n is negative, return -1
    if (n < 0)
        return -1;
    // checking through every element up until the second to last one
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] > divider)
        {
            // checking through every element from the one after i
            for (int j = i + 1; j < n; j++)
            {
                // if the element is smaller than the divider
                if (a[j] < divider)
                {   // if not, it means that there are no elements smaller than the divider after a[i], and that elements are now sorted accordingly
                    // move element in position i to the end of the array
                    rotateLeft(a, n, i);
                    i--;
                    break;
                }
            }
            
        }
    }
    // checking through every element of a
    for (int k = 0; k < n; k++)
    {
        // if element at position k of a is greater than or equal to the divider, return k
        if (a[k] >= divider)
            return k;
    }
    return n;
}

int main()
{
    string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookup(h, 7, "eleni") == 5);
    assert(lookup(h, 7, "ed") == 2);
    assert(lookup(h, 2, "ed") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "greg", "gavin", "fiona", "kevin" };
    assert(countRuns(g, 2) == 2);
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");
    
    string e[4] = { "ed", "xavier", "", "eleni" };
    assert(subsequence(h, 7, e, 4) == 2);
    assert(appendToAll(e, -1, "!") == -1 && e[0] == "ed" && e[2] == "");
    assert(appendToAll(e, 4, "?") == 4 && e[0] == "ed?" && e[3] == "eleni?");
    
    string d[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
    assert(countRuns(d, 5) == 2);
    assert(lookup(d, 5, "gavin") == 0);
    assert(lookup(d, 5, "xavier") == 3);
    assert(lookup(d, 2, "heather") == -1);
    assert(positionOfMax(d, 5) == 3);
    
    string f[3] = { "fiona", "ed", "john" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(positionOfMax(f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");
    assert(divide(h, 7, "fiona") == 3);
    
    string z[0] = {};
    assert(positionOfMax(z, 0) == -1);
    
    string q[4] = { "john", "max", "mark", "ethan"};
    string j[4] = { "john", "max", "mark", "ethan"};
    assert(differ(q, 4, j, 4) == 4);
    assert(rotateLeft(j, 4, 0) == 0 && j[1] == "mark" && j[3] == "john");
    assert(flip(q, 4) == 4 && q[0] == "ethan" && q[3] == "john");
    
    string o[3] = {"dan", "mark", "john"};
    assert(appendToAll(o, 0, "?") == 0 && o[0] == "dan" && o[2] == "john");
    assert(rotateLeft(o, 0, 0) == -1);
    assert(rotateLeft(o, 3, 3) == -1);
    
    cout << "All tests succeeded" << endl;
}
