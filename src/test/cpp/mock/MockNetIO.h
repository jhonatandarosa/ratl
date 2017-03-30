#pragma once

#include <ratl/server/NetIO.h>
#include <gmock/gmock.h>

class MockNetIO : public ratl::server::NetIO {
public:
    MOCK_METHOD2(bind, void(const std::string& address, const int port));
    MOCK_METHOD0(run, void());
    MOCK_METHOD0(stop, void());
};