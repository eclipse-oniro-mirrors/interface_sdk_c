/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_NAPI_INTERFACES_KITS_NAPI_NATIVE_API_H
#define FOUNDATION_ACE_NAPI_INTERFACES_KITS_NAPI_NATIVE_API_H

#ifndef NAPI_VERSION
#define NAPI_VERSION 8
#endif

#ifndef NAPI_EXPERIMENTAL
#define NAPI_EXPERIMENTAL
#endif

#include "common.h"
#include "node_api.h"

#ifdef NAPI_TEST
#ifdef _WIN32
#define NAPI_INNER_EXTERN __declspec(dllexport)
#else
#define NAPI_INNER_EXTERN __attribute__((visibility("default")))
#endif
#else
#ifdef _WIN32
#define NAPI_INNER_EXTERN __declspec(deprecated)
#else
#define NAPI_INNER_EXTERN __attribute__((__deprecated__))
#endif
#endif

NAPI_EXTERN napi_status napi_fatal_exception(napi_env env, napi_value err);

NAPI_EXTERN napi_status napi_create_string_utf16(napi_env env,
                                                 const char16_t* str,
                                                 size_t length,
                                                 napi_value* result);

NAPI_EXTERN napi_status napi_get_value_string_utf16(napi_env env,
                                                    napi_value value,
                                                    char16_t* buf,
                                                    size_t bufsize,
                                                    size_t* result);

NAPI_EXTERN napi_status napi_type_tag_object(napi_env env,
                                             napi_value value,
                                             const napi_type_tag* type_tag);

NAPI_EXTERN napi_status napi_check_object_type_tag(napi_env env,
                                                   napi_value value,
                                                   const napi_type_tag* type_tag,
                                                   bool* result);

NAPI_INNER_EXTERN napi_status napi_adjust_external_memory(napi_env env,
                                                          int64_t change_in_bytes,
                                                          int64_t* adjusted_value);


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Native detach callback of napi_coerce_to_native_binding_object that can be used to
 *        detach the js object and the native object.
 *
 * @since 11
 */
typedef void* (*napi_native_binding_detach_callback)(napi_env env, void* native_object, void* hint);
/**
 * @brief Native attach callback of napi_coerce_to_native_binding_object that can be used to
 *        bind the js object and the native object.
 *
 * @since 11
 */
typedef napi_value (*napi_native_binding_attach_callback)(napi_env env, void* native_object, void* hint);

NAPI_EXTERN napi_status napi_run_script_path(napi_env env, const char* path, napi_value* result);
NAPI_EXTERN napi_status napi_queue_async_work_with_qos(napi_env env, napi_async_work work, napi_qos_t qos);
NAPI_EXTERN napi_status napi_load_module(napi_env env, const char* path, napi_value* result);

/**
 * @brief The module is loaded through the NAPI. By default, the default object is exported from the module.
 *
 * @param env Current running virtual machine context.
 * @param path Path name of the module to be loaded, like @ohos.hilog.
 * @param module_info Path names of bundle and module, like com.example.application/entry.
 * @param result Result of loading a module, which is an exported object of the module.
 * @return Returns the function execution status.
 * @since 12
*/
NAPI_EXTERN napi_status napi_load_module_with_info(napi_env env,
                                                   const char* path,
                                                   const char* module_info,
                                                   napi_value* result);
NAPI_EXTERN napi_status napi_get_instance_data(napi_env env, void** data);
NAPI_EXTERN napi_status napi_set_instance_data(napi_env env,
                                               void* data,
                                               napi_finalize finalize_cb,
                                               void* finalize_hint);
NAPI_EXTERN napi_status napi_remove_env_cleanup_hook(napi_env env, void (*fun)(void* arg), void* arg);
NAPI_EXTERN napi_status napi_add_env_cleanup_hook(napi_env env, void (*fun)(void* arg), void* arg);
NAPI_EXTERN napi_status napi_remove_async_cleanup_hook(napi_async_cleanup_hook_handle remove_handle);
NAPI_EXTERN napi_status napi_add_async_cleanup_hook(napi_env env,
                                                    napi_async_cleanup_hook hook,
                                                    void* arg,
                                                    napi_async_cleanup_hook_handle* remove_handle);
NAPI_EXTERN napi_status napi_async_destroy(napi_env env,
                                           napi_async_context async_context);
NAPI_EXTERN napi_status napi_async_init(napi_env env,
                                        napi_value async_resource,
                                        napi_value async_resource_name,
                                        napi_async_context* result);
NAPI_EXTERN napi_status napi_close_callback_scope(napi_env env, napi_callback_scope scope);
NAPI_EXTERN napi_status napi_open_callback_scope(napi_env env,
                                                 napi_value resource_object,
                                                 napi_async_context context,
                                                 napi_callback_scope* result);
