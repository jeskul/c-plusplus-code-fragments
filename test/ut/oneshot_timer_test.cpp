#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <OneshotTimer.h>
#include <thread>

/*
   Note: Generally it is a bad idea to have sleeps in unit test
         This time I will make an execption due to the nature of the tested class
 */
using namespace testing;

using namespace std::literals::chrono_literals;

/* Dummy class to capture timer expirations using gmock */
class Callback
{
public:
    MOCK_METHOD(void, my_callback, ());
};

class OneshotTimerTest : public Test
{
protected:
   OneshotTimer _timer;
};

TEST_F(OneshotTimerTest, When_Idle_Expect_NothingBad)
{
}

TEST_F(OneshotTimerTest, When_Started_Expect_CallbackAtExpiration)
{
    Callback mock;
    std::function<void(void)> f = std::bind(&Callback::my_callback, &mock);
    EXPECT_CALL(mock, my_callback()).Times(1);
    _timer.start(5ms, f);
    std::this_thread::sleep_for(10ms);
}

TEST_F(OneshotTimerTest, When_Started_Expect_NoCallbackStop)
{
    Callback mock;
    std::function<void(void)> f = std::bind(&Callback::my_callback, &mock);
    EXPECT_CALL(mock, my_callback()).Times(0);
    _timer.start(10ms, f);
    _timer.stop();
    std::this_thread::sleep_for(20ms);
}
