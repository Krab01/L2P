//
//  Dumper.h
//  L2P
//
//  Created by Jaromír Hřibal on 09.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#ifndef __L2P__Dumper__
#define __L2P__Dumper__

#include <iostream>

namespace utils {
    class Dumper {
    public:
        static void hex(const unsigned char * data, size_t len);
        static bool equal(const unsigned char * a, const unsigned char * b, size_t len);
        static bool notEqual(const unsigned char * a, const unsigned char * b, size_t len);
    };
}

#endif /* defined(__L2P__Dumper__) */
