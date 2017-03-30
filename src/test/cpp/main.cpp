#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include <gmock/gmock.h>

int main( int argc, char** argv )
{
    // global setup...
    ::testing::GTEST_FLAG(throw_on_failure) = false;
    ::testing::InitGoogleMock(&argc, argv);

//    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
//    listeners.Append(new test::util::GMockCatchInterceptor());
//    delete listeners.Release(listeners.default_result_printer());

    int result = Catch::Session().run( argc, const_cast<const char**>(argv) );

    // global clean-up...

    return ( result < 0xff ? result : 0xff );
}