// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from waffle_agent_msgs:srv/SearchByLabel.idl
// generated code does not contain a copyright notice

#include "waffle_agent_msgs/srv/detail/search_by_label__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
const rosidl_type_hash_t *
waffle_agent_msgs__srv__SearchByLabel__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf3, 0xf0, 0xd3, 0xa1, 0x1d, 0x21, 0x9a, 0x0a,
      0x5f, 0x15, 0x4e, 0x1a, 0x57, 0xc1, 0x19, 0x06,
      0xca, 0x42, 0x32, 0xf0, 0xbc, 0x81, 0xa4, 0x41,
      0xfa, 0x63, 0x32, 0x74, 0xe5, 0x29, 0x74, 0x69,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
const rosidl_type_hash_t *
waffle_agent_msgs__srv__SearchByLabel_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x42, 0xa8, 0x1d, 0x99, 0x68, 0x37, 0x89, 0xb3,
      0xf3, 0x8d, 0xf3, 0x62, 0x0e, 0x82, 0xc6, 0x84,
      0x19, 0xde, 0x39, 0xc7, 0xde, 0x4f, 0x2e, 0x9e,
      0xd3, 0x9b, 0x35, 0x22, 0xed, 0x3b, 0x7b, 0xcd,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
const rosidl_type_hash_t *
waffle_agent_msgs__srv__SearchByLabel_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x50, 0x7b, 0xc5, 0xb5, 0xc4, 0x4a, 0x5a, 0xb3,
      0xd4, 0x23, 0xd2, 0x31, 0x83, 0x73, 0xe8, 0x41,
      0x44, 0xee, 0x1a, 0x20, 0x4f, 0x86, 0x7b, 0x13,
      0x51, 0x56, 0xca, 0x47, 0xe9, 0x96, 0x1f, 0xa1,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
const rosidl_type_hash_t *
waffle_agent_msgs__srv__SearchByLabel_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x5a, 0x4d, 0x53, 0x27, 0x5a, 0x20, 0xd7, 0x63,
      0x61, 0xe1, 0xed, 0x4f, 0xdf, 0x40, 0xaf, 0x0b,
      0xd9, 0x7c, 0x23, 0xbe, 0xc2, 0xe6, 0xa0, 0xf4,
      0xc8, 0xcb, 0xb5, 0xa8, 0x2d, 0x62, 0xc1, 0x4d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "waffle_agent_msgs/msg/detail/graph_result__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
static const rosidl_type_hash_t waffle_agent_msgs__msg__GraphResult__EXPECTED_HASH = {1, {
    0x4f, 0x34, 0x01, 0x74, 0xb8, 0x81, 0x19, 0x41,
    0xaa, 0xc8, 0xe5, 0xa1, 0x1c, 0x8e, 0x3b, 0xb1,
    0xba, 0xd3, 0xdc, 0xbc, 0x0c, 0x7c, 0x64, 0x8e,
    0x64, 0x72, 0x80, 0xde, 0x8c, 0x67, 0x5d, 0xdf,
  }};
#endif

static char waffle_agent_msgs__srv__SearchByLabel__TYPE_NAME[] = "waffle_agent_msgs/srv/SearchByLabel";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";
static char waffle_agent_msgs__msg__GraphResult__TYPE_NAME[] = "waffle_agent_msgs/msg/GraphResult";
static char waffle_agent_msgs__srv__SearchByLabel_Event__TYPE_NAME[] = "waffle_agent_msgs/srv/SearchByLabel_Event";
static char waffle_agent_msgs__srv__SearchByLabel_Request__TYPE_NAME[] = "waffle_agent_msgs/srv/SearchByLabel_Request";
static char waffle_agent_msgs__srv__SearchByLabel_Response__TYPE_NAME[] = "waffle_agent_msgs/srv/SearchByLabel_Response";

// Define type names, field names, and default values
static char waffle_agent_msgs__srv__SearchByLabel__FIELD_NAME__request_message[] = "request_message";
static char waffle_agent_msgs__srv__SearchByLabel__FIELD_NAME__response_message[] = "response_message";
static char waffle_agent_msgs__srv__SearchByLabel__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field waffle_agent_msgs__srv__SearchByLabel__FIELDS[] = {
  {
    {waffle_agent_msgs__srv__SearchByLabel__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {waffle_agent_msgs__srv__SearchByLabel_Request__TYPE_NAME, 43, 43},
    },
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__srv__SearchByLabel__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {waffle_agent_msgs__srv__SearchByLabel_Response__TYPE_NAME, 44, 44},
    },
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__srv__SearchByLabel__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {waffle_agent_msgs__srv__SearchByLabel_Event__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription waffle_agent_msgs__srv__SearchByLabel__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__msg__GraphResult__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__srv__SearchByLabel_Event__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__srv__SearchByLabel_Request__TYPE_NAME, 43, 43},
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__srv__SearchByLabel_Response__TYPE_NAME, 44, 44},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
waffle_agent_msgs__srv__SearchByLabel__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {waffle_agent_msgs__srv__SearchByLabel__TYPE_NAME, 35, 35},
      {waffle_agent_msgs__srv__SearchByLabel__FIELDS, 3, 3},
    },
    {waffle_agent_msgs__srv__SearchByLabel__REFERENCED_TYPE_DESCRIPTIONS, 6, 6},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&waffle_agent_msgs__msg__GraphResult__EXPECTED_HASH, waffle_agent_msgs__msg__GraphResult__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = waffle_agent_msgs__msg__GraphResult__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = waffle_agent_msgs__srv__SearchByLabel_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = waffle_agent_msgs__srv__SearchByLabel_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[5].fields = waffle_agent_msgs__srv__SearchByLabel_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char waffle_agent_msgs__srv__SearchByLabel_Request__FIELD_NAME__query_text[] = "query_text";

