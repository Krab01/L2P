//
//  Sync.h
//  L2P
//
//  Created by Jaromír Hřibal on 10.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#ifndef __L2P__Sync__
#define __L2P__Sync__

#include <iostream>
#include <uv.h>

#define LOCK(x) utils::Sync::lock(x);
#define UNLOCK(x) utils::Sync::unlock(x);

namespace utils {
    
    class Sync {
        static uv_mutex_t mutexes[];
        static bool initialized;
        static void init();
        static const size_t MUTEX_COUNT = 1;
    public:
        enum MUTEX {
            COUT = 0
        };
        static void lock(MUTEX mutex);
        static void unlock(MUTEX mutex);
        
    };
    
}

#endif /* defined(__L2P__Sync__) */
