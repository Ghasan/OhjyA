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

#include <iostream> //Giving access to 'cout' used to print errors on CLI (Command-Line Interface)
//#include <string> // Gives access to string class
#include "OhjyAClass.h" // Includes OhjyA class declaration file; 'OhjyACalss.h'
using namespace std;

int OhjyA::CharToInt(char chr) {

    if(int(chr)>=65 && int(chr)<=90) return CharArray[int(chr)-65]; // To cipher [A-Z] ASCII code into [11-36]
    else if(int(chr)>=97 && int(chr)<=122) return CharArray[int(chr)-71]; // To cipher [a-z] ASCII code into [37-62]
    else if(int(chr)>=48 && int(chr)<=57) return CharArray[int(chr)+4]; // To cipher [0-9] ASCII code into [63-72]
    else    
        switch (chr) { // Ciphers other ASCII code members as following. Note: not all chars are included
            case '\t': return 10; break;
            case '\n': return 73; break;
            case '=' : return 74; break;
            case '?' : return 75; break;
            case '!' : return 76; break;
            case '&' : return 77; break;
            case ':' : return 78; break;
            case '.' : return 79; break;
            case ',' : return 80; break;
            case ';' : return 81; break;
            case '(' : return 82; break;
            case ')' : return 83; break;
            case '/' : return 84; break;
            case '+' : return 85; break;
            case '-' : return 86; break;
            case '*' : return 87; break;
            case '\'': return 88; break;
            case '\\': return 89; break;
            default  : return 90; // Due to unimportance of other ASCII chars, they're ciphers as if they were just one char
        }
}

char OhjyA::IntToChar(int integer) {

    if(integer>=11 && integer<=36) return char(integer+54); // Decipher [11-36] to [A-Z]
    else if(integer>=37 && integer<=62) return char(integer+60); // Decipher [37-62] to [a-z]
    else if(integer>=63 && integer<=72) return char(integer-15); // Retrieve 0-9 ASCII code
    else
        switch(integer) { // Deciphers other ASCII code members
            case 10: return '\t'; break;
            case 73: return '\n'; break;
            case 74: return '=' ; break;
            case 75: return '?' ; break;
            case 76: return '!' ; break;
            case 77: return '&' ; break;
            case 78: return ':' ; break;
            case 79: return '.' ; break;
            case 80: return ',' ; break;
            case 81: return ';' ; break;
            case 82: return '(' ; break;
            case 83: return ')' ; break;
            case 84: return '/' ; break;
            case 85: return '+' ; break;
            case 86: return '-' ; break;
            case 87: return '*' ; break;
            case 88: return '\''; break;
            case 89: return '\\'; break;
            default: return ' ' ; // Deciphers undefined members as just one member; [SPACE]
        }
}

bool OhjyA::is_int(string str) {

    for(loopVar1 = 0; loopVar1<str.length(); loopVar1++) {  // Loops over the string
        if((int)str[loopVar1]>57 || (int)str[loopVar1]<48) {return false; break;} // If found one non-numeric char, returns false
    }

    return true;    // If no non-numeric char found, return true

}

void OhjyA::StrToInt(string str, int *intpointer) { // To make it clear, this function used to convert *numeric-based string* to integer array

    for(loopVar1 = 0; loopVar1<str.length(); loopVar1++) {
        intpointer[loopVar1] = int(str[loopVar1])-48;
    }
    
}

int OhjyA::NextPositionCheckValidity(int ArrayLength, int CurrentPosition, int PasswordValue) {
    
    // HOW IT WORKS:
    // 1- Adds CurrentPosition with PasswordValue
    // 2- Divid the sum over ArrayLength while ignoring fraction to see how many times the sum exceeded ArrayLength if any
    // 3- Multiply fraction-ignored quotient with ArrayLength
    // 4- Subtract the result form the sum of adding CurrentPosition with PasswordValue

    return ((CurrentPosition + PasswordValue)-((int(CurrentPosition + PasswordValue)/ArrayLength)*ArrayLength));
    
}

void OhjyA::ErrorWarning(string inwhere, string why) {

    cout<<"\nError in: "<<inwhere<<", because of: "<<why<<".\n"; // It's easy. I don't know what to explain

}

