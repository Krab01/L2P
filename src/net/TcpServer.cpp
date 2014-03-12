//
//  TcpServer.cpp
//  L2P
//
//  Created by Jaromír Hřibal on 10.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#include "TcpServer.h"

namespace net {
    
    TcpServer::TcpServer(const char * ip, int port, uv_loop_t * loop) : m_loop(loop), hasOwnLoop(false) {
        m_ip = ip;
        m_port = port;
        started = closed = false;
    }
    
    void TcpServer::start() {
        if (started) return; // server already started
        started = true;
        if (!m_loop) {
            m_loop = new uv_loop_t;
            uv_loop_init(m_loop);
            hasOwnLoop = true;
        }
        uv_async_init(m_loop, &stopEvent, _onServerClose);
        stopEvent.data = (void *) this; // set stop event data to this instance
        if (hasOwnLoop) {
            uv_thread_create(&m_thread, run, (void *)this);
        }
        else {
            _start();
        }
    }
    
    void TcpServer::run(void * ls) {
        TcpServer * _ls = (TcpServer * )ls;
        _ls->start();
    }
    
    void TcpServer::close() {
        closed = true;
        uv_async_send(&stopEvent);
    }
    
    void TcpServer::join() {
        if (hasOwnLoop) {
            uv_thread_join(&m_thread);
        }
    }
    
    void TcpServer::_onServerClose(uv_async_t * stopEvent, int status) {
        TcpServer * server = (TcpServer *) stopEvent->data;
        uv_close((uv_handle_t *)&server->server, NULL);
        uv_walk(server->m_loop, _closeClient, (void *)server->server.data);
        
    }
    
    void TcpServer::_closeClient(uv_handle_t * client, void * arg) {
        TcpServer * server = (TcpServer * )client->data;
        if (server == arg) {
            uv_close(client, _onClientClose);
        }
    }
    
    void TcpServer::_onClientClose(uv_handle_t * handle) {
        ((TcpServer *)handle->data)->onClientClose(handle);
    }
    
    void TcpServer::onClientClose(uv_handle_t *handle) {
        delete handle;
    }
    
    void TcpServer::_start() {
        
        server.data = (void *)this;
        
        if (uv_tcp_init(m_loop, &server) == -1) {
            // error handler
        }
        
        struct sockaddr_in bind_addr;
        uv_ip4_addr(m_ip, m_port, &bind_addr);
        
        if (uv_tcp_bind(&server, (sockaddr *)&bind_addr, 0) == -1) {
            // error handler
        }
        
        if (uv_listen((uv_stream_t *)&server, 128, _onNewConnection) == -1) {
            // error handler
        }
        
        if (hasOwnLoop) {
            uv_run(m_loop, UV_RUN_DEFAULT);
            uv_loop_close(m_loop);
            delete m_loop;
        }
        
    }
    
    void TcpServer::_onNewConnection(uv_stream_t * server, int status) {
        TcpServer * self = (TcpServer *)server->data;
        self->onNewConnection(server, status);
    }
    
    void TcpServer::onNewConnection(uv_stream_t * server, int status) {
        std::cout << "new connectnion recieved!!" << std::endl;
        uv_tcp_t * client = new uv_tcp_t;
        uv_tcp_init(m_loop, client);
        client->data = this;
        uv_accept((uv_stream_t *)server, (uv_stream_t *)client);
        
    }
    
    TcpServer::~TcpServer() {
        
    }
    
}