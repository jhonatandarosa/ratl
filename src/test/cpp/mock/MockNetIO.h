#pragma once

#include <ratl/server/NetIO.h>
#include <gmock/gmock.h>

namespace ratl {
    namespace server {
        class RequestHandler;
    }
}

class MockNetIO : public ratl::server::NetIO {
public:
    MOCK_METHOD2(bind, void(const std::string& address, const int port));
    MOCK_METHOD0(run, void());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD1(setRequestHandler, void(const std::shared_ptr<ratl::server::RequestHandler>&));
};