// Constructing OhjyA object
OhjyA::OhjyA(string newString, string newPasswordString, bool encrypt, bool incomplete, int firstPosition, int secondPosition, int firstValue, int secondValue) {

    // newString is the string you want to encrypt
    // newPasswordString is the numeric-based string
    // encrypt: true to encrypt or false to decrypt
    // incomplete: true to take elements if it's encryption process or put them if it's decryption process
    // or false to not take nor input anyhting. Note: rest parameters will be ignored if no
    // firstPosition is the first position element you want to take or input (Remember that 'take' is when
    // it's encryption process, otherwise 'input' when decryption) For technical issues firstPosition is prefered to
    // be from [1-5]
    // secondPosition is the second position element you take or input.
    // there is no limitation for secondPosition but that it should not exceed stringLength*2 if encryption or stringLength+2 if decryption
    // Next parameters are for the values of first and second position elements (No need to say, you'll just need them in encryption process)

    // This is to fill CharArray with [11-72] numeric sequence, because C++ 
    // doesn't allow declaring elements of array at the time of declaration

    for(loopVar1 = 11; loopVar1<=72; loopVar1++) {
        CharArray[loopVar1-11] = loopVar1;
    }

    // Initializing no_error to true. no_error used to make OhjyA stops from
    // running if no_error turned to false, which indicates a problem
    no_error = true;
                
                //###   Encryption Process of OhjyA Object  ###\\

    if(encrypt == true) {
        encryption = true;  // This variable will help us later time, because 'encrypt' is a local variable for OhjyA object
        is_incomplete = incomplete; // The same goes here; 'incomplete' is a local variable for OhjyA object
        stringLength = newString.length(); // Stores newString length in 'stringLength'

        // If newString is empty, this message appears
        if(stringLength == 0) {ErrorWarning("stringLength","nothing to encrypte"); no_error = false;}
        passwordLength = newPasswordString.length(); // Stores newPasswordString length in 'passwordLength'
        
        // If passwordString is empty, this message appears
        if(passwordLength == 0) {ErrorWarning("passwordLength","no password"); no_error = false;}
        _string = newString;    // Copys newString (Local Scope) to _string (Global Scope)
        stringNumericArray = new int[stringLength]; // Creates a new memory array of int type, and as stringLength
        
        // Because stringNumericArray contains tens numbers which lately will be splitted an used as
        // ones numbers, the nextStringNumericArray will be as twice length of stringNumericArray.
        // Next code creates a new memory array of int type as double length as stringLength

        nextStringNumericArray = new int[2*stringLength];
        passwordArray = new int[passwordLength];    // Creates a new memory array of int type as long as passwordLength
        
        // If newPasswordString isn't a numeric-based string, the next message executed
        if(is_int(newPasswordString) == false) {ErrorWarning("passwordArray", "invalid numeric password"); no_error = false;}
        StrToInt(newPasswordString, passwordArray);
        
        // If you chose to take elements but forgot to enter positions' values, this message executed
        if(incomplete == true && (firstPosition == 0 || secondPosition == 0)) {ErrorWarning("initializing _whatpositions()", "wrong parameters entered"); no_error = false;}
    }

                //###   Decryption Process of OhjyA Object  ###\\

    else {
        encryption = false;
        is_incomplete = incomplete;

        stringLength = newString.length();
        
        // Because less than one tens number dosen't represent any valid char,
        // and that encryptedString relies on tens numbers it should be divisible over 2.
        // If one of this conditions wasn't satisfied, the next message executed

        if(stringLength < 2 || stringLength%2 != 0) {ErrorWarning("stringLength","length is less than 2 or is not divisible over 2"); no_error = false;}
        if(is_int(newString) == false) {ErrorWarning("newString","contains non numeric chars"); no_error = false;}
        passwordLength = newPasswordString.length();
        if(passwordLength == 0) {ErrorWarning("passwordLength","no password"); no_error = false;}

        // If decryption and isn't complete
        if(incomplete == true) {
            
            // If one of the next arguments wasn't changed, error messsage will execute
            if(firstPosition == 0 || secondPosition == 0 || firstValue == 10 || secondValue == 10) {ErrorWarning("initializing _dewhatpositions()", "wrong parameters entered"); no_error = false;}
            stringNumericArray = new int[stringLength+2];   // 'stringLength+2' because we'll add two numbers
            
            // 'stringLength' because we'll use 'anotherStringNumericArray' to keep current string
            //  before adding taken numbers, and then move it whole with the new numbers to
            // stringNumericArray, thus 'stringLength+2'

            anotherStringNumericArray = new int[stringLength];
            
            // We use this function because 'newString' is numeric-based string (We are now decrypting)
            StrToInt(newString, anotherStringNumericArray);
            
            // Because we'll add two numbers and then convert string from ones numbers to
            // tens numbers, we should divide whole string over 2

            nextStringNumericArray = new int[(stringLength+2)/2];
        }

        // If decryption and is complete
        else {
            
            // We don't need here to use anotherStringNumericArray becase we'll not add any number to the string
            stringNumericArray = new int[stringLength];
            StrToInt(newString, stringNumericArray);
            nextStringNumericArray = new int[stringLength/2];   // Easy, because we'll be dealing with tens numbers not ones.
        }

        // The next three lines applies to decryption process no matter if incomplete is true or false
        passwordArray = new int[passwordLength];
        if(is_int(newPasswordString) == false) {ErrorWarning("passwordArray", "invalid numeric password"); no_error = false;}
        StrToInt(newPasswordString, passwordArray);
    }


                //### WHAT TO EXECUTE IF EVREY THING WENT RIGHT ###\\


    if(no_error == true) {  // If at this point no error has recorded in no_error, the rest executed, otherwise stops
                    
                    //### IF ENCRYPTION PROCESS###\\

        if(encrypt == true) { // If it's a encryption process, the following functions executed one by one
            _cipher();
            _sum();
            _storm();
            _numbersmask();
            _whatpositions(firstPosition, secondPosition);
        } 
        
                    //### IF DECRYPTION PROCESS###\\

        else {  // If it's a decryption process, the following functions executed one by one
            _dewhatpositions(firstPosition, secondPosition, firstValue, secondValue);
            _denumbersmask();
            _destorm();
            _desum();
            _decipher();
        }
    }
}

