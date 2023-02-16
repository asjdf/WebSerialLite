#include "WebSerialLite.h"
#include "WebSerialWebPage.h"

void WebSerialClass::begin(AsyncWebServer *server, const char *url) {
  _server = server;
  _server->on(url, HTTP_GET, [](AsyncWebServerRequest *request) {
    // Send Webpage
    AsyncWebServerResponse *response = request->beginResponse_P(
        200, "text/html", WEBSERIAL_HTML, WEBSERIAL_HTML_SIZE);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });


  String backendUrl = url;
  backendUrl.concat("ws");
  _ws = new AsyncWebSocket(backendUrl);
  _ws->onEvent([&](AsyncWebSocket *server, AsyncWebSocketClient *client,
                   AwsEventType type, void *arg, uint8_t *data,
                   size_t len) -> void {
    if (type == WS_EVT_CONNECT) {
#if defined(WEBSERIAL_DEBUG)
      DEBUG_WEB_SERIAL("Client connection received");
#endif
      if (_connCallback != NULL) _connCallback(client);
    } else if (type == WS_EVT_DISCONNECT) {
#if defined(WEBSERIAL_DEBUG)
      DEBUG_WEB_SERIAL("Client disconnected");
#endif
      if (_disconnCallback != NULL) _disconnCallback(client);
    } else if (type == WS_EVT_DATA) {
#if defined(WEBSERIAL_DEBUG)
      DEBUG_WEB_SERIAL("Received Websocket Data");
#endif
      if (_recvMsgCallback != NULL) _recvMsgCallback(data, len);
      if (_recvMsgCallbackPlus != NULL) _recvMsgCallbackPlus(client, data, len);
    } else if (type == WS_EVT_ERROR) {
#if defined(WEBSERIAL_DEBUG)
      DEBUG_WEB_SERIAL("Client error");
#endif
      if (_errCallback != NULL)
        _errCallback(client, *(uint16_t *)arg, (const char *)data, len);
    }
  });
  _server->addHandler(_ws);

#if defined(WEBSERIAL_DEBUG)
  DEBUG_WEB_SERIAL("Attached AsyncWebServer along with Websockets");
#endif
}

void WebSerialClass::onConnect(ConnHandler callbackFunc) {
  _connCallback = callbackFunc;
}
void WebSerialClass::onDisconnect(DisconnHandler callbackFunc) {
  _disconnCallback = callbackFunc;
}
void WebSerialClass::onMessage(RecvMsgHandler callbackFunc) {
  _recvMsgCallback = callbackFunc;
}
void WebSerialClass::onMessage(RecvMsgHandlerPlus callbackFunc) {
  _recvMsgCallbackPlus = callbackFunc;
}
void WebSerialClass::onError(ErrHandler callbackFunc) {
  _errCallback = callbackFunc;
}

// Print
void WebSerialClass::print(String m) { _ws->textAll(m); }
void WebSerialClass::print(const char *m) { _ws->textAll(m); }
void WebSerialClass::print(char *m) { _ws->textAll(m); }
void WebSerialClass::print(int m) { _ws->textAll(String(m)); }
void WebSerialClass::print(uint8_t m) { _ws->textAll(String(m)); }
void WebSerialClass::print(uint16_t m) { _ws->textAll(String(m)); }
void WebSerialClass::print(uint32_t m) { _ws->textAll(String(m)); }
void WebSerialClass::print(double m) { _ws->textAll(String(m)); }
void WebSerialClass::print(float m) { _ws->textAll(String(m)); }

// Print with New Line
void WebSerialClass::println(String m) { _ws->textAll(m + "\n"); }
void WebSerialClass::println(const char *m) { _ws->textAll(String(m) + "\n"); }
void WebSerialClass::println(char *m) { _ws->textAll(String(m) + "\n"); }
void WebSerialClass::println(int m) { _ws->textAll(String(m) + "\n"); }
void WebSerialClass::println(uint8_t m) { _ws->textAll(String(m) + "\n"); }
void WebSerialClass::println(uint16_t m) { _ws->textAll(String(m) + "\n"); }
void WebSerialClass::println(uint32_t m) { _ws->textAll(String(m) + "\n"); }
void WebSerialClass::println(float m) { _ws->textAll(String(m) + "\n"); }
void WebSerialClass::println(double m) { _ws->textAll(String(m) + "\n"); }

#if defined(WEBSERIAL_DEBUG)
void WebSerialClass::DEBUG_WEB_SERIAL(const char *message) {
  Serial.print("[WebSerial] ");
  Serial.println(message);
}
#endif

WebSerialClass WebSerial;