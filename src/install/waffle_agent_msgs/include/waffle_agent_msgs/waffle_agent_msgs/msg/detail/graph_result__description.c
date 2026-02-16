// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from waffle_agent_msgs:msg/GraphResult.idl
// generated code does not contain a copyright notice

#include "waffle_agent_msgs/msg/detail/graph_result__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
const rosidl_type_hash_t *
waffle_agent_msgs__msg__GraphResult__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x4f, 0x34, 0x01, 0x74, 0xb8, 0x81, 0x19, 0x41,
      0xaa, 0xc8, 0xe5, 0xa1, 0x1c, 0x8e, 0x3b, 0xb1,
      0xba, 0xd3, 0xdc, 0xbc, 0x0c, 0x7c, 0x64, 0x8e,
      0x64, 0x72, 0x80, 0xde, 0x8c, 0x67, 0x5d, 0xdf,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char waffle_agent_msgs__msg__GraphResult__TYPE_NAME[] = "waffle_agent_msgs/msg/GraphResult";

// Define type names, field names, and default values
static char waffle_agent_msgs__msg__GraphResult__FIELD_NAME__node_id[] = "node_id";
static char waffle_agent_msgs__msg__GraphResult__FIELD_NAME__label[] = "label";
static char waffle_agent_msgs__msg__GraphResult__FIELD_NAME__score[] = "score";
static char waffle_agent_msgs__msg__GraphResult__FIELD_NAME__position[] = "position";

static rosidl_runtime_c__type_description__Field waffle_agent_msgs__msg__GraphResult__FIELDS[] = {
  {
    {waffle_agent_msgs__msg__GraphResult__FIELD_NAME__node_id, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__msg__GraphResult__FIELD_NAME__label, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__msg__GraphResult__FIELD_NAME__score, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__msg__GraphResult__FIELD_NAME__position, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
waffle_agent_msgs__msg__GraphResult__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {waffle_agent_msgs__msg__GraphResult__TYPE_NAME, 33, 33},
      {waffle_agent_msgs__msg__GraphResult__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 node_id\n"
  "string label\n"
  "float32 score\n"
  "float32[] position";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
waffle_agent_msgs__msg__GraphResult__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {waffle_agent_msgs__msg__GraphResult__TYPE_NAME, 33, 33},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 59, 59},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
waffle_agent_msgs__msg__GraphResult__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *waffle_agent_msgs__msg__GraphResult__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
