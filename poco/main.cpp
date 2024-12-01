#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <iostream>
#include <string>

using namespace Poco::Net;
using namespace Poco;

int main()
{
  try
  {
    // Prepare the request
    URI uri("http://example.com");
    HTTPClientSession session(uri.getHost(), uri.getPort());

    HTTPRequest request(HTTPRequest::HTTP_GET, uri.getPath(), HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");

    session.sendRequest(request);

    // Process the response
    HTTPResponse response;
    std::istream& responseStream = session.receiveResponse(response);
    if (response.getStatus() == HTTPResponse::HTTP_OK)
    {
      // Successful
      std::string responseBody;
      StreamCopier::copyToString(responseStream, responseBody);

      std::cout << "Response: " << responseBody << std::endl;
    }
    else
    {
      // Error
      std::cout << "Error: " << response.getStatus() << " " << response.getReason() << std::endl;
    }
  }
  catch(const Exception& e)
  {
    std::cerr << "Error: " << e.displayText() << std::endl;
    return -1;
  }

  return 0;
}