#pragma once
#include <functional>
#include <queue>
#ifdef _WIN32
#include "../../ExternalLibraries/include/pthreads/pthread.h"
#include "../../ExternalLibraries/include/pthreads/semaphore.h"
#endif

#ifdef __EMSCRIPTEN__
#include <unistd.h>
#include <pthread.h>
#include  <semaphore.h>
#endif

namespace ScummWeb {
namespace WebFrontEnd {
namespace Wasm {
namespace Workers {

template<class T, class U = void *>
class QueueWorker {
public:
	typedef void (*workFunction)(T *, U *);

private:
	std::queue<U *> _workQueue;
	sem_t _lock;
	workFunction _workFunction;
	pthread_t _pThread;
	int _sleepMs;
	bool _stopped;

protected:
	virtual void Init(workFunction workFunction, int sleepMs) {
		_workFunction = workFunction;
		_sleepMs = sleepMs;
	}

	virtual void PreStart(pthread_attr_t* attr) {
	}

	virtual void OnThreadStart() {

	}

public:
	int GetSleepMs();

	U* GetNextJob() {
		U* nextJob = nullptr;
		sem_wait(&_lock);
		while (!_workQueue.empty() && nextJob == nullptr) { //Loop is so we ignore nulls
			nextJob = _workQueue.front();
			_workQueue.pop();
		}
		sem_post(&_lock);

		return nextJob;
	}

	void WorkFunction() {
		OnThreadStart();
		while (!_stopped) {
			for (U* nextJob = GetNextJob(); nextJob != nullptr; nextJob = GetNextJob()) {
				if (nextJob) {
					_workFunction((T *)this, nextJob);
				}
			}
			usleep(_sleepMs);
		}
	}

	QueueWorker() {
		if (sem_init(&_lock, 0, 1) != 0) {
			throw "Failed To Init Semaphore";
		}
		_stopped = false;
		_sleepMs = 0;
		_workFunction = nullptr;
		_pThread = pthread_t();
	}

	~QueueWorker() {
		sem_close(&_lock);
	}

	inline void Enqueue(U* toQueue) {
		sem_wait(&_lock);
		_workQueue.push(toQueue);
		sem_post(&_lock);
	}

	void Start() {
		pthread_attr_t attr;

		pthread_attr_init(&attr);
		PreStart(&attr);
		pthread_create(&_pThread, &attr, &threadCallback, this);
		pthread_attr_destroy(&attr);
	}

	void Stop() {
		_stopped = true;
		pthread_join(_pThread, nullptr);
	}

	static void *threadCallback(void *queueWorker) {
		((QueueWorker<void *> *)queueWorker)->WorkFunction();

		return nullptr;
	}
};

template<class T, class U>
inline int QueueWorker<T, U>::GetSleepMs() {
	return _sleepMs;
}

} // namespace Workers
} // namespace Wasm
} // namespace WebFrontEnd
} // namespace ScummWeb
