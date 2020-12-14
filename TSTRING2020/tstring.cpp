#include "tstring.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

TString::TString(const char* s) : ptr(nullptr), len(0) {
    if (s != nullptr) {
        len = strlen(s);
        ptr = new char[len+1]; // +1 bo na koncu jest jeszcze \0 konczące literał napisowy
        strcpy(ptr, s);
    }
#ifdef DEBUG
    cout << "TString c-tor: [" << (ptr ? ptr : "pusty") << "]" << endl;
#endif
}

TString::~TString() {
#ifdef DEBUG
    cout << "TString d-tor: [" << (ptr ? ptr : "pusty") << "]" << endl;
#endif
    delete [] ptr;
}

TString::TString( const TString& s ) : ptr(nullptr), len(s.len) {
    if (len > 0) {
        ptr = new char[len+1];
        strcpy(ptr,s.ptr);
    }
#ifdef DEBUG
    cout << "TString cc-tor: [" << (ptr ? ptr : "pusty") << "]" << endl;
#endif    
}

TString& TString::operator=( const TString& s ) {
    if ( this != &s ) { // if ( *this != s )
        delete [] ptr;
        ptr = nullptr;
        len = s.len;
        if (len > 0) {
            ptr = new char[len+1];
            strcpy(ptr,s.ptr);
        }
    }
    #ifdef DEBUG
        cout << "TString copy operator=: [" << (ptr ? ptr : "pusty") << "]" << endl;
    #endif   
    return *this;
}

TString::TString( TString&& s ) : ptr(s.ptr), len(s.len) {
    s.ptr = nullptr;
    s.len = 0;

#ifdef DEBUG
    cout << "TString move c-tor: [" << (ptr ? ptr : "pusty") << "]" << endl;
#endif
}

TString& TString::operator=( TString&& s ) {
    if ( this != &s ) {
        delete [] ptr;
        len = s.len;
        ptr = s.ptr;
        s.len = 0;
        s.ptr = nullptr;
    }
    #ifdef DEBUG
        cout << "TString move operator=: [" << (ptr ? ptr : "pusty") << "]" << endl;
    #endif   
    return *this;
}

char& TString::operator[]( size_t n ) {
    if ( ptr==nullptr ) throw "pusty obiekt";
    if ( n < len ) return ptr[n];
    throw out_of_range("In TString::operator[] argument out of scope");
}

const char& TString::operator[]( size_t n ) const {
    if ( ptr==nullptr ) throw "pusty obiekt";
    if ( n < len ) return ptr[n];
    throw out_of_range("In TString::operator[] argument out of scope");
}

TString::erase(){
    while ( ! s.empty() ){
        cout << s <<endl;
        s.erase(ptr);
    }
}

char *TString::insert(size_t pos, const char *c) {
    if (pos <= len) {
        size_t oldlen = len;
        len = len + strlen(c);
        char *tmp = new char[len + 1];
        strcpy(tmp, ptr);
        for (size_t i = pos; i < pos + strlen(c); ++i) {
            tmp[i] = c[i - pos];
        }
        for (size_t i = pos; i < oldlen; ++i) {
            tmp[i + strlen(c)] = ptr[i];
        }
        tmp[len] = '\0';
        delete [] ptr;
        ptr = tmp;
        return ptr + pos;
    }
    else {
        throw out_of_range("zly argument");
    }

    return ptr;
}

char* TString::insert(size_t pos, char c) {
    return insert(pos, string( { c } ).c_str());
}