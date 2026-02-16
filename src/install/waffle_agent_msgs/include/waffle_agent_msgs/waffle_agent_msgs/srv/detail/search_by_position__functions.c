// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from waffle_agent_msgs:srv/SearchByPosition.idl
// generated code does not contain a copyright notice
#include "waffle_agent_msgs/srv/detail/search_by_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `query_position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
waffle_agent_msgs__srv__SearchByPosition_Request__init(waffle_agent_msgs__srv__SearchByPosition_Request * msg)
{
  if (!msg) {
    return false;
  }
  // query_position
  if (!rosidl_runtime_c__float__Sequence__init(&msg->query_position, 0)) {
    waffle_agent_msgs__srv__SearchByPosition_Request__fini(msg);
    return false;
  }
  return true;
}

void
waffle_agent_msgs__srv__SearchByPosition_Request__fini(waffle_agent_msgs__srv__SearchByPosition_Request * msg)
{
  if (!msg) {
    return;
  }
  // query_position
  rosidl_runtime_c__float__Sequence__fini(&msg->query_position);
}

bool
waffle_agent_msgs__srv__SearchByPosition_Request__are_equal(const waffle_agent_msgs__srv__SearchByPosition_Request * lhs, const waffle_agent_msgs__srv__SearchByPosition_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // query_position
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->query_position), &(rhs->query_position)))
  {
    return false;
  }
  return true;
}

bool
waffle_agent_msgs__srv__SearchByPosition_Request__copy(
  const waffle_agent_msgs__srv__SearchByPosition_Request * input,
  waffle_agent_msgs__srv__SearchByPosition_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // query_position
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->query_position), &(output->query_position)))
  {
    return false;
  }
  return true;
}

