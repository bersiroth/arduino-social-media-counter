#ifndef HttpClient_h
#define HttpClient_h

#include <WiFiClientSecure.h>
#include "Utils.h"

class HttpClient
{
  public:
  HttpClient();
  String get(String host, String url);

  private:
  WiFiClientSecure _client;
};

#endif
