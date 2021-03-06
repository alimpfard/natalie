#pragma once

#include <stdlib.h>

#include "natalie/forward.hpp"
#include "natalie/gc.hpp"
#include "natalie/hashmap.hpp"

namespace Natalie {

extern "C" {
#include "onigmo.h"
}

struct GlobalEnv : public gc {
    GlobalEnv() {
        m_globals = static_cast<hashmap *>(GC_MALLOC(sizeof(hashmap)));
        hashmap_init(m_globals, hashmap_hash_string, hashmap_compare_string, 100);
        hashmap_set_key_alloc_funcs(m_globals, hashmap_alloc_key_string, nullptr);
        m_symbols = static_cast<hashmap *>(GC_MALLOC(sizeof(hashmap)));
        hashmap_init(m_symbols, hashmap_hash_string, hashmap_compare_string, 100);
        hashmap_set_key_alloc_funcs(m_symbols, hashmap_alloc_key_string, nullptr);
    }

    hashmap *globals() {
        return m_globals;
    }

    hashmap *symbols() {
        return m_symbols;
    }

    ClassValue *Array() { return m_Array; }
    void set_Array(ClassValue *Array) { m_Array = Array; }

    ClassValue *Object() { return m_Object; }
    void set_Object(ClassValue *Object) { m_Object = Object; }

    ClassValue *Integer() { return m_Integer; }
    void set_Integer(ClassValue *Integer) { m_Integer = Integer; }

    NilValue *nil_obj() { return m_nil_obj; }
    void set_nil_obj(NilValue *nil_obj) { m_nil_obj = nil_obj; }

    TrueValue *true_obj() { return m_true_obj; }
    void set_true_obj(TrueValue *true_obj) { m_true_obj = true_obj; }

    FalseValue *false_obj() { return m_false_obj; }
    void set_false_obj(FalseValue *false_obj) { m_false_obj = false_obj; }

    FiberValue *main_fiber(Env *);

    FiberValue *current_fiber() { return m_current_fiber; }
    void set_current_fiber(FiberValue *fiber) { m_current_fiber = fiber; }
    void reset_current_fiber() { m_current_fiber = m_main_fiber; }

    size_t fiber_argc() { return m_fiber_args.argc; }
    Value **fiber_args() { return m_fiber_args.args; }
    void set_fiber_args(size_t argc, Value **args) {
        m_fiber_args.argc = argc;
        m_fiber_args.args = args;
    }

private:
    hashmap *m_globals { nullptr };
    hashmap *m_symbols { nullptr };
    ClassValue *m_Array { nullptr };
    ClassValue *m_Integer { nullptr };
    ClassValue *m_Object { nullptr };
    NilValue *m_nil_obj { nullptr };
    TrueValue *m_true_obj { nullptr };
    FalseValue *m_false_obj { nullptr };

    FiberValue *m_main_fiber { nullptr };
    FiberValue *m_current_fiber { nullptr };
    struct {
        size_t argc { 0 };
        Value **args { nullptr };
    } m_fiber_args;
};
}
