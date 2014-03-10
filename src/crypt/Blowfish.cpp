//
//  Blowfish.cpp
//  L2P
//
//  Created by Jaromír Hřibal on 09.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#include "Blowfish.h"

namespace crypt {
    
    Blowfish::Blowfish(const unsigned char * key) : m_key(NULL) {
        setKey(key);
    }
    
    void Blowfish::setKey(const unsigned char * key) {
        if (m_key) delete m_key;
        m_key = new BF_KEY;
        BF_set_key(m_key, KEY_LENGHT , key);
    }
    
    /*
     * data must have lenght divided by 8
     */
    void Blowfish::encrypt(unsigned char * data, size_t len) const {
        crypt(data, len, ENCRYPT);
    }
    
    /*
     * data must have lenght divided by 8
     */
    void Blowfish::decrypt(unsigned char * data, size_t len) const {
        crypt(data, len, DECRYPT);
    }
    
    void Blowfish::crypt(unsigned char * data, size_t len, MODE mode) const {
        unsigned char * _data = new unsigned char[BLOCK_LENGHT];
        for (int i = 0; i < len; i+=BLOCK_LENGHT) {
            BF_ecb_encrypt(data + i, _data, m_key, mode == ENCRYPT ? BF_ENCRYPT : BF_DECRYPT);
            memcpy(data + i, _data, BLOCK_LENGHT);
        }
        delete [] _data;
    }
    
    Blowfish::~Blowfish() {
        if (m_key) delete m_key;
    }
    
}