OhjyA::~OhjyA() {
    
    // delete[] anotherStringNumericArray wasn't included because it will executed
    // while program is running as you'll see later

    delete[] stringNumericArray;
    delete[] nextStringNumericArray;
    delete[] passwordArray;
}

OhjyAmember OhjyA::_getmember(string what_member) {

    OhjyAmember member; // Decalre local scope variable of OhjyAmember structure

    // Changes what_member to lowercase, so "stringlenGth" is equal to "STRINGlength"
    for(loopVar1 = 0; loopVar1<what_member.length(); loopVar1++) what_member[loopVar1] = (char)tolower(what_member[loopVar1]);
    
    // Now depending on what variable you ask for, 'member.ptr' will carry the pointer in void format
    // so you'll need later to typecast it. 'member.looptime' will give you how many elements inside
    // the array or NOLOOP (Zero) will be put instead if it's just one variable, and the type of what
    // you ask for will be string format in memeber.type. If you entered wrong query, memebr.ptr will
    // set to 0, memeber.looptime to 0, and memeber.type to "NULL". Error message will execute along
    // with

    if(what_member == "stringlength") {member.ptr = &stringLength; member.looptime = NOLOOP; member.type = "int";}
    else if(what_member == "passwordlength") {member.ptr = &passwordLength; member.looptime = NOLOOP ; member.type = "int";}
    else if(what_member == "stringnumericarray") {member.ptr = stringNumericArray; member.looptime = stringLength; member.type = "int";}
    else if(what_member == "nextstringnumericarray") {member.ptr = nextStringNumericArray; member.looptime = (encryption == true ? stringLength*2 : stringLength/2); member.type = "int";}
    else if(what_member == "passwordarray") {member.ptr = passwordArray; member.looptime = passwordLength; member.type = "int";}

    else if(what_member == "anotherstringnumericarray") {
        if(encryption == false) {
            {member.ptr = anotherStringNumericArray; member.looptime = stringLength-2; member.type = "int";}
        }
        else {
            {member.ptr = 0; member.looptime = NOLOOP; member.type = "NULL"; ErrorWarning("_getmember", "anothertextnumericarray is applicable just in decryption"); no_error = false;}
        }
    }

    else if(what_member == "firstvalue") {member.ptr = &firstValue; member.looptime = NOLOOP; member.type = "int";}
    else if(what_member == "secondvalue") {member.ptr = &secondValue; member.looptime = NOLOOP; member.type = "int";}
    else if(what_member == "realstring") {member.ptr = &realString; member.looptime = NOLOOP; member.type = "string";}
    else if(what_member == "encryptedstring") {member.ptr = &encryptedString; member.looptime = NOLOOP; member.type = "string";}
    else if(what_member == "string") {member.ptr = &_string; member.looptime = NOLOOP; member.type = "string";}
    else if(what_member == "encryption" || what_member == "encrypt") {member.ptr = &encryption; member.looptime = NOLOOP; member.type = "bool";}
    else if(what_member == "isincomplete") {member.ptr = &is_incomplete; member.looptime = NOLOOP; member.type = "bool";}
    else if(what_member == "noerror") {member.ptr = &no_error; member.looptime = NOLOOP; member.type = "bool";}
    else { member.ptr = 0; member.looptime = NOLOOP; member.type = "NULL"; ErrorWarning("_getmember", "invalid query"); no_error = false;}

    return member; // Finally return result in OhjyAmember structure

}

