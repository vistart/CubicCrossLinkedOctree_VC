/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#pragma once
#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <boost/asio.hpp>
#include <boost/thread.hpp>

class ThreadPool {
    boost::thread_group m_workers;
    boost::asio::io_service m_io;
    boost::asio::io_service::work m_work;
public:
    ThreadPool(int size) : m_work(m_io) {
        for (int i = 0; i < size; ++i) {
            m_workers.create_thread([&]() { m_io.run(); });
        }
    }

    template<class F>
    void enqueue_task(F&& func) {
        m_io.post(std::forward<F>(func));
    }

    ~ThreadPool() {
        m_io.stop();
        m_workers.join_all();
    }
};
#endif
