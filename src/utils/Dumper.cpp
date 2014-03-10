//
//  Dumper.cpp
//  L2P
//
//  Created by Jaromír Hřibal on 09.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#include "Dumper.h"
#include <iomanip>

namespace utils {
 
    using namespace std;
    
    void Dumper::hex(const unsigned char * data, size_t len) {
    
        cout << endl;
        
        ios::fmtflags f(cout.flags());
        
        for (int i = 0; i < len; i++) {
            cout << "0x" << std::hex << setw(2) << setfill('0') << ((long)(data[i]) & 255) << " ";
        }
        
        cout.flags(f);
        
        cout << endl;
        
    }
    
    bool Dumper::equal(const unsigned char * a, const unsigned char * b, size_t len) {
        
        for(size_t i = 0; i < len; i++) {
            if (a[i] != b[i]) return false;
        }
        
        return true;
    }
    
    bool Dumper::notEqual(const unsigned char * a, const unsigned char * b, size_t len) {
        
        for(size_t i = 0; i < len; i++) {
            if (a[i] != b[i]) return true;
        }
        
        return false;
    }
    
}