// Rest code is easy to understand as long as you know how OhjyA algorithm works

void OhjyA::_cipher() {
    
    if(no_error == true) {

        for(loopVar1 = 0; loopVar1<stringLength; loopVar1++) {
            stringNumericArray[loopVar1] = CharToInt(_string[loopVar1]);
        }
    }
}

void OhjyA::_sum() {
    
    if(no_error == true) {

        passwordLoop = RESET;
        for(loopVar1 = 0; loopVar1<stringLength; loopVar1++) {
            while(passwordLoop == passwordLength) passwordLoop = RESET;
            stringNumericArray[loopVar1] = stringNumericArray[loopVar1] + passwordArray[passwordLoop];
            passwordLoop++;
        }
    }
}

void OhjyA::_storm() {

    if(no_error == true) {

        for(loopVar1 = 0; loopVar1<stringLength; loopVar1++) {
            nextStringNumericArray[loopVar1*2] = stringNumericArray[loopVar1] / 10;
            nextStringNumericArray[loopVar1*2+1] = stringNumericArray[loopVar1] % 10;
        }
        
        passwordLoop = RESET;
        for(loopVar1 = 0; loopVar1<2*stringLength; loopVar1++) {
            while(passwordLoop == passwordLength) passwordLoop = RESET;
            nextPosition = NextPositionCheckValidity(2*stringLength, loopVar1, passwordArray[passwordLoop]);
            tempMem = nextStringNumericArray[loopVar1];
            nextStringNumericArray[loopVar1] = nextStringNumericArray[nextPosition];
            nextStringNumericArray[nextPosition] = tempMem;
            passwordLoop++;
        }
    }
}

void OhjyA::_numbersmask() {
    
    if(no_error == true) {  

        int numbersMaskArray[] = {0,1,2,3,4,5,6,7,8,9};

        passwordLoop = RESET;
        for(loopVar1 = 0; loopVar1<10; loopVar1++) {
            while(passwordLoop == passwordLength) passwordLoop = RESET;
            nextPosition = NextPositionCheckValidity(10, loopVar1, passwordArray[passwordLoop]);
            tempMem = numbersMaskArray[loopVar1];
            numbersMaskArray[loopVar1] = numbersMaskArray[nextPosition];
            numbersMaskArray[nextPosition] = tempMem;
            passwordLoop++;
        }
        
        encryptedString = "";
        for(loopVar1 = 0; loopVar1<2*stringLength; loopVar1++) {
            nextStringNumericArray[loopVar1] = numbersMaskArray[nextStringNumericArray[loopVar1]];
            encryptedString = encryptedString + char(nextStringNumericArray[loopVar1]+48);
        }
    }
}

void OhjyA::_whatpositions(int firstPosition, int secondPosition) {

    if(no_error == true && is_incomplete == true) {

        if((firstPosition > 2*stringLength || firstPosition < 1) && (secondPosition <= 2*stringLength && secondPosition >= 1)) {ErrorWarning("_whatpositions()", "first position is out of range"); no_error = false;}
        else if((firstPosition <= 2*stringLength && firstPosition >= 1) && (secondPosition > 2*stringLength || secondPosition < 1)) {ErrorWarning("_whatpositions()", "second position is out of range"); no_error = false;}
        else if((firstPosition > 2*stringLength || firstPosition < 1) && (secondPosition > 2*stringLength || secondPosition < 1)) {ErrorWarning("_whatpositions()", "both of first and second positions are out of range"); no_error = false;}
        else if(firstPosition >= secondPosition) {ErrorWarning("_whatpositions()", "first position can not be greater than the second position"); no_error = false;}
        else {
            --firstPosition;
            --secondPosition;
            firstValue = nextStringNumericArray[firstPosition];
            nextStringNumericArray[firstPosition] = -1;
            secondValue = nextStringNumericArray[secondPosition];
            nextStringNumericArray[secondPosition] = -1;
            encryptedString = "";
            for(loopVar1 = 0; loopVar1<2*stringLength; loopVar1++) {
                if(loopVar1 == firstPosition || loopVar1 == secondPosition) continue;
                else {
                    encryptedString = encryptedString + char(nextStringNumericArray[loopVar1]+48);
                }
            }
        }   
    }
}

