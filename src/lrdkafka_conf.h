#ifndef LRDKAFKA_CONF_H
#define LRDKAFKA_CONF_H
#include "lrdkafka.h"

LUALIB_API int lrd_kafka_conf_new(lua_State *L);
LUALIB_API int lrd_kafka_conf_destroy(lua_State *L);
LUALIB_API int lrd_kafka_conf_dup(lua_State *L);
LUALIB_API int lrd_kafka_conf_set(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_events(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_dr_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_dr_msg_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_consume_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_rebalance_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_offset_commit_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_offset_commit_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_throttle_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_log_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_stats_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_socket_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_connect_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_open_cb(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_opaque(lua_State *L);
LUALIB_API int lrd_kafka_opaque(lua_State *L);
LUALIB_API int lrd_kafka_conf_set_default_topic_conf(lua_State *L);
LUALIB_API int lrd_kafka_conf_get(lua_State *L);
LUALIB_API int lrd_kafka_conf_dump(lua_State *L);
LUALIB_API int lrd_kafka_conf_properties_show(lua_State *L);
LUALIB_API int lrd_kafka_conf_gc(lua_State *L);
LUALIB_API int lrd_kafka_conf_open(lua_State *L);

static const struct luaL_Reg lrd_kafka_conf_reg[] = {
  { "destroy", lrd_kafka_conf_destroy },
  { "__gc", lrd_kafka_conf_gc },
  { NULL, NULL }
};

#endif
