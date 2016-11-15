#include "lrdkafka.h"
/* aux */
#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501
LUALIB_API void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
  luaL_checkstack(L, nup+1, "too many upvalues");
  for (; l->name != NULL; l++) {  /* fill the table with given functions */
    int i;
    lua_pushstring(L, l->name);
    for (i = 0; i < nup; i++)  /* copy upvalues to the top */
      lua_pushvalue(L, -(nup+1));
    lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
    lua_settable(L, -(nup + 3));
  }
  lua_pop(L, nup);  /* remove upvalues */
}
#endif

LUALIB_API void lrd_kafka_setmeta(lua_State *L, const char *name) {
  luaL_getmetatable(L, name);
  lua_setmetatable(L, -2);
}

LUALIB_API int lrd_kafka_createmeta(lua_State *L, const char *name, const luaL_Reg *methods) {
  if (!luaL_newmetatable(L, name)) {
    return 0;
  }

  lua_pushstring(L, "__index");
  lua_newtable(L);
  for (; methods->name; methods++) {
    lua_pushstring(L, methods->name);
    lua_pushcfunction(L, methods->func);
    lua_rawset(L, methods->name[0] == '_' ? -5: -3);
  }
  lua_rawset(L, -3);
  lua_pop(L, 1);
  return 1;
}
/* //aux */

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