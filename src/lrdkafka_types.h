#ifndef LRDKAFKA_TYPES_H
#define LRDKAFKA_TYPES_H
#include <librdkafka/rdkafka.h>

typedef struct {
  rd_kafka_conf_t *conf;
} lrd_kafka_conf_t;

typedef struct {
  rd_kafka_topic_t *topc;
} lrd_kafka_topic_t;

typedef struct {
  rd_kafka_topic_conf_t *topic_conf;
} lrd_kafka_topic_conf_t;

typedef struct {
  rd_kafka_queue_t *queue;
} lrd_kafka_queue_t;

typedef struct {
  rd_kafka_t *client;
  lrd_kafka_conf_t *conf;
} lrd_kafka_client_t;

#endif