waffle_agent_msgs__srv__SearchByPosition_Request *
waffle_agent_msgs__srv__SearchByPosition_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__srv__SearchByPosition_Request * msg = (waffle_agent_msgs__srv__SearchByPosition_Request *)allocator.allocate(sizeof(waffle_agent_msgs__srv__SearchByPosition_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(waffle_agent_msgs__srv__SearchByPosition_Request));
  bool success = waffle_agent_msgs__srv__SearchByPosition_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
waffle_agent_msgs__srv__SearchByPosition_Request__destroy(waffle_agent_msgs__srv__SearchByPosition_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    waffle_agent_msgs__srv__SearchByPosition_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__init(waffle_agent_msgs__srv__SearchByPosition_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__srv__SearchByPosition_Request * data = NULL;

  if (size) {
    data = (waffle_agent_msgs__srv__SearchByPosition_Request *)allocator.zero_allocate(size, sizeof(waffle_agent_msgs__srv__SearchByPosition_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = waffle_agent_msgs__srv__SearchByPosition_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        waffle_agent_msgs__srv__SearchByPosition_Request__fini(&data[i - 1]);
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
waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__fini(waffle_agent_msgs__srv__SearchByPosition_Request__Sequence * array)
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
      waffle_agent_msgs__srv__SearchByPosition_Request__fini(&array->data[i]);
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

waffle_agent_msgs__srv__SearchByPosition_Request__Sequence *
waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__srv__SearchByPosition_Request__Sequence * array = (waffle_agent_msgs__srv__SearchByPosition_Request__Sequence *)allocator.allocate(sizeof(waffle_agent_msgs__srv__SearchByPosition_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__destroy(waffle_agent_msgs__srv__SearchByPosition_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__are_equal(const waffle_agent_msgs__srv__SearchByPosition_Request__Sequence * lhs, const waffle_agent_msgs__srv__SearchByPosition_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!waffle_agent_msgs__srv__SearchByPosition_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__copy(
  const waffle_agent_msgs__srv__SearchByPosition_Request__Sequence * input,
  waffle_agent_msgs__srv__SearchByPosition_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(waffle_agent_msgs__srv__SearchByPosition_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    waffle_agent_msgs__srv__SearchByPosition_Request * data =
      (waffle_agent_msgs__srv__SearchByPosition_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!waffle_agent_msgs__srv__SearchByPosition_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          waffle_agent_msgs__srv__SearchByPosition_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!waffle_agent_msgs__srv__SearchByPosition_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `top_k_results`
#include "waffle_agent_msgs/msg/detail/graph_result__functions.h"

bool
waffle_agent_msgs__srv__SearchByPosition_Response__init(waffle_agent_msgs__srv__SearchByPosition_Response * msg)
{
  if (!msg) {
    return false;
  }
  // top_k_results
  if (!waffle_agent_msgs__msg__GraphResult__Sequence__init(&msg->top_k_results, 0)) {
    waffle_agent_msgs__srv__SearchByPosition_Response__fini(msg);
    return false;
  }
  return true;
}

void
waffle_agent_msgs__srv__SearchByPosition_Response__fini(waffle_agent_msgs__srv__SearchByPosition_Response * msg)
{
  if (!msg) {
    return;
  }
  // top_k_results
  waffle_agent_msgs__msg__GraphResult__Sequence__fini(&msg->top_k_results);
}

bool
waffle_agent_msgs__srv__SearchByPosition_Response__are_equal(const waffle_agent_msgs__srv__SearchByPosition_Response * lhs, const waffle_agent_msgs__srv__SearchByPosition_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // top_k_results
  if (!waffle_agent_msgs__msg__GraphResult__Sequence__are_equal(
      &(lhs->top_k_results), &(rhs->top_k_results)))
  {
    return false;
  }
  return true;
}

bool
waffle_agent_msgs__srv__SearchByPosition_Response__copy(
  const waffle_agent_msgs__srv__SearchByPosition_Response * input,
  waffle_agent_msgs__srv__SearchByPosition_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // top_k_results
  if (!waffle_agent_msgs__msg__GraphResult__Sequence__copy(
      &(input->top_k_results), &(output->top_k_results)))
  {
    return false;
  }
  return true;
}

waffle_agent_msgs__srv__SearchByPosition_Response *
waffle_agent_msgs__srv__SearchByPosition_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__srv__SearchByPosition_Response * msg = (waffle_agent_msgs__srv__SearchByPosition_Response *)allocator.allocate(sizeof(waffle_agent_msgs__srv__SearchByPosition_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(waffle_agent_msgs__srv__SearchByPosition_Response));
  bool success = waffle_agent_msgs__srv__SearchByPosition_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
waffle_agent_msgs__srv__SearchByPosition_Response__destroy(waffle_agent_msgs__srv__SearchByPosition_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    waffle_agent_msgs__srv__SearchByPosition_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__init(waffle_agent_msgs__srv__SearchByPosition_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__srv__SearchByPosition_Response * data = NULL;

  if (size) {
    data = (waffle_agent_msgs__srv__SearchByPosition_Response *)allocator.zero_allocate(size, sizeof(waffle_agent_msgs__srv__SearchByPosition_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = waffle_agent_msgs__srv__SearchByPosition_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        waffle_agent_msgs__srv__SearchByPosition_Response__fini(&data[i - 1]);
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
waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__fini(waffle_agent_msgs__srv__SearchByPosition_Response__Sequence * array)
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
      waffle_agent_msgs__srv__SearchByPosition_Response__fini(&array->data[i]);
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

waffle_agent_msgs__srv__SearchByPosition_Response__Sequence *
waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__srv__SearchByPosition_Response__Sequence * array = (waffle_agent_msgs__srv__SearchByPosition_Response__Sequence *)allocator.allocate(sizeof(waffle_agent_msgs__srv__SearchByPosition_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__destroy(waffle_agent_msgs__srv__SearchByPosition_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__are_equal(const waffle_agent_msgs__srv__SearchByPosition_Response__Sequence * lhs, const waffle_agent_msgs__srv__SearchByPosition_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!waffle_agent_msgs__srv__SearchByPosition_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__copy(
  const waffle_agent_msgs__srv__SearchByPosition_Response__Sequence * input,
  waffle_agent_msgs__srv__SearchByPosition_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(waffle_agent_msgs__srv__SearchByPosition_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    waffle_agent_msgs__srv__SearchByPosition_Response * data =
      (waffle_agent_msgs__srv__SearchByPosition_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!waffle_agent_msgs__srv__SearchByPosition_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          waffle_agent_msgs__srv__SearchByPosition_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!waffle_agent_msgs__srv__SearchByPosition_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_position__functions.h"

bool
waffle_agent_msgs__srv__SearchByPosition_Event__init(waffle_agent_msgs__srv__SearchByPosition_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    waffle_agent_msgs__srv__SearchByPosition_Event__fini(msg);
    return false;
  }
  // request
  if (!waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__init(&msg->request, 0)) {
    waffle_agent_msgs__srv__SearchByPosition_Event__fini(msg);
    return false;
  }
  // response
  if (!waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__init(&msg->response, 0)) {
    waffle_agent_msgs__srv__SearchByPosition_Event__fini(msg);
    return false;
  }
  return true;
}

void
waffle_agent_msgs__srv__SearchByPosition_Event__fini(waffle_agent_msgs__srv__SearchByPosition_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__fini(&msg->request);
  // response
  waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__fini(&msg->response);
}

bool
waffle_agent_msgs__srv__SearchByPosition_Event__are_equal(const waffle_agent_msgs__srv__SearchByPosition_Event * lhs, const waffle_agent_msgs__srv__SearchByPosition_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
waffle_agent_msgs__srv__SearchByPosition_Event__copy(
  const waffle_agent_msgs__srv__SearchByPosition_Event * input,
  waffle_agent_msgs__srv__SearchByPosition_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!waffle_agent_msgs__srv__SearchByPosition_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!waffle_agent_msgs__srv__SearchByPosition_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

waffle_agent_msgs__srv__SearchByPosition_Event *
waffle_agent_msgs__srv__SearchByPosition_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__srv__SearchByPosition_Event * msg = (waffle_agent_msgs__srv__SearchByPosition_Event *)allocator.allocate(sizeof(waffle_agent_msgs__srv__SearchByPosition_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(waffle_agent_msgs__srv__SearchByPosition_Event));
  bool success = waffle_agent_msgs__srv__SearchByPosition_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
waffle_agent_msgs__srv__SearchByPosition_Event__destroy(waffle_agent_msgs__srv__SearchByPosition_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    waffle_agent_msgs__srv__SearchByPosition_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
waffle_agent_msgs__srv__SearchByPosition_Event__Sequence__init(waffle_agent_msgs__srv__SearchByPosition_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__srv__SearchByPosition_Event * data = NULL;

  if (size) {
    data = (waffle_agent_msgs__srv__SearchByPosition_Event *)allocator.zero_allocate(size, sizeof(waffle_agent_msgs__srv__SearchByPosition_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = waffle_agent_msgs__srv__SearchByPosition_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        waffle_agent_msgs__srv__SearchByPosition_Event__fini(&data[i - 1]);
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
waffle_agent_msgs__srv__SearchByPosition_Event__Sequence__fini(waffle_agent_msgs__srv__SearchByPosition_Event__Sequence * array)
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
      waffle_agent_msgs__srv__SearchByPosition_Event__fini(&array->data[i]);
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

waffle_agent_msgs__srv__SearchByPosition_Event__Sequence *
waffle_agent_msgs__srv__SearchByPosition_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  waffle_agent_msgs__srv__SearchByPosition_Event__Sequence * array = (waffle_agent_msgs__srv__SearchByPosition_Event__Sequence *)allocator.allocate(sizeof(waffle_agent_msgs__srv__SearchByPosition_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = waffle_agent_msgs__srv__SearchByPosition_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
waffle_agent_msgs__srv__SearchByPosition_Event__Sequence__destroy(waffle_agent_msgs__srv__SearchByPosition_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    waffle_agent_msgs__srv__SearchByPosition_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
waffle_agent_msgs__srv__SearchByPosition_Event__Sequence__are_equal(const waffle_agent_msgs__srv__SearchByPosition_Event__Sequence * lhs, const waffle_agent_msgs__srv__SearchByPosition_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!waffle_agent_msgs__srv__SearchByPosition_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
waffle_agent_msgs__srv__SearchByPosition_Event__Sequence__copy(
  const waffle_agent_msgs__srv__SearchByPosition_Event__Sequence * input,
  waffle_agent_msgs__srv__SearchByPosition_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(waffle_agent_msgs__srv__SearchByPosition_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    waffle_agent_msgs__srv__SearchByPosition_Event * data =
      (waffle_agent_msgs__srv__SearchByPosition_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!waffle_agent_msgs__srv__SearchByPosition_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          waffle_agent_msgs__srv__SearchByPosition_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!waffle_agent_msgs__srv__SearchByPosition_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
