#ifndef ABSTRACTEVENTMONITOR_H
#define ABSTRACTEVENTMONITOR_H

#include "Poco/ActiveResult.h"
#include "Poco/ActiveMethod.h"
#include "Poco/Logger.h"
#include <stdlib.h>

class AbstractEventMonitor: public Poco::Runnable{
public:
    AbstractEventMonitor(const long& timeout): _finished(false), _timeout(timeout), _logger(Poco::Logger::get("EMON")){}
    ~AbstractEventMonitor(){}
    void run(){
        Poco::Thread::trySleep(_timeout);
        Poco::FastMutex::ScopedLock lock(_mutex);
        if(!_finished) {
		_logger.error("Aborting. Reason: Event timeout!");
		abort();
        }
    }

    void finished(){
        Poco::FastMutex::ScopedLock lock(_mutex);
        _finished = true;
    }
private:
    volatile bool _finished;
    const long& _timeout;
    Poco::FastMutex _mutex;
    Poco::Logger& _logger;
};

#endif // ABSTRACTEVENTMONITOR_H