void OhjyA::_dewhatpositions(int firstPosition, int secondPosition, int firstValue, int secondValue) {

    if(no_error == true && is_incomplete == true) {

        if((firstPosition > stringLength+2 || firstPosition < 1) && (secondPosition <= stringLength+2 && secondPosition >= 1)) {ErrorWarning("_dewhatpositions()", "first position is out of range"); no_error = false;}
        else if((firstPosition <= stringLength+2 && firstPosition >= 1) && (secondPosition > stringLength+2 || secondPosition < 1)) {ErrorWarning("_dewhatpositions()", "second position is out of range"); no_error = false;}
        else if((firstPosition > stringLength+2 || firstPosition < 1) && (secondPosition > stringLength+2 || secondPosition < 1)) {ErrorWarning("_dewhatpositions()", "both of first and second positions are out of range"); no_error = false;}
        else if(firstPosition >= secondPosition) {ErrorWarning("_dewhatpositions()", "first position can not be equal or greater than second position"); no_error = false;}
        else {
            --firstPosition; 
            --secondPosition;
            loopVar2 = RESET;
            counter = RESET;

            for(loopVar1 = 0; loopVar1<stringLength+2; loopVar1++) {
                if(counter != 2) {
                    if(loopVar1 == firstPosition) {
                        stringNumericArray[loopVar1] = firstValue;
                        counter++;
                    }
                    else if(loopVar1 == secondPosition) {
                        stringNumericArray[loopVar1] = secondValue;
                        counter++;
                    }
                    else {
                        stringNumericArray[loopVar1] = anotherStringNumericArray[loopVar1-counter];
                    }
                }

                else {
                    stringNumericArray[loopVar1] = anotherStringNumericArray[loopVar1-counter];
                }
            }
        }

        delete[] anotherStringNumericArray;
        stringLength = stringLength+2;

    }
}

void OhjyA::_denumbersmask() {

    if(no_error == true) {
    
        int numbersMaskArray[] = {0,1,2,3,4,5,6,7,8,9};

        passwordLoop = RESET;
        for(loopVar1 = 0; loopVar1<10; loopVar1++) {
            while(passwordLoop == passwordLength) passwordLoop = RESET;
            nextPosition = NextPositionCheckValidity(10, loopVar1, passwordArray[passwordLoop]);
            tempMem = numbersMaskArray[loopVar1];
            numbersMaskArray[loopVar1] = numbersMaskArray[nextPosition];
            numbersMaskArray[nextPosition] = tempMem;
            passwordLoop++;
        }

        for(loopVar1 = 0; loopVar1<stringLength; loopVar1++) {
            for(loopVar2 = 0; loopVar2<10; loopVar2++) {
                if(stringNumericArray[loopVar1] == numbersMaskArray[loopVar2]) {stringNumericArray[loopVar1] = loopVar2; break;}
                else continue;
            }
        }
    }
}

void OhjyA::_destorm() {
    
    if(no_error == true) {
    
        int passwordElementPosition, passwordElementValue;
        for(loopVar1 = stringLength-1; loopVar1>=0; loopVar1--) {
            passwordElementPosition = ((loopVar1+1) - ((int(loopVar1+1)/passwordLength) * passwordLength)) - 1;
            while(passwordElementPosition == -1) passwordElementPosition = passwordLength-1;
            passwordElementValue = passwordArray[passwordElementPosition];
            nextPosition = NextPositionCheckValidity(stringLength, loopVar1, passwordElementValue);
            tempMem = stringNumericArray[loopVar1];
            stringNumericArray[loopVar1] = stringNumericArray[nextPosition];
            stringNumericArray[nextPosition] = tempMem;
        }
        
        for(loopVar1 = 0; loopVar1<stringLength/2; loopVar1++) {
            nextStringNumericArray[loopVar1] = (stringNumericArray[loopVar1*2] * 10) + stringNumericArray[(loopVar1*2)+1];
        }
    }
}

void OhjyA::_desum() {
    
    if(no_error == true) {
    
        passwordLoop = RESET;
        for(loopVar1 = 0; loopVar1<stringLength/2; loopVar1++) {
            while(passwordLoop == passwordLength) passwordLoop = RESET;
            nextStringNumericArray[loopVar1] = nextStringNumericArray[loopVar1] - passwordArray[passwordLoop];
            passwordLoop++;
        }
    }
}

void OhjyA::_decipher() {

    if(no_error == true) {

        realString = "";
        for(loopVar1 = 0; loopVar1 < stringLength/2; loopVar1++) {
            realString = realString + IntToChar(nextStringNumericArray[loopVar1]);
        }
    }
}