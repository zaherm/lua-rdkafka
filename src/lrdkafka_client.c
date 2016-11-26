#include "lrdkafka_client.h"

lrd_kafka_client_t *lrd_kafka_check_client(lua_State *L, int index) {
  lrd_kafka_client_t *c = (lrd_kafka_client_t *) luaL_checkudata(L, index, "client");
  luaL_argcheck(L, c != NULL && c->client != NULL, index, "client expected");
  return c;
}

LUALIB_API int lrd_kafka_client_new(lua_State *L) {
  lrd_kafka_client_t *c = (lrd_kafka_client_t *) lua_newuserdata(L, sizeof(lrd_kafka_client_t));
  lrd_kafka_assert(L, c != NULL, "failed to create client");
  rd_kafka_type_t type = luaL_checkinteger(L, 1);
  lrd_kafka_conf_t *conf = lrd_kafka_check_conf(L, 2);
	char errstr[512];
  c->conf = conf;
  c->client = rd_kafka_new(type, c->conf->conf, errstr, sizeof(errstr));
  if(!c->client) {
    luaL_error(L, errstr);
    return 0;
  }
  lrd_kafka_setmeta(L, "client");
  return 1;
}

LUALIB_API int lrd_kafka_client_destroy(lua_State *L) {
  lrd_kafka_client_t *c = lrd_kafka_check_client(L, 1);
  if(c->client != NULL && c->conf->conf != NULL) {
    rd_kafka_destroy(c->client);
    c->client = NULL;
    c->conf->conf = NULL; //to avoid double free, as the rd_kafka_destroy frees the conf too
  }
  return 0;
}

LUALIB_API int lrd_kafka_client_name(lua_State *L) {
  return 1;
}

LUALIB_API int lrd_kafka_client_memberid(lua_State *L) {
  return 1;
}

LUALIB_API int lrd_kafka_client_push_consts(lua_State *L) {
  lua_pushinteger(L, RD_KAFKA_PRODUCER);
  lua_setfield(L, -2, "PRODUCER");
  lua_pushinteger(L, RD_KAFKA_CONSUMER);
  lua_setfield(L, -2, "CONSUMER");
  return 0;
}

LUALIB_API int lrd_kafka_client_meta(lua_State *L) {
  lrd_kafka_createmeta(L, "client", lrd_kafka_client_methods);
  return 0;
}


