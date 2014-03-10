//
//  Blowfish.h
//  L2P
//
//  Created by Jaromír Hřibal on 09.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#ifndef __L2P__Blowfish__
#define __L2P__Blowfish__

#include <iostream>
#include <openssl/blowfish.h>
#include "crypt.h"

namespace crypt {
    
    class Blowfish {
        BF_KEY * m_key;
        void crypt(unsigned char * data, size_t len, MODE mode) const;
    public:
        static const size_t KEY_LENGHT = 16; // each new key must have lenght 16
        static const size_t BLOCK_LENGHT = 8; // data must be divided by 8
        Blowfish(const unsigned char * key);
        void setKey(const unsigned char * key);
        // encrypts or decrypts inplace, no need to pass additional buffer for result
        void encrypt(unsigned char * data, size_t len) const;
        void decrypt(unsigned char * data, size_t len) const;
        ~Blowfish();
    };
    
}


#endif /* defined(__L2P__Blowfish__) */
