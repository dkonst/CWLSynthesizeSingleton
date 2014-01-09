//
//  CWLSynthesizeSingleton.h
//  CocoaWithLove
//
//  Created by Matt Gallagher on 2011/08/23.
//  Copyright (c) 2011 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file, free of charge, in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//

#import <objc/runtime.h>

#define CWL_DECLARE_SINGLETON_FOR_CLASS_WITH_ACCESSOR(classname, accessorMethodName) \
+ (classname *)accessorMethodName;

#if __has_feature(objc_arc)
	#define CWL_SYNTHESIZE_SINGLETON_RETAIN_METHODS
#else
	#define CWL_SYNTHESIZE_SINGLETON_RETAIN_METHODS \
	- (id)retain \
	{ \
		return self; \
	} \
	 \
	- (NSUInteger)retainCount \
	{ \
		return NSUIntegerMax; \
	} \
	 \
	- (oneway void)release \
	{ \
	} \
	 \
	- (id)autorelease \
	{ \
		return self; \
	}
#endif

#define CWL_SYNTHESIZE_SINGLETON_FOR_CLASS_WITH_ACCESSOR(classname, accessorMethodName) \
 \
static classname *_accessorMethodName = nil; \
 \
+ (classname *)accessorMethodName \
{ \
	@synchronized(self) \
	{ \
		if (_accessorMethodName == nil) \
		{ \
			_accessorMethodName = [super allocWithZone:NULL]; \
			_accessorMethodName = [_accessorMethodName init]; \
			method_exchangeImplementations(\
				class_getClassMethod([_accessorMethodName class], @selector(accessorMethodName)),\
				class_getClassMethod([_accessorMethodName class], @selector(cwl_lockless_##accessorMethodName)));\
			method_exchangeImplementations(\
				class_getInstanceMethod([_accessorMethodName class], @selector(init)),\
				class_getInstanceMethod([_accessorMethodName class], @selector(cwl_onlyInitOnce)));\
		} \
	} \
	 \
	return _accessorMethodName; \
} \
 \
+ (classname *)cwl_lockless_##accessorMethodName \
{ \
	return _accessorMethodName; \
} \
\
+ (id)allocWithZone:(NSZone *)zone \
{ \
	return [self accessorMethodName]; \
} \
 \
- (id)copyWithZone:(NSZone *)zone \
{ \
	return self; \
} \
- (id)cwl_onlyInitOnce \
{ \
	return self;\
} \
 \
CWL_SYNTHESIZE_SINGLETON_RETAIN_METHODS

#define CWL_DECLARE_SINGLETON_FOR_CLASS(classname) CWL_DECLARE_SINGLETON_FOR_CLASS_WITH_ACCESSOR(classname, sharedInstance)
#define CWL_SYNTHESIZE_SINGLETON_FOR_CLASS(classname) CWL_SYNTHESIZE_SINGLETON_FOR_CLASS_WITH_ACCESSOR(classname, sharedInstance)
