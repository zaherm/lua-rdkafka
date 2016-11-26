#ifndef LRDKAFKA_CONF_H
#define LRDKAFKA_CONF_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "lauxlib.h"

#include "lrdkafka_types.h"
#include "lrdkafka_aux.h"

lrd_kafka_conf_t *lrd_kafka_check_conf(lua_State *L, int index);


LUALIB_API int lrd_kafka_conf_new(lua_State *L);
LUALIB_API int lrd_kafka_conf_destroy(lua_State *L);
LUALIB_API int lrd_kafka_conf_dup(lua_State *L);
LUALIB_API int lrd_kafka_conf_set(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_events(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_default_topic_conf(lua_State *L);
LUALIB_API int lrd_kafka_conf_get(lua_State *L);
LUALIB_API int lrd_kafka_conf_dump(lua_State *L);
LUALIB_API int lrd_kafka_conf_properties_show(lua_State *L);
LUALIB_API int lrd_kafka_conf_gc(lua_State *L);
LUALIB_API int lrd_kafka_conf_meta(lua_State *L);

static const struct luaL_Reg lrd_kafka_conf_methods[] = {
  { "destroy", lrd_kafka_conf_destroy },
  { "dup", lrd_kafka_conf_dup },
  { "set", lrd_kafka_conf_set },
  { "set_events", lrd_kafka_conf_set_events },
  { "get", lrd_kafka_conf_get },
  { "dump", lrd_kafka_conf_dump },
  { "__gc", lrd_kafka_conf_gc },
  { NULL, NULL }
};

#endif

