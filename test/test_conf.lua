local rdkafka = require("rdkafka")

assert(rdkafka._VERSION == "lua-rdkafka 0.0.1")

local conf = rdkafka.conf()
assert(conf)
assert(conf == conf)
assert(conf.class == "conf")
assert(conf ~= conf:dup()) --nothing deep here, just check table address
local res, err = conf:set("conf.unknown", "1")
assert(res == -2)
ok, res = conf:get("request.required.acks")

res, _ = conf:set("group.id", "1")
assert(res == 0)

local res, val = conf:get("group.id")
assert(val == "1")
local dump = conf:dump()
assert(type(dump) == "table")
collectgarbage()

