#pragma once

#include <sys/types.h>
#include <unistd.h>

#include "natalie/forward.hpp"
#include "natalie/integer_value.hpp"
#include "natalie/value.hpp"

namespace Natalie {

struct ProcessModule : Value {

    static Value *pid(Env *env) {
        pid_t pid = getpid();
        return new IntegerValue { env, pid };
    }
};

}
