#include <iostream>

#include <DispatchQueue.hpp>

DispatchQueue::DispatchQueue(size_t numThreads): threads_{numThreads}
{
	for(size_t i = 0; i < numThreads; ++i)
	{
		threads_[i] = std::thread(&DispatchQueue::doDispatch, this);
	}
}

void DispatchQueue::doDispatch()
{
	while(true)
	{
		std::unique_lock ul(mutex_);
		cv_.wait(ul, [this]{ return quit_ or callbackQueue_.size(); });
		if(quit_)
			return;
		auto const op = std::move(callbackQueue_.front());
		callbackQueue_.pop_front();
		ul.unlock();
		op();
	}
}

DispatchQueue::~DispatchQueue()
{
	std::unique_lock ul(mutex_);
	quit_ = true;
	ul.unlock();
	cv_.notify_all();

	for(auto& t : threads_)
	{
		if(t.joinable())
		{
			t.join();
		}
	}
}

