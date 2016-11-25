#ifndef LRDKAFKA_AUX_H
#define LRDKAFKA_AUX_H
#include "lauxlib.h"

#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501
LUALIB_API void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup);
#endif

LUALIB_API void lrd_kafka_setmeta(lua_State *L, const char *name);
LUALIB_API int lrd_kafka_createmeta(lua_State *L, const char *name, const luaL_Reg *methods);

void lrd_kafka_assert(lua_State *L, int cond, const char *msg) ;
#endif
