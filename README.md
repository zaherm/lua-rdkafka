# lua-rdkafka
librdkafka Lua binding

# doc
###  rdkafka
####  rdkafka.version_str()
Returns the version of the librdkafka as a string.

####  rdkafka.version()
Returns the number representation of the librdkafka version.

### rdkafka.conf()
Create new instance of the *conf*.

#### conf:get(name)
Get the conf value of *name*. Return value is _string_.

#### conf:get(name, value)
Sets conf of *name* (string) to *value* (string).

#### conf:dup()
Duplicates a conf object. Returns new *conf* object.

#### conf:dump()
Dumps *conf* as a table, both key and value of the table are _strings_.

### rdkafka.topic_conf()
Create new instance of the *topic_conf*.

#### topic_conf:get(name)
Get the  value of *name*. Return value is _string_.

#### topic_conf:get(name, value)
Set *name* (string) to *value* (string).

#### topic_conf:dup()
Duplicates a topic_conf object. Returns new *topic_conf* object.

#### topic_conf:dump()
Dumps *topic_conf* as a table, both key and value of the table are _strings_.
