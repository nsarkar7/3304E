#include "async.hpp"

#include <list>
#include <string>

#include "common.h"
#include "pros/apix.h"
#include "pros/rtos.hpp"

static pros::Mutex asyncQueueLock;
static std::list<std::function<void()>> asyncExecQueue;

pros::c::sem_t asyncExecSem = nullptr;

namespace src::Actions {

void workerExec(void*) {
    while (!pros::competition::is_disabled() && pros::c::sem_wait(asyncExecSem, TIMEOUT_MAX)) {  // waits to be notified to execute
        asyncQueueLock.take();

        auto func = asyncExecQueue.front();
        asyncExecQueue.pop_front();

        asyncQueueLock.give();

        func();  // pull+pop front function off queue and run it.
        pdelay(1);
    }
}

void startWorkers() {
    asyncQueueLock.take();
    asyncExecQueue.clear();  // clears queue on program start.
    asyncQueueLock.give();

    asyncExecSem = pros::c::sem_create(NUM_WORKERS * 3, 0);
    for (int i = 0; i < NUM_WORKERS; i++) {
        pros::Task _(workerExec, nullptr, ("asyncWorker" + std::to_string(i)).c_str());
    }
}

void doAsync(std::function<void()> func) {
    asyncQueueLock.take();
    asyncExecQueue.push_back(func);   // adds to list of functions to be executed asynchronously.
    pros::c::sem_post(asyncExecSem);  // notifies workers a task is available to execute.
    asyncQueueLock.give();
}

}