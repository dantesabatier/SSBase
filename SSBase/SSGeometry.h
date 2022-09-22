//
//  SSGeometry.h
//  SSBase
//
//  Created by Dante Sabatier on 4/21/12.
//  Copyright (c) 2012 Dante Sabatier. All rights reserved.
//

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import "SSDefines.h"
#if TARGET_OS_IPHONE
#import <UIKit/UIGeometry.h>
#endif

// kSSUsesOldGeometry irrelevant for swift
#if TARGET_OS_IPHONE
// kSSUsesOldGeometry is always false for iOS. See below.
#define kSSUsesOldGeometry 0
#else
// Geometry is flipped since OS X 10.8. Obviously this affects the way we draw and accommodate things on the screen.
#if (__MAC_OS_X_VERSION_MAX_ALLOWED <= __MAC_10_7)
// kSSUsesOldGeometry, at compiling time, Base SDK is less than or equal to 10.7, always true
#define kSSUsesOldGeometry 1
#else
 // kSSUsesOldGeometry, at runtime, OS X version is less than or equal to 10.7, value depends on appkit version number
#define kSSUsesOldGeometry (floor(NSAppKitVersionNumber) <= NSAppKitVersionNumber10_7)
#endif
#endif

typedef CGSize SSSize;
typedef CGRect SSRect;
typedef CGPoint SSPoint;

typedef NS_OPTIONS(NSUInteger, SSRectCorner) {
    SSRectCornerTopLeft = 1,
    SSRectCornerBottomLeft = 2,
    SSRectCornerTopRight = 4,
    SSRectCornerBottomRight = 8,
    SSRectTopCorners = (SSRectCornerTopLeft|SSRectCornerTopRight),
    SSRectBottomCorners = (SSRectCornerBottomLeft|SSRectCornerBottomRight),
    SSRectLeftCorners = (SSRectCornerTopLeft|SSRectCornerBottomLeft),
    SSRectRightCorners = (SSRectCornerTopRight|SSRectCornerBottomRight),
    SSRectAllCorners = (SSRectCornerTopLeft|SSRectCornerBottomLeft|SSRectCornerTopRight|SSRectCornerBottomRight)
} NS_SWIFT_NAME(SSRect.RectCorner);

typedef NS_ENUM(NSInteger, SSRectPosition) {
    SSRectPositionLeft, //CGRectMinXEdge
    SSRectPositionBottom, //CGRectMinYEdge
    SSRectPositionRight, //CGRectMaxXEdge
    SSRectPositionTop, //CGRectMaxYEdge
    SSRectPositionLeftTop,
    SSRectPositionBottomRight,
    SSRectPositionRightTop,
    SSRectPositionTopRight,
    SSRectPositionLeftBottom,
    SSRectPositionBottomLeft,
    SSRectPositionRightBottom,
    SSRectPositionTopLeft,
    SSRectPositionCenter
} NS_SWIFT_NAME(SSRect.RectPosition);

typedef NS_ENUM(NSInteger, SSRectResizingMethod) {
    SSRectResizingMethodScale,
    SSRectResizingMethodCropStart,
    SSRectResizingMethodCrop,
    SSRectResizingMethodCropEnd,
    SSRectResizingMethodCropTopLeft,
    SSRectResizingMethodCropTopCenter,
    SSRectResizingMethodCropTopRight,
    SSRectResizingMethodCropCenterLeft,
    SSRectResizingMethodCropCenter,
    SSRectResizingMethodCropCenterRight,
    SSRectResizingMethodCropBottomLeft,
    SSRectResizingMethodCropBottomCenter,
    SSRectResizingMethodCropBottomRight
} NS_SWIFT_NAME(SSRect.RectResizingMethod);

typedef NS_ENUM(NSInteger, SSSizeShape) {
    SSSizeShapeSquare,
    SSSizeShapePortrait,
    SSSizeShapeLandscape
} NS_SWIFT_NAME(SSSize.Shape);

