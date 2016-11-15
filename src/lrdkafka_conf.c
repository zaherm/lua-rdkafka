#include "lrdkafka_conf.h"

LUALIB_API int lrd_kafka_conf_new(lua_State *L) {
    return 1;
}

LUALIB_API int lrd_kafka_conf_destroy(lua_State *L) {
    return 1;
}

LUALIB_API int lrd_kafka_conf_gc(lua_State *L) {
    return 0;
}

static luaL_Reg lrd_kafka_conf_mod[] = {
  { "conf", lrd_kafka_conf_new },
  { NULL, NULL }
};

LUALIB_API int lrd_kafka_conf_open(lua_State *L) {
    lrd_kafka_createmeta(L, "conf", lrd_kafka_conf_reg);
    luaL_setfuncs(L, lrd_kafka_conf_mod, 0);
    return 0;
}
