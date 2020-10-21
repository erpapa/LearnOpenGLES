/**
 * \file defines.h
 * Application-wide constants and macros.
 */
#pragma once

/**
 * \def __has_feature
 * Dummy \c __has_feature implementation for when not using Clang (in which
 * case all requested features are reported as unimplemented).
 *
 * \param feature compiler feature to query
 */
#ifndef __has_feature
#define __has_feature(feature) 0
#endif

/**
 * \def __has_include
 * Dummy \c __has_include implementation for when not using compilers
 * supporting this feature (in which case all requested files are reported as
 * missing).
 *
 * \param header include file to query
 */
#ifndef __has_include
#define __has_include(header) 0
#endif

/**
 * \def OVERRIDE
 * Marks a member function as overriding a virtual function in its base class.
 */
#ifndef OVERRIDE
#if (_MSC_VER >= 1700) || __has_feature(cxx_override_control)
#define OVERRIDE override
#ifdef _MSC_VER
#pragma warning(disable : 4481)
#endif
#else
#define OVERRIDE
#endif
#endif

/**
 * \def NULLPTR
 * Null pointer constant (resolves to C++11's \c nullptr where possible).
 */
#ifndef NULLPTR
#if (_MSC_VER >= 1600) || __has_feature(cxx_nullptr)
#define NULLPTR nullptr
#else
#define NULLPTR NULL
#endif
#endif

/**
 * Marks a pointer parameter as not being required and \e not \c null. This is
 * preferable to the \c #NONNULL attribute since it is specified directly on
 * the parameter (and not by index) and it valid on for templates and other
 * inline implementations.
 *
 * \todo works only for Clang; map to MSVS's SAL \c _Inout_ or rethink?
 * \sa #_NULLABLE
 */
#ifndef _NONNULL
#if __has_feature(nullability)
#define _NONNULL _Nonnull
#else
#define _NONNULL 
#endif
#endif

/**
 * Marks a pointer parameter as being optional.
 *
 * \todo works only for Clang; map to MSVS's SAL \c _Inout_opt_ or rethink?
 * \sa #_NONNULL
 */
#ifndef _NULLABLE
#if __has_feature(nullability)
#define _NULLABLE _Nullable
#else
#define _NULLABLE 
#endif
#endif

/*
 * When ARC is enabled we can't pass out the Obj-C handles (which we can work
 * around) but we'd have to also branch the (still compatible) pre-ARC code.
 */
#if __has_feature(objc_arc)
#error "Cannot build with ARC enabled"
#endif

/**
 * \def AUTO_RELEASE_POOL_ACQUIRE
 * Starts an auto-release pool block.
 */
#ifndef AUTO_RELEASE_POOL_ACQUIRE
#if __MAC_OS_X_VERSION_MIN_REQUIRED < 1060
#define AUTO_RELEASE_POOL_ACQUIRE NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
#else
#define AUTO_RELEASE_POOL_ACQUIRE @autoreleasepool {
#endif
#endif

/**
 * \def AUTO_RELEASE_POOL_RELEASE
 * Ends an auto-release pool block.
 */
#ifndef AUTO_RELEASE_POOL_RELEASE
#if __MAC_OS_X_VERSION_MIN_REQUIRED < 1060
#define AUTO_RELEASE_POOL_RELEASE [pool release];
#else
#define AUTO_RELEASE_POOL_RELEASE }
#endif
#endif
