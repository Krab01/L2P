//
//  TcpServer.h
//  L2P
//
//  Created by Jaromír Hřibal on 10.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#ifndef __L2P__TcpServer__
#define __L2P__TcpServer__

#include <iostream>
#include <uv.h>

namespace net {
    
    class TcpServer {
        uv_thread_t m_thread;
        uv_loop_t * m_loop;
        uv_tcp_t server;
        uv_async_t stopEvent;
        bool hasOwnLoop;
        const char * m_ip;
        int m_port;
        bool started;
        bool closed;
        void onNewConnection(uv_stream_t * server, int status);
        void onClientClose(uv_handle_t * handle);
        static void run(void * ls);
        static void _onNewConnection(uv_stream_t * server, int status);
        static void _closeClients(uv_handle_t * handle, void * arg);
        static void _onServerClose(uv_async_t * stopEvent, int status);
        static void _closeClient(uv_handle_t * client, void * arg);
        static void _onClientClose(uv_handle_t * handle);
        void _start();
    public:
        TcpServer(const char * ip, int port, uv_loop_t * loop = NULL);
        void close();
        void startInThread();
        void start();
        void join();
        ~TcpServer();
    };
    
}

#endif /* defined(__L2P__TcpServer__) */
