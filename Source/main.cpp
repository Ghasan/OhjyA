/*

OhjyA Program 1 beta 3, based on OhjyA C++ 1 beta 5.

OhjyA Program is an ASCII-text file encryption program based on 'OhjyA Algorithm'.
Copyright (C) 2010  Ghasan Al-Sakkaf

OhjyA Program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OhjyA Program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OhjyA Program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <cstdlib>
//#include <string>
#include <sstream>
#include <fstream>
#include "OhjyAClass.h"
using std::getline;

string filePath, newFilePath, fileContent, password, s_encryption, s_incomplete, s_firstPosition, s_secondPosition, s_firstValue, s_secondValue, nextC; 
int firstPosition, secondPosition, firstValue, secondValue, loopVar1;
bool encryption, incomplete, first_time_running = true, ohjya_created = false;
OhjyA *newOhjyAptr = 0;

void loop_if_no_entry(string &str, string what_to_enter) {

    while(str.length() == 0) {
        cout<<"Nothing typed. Try again.\n"<<what_to_enter;
        getline(cin, str);
    }
}

string return_in_lower(string str) {

    string fstr = str;
    for(loopVar1 = 0; loopVar1<fstr.length(); loopVar1++) fstr[loopVar1] = (char)tolower(fstr[loopVar1]);

    return fstr;

}

bool is_it_int(string str) {

    for(loopVar1 = 0; loopVar1<str.length(); loopVar1++) {
        if((int)str[loopVar1]>57 || (int)str[loopVar1]<48) {return false; break;}
    }

    return true;

}

void another_time_running() {

    cout<<"\n---^---\n\n";
    first_time_running = false;

}

void exit_or_again(string str, int (*insertmain)()) {

    if(return_in_lower(str) == "exit") exit(0);
    else if(return_in_lower(str) == "again") {
        if(newOhjyAptr == 0) {another_time_running(); exit(insertmain());}
        else {newOhjyAptr->~OhjyA(); newOhjyAptr = 0; another_time_running(); exit(insertmain());}
    }
}

int main() {

    while(first_time_running == true) {

        cout<<"OhjyA Program 1 beta 3, based on OhjyA C++ 1 beta 5.\nOhjyA Program is an ASCII-text file encryption\nprogram based on 'OhjyA Algorithm'.\nCopyright (C) 2010 Ghasan Al-Sakkaf.\nOhjyA is licensed under GNU General Public License version 3.\n---------\n\n";
        first_time_running = false;

    }

    cout<<"File path: ";
    getline(cin, filePath);
    loop_if_no_entry(filePath, "File path: ");
    exit_or_again(filePath, main);
    ifstream readFile(filePath.c_str());
    getline(readFile, fileContent, char(0));
    readFile.close();

    cout<<"Enter password: ";
    getline(cin, password);
    loop_if_no_entry(password, "Enter password: ");
    exit_or_again(password, main);

    cout<<"Do you want to encrypt or decrypt? \"en\" to encrypt or \"de\" to decrypt: ";
    getline(cin, s_encryption);
    exit_or_again(s_encryption, main);

    while(!(return_in_lower(s_encryption) == "en" || return_in_lower(s_encryption) == "de")) {
        cout<<"Invalid input. Try again.\nDo you want to encrypt or decrypt? \"en\" to encrypt or \"de\" to decrypt: ";
        getline(cin, s_encryption); 
        exit_or_again(s_encryption, main);
    }

    if(s_encryption == "en") {
        encryption = true;
        
        cout<<"Do you want to take elements? Type \"yes\" or \"no\". Range from "<<1<<", "<<fileContent.length()*2<<": ";
        getline(cin, s_incomplete);
        exit_or_again(s_incomplete, main);

        while(!(return_in_lower(s_incomplete) == "yes" || return_in_lower(s_incomplete) == "no")) {
            cout<<"Invalid input. Try again.\nDo you want to take elements? Type \"yes\" or \"no\". Range from 1 to "<<fileContent.length()*2<<": ";
            getline(cin, s_incomplete);
            exit_or_again(s_incomplete, main);
        }

        if(s_incomplete == "yes") {
            incomplete = true;

            cout<<"Enter first position: ";
            getline(cin, s_firstPosition);
            exit_or_again(s_firstPosition, main);

            while(is_it_int(s_firstPosition) == false) {
                cout<<"Invalid input. Try again.\nEnter first position: ";
                getline(cin, s_firstPosition);
                exit_or_again(s_firstPosition, main);
            }

            stringstream(s_firstPosition)>>firstPosition;

            cout<<"Enter second position: ";
            getline(cin, s_secondPosition);
            exit_or_again(s_secondPosition, main);

            while(is_it_int(s_secondPosition) == false) {
                cout<<"Invalid input. Try again.\nEnter second position: ";
                getline(cin, s_secondPosition);
                exit_or_again(s_secondPosition, main);
            }

            stringstream(s_secondPosition)>>secondPosition;

            OhjyA newOhjyA(fileContent, password, encryption, incomplete, firstPosition, secondPosition);
            newOhjyAptr = &newOhjyA;

            OhjyAmember no_error;
            no_error = newOhjyA._getmember("noerror");
            bool *no_errorptr;
            no_errorptr = (bool*) no_error.ptr;

            if(*no_errorptr == true) {
                
                OhjyAmember encryptedfile;
                encryptedfile = newOhjyA._getmember("encryptedstring");
                string *encryptedfileptr;
                encryptedfileptr = (string*)encryptedfile.ptr;
                
                newFilePath = filePath + ".ohj";
                ofstream newFile(newFilePath.c_str(), ios::trunc);
                newFile<<*encryptedfileptr;
                newFile.close();
                
                OhjyAmember firstvalue;
                firstvalue = newOhjyA._getmember("firstvalue");
                int *firstvalueptr;
                firstvalueptr = (int*)firstvalue.ptr;
                firstValue = *firstvalueptr;
                
                OhjyAmember secondvalue;
                secondvalue = newOhjyA._getmember("secondvalue");
                int *secondvalueptr;
                secondvalueptr = (int*)secondvalue.ptr;
                secondValue = *secondvalueptr;
                
                newOhjyA.~OhjyA();
                newOhjyAptr = 0;

                cout<<"\nEncryption is successful!\nDon't forget these parameters:\nFirst position: "<<firstPosition<<", Value: "<<firstValue<<".\nSecond position: "<<secondPosition<<", Value: "<<secondValue<<".";
                cout<<"\n\nRun again? Type \"yes\" or \"no\": ";
                getline(cin, nextC);
                if(return_in_lower(nextC) == "no") exit(0);
                exit_or_again(nextC, main);

                while(return_in_lower(nextC) != "yes") {
                    cout<<"Invalid input. Try again.\nRun again? Type \"yes\" or \"no\": ";
                    getline(cin, nextC);
                    if(return_in_lower(nextC) == "no") exit(0);
                    exit_or_again(nextC, main);
                }
                
                another_time_running();
                exit(main());
            }
            
            else {
            
                newOhjyA.~OhjyA();
                newOhjyAptr = 0;

                cout<<"\nOops! Looks like an error occured!\nTry again or exit. \"yes\" to try again or \"no\" to exit: ";
                getline(cin, nextC);
                if(return_in_lower(nextC) == "no") exit(0);
                exit_or_again(nextC, main);

                while(return_in_lower(nextC) != "yes") {
                    cout<<"Invalid input. Try again.\nRun again? Type \"yes\" or \"no\": ";
                    getline(cin, nextC);
                    if(return_in_lower(nextC) == "no") exit(0);
                    exit_or_again(nextC, main);
                }
                
                another_time_running();
                exit(main());
            }
        }
            
        else {
        
            incomplete = false;
        
            OhjyA newOhjyA(fileContent, password, encryption, incomplete);
            newOhjyAptr = &newOhjyA;

            OhjyAmember no_error;
            no_error = newOhjyA._getmember("noerror");
            bool *no_errorptr;
            no_errorptr = (bool*) no_error.ptr;

            if(*no_errorptr == true) {
                
                OhjyAmember encryptedfile;
                encryptedfile = newOhjyA._getmember("encryptedstring");
                string *encryptedfileptr;
                encryptedfileptr = (string*)encryptedfile.ptr;
                
                newFilePath = filePath + ".ohj";
                ofstream newFile(newFilePath.c_str(), ios::trunc);
                newFile<<*encryptedfileptr;
                newFile.close();

                newOhjyA.~OhjyA();
                newOhjyAptr = 0;

                cout<<"\nEncryption is successful!";
                cout<<"\nRun again? Type \"yes\" or \"no\": ";
                getline(cin, nextC);
                if(return_in_lower(nextC) == "no") exit(0);
                exit_or_again(nextC, main);

                while(return_in_lower(nextC) != "yes") {
                    cout<<"Invalid input. Try again.\nRun again? Type \"yes\" or \"no\": ";
                    getline(cin, nextC);
                    if(return_in_lower(nextC) == "no") exit(0);
                    exit_or_again(nextC, main);
                }
                
                another_time_running();
                exit(main());
            }
            
            else {
                
                newOhjyA.~OhjyA();
                newOhjyAptr = 0;

                cout<<"\nOops! Looks like an error occured!\nTry again or exit. \"yes\" to try again or \"no\" to exit: ";
                getline(cin, nextC);
                if(return_in_lower(nextC) == "no") exit(0);
                exit_or_again(nextC, main);

                while(return_in_lower(nextC) != "yes") {
                    cout<<"Invalid input. Try again.\nRun again? Type \"yes\" or \"no\": ";
                    getline(cin, nextC);
                    if(return_in_lower(nextC) == "no") exit(0);
                    exit_or_again(nextC, main);
                }
                
                another_time_running();
                exit(main());
            }
        }
    }

    else {
    
        encryption = false;
        
        cout<<"Do you want to input elements? Type \"yes\" or \"no\": ";
        getline(cin, s_incomplete);
        exit_or_again(s_incomplete, main);

        while(!(return_in_lower(s_incomplete) == "yes" || return_in_lower(s_incomplete) == "no")) {
            cout<<"Invalid input. Try again.\nDo you want to input elements? Type \"yes\" or \"no\": ";
            getline(cin, s_incomplete);
            exit_or_again(s_incomplete, main);
        }
        
        if(s_incomplete == "yes") {
        
            incomplete = true;
            
            cout<<"Enter first position: ";
            getline(cin, s_firstPosition);
            exit_or_again(s_firstPosition, main);

            while(is_it_int(s_firstPosition) == false) {
                cout<<"Invalid input. Try again.\nEnter first position: ";
                getline(cin, s_firstPosition);
                exit_or_again(s_firstPosition, main);
            }

            stringstream(s_firstPosition)>>firstPosition;
            
            cout<<"Enter first value: ";
            getline(cin, s_firstValue);
            exit_or_again(s_firstValue, main);

            while(is_it_int(s_firstValue) == false) {
                cout<<"Invalid input. Try again.\nEnter first Value: ";
                getline(cin, s_firstValue);
                exit_or_again(s_firstValue, main);
            }

            stringstream(s_firstValue)>>firstValue;
            
            cout<<"Enter second position: ";
            getline(cin, s_secondPosition);
            exit_or_again(s_secondPosition, main);

            while(is_it_int(s_secondPosition) == false) {
                cout<<"Invalid input. Try again.\nEnter second position: ";
                getline(cin, s_secondPosition);
                exit_or_again(s_secondPosition, main);
            }

            stringstream(s_secondPosition)>>secondPosition;
        
            cout<<"Enter second value: ";
            getline(cin, s_secondValue);
            exit_or_again(s_secondValue, main);

            while(is_it_int(s_secondValue) == false) {
                cout<<"Invalid input. Try again.\nEnter second Value: ";
                getline(cin, s_secondValue);
                exit_or_again(s_secondValue, main);
            }

            stringstream(s_secondValue)>>secondValue;
            
            OhjyA newOhjyA(fileContent, password, encryption, incomplete, firstPosition, secondPosition, firstValue, secondValue);
            newOhjyAptr = &newOhjyA;

            OhjyAmember no_error;
            no_error = newOhjyA._getmember("noerror");
            bool *no_errorptr;
            no_errorptr = (bool*)no_error.ptr;
            
            if(*no_errorptr == true) {
            
                OhjyAmember realfile;
                realfile = newOhjyA._getmember("realstring");
                string *realfileptr;
                realfileptr = (string*)realfile.ptr;
                
                newFilePath = filePath.replace(filePath.end()-4, filePath.end(), "");
                ofstream newFile(newFilePath.c_str(), ios::trunc);
                newFile<<*realfileptr;
                newFile.close();
                
                newOhjyA.~OhjyA();
                newOhjyAptr = 0;
                
                cout<<"\nDecryption is successful!";
                cout<<"\nRun again? Type \"yes\" or \"no\": ";
                getline(cin, nextC);
                if(return_in_lower(nextC) == "no") exit(0);
                exit_or_again(nextC, main);

                while(return_in_lower(nextC) != "yes") {
                    cout<<"Invalid input. Try again.\nRun again? Type \"yes\" or \"no\": ";
                    getline(cin, nextC);
                    if(return_in_lower(nextC) == "no") exit(0);
                    exit_or_again(nextC, main);
                }
                
                another_time_running();
                exit(main());
            }
            
            else {
                
                newOhjyA.~OhjyA();
                newOhjyAptr = 0;
                
                cout<<"\nOops! Looks like an error occured!\nTry again or exit. \"yes\" to try again or \"no\" to exit: ";
                getline(cin, nextC);
                if(return_in_lower(nextC) == "no") exit(0);
                exit_or_again(nextC, main);

                while(return_in_lower(nextC) != "yes") {
                    cout<<"Invalid input. Try again.\nRun again? Type \"yes\" or \"no\": ";
                    getline(cin, nextC);
                    if(return_in_lower(nextC) == "no") exit(0);
                    exit_or_again(nextC, main);
                }
                
                another_time_running();
                exit(main());
            }
        }
        
        else {
        
            incomplete = false;
                        
            OhjyA newOhjyA(fileContent, password, encryption, incomplete, firstPosition, secondPosition, firstValue, secondValue);
            newOhjyAptr = &newOhjyA;

            OhjyAmember no_error;
            no_error = newOhjyA._getmember("noerror");
            bool *no_errorptr;
            no_errorptr = (bool*)no_error.ptr;
            
            if(*no_errorptr == true) {
            
                OhjyAmember realfile;
                realfile = newOhjyA._getmember("realstring");
                string *realfileptr;
                realfileptr = (string*)realfile.ptr;
                
                newFilePath = filePath.replace(filePath.end()-4, filePath.end(), "");
                ofstream newFile(newFilePath.c_str(), ios::trunc);
                newFile<<*realfileptr;
                newFile.close();
                
                newOhjyA.~OhjyA();
                newOhjyAptr = 0;
                
                cout<<"\nDecryption is successful!";
                cout<<"\nRun again? Type \"yes\" or \"no\": ";
                getline(cin, nextC);
                if(return_in_lower(nextC) == "no") exit(0);
                exit_or_again(nextC, main);

                while(return_in_lower(nextC) != "yes") {
                    cout<<"Invalid input. Try again.\nRun again? Type \"yes\" or \"no\": ";
                    getline(cin, nextC);
                    if(return_in_lower(nextC) == "no") exit(0);
                    exit_or_again(nextC, main);
                }
                
                another_time_running();
                exit(main());
            }
            
            else {
                
                newOhjyA.~OhjyA();
                newOhjyAptr = 0;
                
                cout<<"\nOops! Looks like an error occured!\nTry again or exit. \"yes\" to try again or \"no\" to exit: ";
                getline(cin, nextC);
                if(return_in_lower(nextC) == "no") exit(0);
                exit_or_again(nextC, main);

                while(return_in_lower(nextC) != "yes") {
                    cout<<"Invalid input. Try again.\nRun again? Type \"yes\" or \"no\": ";
                    getline(cin, nextC);
                    if(return_in_lower(nextC) == "no") exit(0);
                    exit_or_again(nextC, main);
                }
                
                another_time_running();
                exit(main());
            }
        }
    }
}