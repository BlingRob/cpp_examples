#include <iostream>
#include <boost/asio.hpp>

void connect_handler(const boost::system::error_code& error)
{
  if (!error)
  {
    std::cout << "Connected" << std::endl;
  }
  else
  {
    std::cerr << error << std::endl;
  }
}

int main()
{
    boost::asio::io_context io(1);

    boost::asio::ip::tcp::socket sock(io);
    boost::asio::ip::tcp::endpoint endpoint(
    boost::asio::ip::address::from_string("146.20.110.251"), 80);
    sock.async_connect(endpoint, connect_handler);

    io.run_one();

    return 0;
}