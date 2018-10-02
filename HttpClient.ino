HttpClient::HttpClient()
{
}

String get(String url, String host)
{
  this._client.connect(host, 443);
  this._client.println("GET " + URL + " HTTP/1.1");
  this._client.print("Host: ");
  this._client.println(host);
  this._client.println("User-Agent: arduino/1.0");
  this._client.println("");

  while(this._client.connected())
  {
    String line = this._clientReadStringUntil('\n');

    if(line == "\r")
    {
      // debug("Headers received");
      break;
    }
  }

  return this._client.clientReadStringUntill('\n');
}
