#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <functional>
#include <vector>

class DispatchQueue
{

using CallBack = std::function<void()>;

public:
	DispatchQueue(DispatchQueue const&) = delete;
	DispatchQueue(DispatchQueue &) = delete;
	DispatchQueue& operator=(DispatchQueue const&) = delete;
	DispatchQueue& operator=(DispatchQueue &&) = delete;

	DispatchQueue(size_t numThreads = 1);

	void dispatch(auto&& ... cb)
	{
		(dispatchImpl(std::forward<decltype(cb)>(cb)), ...);
	}

	~DispatchQueue();

private:
	void doDispatch();

	void dispatchImpl(auto&& cb)
	{
		std::lock_guard lg(mutex_);
		callbackQueue_.emplace_back(std::forward<decltype(cb)>(cb));
		cv_.notify_one();
	}

private:
	std::mutex mutex_;
	std::condition_variable cv_;
	std::deque<CallBack> callbackQueue_;
	std::vector<std::thread> threads_;
	bool quit_{false};

};
