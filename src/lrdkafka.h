#ifndef LRDKAFKA_H
#define LRDKAFKA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "lauxlib.h"
#include <librdkafka/rdkafka.h>
#include "lrdkafka_types.h"
#include "lrdkafka_aux.h"
#include "lrdkafka_conf.h"
#include "lrdkafka_topic_conf.h"
#include "lrdkafka_client.h"


#define LRDKAFKA_VERSION "lua-rdkafka 0.0.1"
#define LRDKAFKA_COPYRIGHT "Copyright (C) 2016, Zaher Marzuq"
#define LRDKAFKA_DESCRIPTION "rdkafka binding for Lua"


LUALIB_API int lrd_kafka_meta(lua_State *L);
LUALIB_API int lrd_kafka_version(lua_State *L);
LUALIB_API int lrd_kafka_version_str(lua_State *L);

static const luaL_Reg lrd_kafka_mods[] = {
  { "conf", lrd_kafka_conf_meta },
  { "topic_conf", lrd_kafka_topic_conf_meta },
  { "client", lrd_kafka_client_meta },
  {NULL, NULL}
};

static const luaL_Reg lrdkafka_funcs[] = {
  { "version", lrd_kafka_version },
  { "version_str", lrd_kafka_version_str },
  { "conf", lrd_kafka_conf_new },
  { "topic_conf", lrd_kafka_topic_conf_new },
  { "client", lrd_kafka_client_new },
  { NULL, NULL }
};

#endif

