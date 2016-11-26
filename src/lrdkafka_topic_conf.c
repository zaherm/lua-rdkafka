#include "lrdkafka_topic_conf.h"

lrd_kafka_topic_conf_t *lrd_kafka_check_topic_conf(lua_State *L, int index) {
  lrd_kafka_topic_conf_t *tc = (lrd_kafka_topic_conf_t *) luaL_checkudata(L, index, "topic_conf");
  luaL_argcheck(L, tc != NULL && tc->topic_conf != NULL, index, "topic_conf expected");
  return tc;
}

LUALIB_API int lrd_kafka_topic_conf_new(lua_State *L) {
  lrd_kafka_topic_conf_t *tc = (lrd_kafka_topic_conf_t *) lua_newuserdata(L, sizeof(lrd_kafka_topic_conf_t));
  tc->topic_conf = rd_kafka_topic_conf_new();
  lrd_kafka_setmeta(L, "topic_conf");
  return 1;
}

LUALIB_API int lrd_kafka_topic_conf_dup(lua_State *L) {
  lrd_kafka_topic_conf_t *tc = lrd_kafka_check_topic_conf(L, 1);
  lrd_kafka_topic_conf_t *dup = (lrd_kafka_topic_conf_t *) lua_newuserdata(L, sizeof(lrd_kafka_topic_conf_t));
  dup->topic_conf = rd_kafka_topic_conf_dup(tc->topic_conf);
  lrd_kafka_setmeta(L, "topic_conf");
  return 1;
}

LUALIB_API int lrd_kafka_topic_conf_destroy(lua_State *L) {
  lrd_kafka_topic_conf_t *tc = lrd_kafka_check_topic_conf(L, 1);
  if(tc != NULL && tc->topic_conf != NULL) {
    rd_kafka_topic_conf_destroy(tc->topic_conf);
    tc->topic_conf = NULL;
  }
  return 0;
}
LUALIB_API int lrd_kafka_topic_conf_set(lua_State *L) {
  lrd_kafka_topic_conf_t *tc = lrd_kafka_check_topic_conf(L, 1);
  const char *name = luaL_checkstring(L, 2);
  const char *value = luaL_checkstring(L, 3);
  char errstr[512];
  rd_kafka_conf_res_t res = rd_kafka_topic_conf_set(tc->topic_conf, name, value,
                                                    errstr, sizeof(errstr));
  lua_pushinteger(L, res);
  if(res != RD_KAFKA_CONF_OK) {
    lua_pushstring(L, errstr);
  }
  else {
    lua_pushnil(L);
  }
  return 2;
}
LUALIB_API int lrd_kafka_topic_conf_get(lua_State *L) {
  lrd_kafka_topic_conf_t *tc = lrd_kafka_check_topic_conf(L, 1);
  const char *name = luaL_checkstring(L, 2);
  char value[512];
  size_t value_len = sizeof(value);
  rd_kafka_conf_res_t res = rd_kafka_topic_conf_get(tc->topic_conf, name,
                                                    value, &value_len);
  lua_pushinteger(L, res);
  if(res == RD_KAFKA_CONF_OK) {
    lua_pushstring(L, value);
  }
  else {
    lua_pushnil(L);
  }
  return 2;
}

LUALIB_API int lrd_kafka_topic_conf_dump(lua_State *L){
  lrd_kafka_topic_conf_t *tc = lrd_kafka_check_topic_conf(L, 1);
  size_t cntp;
  const char **arr_conf = rd_kafka_topic_conf_dump(tc->topic_conf, &cntp);
  size_t i;
  lua_newtable(L);
  for(i = 0; i < cntp; i += 2) {
    lua_pushstring(L, arr_conf[i + 1]);
    lua_setfield(L, -2, arr_conf[i]);
  }
  rd_kafka_conf_dump_free(arr_conf, cntp);
  return 1;
}

LUALIB_API int lrd_kafka_topic_conf_gc(lua_State *L) {
  return lrd_kafka_topic_conf_destroy(L);
}

static luaL_Reg lrd_kafka_topic_conf_mod[] = {
  { "__call", lrd_kafka_topic_conf_new },
  { NULL, NULL }
};

LUALIB_API int lrd_kafka_topic_conf_meta(lua_State *L) {
  lrd_kafka_createmeta(L, "topic_conf", lrd_kafka_topic_conf_methods);
  luaL_setfuncs(L, lrd_kafka_topic_conf_mod, 0);
  return 0;
}

