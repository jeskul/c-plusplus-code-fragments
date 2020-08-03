#ifndef ONESHOT_TIMER_H
#define ONESHOT_TIMER_H

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <MessageQueue.h>

using TimeoutFunction = std::function<void(void)>;

class OneshotTimer
{
public:
    OneshotTimer();
    virtual ~OneshotTimer();

    void start(std::chrono::milliseconds timerDuration, TimeoutFunction callbackFunction);
    void stop();

private:

    enum class message_id {start, stop, timeout, exit};
    struct Message
    {
      message_id                mId;
      std::chrono::milliseconds mDuration;
      TimeoutFunction           mCallbackFunction;
    };

    std::thread        mThread;
    MsgQueue<Message>  mQueue;

    void run();
};

#endif // ONESHOT_TIMER_H
