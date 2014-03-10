//
//  LoginServer.cpp
//  L2P
//
//  Created by Jaromír Hřibal on 10.03.14.
//  Copyright (c) 2014 Jaromír Hřibal. All rights reserved.
//

#include "LoginServer.h"

namespace net {
    
    LoginServer * LoginServer::m_instance = NULL;
    
    LoginServer::LoginServer(const char * ip, int port) {
        m_loop = new uv_loop_t;
        uv_loop_init(m_loop);
        m_ip = ip;
        m_port = port;
    }
    
    void LoginServer::start(const char * ip, int port) {
        if (!m_instance) {
            m_instance = new LoginServer(ip, port);
            uv_thread_create(&(m_instance->m_thread), run, (void *)m_instance);
        }
    }
    
    void LoginServer::run(void * ls) {
        LoginServer * _ls = (LoginServer * )ls;
        _ls->init();
        uv_run(_ls->m_loop, UV_RUN_DEFAULT);
    }
    
    void LoginServer::join() {
        if (!m_instance) return;
        uv_thread_join(&(m_instance->m_thread));
    }
    
    void LoginServer::init() {
        
        uv_tcp_t * server = new uv_tcp_t;
        
        if (uv_tcp_init(m_loop, server) == -1) {
            // error handler
        }
        
        struct sockaddr_in bind_addr;
        uv_ip4_addr(m_ip, m_port, &bind_addr);
        
        if (uv_tcp_bind(server, (sockaddr *)&bind_addr, 0) == -1) {
            // error handler
        }
        
        if (uv_listen((uv_stream_t *)server, 128, _onNewConnection) == -1) {
            // error handler
        }
        
    }
    
    void LoginServer::_onNewConnection(uv_stream_t * server, int status) {
        m_instance->onNewConnection(server, status);
    }
    
    void LoginServer::onNewConnection(uv_stream_t * server, int status) {
        std::cout << "new connectnion recieved!!" << std::endl;
    }
    
    LoginServer::~LoginServer() {}
    
}