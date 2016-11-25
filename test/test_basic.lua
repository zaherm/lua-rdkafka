local rdkafka = require("rdkafka")

for k,v in pairs(rdkafka) do
    print(k, v)
end
assert(rdkafka._VERSION == "lua-rdkafka 0.0.1")
print(rdkafka.version_str())
print(rdkafka.version())

local conf = rdkafka.conf()
assert(conf)
assert(conf == conf)
assert(conf.class == "conf")
assert(conf ~= conf:dup()) --nothing deep here, just check table address
local res, err = conf:set("conf.unknown", "1")
print(":set", res, err)
assert(res == -2)
ok, res = conf:get("request.required.acks")
print(":get", ok, res)

print(conf:set("group.id", "1"))
local res, val = conf:get("group.id")
print(res, val == "1", string.len(val))
assert(val == "1")
local dump = conf:dump()
assert(type(dump) == "table")
for k,v in pairs(dump) do
    print(k..": "..v)
end
collectgarbage()