NAPI_EXTERN napi_status node_api_get_module_file_name(napi_env env, const char** result);
// Create JSObject with initial properties given by descriptors, note that property key must be String,
// and must can not convert to element_index, also all keys must not duplicate.
NAPI_EXTERN napi_status napi_create_object_with_properties(napi_env env,
                                                           napi_value* result,
                                                           size_t property_count,
                                                           const napi_property_descriptor* properties);
// Create JSObject with initial properties given by keys and values, note that property key must be String,
// and must can not convert to element_index, also all keys must not duplicate.
NAPI_EXTERN napi_status napi_create_object_with_named_properties(napi_env env,
                                                                 napi_value* result,
                                                                 size_t property_count,
                                                                 const char** keys,
                                                                 const napi_value* values);
/**
 * @brief This API sets native properties to a object and converts this js object to native binding object.
 *
 * @param[in] env Current running virtual machine context.
 * @param[in] js_object The JavaScript value to coerce.
 * @param[in] detach_cb Native callback that can be used to detach the js object and the native object.
 * @param[in] attach_cb Native callback that can be used to bind the js object and the native object.
 * @param[in] native_object User-provided native instance to pass to thr detach callback and attach callback.
 * @param[in] hint Optional hint to pass to the detach callback and attach callback.
 * @return Return the function execution status.
 * @since 11
 */
NAPI_EXTERN napi_status napi_coerce_to_native_binding_object(napi_env env,
                                                             napi_value js_object,
                                                             napi_native_binding_detach_callback detach_cb,
                                                             napi_native_binding_attach_callback attach_cb,
                                                             void* native_object,
                                                             void* hint);
NAPI_EXTERN napi_status napi_add_finalizer(napi_env env,
                                           napi_value js_object,
                                           void* native_object,
                                           napi_finalize finalize_cb,
                                           void* finalize_hint,
                                           napi_ref* result);
/**
 * @brief Create the ark runtime.
 *
 * @param env Indicates the ark runtime environment.
 * @since 12
 */
NAPI_EXTERN napi_status napi_create_ark_runtime(napi_env* env);

/**
 * @brief Destroy the ark runtime.
 *
 * @param env Indicates the ark runtime environment.
 * @since 12
 */
NAPI_EXTERN napi_status napi_destroy_ark_runtime(napi_env* env);

