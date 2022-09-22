//
//  SSDefines.h
//  SSBase
//
//  Created by Dante Sabatier on 1/17/12.
//  Copyright (c) 2012 Dante Sabatier. All rights reserved.
//

#import <TargetConditionals.h>
#import <AvailabilityMacros.h>
#import <Availability.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSZone.h>
#import <objc/runtime.h>
#import <objc/objc-sync.h>
#import <objc/NSObjCRuntime.h>
#if !TARGET_OS_IPHONE
#import <AppKit/NSApplication.h>
#import <AppKit/NSNibDeclarations.h>
#endif

extern uint64_t dispatch_benchmark(size_t count, void (^block)(void));
extern id objc_getProperty(id self, SEL _cmd, ptrdiff_t offset, BOOL atomic);
extern void objc_setProperty(id self, SEL _cmd, ptrdiff_t offset, id newValue, BOOL atomic, BOOL shouldCopy);
extern void objc_copyStruct(void *dest, const void *src, ptrdiff_t size, BOOL atomic, BOOL hasStrong);

#if !TARGET_OS_IPHONE
#ifndef NSAppKitVersionNumber10_6
#define NSAppKitVersionNumber10_6 1038
#endif

#ifndef NSAppKitVersionNumber10_7
#define NSAppKitVersionNumber10_7 1138
#endif

#ifndef NSAppKitVersionNumber10_8
#define NSAppKitVersionNumber10_8 1187
#endif

#ifndef NSAppKitVersionNumber10_9
#define NSAppKitVersionNumber10_9 1265
#endif

#ifndef NSAppKitVersionNumber10_10_Max
#define NSAppKitVersionNumber10_10_Max 1349
#endif
#endif

#ifndef NSAppKitVersionNumber10_14
#define NSAppKitVersionNumber10_14 1641.10
#endif

#ifndef IB_DESIGNABLE
#define IB_DESIGNABLE
#endif

#ifndef IBInspectable
#define IBInspectable
#endif

#ifndef __has_builtin
#define __has_builtin(x) 0
#endif
#ifndef __has_include
#define __has_include(x) 0
#endif
#ifndef __has_feature
#define __has_feature(x) 0
#endif
#ifndef __has_attribute
#define __has_attribute(x) 0
#endif
#ifndef __has_extension
#define __has_extension(x) 0
#endif

#ifndef NS_AVAILABLE
#define NS_AVAILABLE
#endif

#if !__has_feature(objc_instancetype)
#undef instancetype
#define instancetype id
#endif

#if !defined(__unsafe_unretained)
#define __unsafe_unretained
#endif

#if !__has_feature(nullability)
# define nonnull
# define nullable
# define null_unspecified
# define __nonnull
# define __nullable
# define __null_unspecified
#endif

#if __has_feature(objc_generics)
#   define __GENERICS(class, ...)      class<__VA_ARGS__>
#   define __GENERICS_TYPE(type)       type
#else
#   define __GENERICS(class, ...)      class
#   define __GENERICS_TYPE(type)       id
#endif

#ifndef CF_ENUM
#define CF_ENUM(_type, _name) \
_type _name;              \
enum
#endif

#ifndef NS_ENUM
#define NS_ENUM(_type, _name) \
_type _name;              \
enum
#endif

#ifndef NS_OPTIONS
#define NS_OPTIONS(_type, _name) \
_type _name;                 \
enum
#endif

#if __has_feature(assume_nonnull)
#define CF_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define CF_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
#else
#define CF_ASSUME_NONNULL_BEGIN
#define CF_ASSUME_NONNULL_END
#endif

#ifndef CF_IMPLICIT_BRIDGING_ENABLED
#if __has_feature(arc_cf_code_audited)
#define CF_IMPLICIT_BRIDGING_ENABLED _Pragma("clang arc_cf_code_audited begin")
#else
#define CF_IMPLICIT_BRIDGING_ENABLED
#endif
#endif

#ifndef CF_IMPLICIT_BRIDGING_DISABLED
#if __has_feature(arc_cf_code_audited)
#define CF_IMPLICIT_BRIDGING_DISABLED _Pragma("clang arc_cf_code_audited end")
#else
#define CF_IMPLICIT_BRIDGING_DISABLED
#endif
#endif

#if !defined(NS_ASSUME_NONNULL_BEGIN)
# if  __has_feature(assume_nonnull)
#  define NS_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#  define NS_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
# else
#  define NS_ASSUME_NONNULL_BEGIN
#  define NS_ASSUME_NONNULL_END
# endif
#endif

#ifndef NS_REQUIRES_SUPER
#if __has_attribute(objc_requires_super)
#define NS_REQUIRES_SUPER __attribute__((objc_requires_super))
#else
#define NS_REQUIRES_SUPER
#endif
#endif

#ifndef NS_DESIGNATED_INITIALIZER
#if __has_attribute(objc_designated_initializer)
#define NS_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
#else
#define NS_DESIGNATED_INITIALIZER
#endif
#endif

#ifndef NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
#if __has_attribute(objc_protocol_requires_explicit_implementation)
#define NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION __attribute__((objc_protocol_requires_explicit_implementation))
#else
#define NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
#endif
#endif

