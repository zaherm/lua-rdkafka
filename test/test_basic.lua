local rdkafka = require("rdkafka")

for k,v in pairs(rdkafka) do
    print(k, v)
end
assert(rdkafka._VERSION == "lua-rdkafka 0.0.1")
print(rdkafka.version_str())
print(rdkafka.version())