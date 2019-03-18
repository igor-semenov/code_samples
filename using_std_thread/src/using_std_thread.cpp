#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

class Usage {
 public:
  Usage() : th_([this]() { run(); }) {}
  virtual ~Usage() noexcept {}
  virtual void run() {}
 private:
  std::thread th_;
};

class BadUsage : public Usage {
 public:
  BadUsage() : ptr_((std::this_thread::sleep_for(std::chrono::milliseconds(1)), new char[100])) {}
  ~BadUsage() noexcept { delete[] ptr_; }
  void run() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::memcpy(ptr_, "Hello", sizeof("Hello"));
  }
 private:
  char* ptr_;
};

/*
class JoinUsage : public Usage {
 public:
  void run() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  void join() {
    if (th_.joinable()) {
      th_.join();
    }
  }
};
*/

class TwoPhaseUsage {
 public:
  TwoPhaseUsage() = default;
  ~TwoPhaseUsage() noexcept {}
  void start() { th_.reset(new std::thread([this](){ run(); })); }
  virtual void run() {}
  void join() {
    if (th_ && th_->joinable()) {
      th_->join();
    }
  }
 private:
  std::unique_ptr<std::thread> th_;
};


class GoodUsage : public TwoPhaseUsage {
 public:
  GoodUsage() : ptr_((std::this_thread::sleep_for(std::chrono::milliseconds(1)), new char[100])) {}
  ~GoodUsage() noexcept { delete[] ptr_; }
  void run() {
    std::memcpy(ptr_, "Hello", sizeof("Hello"));
  }
 private:
  char* ptr_;
};


int main() {
  GoodUsage gu;
  gu.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  gu.join();
  return 0;
}