#ifndef TARGET_MACOS
#define TARGET_MACOS (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#endif

#ifdef __cplusplus
#define SS_EXTERN extern "C"
#else
#define SS_EXTERN extern
#endif

#ifndef SS_VISIBLE
#if __has_attribute(visibility)
#define SS_VISIBLE __attribute__((visibility ("default")))
#else
#define SS_VISIBLE
#endif
#endif

#ifndef SS_EXPORT
#define SS_EXPORT SS_EXTERN SS_VISIBLE
#endif

#ifndef SS_INLINE
#if __has_attribute(always_inline)
#define SS_INLINE static __inline__ __attribute__((always_inline))
#else
#define SS_INLINE static inline
#endif
#endif

#ifndef SS_CONST
#if __has_attribute(const)
#define SS_CONST __attribute__((const))
#else
#define SS_CONST
#endif
#endif

#ifndef SS_PURE
#if __has_attribute(pure)
#define SS_PURE __attribute__((pure))
#else
#define SS_PURE
#endif
#endif

#ifndef SS_UNUSED
#if __has_attribute(unused)
#define SS_UNUSED __attribute__((unused))
#else
#define SS_UNUSED
#endif
#endif

#ifndef SS_UNUSED_IPHONE
#if TARGET_OS_IPHONE
#define SS_UNUSED_IPHONE SS_UNUSED
#else
#define SS_UNUSED_IPHONE
#endif
#endif

#ifndef SS_UNUSED_MAC
#if TARGET_OS_IPHONE
#define SS_UNUSED_MAC
#else
#define SS_UNUSED_MAC SS_UNUSED
#endif
#endif

#ifndef SS_DEPRECATED
#if __has_attribute(deprecated)
#define SS_DEPRECATED __attribute__((deprecated))
#else
#define SS_DEPRECATED
#endif
#endif

#ifndef SS_UNAVAILABLE
#if __has_attribute(unavailable)
#define SS_UNAVAILABLE __attribute__((unavailable))
#else
#define SS_UNAVAILABLE
#endif
#endif

#ifndef SS_UNAVAILABLE_IPHONE
#if TARGET_OS_IPHONE
#define SS_UNAVAILABLE_IPHONE SS_UNAVAILABLE
#else
#define SS_UNAVAILABLE_IPHONE
#endif
#endif

#ifndef SS_UNAVAILABLE_MAC
#if TARGET_OS_IPHONE
#define SS_UNAVAILABLE_MAC
#else
#define SS_UNAVAILABLE_MAC SS_UNAVAILABLE
#endif
#endif

#ifndef SS_UNAVAILABLE_WATCHOS
#if TARGET_OS_WATCH
#define SS_UNAVAILABLE_WATCHOS SS_UNAVAILABLE
#else
#define SS_UNAVAILABLE_WATCHOS
#endif
#endif

#ifndef SS_NONNULL
#if __has_attribute(nonnull)
#define SS_NONNULL(...) __attribute__((nonnull (__VA_ARGS__)))
#else
#define SS_NONNULL(...)
#endif
#endif

#ifndef SWAP
#define SWAP(A, B) do { __typeof__(A) __temp = (A); (A) = (B); (B) = __temp;} while(0)
#endif

#ifndef SS_NONNAN
#define SS_NONNAN(x) isnan(x) ? 0.0 : x
#endif

#ifndef RADIANS
#define RADIANS(x) (x * M_PI/180.0)
#endif

#ifndef DEGREES
#define DEGREES(x) (x * 180.0/M_PI)
#endif

#ifndef FLOOR
#if defined(__LP64__) && __LP64__
#define FLOOR(x) floor(x)
#else
#define FLOOR(x) floorf(x)
#endif
#endif

#ifndef CEIL
#if defined(__LP64__) && __LP64__
#define CEIL(x) ceil(x)
#else
#define CEIL(x) ceilf(x)
#endif
#endif

#ifndef ROUND
#if defined(__LP64__) && __LP64__
#define ROUND(x) round(x)
#else
#define ROUND(x) roundf(x)
#endif
#endif

#ifndef FABS
#if defined(__LP64__) && __LP64__
#define FABS(x) fabs(x)
#else
#define FABS(x) fabsf(x)
#endif
#endif

#ifndef SIN
#if defined(__LP64__) && __LP64__
#define SIN(x) sin(x)
#else
#define SIN(x) sinf(x)
#endif
#endif

#ifndef COS
#if defined(__LP64__) && __LP64__
#define COS(x) cos(x)
#else
#define COS(x) cosf(x)
#endif
#endif

#ifndef TAN
#if defined(__LP64__) && __LP64__
#define TAN(x) tan(x)
#else
#define TAN(x) tanf(x)
#endif
#endif

#ifndef POW
#if defined(__LP64__) && __LP64__
#define POW(x, n) pow(x, n)
#else
#define POW(x, n) powf(x, n)
#endif
#endif

#ifndef SQRT
#if defined(__LP64__) && __LP64__
#define SQRT(x) sqrt(x)
#else
#define SQRT(x) sqrtf(x)
#endif
#endif

