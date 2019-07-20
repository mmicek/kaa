#include <functional>

#include <Python.h>

#include "kaacore/physics.h"
#include "kaacore/timers.h"
#include "kaacore/log.h"

using namespace kaacore;


struct PythonicCallbackWrapper {
    PyObject* py_callback;
    bool is_weakref;

    PythonicCallbackWrapper(PyObject* py_callback, bool is_weakref=false)
        : py_callback(py_callback), is_weakref(is_weakref)
    {
        log("Creating PythonicCallbackWrapper: %p", py_callback);
        Py_INCREF(this->py_callback);
    }

    PythonicCallbackWrapper(const PythonicCallbackWrapper& wrapper)
    {
        this->py_callback = wrapper.py_callback;
        this->is_weakref = wrapper.is_weakref;
        Py_INCREF(this->py_callback);
    }

    ~PythonicCallbackWrapper()
    {
        assert(this->py_callback != nullptr);
        Py_DECREF(this->py_callback);
    }

    PythonicCallbackWrapper& operator=(const PythonicCallbackWrapper& wrapper)
    {
        this->~PythonicCallbackWrapper();
        this->py_callback = wrapper.py_callback;
        this->is_weakref = wrapper.is_weakref;
        Py_INCREF(this->py_callback);
    }
};


typedef int (*CythonCollisionHandler)(PythonicCallbackWrapper, Arbiter,
                                      CollisionPair, CollisionPair);


CollisionHandlerFunc bind_cython_collision_handler(
    const CythonCollisionHandler cy_handler, const PythonicCallbackWrapper callback
)
{
    using namespace std::placeholders;

    return std::bind(cy_handler, callback, _1, _2, _3);
}

typedef void (*CythonTimerCallback)(PythonicCallbackWrapper);


TimerCallback bind_cython_timer_callback(
    const CythonTimerCallback cy_handler, const PythonicCallbackWrapper callback
)
{
    return std::bind(cy_handler, callback);
}
