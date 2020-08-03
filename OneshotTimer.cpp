#include "OneshotTimer.h"

OneshotTimer::OneshotTimer()
{
    mThread = std::thread(&OneshotTimer::run, this);
}

OneshotTimer::~OneshotTimer()
{
  mQueue.send(Message{.mId=message_id::exit});
  mThread.join();
}

void OneshotTimer::start(std::chrono::milliseconds timerDuration, TimeoutFunction callbackFunction)
{
    mQueue.send(Message{.mId=message_id::start,
                        .mDuration=timerDuration,
                        .mCallbackFunction=callbackFunction});
}

void OneshotTimer::stop()
{
    mQueue.send(Message{.mId=message_id::stop});
}

void OneshotTimer::run()
{
    std::chrono::milliseconds timeout_duration;
    TimeoutFunction callback;
    bool notExit = true;
    bool running = false;

    while(notExit)
    {
        Message msg;
        if(running)
        {
            msg = mQueue.receive_with_timeout(timeout_duration, Message{.mId=message_id::timeout});
        }
        else
        {
            msg = mQueue.receive();
        }

        switch (msg.mId)
        {
            case message_id::start:
                running = true;
                timeout_duration = msg.mDuration;
                callback = msg.mCallbackFunction;
                break;

            case message_id::stop:
                running = false;
                break;

            case message_id::exit:
                notExit = false;
                break;

            case message_id::timeout:
                running = false;
                callback();
                break;
        }
    }
}
