// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from waffle_agent_msgs:msg/GraphResult.idl
// generated code does not contain a copyright notice
#include "waffle_agent_msgs/msg/detail/graph_result__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `label`
#include "rosidl_runtime_c/string_functions.h"
// Member `position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
waffle_agent_msgs__msg__GraphResult__init(waffle_agent_msgs__msg__GraphResult * msg)
{
  if (!msg) {
    return false;
  }
  // node_id
  // label
  if (!rosidl_runtime_c__String__init(&msg->label)) {
    waffle_agent_msgs__msg__GraphResult__fini(msg);
    return false;
  }
  // score
  // position
  if (!rosidl_runtime_c__float__Sequence__init(&msg->position, 0)) {
    waffle_agent_msgs__msg__GraphResult__fini(msg);
    return false;
  }
  return true;
}

void
waffle_agent_msgs__msg__GraphResult__fini(waffle_agent_msgs__msg__GraphResult * msg)
{
  if (!msg) {
    return;
  }
  // node_id
  // label
  rosidl_runtime_c__String__fini(&msg->label);
  // score
  // position
  rosidl_runtime_c__float__Sequence__fini(&msg->position);
}

bool
waffle_agent_msgs__msg__GraphResult__are_equal(const waffle_agent_msgs__msg__GraphResult * lhs, const waffle_agent_msgs__msg__GraphResult * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // node_id
  if (lhs->node_id != rhs->node_id) {
    return false;
  }
  // label
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->label), &(rhs->label)))
  {
    return false;
  }
  // score
  if (lhs->score != rhs->score) {
    return false;
  }
  // position
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  return true;
}

bool
waffle_agent_msgs__msg__GraphResult__copy(
  const waffle_agent_msgs__msg__GraphResult * input,
  waffle_agent_msgs__msg__GraphResult * output)
{
  if (!input || !output) {
    return false;
  }
  // node_id
  output->node_id = input->node_id;
  // label
  if (!rosidl_runtime_c__String__copy(
      &(input->label), &(output->label)))
  {
    return false;
  }
  // score
  output->score = input->score;
  // position
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  return true;
}

waffle_agent_msgs__msg__GraphResult *
waffle_agent_msgs__msg__GraphResult__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__msg__GraphResult * msg = (waffle_agent_msgs__msg__GraphResult *)allocator.allocate(sizeof(waffle_agent_msgs__msg__GraphResult), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(waffle_agent_msgs__msg__GraphResult));
  bool success = waffle_agent_msgs__msg__GraphResult__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
waffle_agent_msgs__msg__GraphResult__destroy(waffle_agent_msgs__msg__GraphResult * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    waffle_agent_msgs__msg__GraphResult__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
waffle_agent_msgs__msg__GraphResult__Sequence__init(waffle_agent_msgs__msg__GraphResult__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__msg__GraphResult * data = NULL;

  if (size) {
    data = (waffle_agent_msgs__msg__GraphResult *)allocator.zero_allocate(size, sizeof(waffle_agent_msgs__msg__GraphResult), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = waffle_agent_msgs__msg__GraphResult__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        waffle_agent_msgs__msg__GraphResult__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
waffle_agent_msgs__msg__GraphResult__Sequence__fini(waffle_agent_msgs__msg__GraphResult__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      waffle_agent_msgs__msg__GraphResult__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

waffle_agent_msgs__msg__GraphResult__Sequence *
waffle_agent_msgs__msg__GraphResult__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__msg__GraphResult__Sequence * array = (waffle_agent_msgs__msg__GraphResult__Sequence *)allocator.allocate(sizeof(waffle_agent_msgs__msg__GraphResult__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = waffle_agent_msgs__msg__GraphResult__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
waffle_agent_msgs__msg__GraphResult__Sequence__destroy(waffle_agent_msgs__msg__GraphResult__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    waffle_agent_msgs__msg__GraphResult__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
waffle_agent_msgs__msg__GraphResult__Sequence__are_equal(const waffle_agent_msgs__msg__GraphResult__Sequence * lhs, const waffle_agent_msgs__msg__GraphResult__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!waffle_agent_msgs__msg__GraphResult__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
waffle_agent_msgs__msg__GraphResult__Sequence__copy(
  const waffle_agent_msgs__msg__GraphResult__Sequence * input,
  waffle_agent_msgs__msg__GraphResult__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(waffle_agent_msgs__msg__GraphResult);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    waffle_agent_msgs__msg__GraphResult * data =
      (waffle_agent_msgs__msg__GraphResult *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!waffle_agent_msgs__msg__GraphResult__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          waffle_agent_msgs__msg__GraphResult__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!waffle_agent_msgs__msg__GraphResult__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
