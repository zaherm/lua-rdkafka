#include "lrdkafka_conf.h"

lrd_kafka_conf_t *lrd_kafka_check_conf(lua_State *L, int index) {
  lrd_kafka_conf_t *c = (lrd_kafka_conf_t *) luaL_checkudata(L, index, "conf");
  luaL_argcheck(L, c != NULL && c->conf != NULL, index, "conf expected");
  return c;
}

LUALIB_API int lrd_kafka_conf_new(lua_State *L) {
  lrd_kafka_conf_t *c = (lrd_kafka_conf_t *) lua_newuserdata(L, sizeof(lrd_kafka_conf_t));
  lrd_kafka_assert(L, c!= NULL, "failed to create conf");
  c->conf = rd_kafka_conf_new();
  lrd_kafka_setmeta(L, "conf");
  return 1;
}

LUALIB_API int lrd_kafka_conf_dup(lua_State *L) {
  lrd_kafka_conf_t *c = lrd_kafka_check_conf(L, 1);
  lrd_kafka_conf_t *new_conf = (lrd_kafka_conf_t *) lua_newuserdata(L, sizeof(lrd_kafka_conf_t));
  lrd_kafka_assert(L, new_conf!= NULL, "failed to duplicate conf");
  new_conf->conf = rd_kafka_conf_dup(c->conf);
  lrd_kafka_setmeta(L, "conf");
  return 1;
}

/* rd_kafka_conf_res_t rd_kafka_conf_set(rd_kafka_conf_t *conf,
   const char *name,
   const char *value,
   char *errstr, size_t errstr_size);
   */
LUALIB_API int lrd_kafka_conf_set(lua_State *L) {
  lrd_kafka_conf_t *c = lrd_kafka_check_conf(L, 1);
  const char *name = luaL_checkstring(L, 2);
  const char *value = luaL_checkstring(L, 3);
  char errstr[512];
  rd_kafka_conf_res_t res = rd_kafka_conf_set(c->conf, name, value, errstr, sizeof(errstr));
  lua_pushinteger(L, res);
  if(res != RD_KAFKA_CONF_OK) {
    lua_pushstring(L, errstr);
  }
  else {
    lua_pushnil(L);
  }
  return 2;
}

/* void rd_kafka_conf_set_events(rd_kafka_conf_t *conf, int events);
*/
LUALIB_API int lrd_kafka_conf_set_events(lua_State *L) {
  lrd_kafka_conf_t *c = lrd_kafka_check_conf(L, 1);
  int events = luaL_checkint(L, 2);
  rd_kafka_conf_set_events(c->conf, events);
  return 0;
}

LUALIB_API int lrd_kafka_conf_destroy(lua_State *L) {
  lrd_kafka_conf_t *c = lrd_kafka_check_conf(L, 1);
  if(c!= NULL && c->conf != NULL) {
    rd_kafka_conf_destroy(c->conf);
    c->conf = NULL;
  }
  return 1;
}
/* rd_kafka_conf_res_t rd_kafka_conf_get (const rd_kafka_conf_t *conf,
   const char *name,
   char *dest, size_t *dest_size);

*/
LUALIB_API int lrd_kafka_conf_get(lua_State *L) {
  lrd_kafka_conf_t *c = lrd_kafka_check_conf(L, 1);
  const char *name = luaL_checkstring(L, 2);
  char value[512];
  size_t value_len = sizeof(value);
  rd_kafka_conf_res_t res = rd_kafka_conf_get(c->conf, name, value, &value_len);
  lua_pushinteger(L, res);
  if(res == RD_KAFKA_CONF_OK) {
    lua_pushstring(L, value);
  }
  else {
    lua_pushnil(L);
  }
  return 2;
}

LUALIB_API int lrd_kafka_conf_dump(lua_State *L) {
  lrd_kafka_conf_t *c = lrd_kafka_check_conf(L, 1);
  size_t cntp;
  const char **arr_conf = rd_kafka_conf_dump(c->conf, &cntp);
  size_t i;
  lua_newtable(L);
  for(i = 0; i < cntp; i += 2) {
    lua_pushstring(L, arr_conf[i + 1]);
    lua_setfield(L, -2, arr_conf[i]);
  }
  rd_kafka_conf_dump_free(arr_conf, cntp);
  return 1;
}

LUALIB_API int lrd_kafka_conf_gc(lua_State *L) {
  return lrd_kafka_conf_destroy(L);
}

static luaL_Reg lrd_kafka_conf_mod[] = {
  { "conf", lrd_kafka_conf_new },
  { NULL, NULL }
};

LUALIB_API int lrd_kafka_conf_meta(lua_State *L) {
  lrd_kafka_createmeta(L, "conf", lrd_kafka_conf_reg);
  luaL_setfuncs(L, lrd_kafka_conf_mod, 0);
  return 0;
}
