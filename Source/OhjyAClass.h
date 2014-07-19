/*

OhjyA C++ 1 beta 5, based on OhjyA Algorithm 1.

OhjyA C++ is a C++ Class Library used to gain access to OhjyA algorithm with ease.
Copyright (C) 2010  Ghasan Al-Sakkaf

This file is part of OhjyA C++.

OhjyA C++ is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OhjyA C++ is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OhjyA C++.  If not, see <http://www.gnu.org/licenses/>.

*/


/*

How to read comments:

1- Comments either placed right after the specified line or above it.
2- Comments/Line; comments describe just one line next to it or below it,
   unless otherwise stated to describe varoius ones.

*/

#ifndef OhjyA_H
#define OhjyA_H

#define RESET 0 // To Make source code more readable
#define NOLOOP 0

#include <string>
using namespace std;

struct OhjyAmember {    // A new data type to store information of OhjyA private members

        void *ptr;  // void because OhjyA members are with different types
        short int looptime; // Used if member is a numeric array telling  you how many elements inside it
        string type;    // Stores member type in string format

};

class OhjyA {   // OhjyA Class Declaration

    // Private members

    int stringLength, passwordLength, passwordLoop, loopVar1, loopVar2, tempMem, nextPosition, firstValue, secondValue, counter;
    int *stringNumericArray, *nextStringNumericArray, *passwordArray, *anotherStringNumericArray;
    string _string, realString, encryptedString;
    bool encryption, is_incomplete, no_error;
    
    int CharArray[62];  // Used to store numeric values of chars ranging from {A-Z, a-z, 0-9}
    
    int CharToInt(char chr);    // Return numeric equivalent of specific char
    char IntToChar(int integer);    // Return char of numeric value
    bool is_int(string str);    // Checks wheather or not entered strign is an integer
    
    // Fill specified int array with string chars e.g. passwordString to passwordArray
    void StrToInt(string Str, int *intpointer);
    
    // Return the next position current position should swap with
    int NextPositionCheckValidity(int ArrayLength, int CurrentPosition, int PasswordValue);

    void ErrorWarning(string function, string what_variable);   // Print on the CLI what's the error
    void _checkstring();    // Checks if file is valid
    void _checkpassword();  // Checks if password is valid
    void _cipher(); // Ciphers text (Just changes them from thier char status to thier equivalent numeric using CharToInt())
    void _decipher();   // Deciphers text (Just changes tens numbers into thier equivalent char using IntToChar())
    void _sum();    // Adding passwordArray elements to fileNumericArray elements
    void _desum();  // Subtracting passwordArray elements from fileNumericArray elements
    void _storm();  // Swapping elements depending on password (Detailed description can be found in OhjyA Algorithm 1 Datasheet)
    void _destorm();    // Undo elements swapping
    void _numbersmask();    // Represent numbers with other ones / Masking numbers (Detailed description can be found in OhjyA Algorithm 1 Datasheet)
    void _denumbersmask();  // Undo masking numbers
    void _whatpositions(int firstPosition, int secondPosition); // Take elements from encryptedFile
    void _dewhatpositions(int firstPosition, int secondPosition, int firstValue, int secondValue);  // Putting taken elements in thier correct position before decryption

// Public members

public:
    
    // Constructing OhjyA object. Notice not all arguments are necessary depending on what actually you want to construct
    // Refer to 'OhjyA C++ 1 beta 3 Datasheet' for detailed information

    OhjyA(string newFileString, string newPasswordString,bool encrypt, bool incomplete = false, int firstPosition = 0, int secondPosition = 0, int firstValue = 10, int secondValue = 10);
    ~OhjyA();   // Destructor of OhjyA object
    OhjyAmember _getmember(string what_member); // A function giving access to OhjyA private members using OhjyAmember structure

};

#endif