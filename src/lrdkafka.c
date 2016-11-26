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

LUALIB_API int lrd_kafka_meta(lua_State *L) {
  lrd_kafka_createmeta(L, "kafka", lrdkafka_reg);
  return 0;
}

LUALIB_API int lrd_kafka_new(lua_State *L) {
  return 1;
}

static const luaL_Reg lrd_kafka_mods[] = {
  { "kafka", lrd_kafka_meta },
  { "conf", lrd_kafka_conf_meta },
  { "topic_conf", lrd_kafka_topic_conf_meta },
  {NULL, NULL}
};

LUALIB_API int luaopen_rdkafka(lua_State *L) {
  lua_newtable(L);

  for (int i = 0; lrd_kafka_mods[i].name; i++) {
   lrd_kafka_mods[i].func(L);
  }
  // set the metatable of the main module to 'kafka'
  lrd_kafka_setmeta(L, "kafka");
  // push info
  lua_pushliteral(L, LRDKAFKA_VERSION);
  lua_setfield(L, -2, "_VERSION");
  lua_pushliteral(L, LRDKAFKA_COPYRIGHT);
  lua_setfield(L, -2, "_COPYRIGHT");
  lua_pushliteral(L, LRDKAFKA_DESCRIPTION);
  lua_setfield(L, -2, "_DESCRIPTION");

  return 1;
}

