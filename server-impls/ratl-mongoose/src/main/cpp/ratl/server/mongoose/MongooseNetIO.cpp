#include <ratl/server/mongoose/MongooseNetIO.h>

#include <mongoose/mongoose.h>

#include <ratl/server/RequestHandler.h>
#include <ratl/rest/Request.h>
#include <ratl/rest/Response.h>

using ratl::server::mongoose::MongooseNetIO;
using ratl::rest::Request;
using ratl::rest::Response;

void ev_handler(struct mg_connection *nc, int ev, void *p);

const char * status_message(int status_code) {
    switch (status_code) {
    case 100:
        return "Continue";
    case 101:
        return "Switching Protocols";
    case 102:
        return "Processing";

    case 200:
        return "OK";
    case 201:
        return "Created";
    case 202:
        return "Accepted";
    case 203:
        return "Non-Authoritative Information";
    case 204:
        return "No Content";
    case 205:
        return "Reset Content";
    case 206:
        return "Partial Content";
    case 207:
        return "Multi-Status";
    case 208:
        return "Already Reported";
    case 226:
        return "IM Used";

    case 300:
        return "Multiple Choices";
    case 301:
        return "Moved";
    case 302:
        return "Found";
    case 303:
        return "See Other";
    case 304:
        return "Not Modified";
    case 305:
        return "Use Proxy";
    case 306:
        return "Switch Proxy";
    case 307:
        return "Temporary Redirect";
    case 308:
        return "Permanent Redirect";

    case 400:
        return "Bad Request";
    case 401:
        return "Unauthorized";
    case 402:
        return "Payment Required";
    case 403:
        return "Forbidden";
    case 404:
        return "Not Found";
    case 405:
        return "Method Not Allowed";
    case 406:
        return "Not Acceptable";
    case 407:
        return "Proxy Authentication Required";
    case 408:
        return "Request Timeout";
    case 409:
        return "Conflict";
    case 410:
        return "Gone";
    case 411:
        return "Length Required";
    case 412:
        return "Precondition Failed";
    case 413:
        return "Payload Too Large";
    case 414:
        return "URI Too Long";
    case 415:
        return "Unsupported Media Type";
    case 416:
        return "Requested Range Not Satisfiable";
    case 417:
        return "Expectation Failed";
    case 418:
        return "I'm a teapot";
    case 422:
        return "Unprocessable Entity";
    case 423:
        return "Locked";
    case 424:
        return "Failed Dependency";
    case 426:
        return "Upgrade Required";
    case 428:
        return "Precondition Required";
    case 429:
        return "Too Many Requests";
    case 431:
        return "Request Header Fields Too Large";
    case 451:
        return "Unavailable For Legal Reasons";

    case 500:
        return "Internal Server Error";
    case 501:
      return "Not Implemented";
    case 502:
        return "Bad Gateway";
    case 503:
        return "Service Unavailable";
    case 504:
      return "Gateway Timeout";
    case 505:
      return "HTTP Version Not Supported";
    case 506:
      return "Variant Also Negotiates";
    case 507:
      return "Insufficient Storage";
    case 508:
      return "Loop Detected";
    case 510:
      return "Not Extended";
    case 511:
      return "Network Authentication Required";

    default:
        return "OK";
    }
}

std::string to_string(const mg_str& str) {
    return {str.p, str.len};
}

Request createRequest(struct http_message* hm) {
    return {to_string(hm->uri), to_string(hm->method), to_string(hm->body)};
}

void send_response(struct mg_connection *c, const Response& response) {
    mg_printf(c, "HTTP/1.1 %d %s\r\nServer: %s\r\n", response.httpCode,
                  status_message(response.httpCode), "ratl 0.0.1 - Powered By Mongoose");
    if (response.content.empty()) {
        mg_printf(c, "Content-Length: %d\r\n", 0);
    } else {
        const auto payload = response.content.dump();

        mg_printf(c, "Content-Type: application/json\r\n");
        mg_printf(c, "Content-Length: %d\r\n", payload.size());
        mg_send(c, "\r\n", 2);
        mg_printf(c, "%s", payload.c_str());
    }
    mg_send(c, "\r\n", 2);
//        mg_send_head(nc, response.httpCode, 0, "Content-Type: text/plain");
//        mg_printf(nc, "%.*s", hm->message.len, hm->message.p);
//        mg_send_response_line(nc, 200, nullptr);
//        mg_send_http_chunk(nc, "", 0);
//        mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
}


class MongooseServer {
public:
    virtual Response handleRequest(const Request& request) = 0;
};

class MongooseNetIO::Impl : public MongooseServer {
public:
    struct mg_mgr mgr;
    struct mg_connection *nc;
//    const int http_port = 5002;
    struct mg_serve_http_opts s_http_server_opts;
    bool alive{false};
    std::shared_ptr<RequestHandler> handler;


    void initialize(const std::string &address, const int port) {
        mg_mgr_init(&mgr, nullptr);
        mgr.user_data = this;
        const auto s_http_port = std::to_string(port).c_str();
//        printf("Starting web server on port %s\n", s_http_port);
//        using namespace std::placeholders;
        nc = mg_bind(&mgr, s_http_port, ev_handler);
        if (nc == nullptr) {
//            printf("Failed to create listener\n");
        }
        nc->user_data = this;

        // Set up HTTP server parameters
        mg_set_protocol_http_websocket(nc);
//        s_http_server_opts.document_root = ".";  // Serve current directory
//        s_http_server_opts.enable_directory_listing = "yes";
    }

    void run() {
        alive = true;
        while (alive) {
            mg_mgr_poll(&mgr, 1000);
        }
    }

    void stop() {
        alive = false;
        mg_mgr_free(&mgr);
    }

    Response handleRequest(const Request& request) override {
        return handler->process(request);
    }
};

void ev_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        auto httpServer = static_cast<MongooseServer*>(nc->user_data);
        auto hm = (struct http_message *) p;
        auto request = createRequest(hm);
        auto response = httpServer->handleRequest(request);

        send_response(nc, response);

//        httpServer->handleRequest((struct http_message *) p);

//
    }
}

MongooseNetIO::MongooseNetIO()
    : pImpl(new Impl{})
{
}

MongooseNetIO::~MongooseNetIO() {
    delete pImpl;
}

void MongooseNetIO::bind(const std::string &address, const int port) {
    pImpl->initialize(address, port);
}

void MongooseNetIO::run() {
    pImpl->run();
}

void MongooseNetIO::stop() {
    pImpl->stop();
}

void MongooseNetIO::setRequestHandler(const std::shared_ptr<RequestHandler> &handler) {
    pImpl->handler = handler;
}
