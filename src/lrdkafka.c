#include "lrdkafka.h"

LUALIB_API int lrd_kafka_version(lua_State *L) {
    int version = rd_kafka_version();
    lua_pushinteger(L, version);
    return 1;
}

LUALIB_API int lrd_kafka_version_str(lua_State *L) {
    const char *version = rd_kafka_version_str();
    if(version != NULL) {
        lua_pushstring(L, version);
        return 1;
    }
    return 0;
}


static const luaL_Reg lrdkafka_funcs[] = {
  { "version", lrd_kafka_version },
  { "version_str", lrd_kafka_version_str },
  { NULL, NULL }
};

static const luaL_Reg lrd_kafka_mods[] = {
  { "conf", lrd_kafka_conf_open },
  { "topic_conf", lrd_kafka_topic_conf_open },
  {NULL, NULL}
};

LUALIB_API int luaopen_rdkafka(lua_State *L) {
  lua_newtable(L);
  
  for (int i = 0; lrd_kafka_mods[i].name; i++) {
    lrd_kafka_mods[i].func(L);
  }

  luaL_setfuncs(L, lrdkafka_funcs, 0);
  lua_pushliteral(L, LRDKAFKA_VERSION);
  lua_setfield(L, -2, "_VERSION");
  lua_pushliteral(L, LRDKAFKA_COPYRIGHT);
  lua_setfield(L, -2, "_COPYRIGHT");
  lua_pushliteral(L, LRDKAFKA_DESCRIPTION);
  lua_setfield(L, -2, "_DESCRIPTION");

  return 1;
}