static rosidl_runtime_c__type_description__Field waffle_agent_msgs__srv__SearchByLabel_Request__FIELDS[] = {
  {
    {waffle_agent_msgs__srv__SearchByLabel_Request__FIELD_NAME__query_text, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
waffle_agent_msgs__srv__SearchByLabel_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {waffle_agent_msgs__srv__SearchByLabel_Request__TYPE_NAME, 43, 43},
      {waffle_agent_msgs__srv__SearchByLabel_Request__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char waffle_agent_msgs__srv__SearchByLabel_Response__FIELD_NAME__top_k_results[] = "top_k_results";

static rosidl_runtime_c__type_description__Field waffle_agent_msgs__srv__SearchByLabel_Response__FIELDS[] = {
  {
    {waffle_agent_msgs__srv__SearchByLabel_Response__FIELD_NAME__top_k_results, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {waffle_agent_msgs__msg__GraphResult__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription waffle_agent_msgs__srv__SearchByLabel_Response__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {waffle_agent_msgs__msg__GraphResult__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
waffle_agent_msgs__srv__SearchByLabel_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {waffle_agent_msgs__srv__SearchByLabel_Response__TYPE_NAME, 44, 44},
      {waffle_agent_msgs__srv__SearchByLabel_Response__FIELDS, 1, 1},
    },
    {waffle_agent_msgs__srv__SearchByLabel_Response__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&waffle_agent_msgs__msg__GraphResult__EXPECTED_HASH, waffle_agent_msgs__msg__GraphResult__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = waffle_agent_msgs__msg__GraphResult__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char waffle_agent_msgs__srv__SearchByLabel_Event__FIELD_NAME__info[] = "info";
static char waffle_agent_msgs__srv__SearchByLabel_Event__FIELD_NAME__request[] = "request";
static char waffle_agent_msgs__srv__SearchByLabel_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field waffle_agent_msgs__srv__SearchByLabel_Event__FIELDS[] = {
  {
    {waffle_agent_msgs__srv__SearchByLabel_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__srv__SearchByLabel_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {waffle_agent_msgs__srv__SearchByLabel_Request__TYPE_NAME, 43, 43},
    },
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__srv__SearchByLabel_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {waffle_agent_msgs__srv__SearchByLabel_Response__TYPE_NAME, 44, 44},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription waffle_agent_msgs__srv__SearchByLabel_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__msg__GraphResult__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__srv__SearchByLabel_Request__TYPE_NAME, 43, 43},
    {NULL, 0, 0},
  },
  {
    {waffle_agent_msgs__srv__SearchByLabel_Response__TYPE_NAME, 44, 44},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
waffle_agent_msgs__srv__SearchByLabel_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {waffle_agent_msgs__srv__SearchByLabel_Event__TYPE_NAME, 41, 41},
      {waffle_agent_msgs__srv__SearchByLabel_Event__FIELDS, 3, 3},
    },
    {waffle_agent_msgs__srv__SearchByLabel_Event__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&waffle_agent_msgs__msg__GraphResult__EXPECTED_HASH, waffle_agent_msgs__msg__GraphResult__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = waffle_agent_msgs__msg__GraphResult__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = waffle_agent_msgs__srv__SearchByLabel_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = waffle_agent_msgs__srv__SearchByLabel_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string query_text\n"
  "---\n"
  "GraphResult[] top_k_results";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
waffle_agent_msgs__srv__SearchByLabel__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {waffle_agent_msgs__srv__SearchByLabel__TYPE_NAME, 35, 35},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 49, 49},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
waffle_agent_msgs__srv__SearchByLabel_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {waffle_agent_msgs__srv__SearchByLabel_Request__TYPE_NAME, 43, 43},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
waffle_agent_msgs__srv__SearchByLabel_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {waffle_agent_msgs__srv__SearchByLabel_Response__TYPE_NAME, 44, 44},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
waffle_agent_msgs__srv__SearchByLabel_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {waffle_agent_msgs__srv__SearchByLabel_Event__TYPE_NAME, 41, 41},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
waffle_agent_msgs__srv__SearchByLabel__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[7];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 7, 7};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *waffle_agent_msgs__srv__SearchByLabel__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *waffle_agent_msgs__msg__GraphResult__get_individual_type_description_source(NULL);
    sources[4] = *waffle_agent_msgs__srv__SearchByLabel_Event__get_individual_type_description_source(NULL);
    sources[5] = *waffle_agent_msgs__srv__SearchByLabel_Request__get_individual_type_description_source(NULL);
    sources[6] = *waffle_agent_msgs__srv__SearchByLabel_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
waffle_agent_msgs__srv__SearchByLabel_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *waffle_agent_msgs__srv__SearchByLabel_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
waffle_agent_msgs__srv__SearchByLabel_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *waffle_agent_msgs__srv__SearchByLabel_Response__get_individual_type_description_source(NULL),
    sources[1] = *waffle_agent_msgs__msg__GraphResult__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
waffle_agent_msgs__srv__SearchByLabel_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *waffle_agent_msgs__srv__SearchByLabel_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *waffle_agent_msgs__msg__GraphResult__get_individual_type_description_source(NULL);
    sources[4] = *waffle_agent_msgs__srv__SearchByLabel_Request__get_individual_type_description_source(NULL);
    sources[5] = *waffle_agent_msgs__srv__SearchByLabel_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
