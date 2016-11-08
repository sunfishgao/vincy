#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <unistd.h>
#include <set>
#include <functional>

#include "tcp_connection.h"
#include "http_handler.h"
#include "http_message.h"
namespace vincy {

//using boost::asio::ip::tcp::acceptor;

class HttpServer
{
public:
    typedef std::function<void(TcpConnection::Pointer)> ConnectionCallback;

public:
    HttpServer(io_service& ioservice, std::size_t port);
    void handleFunc(const std::string& path, const HttpHandler::HandleFunc& func);

private:
    void startAccept();
    void handleAccept(TcpConnection::Pointer conn,  const boost::system::error_code &ec);
    void handleClose(TcpConnection::Pointer conn);
    void handleRead(TcpConnection::Pointer conn, std::size_t bytes_transfered);

    boost::asio::ip::tcp::acceptor acceptor_;
    std::set<TcpConnection::Pointer> conns_;
    HttpHandler handler_;

};

}



#endif // TCPSERVER_H
