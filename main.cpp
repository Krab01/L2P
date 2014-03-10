//
//  main.cpp
//  L2P
//
//  Created by Jaromír Hřibal on 09.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#include <iostream>
#include "src/utils/Dumper.h"
#include "src/crypt/RSA.h"
#include <openssl/rand.h>
#include "src/crypt/Blowfish.h"
#include "src/net/LoginServer.h"
#include "src/utils/Sync.h"

using namespace std;
using namespace utils;

void signal_handler(uv_signal_t * handle, int signum) {
    cout << "signal " << signum  << "caught" << endl;
}

int main(int argc, const char * argv[])
{
    /* initialize openssl random generator */
    const char * seed = "asfanfasfflalkhflhafoih";
    RAND_seed(seed, (size_t)strlen(seed));
    
    uv_signal_t sigterm;
    uv_signal_init(uv_default_loop(), &sigterm);
    uv_signal_start(&sigterm, signal_handler, SIGTERM);
    
    uv_signal_t sigint;
    uv_signal_init(uv_default_loop(), &sigint);
    uv_signal_start(&sigint, signal_handler, SIGINT);
    
    LOCK(Sync::MUTEX::COUT);
    cout << "ahoj\n";
    UNLOCK(Sync::MUTEX::COUT);
    
    //net::LoginServer::start("127.0.0.1", 3000);
    
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    
    //net::LoginServer::join();
    
    return 0;
}