SS_EXPORT CGRect SSRectGetGridRectForItemAtIndex(CGRect rect, NSInteger index, NSInteger numberOfItems, CGSize cellSize, CGSize intercellSpacing, NSInteger *numberOfColumns, NSInteger *numberOfRows) CF_SWIFT_NAME(SSRect.rect(self:at:_:_:_:_:_:));
SS_EXPORT CGRect SSRectMakeWithPoints(CGPoint startPoint, CGPoint endPoint) CF_SWIFT_NAME(SSRect.init(with:and:));
SS_EXPORT CGRect SSRectMakeWithAspectRatioInsideRect(CGRect aspectRatio, CGRect boundingRect, SSRectResizingMethod resizingMethod) CF_SWIFT_NAME(SSRect.init(maintaining:inside:using:));
SS_EXPORT CGRect SSRectScale(CGRect rect, CGFloat factor) CF_SWIFT_NAME(SSRect.scale(self:factor:));
SS_EXPORT CGFloat SSRectGetResizeScaleFactor(CGRect sourceRect, CGRect destinationRect) CF_SWIFT_NAME(SSRect.scaleFactor(self:to:));
SS_EXPORT void SSRectDivideEqually(CGRect rect, CGRectEdge edge, NSUInteger segments, CGRect *buffer) CF_SWIFT_NAME(SSRect.dividedEqually(self:from:in:buffer:));
SS_EXPORT void SSRectGetDrawingPointsForAngle(CGRect rect, CGFloat angle, CGPoint *startPoint, CGPoint *endPoint) CF_SWIFT_NAME(SSRect.points(self:for:_:_:));
SS_EXPORT SSRectPosition SSRectGetInversePosition(SSRectPosition position, bool byEdge) CF_SWIFT_NAME(SSRect.inverse(position:_:)) SS_PURE;
SS_EXPORT CGRectEdge SSRectGetInverseEdge(CGRectEdge edge) CF_SWIFT_NAME(SSRect.inverse(edge:)) SS_PURE;
SS_EXPORT CGRect SSRectGetDestinationRectForEdge(CGRect rect, CGRectEdge edge) CF_SWIFT_NAME(SSRect.destination(self:for:));
SS_EXPORT CGPoint SSPointFromString(NSString *string) CF_SWIFT_UNAVAILABLE("");
SS_EXPORT NSString *SSStringFromPoint(CGPoint point) CF_SWIFT_UNAVAILABLE("");
SS_EXPORT CGRect SSRectFromString(NSString *string) CF_SWIFT_UNAVAILABLE("");
SS_EXPORT NSString *SSStringFromRect(CGRect rect) CF_SWIFT_UNAVAILABLE("");
SS_EXPORT CGSize SSSizeFromString(NSString *string) CF_SWIFT_UNAVAILABLE("");
SS_EXPORT NSString *SSStringFromSize(CGSize size) CF_SWIFT_UNAVAILABLE("");
SS_EXPORT CGPoint SSRectGetPointAtPosition(CGRect rect, SSRectPosition position, CGSize offset) CF_SWIFT_NAME(SSRect.point(self:at:offset:));
SS_EXPORT CGRect SSRectMakeWithSize(CGSize size) CF_SWIFT_NAME(SSRect.init(size:));
SS_EXPORT CGRect SSRectMakeWithWidthAndHeight(CGFloat width, CGFloat height) CF_SWIFT_NAME(SSRect.init(width:height:));
SS_EXPORT CGRect SSRectMakeSquare(CGFloat squareSize) CF_SWIFT_NAME(SSRect.square(_:));
SS_EXPORT CGRect SSRectMakeWithPoint(CGPoint point) CF_SWIFT_NAME(SSRect.int(_:));
SS_EXPORT CGRect SSRectMakeSquareAtPoint(CGPoint point, CGFloat squareSize) CF_SWIFT_NAME(SSRect.square(at:_:));
SS_EXPORT CGPoint SSRectGetCenterPoint(CGRect rect) CF_SWIFT_NAME(getter:SSRect.center(self:));
SS_EXPORT CGRect SSRectCenteredSize(CGRect rect, CGSize size) CF_SWIFT_NAME(SSRect.centered(self:in:));
SS_EXPORT CGRect SSRectCenteredSquare(CGRect rect, CGFloat squareSize) CF_SWIFT_NAME(SSRect.centered(self:in:));
SS_EXPORT CGRect SSRectCenteredAroundPoint(CGRect rect, CGPoint point) CF_SWIFT_NAME(SSRect.centered(self:around:));
SS_EXPORT CGRect SSRectCenteredRect(CGRect rect, CGRect bounds) CF_SWIFT_NAME(SSRect.centered(self:in:));
SS_EXPORT CGSize SSSizeMakeWithAspectRatioInsideSize(CGSize aspectRatio, CGSize boundingSize, SSRectResizingMethod resizingMethod) CF_SWIFT_NAME(SSSize.init(maintaining:inside:using:));
SS_EXPORT CGFloat SSSizeGetResizeScaleFactor(CGSize sourceSize, CGSize destinationSize) CF_SWIFT_NAME(SSSize.scaleFactor(self:to:));
SS_EXPORT CGSize SSSizeScale(CGSize size, CGFloat factor) CF_SWIFT_NAME(SSSize.scale(self:factor:));
SS_EXPORT CGSize SSSizeMakeSquare(CGFloat squareSize) CF_SWIFT_NAME(SSSize.square(_:));
SS_EXPORT CGSize SSSizeIntegral(CGSize size) CF_SWIFT_NAME(SSSize.integral(self:));
SS_EXPORT NSComparisonResult SSSizeCompare(CGSize size1, CGSize size2) CF_SWIFT_NAME(SSSize.compare(_:_:));
SS_EXPORT bool SSSizeIsGreaterThanSize(CGSize size1, CGSize size2) CF_SWIFT_NAME(SSSize.greaterThan(self:_:));
SS_EXPORT bool SSSizeIsLessThanSize(CGSize size1, CGSize size2) CF_SWIFT_NAME(SSSize.lessThan(self:_:));
SS_EXPORT bool SSSizeIsEmpty(CGSize size) CF_SWIFT_NAME(getter:SSSize.isEmpty(self:));
SS_EXPORT bool SSSizeIsSquare(CGSize size) CF_SWIFT_NAME(getter:SSSize.isSquare(self:));
SS_EXPORT bool SSSizeIsPortrait(CGSize size) CF_SWIFT_NAME(getter:SSSize.isPortrait(self:));
SS_EXPORT bool SSSizeIsLandscape(CGSize size) CF_SWIFT_NAME(getter:SSSize.isLandscape(self:));
SS_EXPORT SSSizeShape SSSizeGetShape(CGSize size) CF_SWIFT_NAME(getter:SSSize.shape(self:)) SS_PURE;
SS_EXPORT CGRect SSSizeCenteredAroundPoint(CGSize size, CGPoint point) CF_SWIFT_NAME(SSSize.centered(self:_:));
SS_EXPORT CGFloat SSPointGetDistanceToPoint(CGPoint point, CGPoint otherPoint) CF_SWIFT_NAME(SSPoint.distance(self:to:));
SS_EXPORT const CGPoint SSPointCenter CF_SWIFT_NAME(SSPoint.center); // {0.5, 0.5}
SS_EXPORT const CGPoint SSPointRight CF_SWIFT_NAME(SSPoint.right); // {1.0, 0.5}
SS_EXPORT const CGPoint SSPointLeft CF_SWIFT_NAME(SSPoint.left); // {0.0, 0.5}
SS_EXPORT const CGPoint SSPointTopCenter CF_SWIFT_NAME(SSPoint.topCenter); // {0.5, 0.0} if kSSUsesOldGeometry {0.5, 1.0}
SS_EXPORT const CGPoint SSPointTopRight CF_SWIFT_NAME(SSPoint.topRight); // {1.0, 0.0} if kSSUsesOldGeometry {1.0, 1.0}
SS_EXPORT const CGPoint SSPointTopLeft CF_SWIFT_NAME(SSPoint.topLeft); // {0.0, 0.0} if kSSUsesOldGeometry {0.0, 1.0}
SS_EXPORT const CGPoint SSPointBottomCenter CF_SWIFT_NAME(SSPoint.bottomCenter); // {0.5, 1.0} if kSSUsesOldGeometry {0.5, 0.0}
SS_EXPORT const CGPoint SSPointBottomRight CF_SWIFT_NAME(SSPoint.bottomRight); // {1.0, 1.0} if kSSUsesOldGeometry {1.0, 0.0}
SS_EXPORT const CGPoint SSPointBottomLeft CF_SWIFT_NAME(SSPoint.bottomLeft); // {0.0, 1.0} if kSSUsesOldGeometry {0.0, 0.0}
