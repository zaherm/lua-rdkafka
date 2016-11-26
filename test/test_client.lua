local rdkafka = require("rdkafka")


assert(rdkafka._VERSION == "lua-rdkafka 0.0.1")
local conf = rdkafka.conf()
local client = rdkafka.client(1, conf)
assert(client)

client = nil

collectgarbage()

