#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

template <class T> class MsgQueue
{
public:
  MsgQueue() = default;
  virtual ~MsgQueue() {}

  void send(T msg)
  {
    std::lock_guard<std::mutex> lk(m_);
    queue_.push(msg);

    cv_.notify_one();
  }

  T receive()
  {
    std::unique_lock<std::mutex> lk(m_);
    cv_.wait(lk, [this]{return queue_.size() > 0;});

    T msg = queue_.front();
    queue_.pop();

    return msg;
  }

  T receive_with_timeout(std::chrono::milliseconds timeout, T timeout_message)
  {
    std::unique_lock<std::mutex> lk(m_);
    auto res = cv_.wait_for(lk, timeout, [this]{return queue_.size() > 0;});

    if (res)
    {
      T msg = queue_.front();
      queue_.pop();
      return msg;
    }
    else
    {
      return timeout_message;
    }
  }

private:
  std::mutex m_;
  std::condition_variable cv_;
  std::queue<T> queue_;
};

#endif // MESSAGEQUEUE_H
