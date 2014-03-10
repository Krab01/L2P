//
//  Sync.cpp
//  L2P
//
//  Created by Jaromír Hřibal on 10.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#include "Sync.h"
#include <uv.h>

namespace utils {
    
    bool Sync::initialized = false;
    
    uv_mutex_t Sync::mutexes[Sync::MUTEX_COUNT];
    
    void Sync::lock(MUTEX mutex) {
        if (!Sync::initialized) {
            Sync::init();
        }
        uv_mutex_lock(&Sync::mutexes[mutex]);
    }
    
    void Sync::unlock(MUTEX mutex) {
        uv_mutex_unlock(&Sync::mutexes[mutex]);
    }
    
    void Sync::init() {
        
        size_t s = sizeof(Sync::mutexes)/sizeof(uv_mutex_t);
        
        for (size_t i = 0; i < s; i++) {
            uv_mutex_init(&(Sync::mutexes[i]));
        }
        
        Sync::initialized = true;
        
    }
}