#ifndef ss_retain
#if __has_feature(objc_arc)
#define ss_retain self
#define ss_dealloc self
#define release self
#define autorelease self
#else
#define ss_retain retain
#define ss_dealloc dealloc
#define __bridge
#endif
#endif

#ifndef ss_weak
#if (__has_feature(objc_arc)) && ((defined __IPHONE_OS_VERSION_MIN_REQUIRED && __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_5_0) || (defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED > __MAC_10_7))
#define ss_weak weak
#define __ss_weak __weak
#define ss_strong strong
#else
#define ss_weak unsafe_unretained
#define __ss_weak __unsafe_unretained
#define ss_strong retain
#endif
#endif

#ifndef SSSynchronized
#define SSSynchronized(obj, block) ({ \
if (block && (objc_sync_enter(obj) == OBJC_SYNC_SUCCESS)) \
{ \
block(); \
objc_sync_exit(obj); \
} \
})
#endif

#ifndef SSAutorelease
#if __has_feature(objc_arc)
#define SSAutorelease(x) (__bridge __typeof(x))CFBridgingRelease(x)
#else
#define SSAutorelease(x) (__typeof(x))[NSMakeCollectable(x) autorelease]
#endif
#endif

#ifndef SSRetainedTypeSet
#define SSRetainedTypeSet(a, b) do {if (a != b){if (a) {CFRelease(a); a = NULL;} if (b) a = (__typeof(b))CFRetain(b);}} while(0)
#endif

#ifndef SSNonAtomicRetainedSet
#define SSNonAtomicRetainedSet(a, b) do {if (![a isEqual:b]){ if (a) { [a release]; a = nil;} if (b) a = [b ss_retain]; }} while (0)
#endif

#ifndef SSNonAtomicCopiedSet
#define SSNonAtomicCopiedSet(a, b) do {if (![a isEqual:b]){ if (a) { [a release]; a = nil;} if (b) a = [b copy]; }} while (0)
#endif

#ifndef SSAtomicRetainedSet
#define SSAtomicRetainedSet(dest, source) objc_setProperty(self, _cmd, (ptrdiff_t)(&dest) - (ptrdiff_t)(self), source, YES, NO)
#endif

#ifndef SSAtomicCopiedSet
#define SSAtomicCopiedSet(dest, source) objc_setProperty(self, _cmd, (ptrdiff_t)(&dest) - (ptrdiff_t)(self), source, YES, YES)
#endif

#ifndef SSAtomicAutoreleasedGet
#define SSAtomicAutoreleasedGet(source) objc_getProperty(self, _cmd, (ptrdiff_t)(&source) - (ptrdiff_t)(self), YES)
#endif

#ifndef SSAtomicStruct
#define SSAtomicStruct(dest, source) objc_copyStruct(&dest, &source, sizeof(__typeof__(source)), YES, NO)
#endif

#ifndef SSGetAssociatedValueForKey
#define SSGetAssociatedValueForKey(key) objc_getAssociatedObject(self, (__bridge const void *)(key));
#endif

#ifndef SSSetAssociatedValueForKey
#define SSSetAssociatedValueForKey(key, value, associationPolicy) objc_setAssociatedObject(self, (__bridge const void *)(key), value, associationPolicy);
#endif

#ifndef SSSetAtomicRetainedAssociatedValueForKey
#define SSSetAtomicRetainedAssociatedValueForKey(key, value) SSSetAssociatedValueForKey(key, value, OBJC_ASSOCIATION_RETAIN);
#endif

#ifndef SSSetNonAtomicRetainedAssociatedValueForKey
#define SSSetNonAtomicRetainedAssociatedValueForKey(key, value) SSSetAssociatedValueForKey(key, value, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
#endif

#ifndef SSSetAtomicCopiedAssociatedValueForKey
#define SSSetAtomicCopiedAssociatedValueForKey(key, value) SSSetAssociatedValueForKey(key, value, OBJC_ASSOCIATION_COPY);
#endif

#ifndef SSSetNonAtomicCopiedAssociatedValueForKey
#define SSSetNonAtomicCopiedAssociatedValueForKey(key, value) SSSetAssociatedValueForKey(key, value, OBJC_ASSOCIATION_COPY_NONATOMIC);
#endif

#ifndef SSSetWeakAssociatedValueForKey
#define SSSetWeakAssociatedValueForKey(key, value) SSSetAssociatedValueForKey(key, value, OBJC_ASSOCIATION_ASSIGN);
#endif

#ifndef SSLocalizedString
#define SSLocalizedString(key, comment) [[NSBundle bundleForClass:[self class]] localizedStringForKey:(key) value:@"" table:nil]
#endif

#ifndef SSParameterAssert
#if DEBUG
#define SSParameterAssert(condition) NSParameterAssert(condition)
#else
#define SSParameterAssert(condition)
#endif
#endif

#ifndef SSDebugLog
#if DEBUG
#define SSDebugLog(...) NSLog(__VA_ARGS__)
#else
#define SSDebugLog(...)
#endif
#endif

