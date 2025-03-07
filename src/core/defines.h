/**
 * Copyright 2025 Santiago Silvera
 *
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
 * @file defines.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief This file contains global type definitions which are used
 * throughout the entire engine and applications referencing it.
 * Numeric types are asserted statically to guarantee expected size.
 * @version 2.0
 * @date 2024-04-03
 *
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2024
 *
 */

/**
 * Modifications:
 * - 2025-03-06 Santiago Silvera: Removed KOHI specific defines and added NEBULA specific defines.
 */

 #pragma once

 // Unsigned int types.
 
 /** @brief Unsigned 8-bit integer */
 typedef unsigned char u8;
 
 /** @brief Unsigned 16-bit integer */
 typedef unsigned short u16;
 
 /** @brief Unsigned 32-bit integer */
 typedef unsigned int u32;
 
 /** @brief Unsigned 64-bit integer */
 typedef unsigned long long u64;
 
 // Signed int types.
 
 /** @brief Signed 8-bit integer */
 typedef signed char i8;
 
 /** @brief Signed 16-bit integer */
 typedef signed short i16;
 
 /** @brief Signed 32-bit integer */
 typedef signed int i32;
 
 /** @brief Signed 64-bit integer */
 typedef signed long long i64;
 
 // Floating point types
 
 /** @brief 32-bit floating point number */
 typedef float f32;
 
 /** @brief 64-bit floating point number */
 typedef double f64;
 
 // Boolean types
 
 /** @brief 32-bit boolean type, used for APIs which require it */
 typedef int b32;
 
 /** @brief 8-bit boolean type */
 typedef _Bool b8;

/**
 * Modifications:
 * - 2025-03-06 Santiago Silvera: removed _Bool type, range definitions, static assertions.
 */
 
 /** @brief True.*/
 #define true 1
 
 /** @brief False. */
 #define false 0
 
 /**
  * @brief Any id set to this should be considered invalid,
  * and not actually pointing to a real object.
  */
 #define INVALID_ID_U64 18446744073709551615UL
 #define INVALID_ID 4294967295U
 #define INVALID_ID_U32 INVALID_ID
 #define INVALID_ID_U16 65535U
 #define INVALID_ID_U8 255U
 
 #define U64_MAX 18446744073709551615UL
 #define U32_MAX 4294967295U
 #define U16_MAX 65535U
 #define U8_MAX 255U
 #define U64_MIN 0UL
 #define U32_MIN 0U
 #define U16_MIN 0U
 #define U8_MIN 0U
 
 #define I8_MAX 127
 #define I16_MAX 32767
 #define I32_MAX 2147483647
 #define I64_MAX 9223372036854775807L
 #define I8_MIN (-I8_MAX - 1)
 #define I16_MIN (-I16_MAX - 1)
 #define I32_MIN (-I32_MAX - 1)
 #define I64_MIN (-I64_MAX - 1)
 
/**
 * Modifications:
 * - 2025-03-06 Santiago Silvera: removed platform detection and changed KOHI naming to NEBULA naming.
 */

 #ifdef NEXPORT
 // Exports
 #    ifdef _MSC_VER
 #        define NAPI __declspec(dllexport)
 #    else
 #        define NAPI __attribute__((visibility("default")))
 #    endif
 #else
 // Imports
 #    ifdef _MSC_VER
 /** @brief Import/export qualifier */
 #        define NAPI __declspec(dllimport)
 #    else
 /** @brief Import/export qualifier */
 #        define NAPI
 #    endif
 #endif
 
 #if _DEBUG
 #    define NEBULA_DEBUG 1
 #    define NEBULA_RELEASE 0
 #else
 #    define NEBULA_RELEASE 1
 #    define NEBULA_DEBUG 0
 #endif

 /**
 * Modifications:
 * - 2025-03-06 Santiago Silvera: removed KCLAMP, changed KINLINE to NINLINE
 */
 
 // Inlining
 #if defined(__clang__) || defined(__gcc__)
 /** @brief Inline qualifier */
 #    define NINLINE __attribute__((always_inline)) inline
 
 /** @brief No-inline qualifier */
 #    define NNOINLINE __attribute__((noinline))
 #elif defined(_MSC_VER)
 
 /** @brief Inline qualifier */
 #    define NINLINE __forceinline
 
 /** @brief No-inline qualifier */
 #    define NNOINLINE __declspec(noinline)
 #else
 
 /** @brief Inline qualifier */
 #    define NINLINE static inline
 
 /** @brief No-inline qualifier */
 #    define NNOINLINE
 #endif
 
 // Deprecation
//  #if defined(__clang__) || defined(__gcc__)
//  /** @brief Mark something (i.e. a function) as deprecated. */
//  #    define NDEPRECATED(message) __attribute__((deprecated(message)))
//  #elif defined(_MSC_VER)
//  /** @brief Mark something (i.e. a function) as deprecated. */
//  #    define NDEPRECATED(message) __declspec(deprecated(message))
//  #else
//  #    error "Unsupported compiler - don't know how to define deprecations!"
//  #endif
 
 /** @brief Gets the number of bytes from amount of gibibytes (GiB) (1024*1024*1024) */
 #define GIBIBYTES(amount) ((amount) * 1024ULL * 1024ULL * 1024ULL)
 /** @brief Gets the number of bytes from amount of mebibytes (MiB) (1024*1024) */
 #define MEBIBYTES(amount) ((amount) * 1024ULL * 1024ULL)
 /** @brief Gets the number of bytes from amount of kibibytes (KiB) (1024) */
 #define KIBIBYTES(amount) ((amount) * 1024ULL)
 
 /** @brief Gets the number of bytes from amount of gigabytes (GB) (1000*1000*1000) */
 #define GIGABYTES(amount) ((amount) * 1000ULL * 1000ULL * 1000ULL)
 /** @brief Gets the number of bytes from amount of megabytes (MB) (1000*1000) */
 #define MEGABYTES(amount) ((amount) * 1000ULL * 1000ULL)
 /** @brief Gets the number of bytes from amount of kilobytes (KB) (1000) */
 #define KILOBYTES(amount) ((amount) * 1000ULL)
 
 /**
 * Modifications:
 * - 2025-03-06 Santiago Silvera: removed get_aligned and get_aligned_range.
 */

 #define NMIN(x, y) (x < y ? x : y)
 #define NMAX(x, y) (x > y ? x : y)
 
 /**
  * @brief Indicates if the provided flag is set in the given flags int.
  */
 #define FLAG_GET(flags, flag) ((flags & flag) == flag)
 
 /**
  * @brief Sets a flag within the flags int to enabled/disabled.
  *
  * @param flags The flags int to write to.
  * @param flag The flag to set.
  * @param enabled Indicates if the flag is enabled or not.
  */
 #define FLAG_SET(flags, flag, enabled) (flags = (enabled ? (flags | flag) : (flags & ~flag)))