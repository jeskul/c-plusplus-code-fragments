/* The contents are just an example on how to use the OneshotTimer class.
   Real tests are done in the unit tests */

#include <OneshotTimer.h>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std::literals::chrono_literals;

const std::chrono::milliseconds kTimeout = 1000ms;

void timeout_handler()
{
  std::cout << "timeout happened!\n";
}

int main(int argc, char *argv[])
{
  OneshotTimer timer;

  timer.start(kTimeout, []{std::cout << "Never!\n";});
  for (int i=0; i<10; ++i)
  {
    std::this_thread::sleep_for(10ms);
    timer.stop();
    //std::this_thread::sleep_for(1ms);
    timer.start(kTimeout, []{});
  }

  timer.stop();
  for (int i=0; i<10; ++i)
  {
    std::this_thread::sleep_for(10ms);
    timer.stop();
    //std::this_thread::sleep_for(1ms);
    timer.start(10ms, timeout_handler);
    std::this_thread::sleep_for(20ms);
  }

  return 0;
}
