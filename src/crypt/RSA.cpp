//
//  RSA.cpp
//  L2P
//
//  Created by Jaromír Hřibal on 09.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#include "RSA.h"
#include <openssl/engine.h>
#include <openssl/err.h>

namespace crypt {
    
    RSA::RSA() : m_rsa(NULL), m_pub_exp(NULL) {
        m_rsa = RSA_new();
        m_pub_exp = BN_new();
        BN_init(m_pub_exp);
        BN_set_word(m_pub_exp, PUB_EXP);
        RSA_generate_key_ex(m_rsa, KEY_LENGHT, m_pub_exp, NULL);
    }
    
    unsigned char * RSA::encrypt(const unsigned char * data) const {
        // encrypting with public key
        return crypt(data, MODE::ENCRYPT);
        
    }
    
    unsigned char * RSA::createBuffer() const {
        return new unsigned char[RSA_size(m_rsa)];
    }
    
    unsigned char * RSA::decrypt(const unsigned char * data) const {
        // decrypting with private key
        return crypt(data, MODE::DECRYPT);
    }
    
    /*
     * it crypts and decrypts data to buffer size defined by RSA_size
     * RSA with no padding can probably decrypt message with max lenght <= RSA_size ??
     */
    unsigned char * RSA::crypt(const unsigned char * data, MODE mode) const {
        unsigned char * _data = createBuffer();
        if (mode == MODE::ENCRYPT) {
            if (RSA_public_encrypt(RSA_size(m_rsa), data, _data, m_rsa, PADDING) == -1) {
                ERR_load_CRYPTO_strings();
                ERR_print_errors_fp(stdout);
                ERR_free_strings();
            }
        }
        else {
            if (RSA_private_decrypt(RSA_size(m_rsa), data, _data, m_rsa, PADDING) == -1) {
                ERR_load_CRYPTO_strings();
                ERR_print_errors_fp(stdout);
                ERR_free_strings();
            };
        }
        return _data;
    }
    
    unsigned char * RSA::getPublicKey() const {
        unsigned char * _data = createBuffer();
        BN_bn2bin(m_rsa->n, _data);
        return _data;
    }
    
    unsigned char * RSA::scrambledMod() const {
        
        unsigned char * scrambledMod = createBuffer();
        
        BN_bn2bin(m_rsa->n, scrambledMod);
        
        // step 1 : 0x4d-0x50 <-> 0x00-0x04
        for (int i = 0; i < 4; i++)
        {
            unsigned char temp = scrambledMod[0x00 + i];
            scrambledMod[0x00 + i] = scrambledMod[0x4d + i];
            scrambledMod[0x4d + i] = temp;
        }
        
        // step 2 : xor first 0x40 bytes with last 0x40 bytes
        for (int i = 0; i < 0x40; i++)
        {
            scrambledMod[i] = (unsigned char) (scrambledMod[i] ^ scrambledMod[0x40 + i]);
        }
        
        // step 3 : xor bytes 0x0d-0x10 with bytes 0x34-0x38
        for (int i = 0; i < 4; i++)
        {
            scrambledMod[0x0d + i] = (unsigned char) (scrambledMod[0x0d + i] ^ scrambledMod[0x34 + i]);
        }
        
        // step 4 : xor last 0x40 bytes with first 0x40 bytes
        for (int i = 0; i < 0x40; i++)
        {
            scrambledMod[0x40 + i] = (unsigned char) (scrambledMod[0x40 + i] ^ scrambledMod[i]);
        }
        
        return scrambledMod;
        
    }
    
    
    RSA::~RSA() {
        if (m_pub_exp) {
            BN_free(m_pub_exp);
            m_pub_exp = NULL;
        }
        if (m_rsa) {
            RSA_free(m_rsa);
            m_rsa = NULL;
        }
    }
    
}