//
//  RSA.h
//  L2P
//
//  Created by Jaromír Hřibal on 09.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#ifndef __L2P__RSA__
#define __L2P__RSA__

#include <iostream>
#include <openssl/rsa.h>
#include "crypt.h"

namespace crypt {
    
    class RSA {
        ::RSA * m_rsa;
        BIGNUM * m_pub_exp;
        unsigned char * crypt(const unsigned char * data, MODE mode) const;
        unsigned char * createBuffer() const;
    public:
        static const size_t KEY_LENGHT = 1024;
        static const int PUB_EXP = 65537;
        static const int PADDING = RSA_NO_PADDING;
        RSA();
        unsigned char * encrypt(const unsigned char * data) const; // data must have lenght = 128
        unsigned char * decrypt(const unsigned char * data) const; // returned data will have lenght 128
        unsigned char * getPublicKey() const;
        unsigned char * scrambledMod() const;
        ~RSA();
    };
    
}

#endif /* defined(__L2P__RSA__) */
