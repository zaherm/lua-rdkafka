local rdkafka = require("rdkafka")

local topic_conf = rdkafka.topic_conf()
local test_conf = {
  ["offset.store.sync.interval.ms"] = "-1",
  ["consume.callback.max.messages"]= "0",
  ["produce.offset.report"] = "false",
  ["auto.commit.enable"] = "true",
  ["message.timeout.ms"] = "700000",
  ["request.timeout.ms"] = "2000"
}

assert(topic_conf.class == "topic_conf")
local res, val
for k,v in pairs(test_conf) do
  res, _ = topic_conf:set(k, v)
  assert(res == 0)
  res, val = topic_conf:get(k)
  assert(res == 0)
  assert(val == v)
end
