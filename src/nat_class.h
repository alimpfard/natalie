#ifndef __NAT_CLASS__
#define __NAT_CLASS__

NatObject *Class_new(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs);

#endif