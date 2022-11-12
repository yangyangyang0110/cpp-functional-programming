/* Proj: cpp-functional-programming
 * File: boost-asio.cc
 * Created Date: 2022/10/11
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/11 09:14:57
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <boost/asio.hpp>
#include <boost/thread/future.hpp>
#include <iostream>

using tcp = boost::asio::ip::tcp;

class Session
{
public:
    explicit Session(boost::asio::io_service &io_service)
        : socket_(io_service)
    {
    }
    tcp::socket &getSocket() noexcept { return socket_; }

    void start()
    {
        socket_.async_read_some(
            boost::asio::buffer(data_, MaxDataSize),
            boost::bind(&Session::handle_read, this, boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void handle_read(const boost::system::error_code &error, size_t bytes_transferred)
    {
        if (!error) {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(data_, bytes_transferred),
                                     boost::bind(&Session::handle_write, this,
                                                 boost::asio::placeholders::error));
        } else {
            delete this;
        }
    }

    void handle_write(const boost::system::error_code &error)
    {
        if (!error) {
            socket_.async_read_some(
                boost::asio::buffer(data_, MaxDataSize),
                boost::bind(&Session::handle_read, this, boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
        } else {
            delete this;
        }
    }

private:
    tcp::socket socket_;
    enum { MaxDataSize = 1024 };
    char data_[MaxDataSize]{};
};

class Server
{
public:
    Server(boost::asio::io_service &io_service, int port)
        : io_service_(io_service)
        , acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
    {
        auto *new_session = new Session(io_service_);
        acceptor_.async_accept(new_session->getSocket(),
                               boost::bind(&Server::handleAccept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handleAccept(Session *new_session, const boost::system::error_code &error)
    {
        if (error) {
            delete new_session;
        } else {
            new_session->start();
            new_session = new Session(io_service_);
            acceptor_.async_accept(new_session->getSocket(),
                                   boost::bind(&Server::handleAccept, this, new_session,
                                               boost::asio::placeholders::error));
        }
    }

private:
    boost::asio::io_service &io_service_;
    tcp::acceptor acceptor_;
};

int main()
{
    try {
        boost::asio::io_service io_server;
        Server srv(io_server, 8888);
        io_server.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
