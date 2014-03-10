//
//  LoginServer.h
//  L2P
//
//  Created by Jaromír Hřibal on 10.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#ifndef __L2P__LoginServer__
#define __L2P__LoginServer__

#include <iostream>
#include <uv.h>

namespace net {
    
    class LoginServer {
        static LoginServer * m_instance;
        LoginServer(const char * ip, int port);
        uv_thread_t m_thread;
        uv_loop_t * m_loop;
        const char * m_ip;
        int m_port;
        static void run(void * ls);
        void init();
        static void _onNewConnection(uv_stream_t * server, int status);
        void onNewConnection(uv_stream_t * server, int status);
    public:
        static void start(const char * ip, int port);
        static void join();
        ~LoginServer();
    };
    
}

#endif /* defined(__L2P__LoginServer__) */