/*
 * @brief Defines a sendable class.
 *
 * @param env: The environment that the API is invoked under.
 * @param utf8name: Name of the ArkTS constructor function.
 * @param length: The length of the utf8name in bytes, or NAPI_AUTO_LENGTH if it is null-terminated.
 * @param constructor: Callback function that handles constructing instances of the class.
 * @param data: Optional data to be passed to the constructor callback as the data property of the callback info.
 * @param property_count: Number of items in the properties array argument.
 * @param properties: Array of property descriptors describing static and instance data properties, accessors, and
 * methods on the class. See napi_property_descriptor.
 * @param parent: A napi_value representing the Superclass.
 * @param result: A napi_value representing the constructor function for the class.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_define_sendable_class(napi_env env,
                                                   const char* utf8name,
                                                   size_t length,
                                                   napi_callback constructor,
                                                   void* data,
                                                   size_t property_count,
                                                   const napi_property_descriptor* properties,
                                                   napi_value parent,
                                                   napi_value* result);

/**
 * @brief Queries a napi_value to check if it is sendable.
 *
 * @param env The environment that the API is invoked under.
 * @param value The napi_value to be checked.
 * @param result Boolean value that is set to true if napi_value is sendable, false otherwise.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_is_sendable(napi_env env, napi_value value, bool* result);
/**
 * @brief Defines a sendable object.
 *
 * @param env The environment that the API is invoked under.
 * @param property_count The count of object properties.
 * @param properties Object properties.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_create_sendable_object_with_properties(napi_env env, size_t property_count,
                                                                    const napi_property_descriptor* properties,
                                                                    napi_value* result);
/**
 * @brief Wraps a native instance in a ArkTS object.
 *
 * @param env The environment that the API is invoked under.
 * @param js_object The ArkTS object that will be the wrapper for the native object.
 * @param native_object The native instance that will be wrapped in the ArkTS object.
 * @param finalize_lib Optional native callback that can be used to free the native instance when the ArkTS object
 * has been garbage-collected.
 * @param finalize_hint Optional contextual hint that is passed to the finalize callback.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_wrap_sendable(napi_env env, napi_value js_object, void* native_object,
                                           napi_finalize finalize_cb, void* finalize_hint);
/**
 * @brief Wraps a native instance in a ArkTS object.
 *
 * @param env The environment that the API is invoked under.
 * @param js_object The ArkTS object that will be the wrapper for the native object.
 * @param native_object The native instance that will be wrapped in the ArkTS object.
 * @param finalize_lib Optional native callback that can be used to free the native instance when the ArkTS object
 * has been garbage-collected.
 * @param finalize_hint Optional contextual hint that is passed to the finalize callback.
 * @param native_binding_size The size of native binding.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_wrap_sendable_with_size(napi_env env, napi_value js_object, void* native_object,
                                                     napi_finalize finalize_cb, void* finalize_hint,
                                                     size_t native_binding_size);
/**
 * @brief Retrieves a native instance that was previously wrapped in a ArkTS object.
 *
 * @param env The environment that the API is invoked under.
 * @param js_object The object associated with the native instance.
 * @param result Pointer to the wrapped native instance.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_unwrap_sendable(napi_env env, napi_value js_object, void** result);
/**
 * @brief Retrieves a native instance that was previously wrapped in a ArkTS object and removes the wrapping.
 *
 * @param env The environment that the API is invoked under.
 * @param js_object The object associated with the native instance.
 * @param result Pointer to the wrapped native instance.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_remove_wrap_sendable(napi_env env, napi_value js_object, void** result);
/*
 * @brief Create a sendable array.
 *
 * @param env: The environment that the API is invoked under.
 * @param result: A napi_value representing a sendable array.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_create_sendable_array(napi_env env, napi_value* result);

/*
 * @brief Create a sendable array with length.
 *
 * @param env: The environment that the API is invoked under.
 * @param length: The initial length of the sendable array.
 * @param result: A napi_value representing a sendable array.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_create_sendable_array_with_length(napi_env env, size_t length, napi_value* result);

/*
 * @brief Create a sendable arraybuffer.
 *
 * @param env: The environment that the API is invoked under.
 * @param byte_length: The length in bytes of the sendable arraybuffer to create.
 * @param data: Pointer to the underlying byte buffer of the sendable arraybuffer.
 * @param result: A napi_value representing a sendable arraybuffer.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_create_sendable_arraybuffer(napi_env env, size_t byte_length,
                                                         void** data, napi_value* result);

/*
 * @brief Create a sendable typedarray.
 *
 * @param env: The environment that the API is invoked under.
 * @param type: Scalar datatype of the elements within the sendable typedarray.
 * @param length: Number of elements in the typedarray.
 * @param arraybuffer: Sendable arraybuffer underlying the sendable typedarray.
 * @param byte_offset: The byte offset within the sendable arraybuffer from
 * which to start projecting the sendable typedarray.
 * @param result: A napi_value representing a sendable typedarray.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_create_sendable_typedarray(napi_env env,
                                                        napi_typedarray_type type,
                                                        size_t length,
                                                        napi_value arraybuffer,
                                                        size_t byte_offset,
                                                        napi_value* result);

/**
 * @brief Run the event loop by the given env and running mode in current thread.
 *
 * Support to run the native event loop in an asynchronous native thread with the specified running mode.
 *
 * @param env Current running virtual machine context.
 * @param mode Indicates the running mode of the native event loop.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_run_event_loop(napi_env env, napi_event_mode mode);

/**
 * @brief Stop the event loop in current thread.
 *
 * Support to stop the running event loop in current native thread.
 *
 * @param env Current running virtual machine context.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_stop_event_loop(napi_env env);

/**
 * @brief Serialize a JS object.
 *
 * @param env Current running virtual machine context.
 * @param object The JavaScript value to serialize.
 * @param transfer_list List of data to transfer in transfer mode.
 * @param clone_list List of Sendable data to transfer in clone mode.
 * @param result Serialization result of the JS object.
 * @return Returns the function execution status.
 * @since 12
*/
NAPI_EXTERN napi_status napi_serialize(napi_env env,
                                       napi_value object,
                                       napi_value transfer_list,
                                       napi_value clone_list,
                                       void** result);

/**
 * @brief Restore serialization data to a ArkTS object.
 *
 * @param env Current running virtual machine context.
 * @param buffer Data to deserialize.
 * @param object ArkTS object obtained by deserialization.
 * @return Returns the function execution status.
 * @since 12
*/
NAPI_EXTERN napi_status napi_deserialize(napi_env env, void* buffer, napi_value* object);

/**
 * @brief Delete serialization data.
 *
 * @param env Current running virtual machine context.
 * @param buffer Data to delete.
 * @return Returns the function execution status.
 * @since 12
*/
NAPI_EXTERN napi_status napi_delete_serialization_data(napi_env env, void* buffer);

/**
 * @brief Dispatch a task with specified priority from a native thread to an ArkTS thread, the task will execute
 *        the given thread safe function.
 *
 * @param func Indicates the thread safe function.
 * @param data Indicates the data anticipated to be transferred to the ArkTS thread.
 * @param priority Indicates the priority of the task dispatched.
 * @param isTail Indicates the way of the task dispatched into the native event queue. When "isTail" is true,
 *        the task will be dispatched to the tail of the native event queue. Conversely, when "isTail" is false, the
 *        tasks will be dispatched to the head of the native event queue.
 * @return Return the function execution status.
 * @since 12
 */
NAPI_EXTERN napi_status napi_call_threadsafe_function_with_priority(napi_threadsafe_function func,
                                                                    void *data,
                                                                    napi_task_priority priority,
                                                                    bool isTail);
#ifdef __cplusplus
}
#endif
#endif /* FOUNDATION_ACE_NAPI_INTERFACES_KITS_NAPI_NATIVE_API_H */
