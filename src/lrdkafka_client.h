#ifndef LRDKAFKA_CLIENT_H
#define LRDKAFKA_CLIENT_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "lauxlib.h"

#include "lrdkafka_types.h"
#include "lrdkafka_aux.h"
#include "lrdkafka_conf.h"

lrd_kafka_client_t *lrd_kafka_check_client(lua_State *L, int index);

LUALIB_API int lrd_kafka_client_meta(lua_State *L);
LUALIB_API int lrd_kafka_client_new(lua_State *L);
LUALIB_API int lrd_kafka_client_destroy(lua_State *L);
LUALIB_API int lrd_kafka_client_name(lua_State *L);
LUALIB_API int lrd_kafka_client_memberid(lua_State *L);

static const struct luaL_Reg lrd_kafka_client_methods[] = {
  { "destroy", lrd_kafka_client_destroy },
  { "name", lrd_kafka_client_name },
  { "memberid", lrd_kafka_client_memberid },
  { "__gc", lrd_kafka_client_destroy },
  { NULL, NULL }
};


#endif

