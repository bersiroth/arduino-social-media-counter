#include "Utils.h"

HttpClient::HttpClient()
{
}

String HttpClient::get(const char* host, String url)
{
  this->_client.connect(host, static_cast<uint16_t>(443));
  this->_client.println("GET " + url + " HTTP/1.1");
  this->_client.print("Host: ");
  this->_client.println(host);
  this->_client.println("User-Agent: arduino/1.0");
  this->_client.println("");

  while(this->_client.connected())
  {
    String line = this->_client.readStringUntil('\n');
    if(line == "\r")
    {
      debug("Headers received");
      break;
    }
  }

  return this->_client.readStringUntil('\n');
}
