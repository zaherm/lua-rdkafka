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

#define LRDKAFKA_VERSION "lua-rdkafka 0.0.1"
#define LRDKAFKA_COPYRIGHT "Copyright (C) 2016, Zaher Marzuq"
#define LRDKAFKA_DESCRIPTION "rdkafka binding for Lua"

LUALIB_API int lrd_kafka_version(lua_State *L);
LUALIB_API int lrd_kafka_version_str(lua_State *L);

#endif

