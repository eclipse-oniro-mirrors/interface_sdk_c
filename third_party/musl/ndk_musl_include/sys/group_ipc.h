
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

/**
 * @addtogroup MuslGroupIPC
 * @{
 *
 * @brief Provides group-scoped shared memory and named semaphore interfaces.
 * @since 26.2.0
 */

/**
 * @file group_ipc.h
 * @brief Declares interfaces for shared memory and named semaphores in group-specific directories.
 * @syscap SystemCapability.Base
 * @include <sys/group_ipc.h>
 * @library libc.so
 * @kit CStandardLibrary
 * @since 26.2.0
 */

#ifndef _SYS_GROUP_IPC_H
#define _SYS_GROUP_IPC_H

#include <semaphore.h>
#include <sys/mman.h>

/**
 * @brief Requests the gid_t definition required by this header.
 * @since 26.2.0
 */
#define __NEED_gid_t
#include <bits/alltypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates or opens a named semaphore in the directory selected by gid.
 *
 * When O_CREAT is specified, the variadic arguments must be a mode_t mode followed by an
 * unsigned int value. These creation attributes are ignored when opening an existing semaphore.
 * This function is a POSIX handle-returning function, not a status-code function: the return
 * value is a semaphore handle, and SEM_FAILED is the sentinel failure value. It uses the common
 * errno error model; the return type matches the POSIX sem_open declaration.
 *
 * @param name [in] Name of the semaphore. Cannot be NULL. Must be a NUL-terminated string of
 *     1 to NAME_MAX (255) bytes after leading slashes are removed; must not contain '/',
 *     and must not be '.' or '..'. The string is not modified and remains owned by the caller.
 * @param flags [in] Open flags. Supports O_CREAT and O_EXCL.
 * @param gid [in] Application-supplied group identifier used to select the directory.
 * @return <ul>
 *     <li>A valid semaphore handle if the semaphore is created or opened successfully.</li>
 *     <li>SEM_FAILED if the operation fails. errno is set to a common error code such as
 *     EACCES, EEXIST, EINVAL, ENAMETOOLONG, ENOENT, ENOTDIR, EMFILE, or ENOMEM.
 *     No module-specific error codes are defined.</li>
 *     </ul>
 * @since 26.2.0
 */
sem_t *group_sem_open(const char *name, int flags, gid_t gid, ...);

/**
 * @brief Removes the name of a group-scoped semaphore.
 *
 * This function is a POSIX status-style function and uses the common errno error model: the
 * return type matches the POSIX sem_unlink declaration, success is 0, and failure is -1 with
 * errno set. No dedicated module error-code enum or module-specific error codes are defined.
 *
 * @param name [in] Name of the semaphore. Cannot be NULL. Must be a NUL-terminated string of
 *     1 to NAME_MAX (255) bytes after leading slashes are removed; must not contain '/',
 *     and must not be '.' or '..'. The string is not modified and remains owned by the caller.
 * @param gid [in] Application-supplied group identifier used to select the directory.
 * @return <ul>
 *     <li>0 if the name is removed successfully.</li>
 *     <li>-1 if the operation fails. errno is set to a common error code such as EACCES,
 *     EPERM, EINVAL, ENAMETOOLONG, ENOENT, ENOTDIR, or EROFS. No module-specific error codes
 *     are defined.</li>
 *     </ul>
 * @since 26.2.0
 */
int group_sem_unlink(const char *name, gid_t gid);

/**
 * @brief Creates or opens a shared memory object in the directory selected by gid.
 *
 * This function is a POSIX handle-returning function, not a status-code function: the
 * nonnegative return value is a file descriptor and -1 is the sentinel failure value. It uses
 * the common errno error model; the return type matches the POSIX shm_open declaration.
 *
 * @param name [in] Name of the shared memory object. Cannot be NULL. Must be a NUL-terminated
 *     string of 1 to NAME_MAX (255) bytes after leading slashes are removed; must not contain
 *     '/', and must not be '.' or '..'. The string is not modified and remains owned by the caller.
 * @param flag [in] Open flags, such as O_RDONLY, O_RDWR, O_CREAT, O_EXCL and O_TRUNC.
 * @param mode [in] Access permissions for a newly created object, subject to umask.
 * @param gid [in] Application-supplied group identifier used to select the directory.
 * @return <ul>
 *     <li>A nonnegative file descriptor for the shared memory object if the operation succeeds.</li>
 *     <li>-1 if the operation fails. errno is set to a common error code such as EACCES,
 *     EEXIST, EINVAL, ENAMETOOLONG, ENOENT, ENOTDIR, ELOOP, EMFILE, or ENFILE.
 *     No module-specific error codes are defined.</li>
 *     </ul>
 * @since 26.2.0
 */
int group_shm_open(const char *name, int flag, mode_t mode, gid_t gid);

/**
 * @brief Removes the name of a group-scoped shared memory object.
 *
 * This function is a POSIX status-style function and uses the common errno error model: the
 * return type matches the POSIX shm_unlink declaration, success is 0, and failure is -1 with
 * errno set. No dedicated module error-code enum or module-specific error codes are defined.
 *
 * @param name [in] Name of the shared memory object. Cannot be NULL. Must be a NUL-terminated
 *     string of 1 to NAME_MAX (255) bytes after leading slashes are removed; must not contain
 *     '/', and must not be '.' or '..'. The string is not modified and remains owned by the caller.
 * @param gid [in] Application-supplied group identifier used to select the directory.
 * @return <ul>
 *     <li>0 if the name is removed successfully.</li>
 *     <li>-1 if the operation fails. errno is set to a common error code such as EACCES,
 *     EPERM, EINVAL, ENAMETOOLONG, ENOENT, ENOTDIR, or EROFS. No module-specific error codes
 *     are defined.</li>
 *     </ul>
 * @since 26.2.0
 */
int group_shm_unlink(const char *name, gid_t gid);

#ifdef __cplusplus
}
#endif
#endif

/** @} */
