#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

int main()
{
    boost::system::error_code ec;

    boost::asio::io_service ioc(1);

    boost::asio::io_service::work work(ioc);

    boost::asio::ip::tcp::socket sckt(ioc);

    boost::asio::ip::tcp::resolver resolver(ioc);

    boost::asio::ip::tcp::resolver::query query("http://www.packtpub.com", boost::lexical_cast<std::string>(80));

    boost::asio::deadline_timer timer(ioc);

    timer.expires_from_now(boost::posix_time::seconds(10));

    timer.async_wait([&ioc](const boost::system::error_code& error)
    {
        ioc.stop();
    });

    try
    {
        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

        boost::asio::ip::tcp::endpoint endpoint = *iterator;

        std::cout << "Connect to " << endpoint << std::endl;

        sckt.connect(endpoint);

        sckt.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

        sckt.close(ec);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl; 
    }

    ioc.run();

    return 0;
}