//
//  SSGeometry.m
//  SSBase
//
//  Created by Dante Sabatier on 4/21/12.
//  Copyright (c) 2012 Dante Sabatier. All rights reserved.
//

#import "SSGeometry.h"

const CGPoint SSPointCenter = {0.5, 0.5};
const CGPoint SSPointRight = {1.0, 0.5};
const CGPoint SSPointLeft = {0.0, 0.5};
const CGPoint SSPointTopCenter = {0.5, 0.0};
const CGPoint SSPointTopRight = {1.0, 0.0};
const CGPoint SSPointTopLeft = {0.0, 0.0};
const CGPoint SSPointBottomCenter = {0.5, 1.0};
const CGPoint SSPointBottomRight = {1.0, 1.0};
const CGPoint SSPointBottomLeft = {0.0, 1.0};

CGRect SSRectGetGridRectForItemAtIndex(CGRect rect, NSInteger index, NSInteger numberOfItems, CGSize cellSize, CGSize intercellSpacing, NSInteger *numberOfColumns, NSInteger *numberOfRows) {
    if (!NSLocationInRange(index, NSMakeRange(0, numberOfItems))) {
        return CGRectZero;
    }
    
    NSInteger maxNumberOfColumns = 0;
    if (numberOfColumns) {
        maxNumberOfColumns = *numberOfColumns;
    }
        
    NSInteger maxNumberOfRows = 0;
    if (numberOfRows) {
        maxNumberOfRows = *numberOfRows;
    }
    
    NSInteger columns = MAX(MIN((NSInteger)FLOOR((CGRectGetWidth(rect) - (intercellSpacing.width*(CGFloat)2.0))/(cellSize.width + intercellSpacing.width)), numberOfItems), 1);
    if (maxNumberOfColumns > 0) {
        columns = MIN(columns, maxNumberOfColumns);
    }
    
    NSInteger rows = (NSInteger)CEIL((CGFloat)numberOfItems/(CGFloat)columns);
    if ((maxNumberOfRows > 0) && (rows >= maxNumberOfRows)) {
        columns = MAX((NSInteger)MIN(CEIL((CGFloat)numberOfItems/(CGFloat)maxNumberOfRows), numberOfItems), 1);
        rows = maxNumberOfRows;
    }
    
    if (numberOfColumns) {
        *numberOfColumns = columns;
    }
        
    if (numberOfRows) {
        *numberOfRows = rows;
    }
    
    NSInteger column = index % columns;
    NSInteger row = (index - column) / columns;
    CGFloat interitemSpacing = (intercellSpacing.width > 0.0) ? FABS((CGRectGetWidth(rect) - (columns * cellSize.width)) / columns) : 0.0;
    return CGRectMake(intercellSpacing.width + (interitemSpacing*(CGFloat)0.5) + (column * (cellSize.width + interitemSpacing)), intercellSpacing.height + (row * (cellSize.height + intercellSpacing.height)), cellSize.width, cellSize.height);
}

CGRect SSRectMakeWithPoints(CGPoint startPoint, CGPoint endPoint) {
    CGFloat xDistance = endPoint.x - startPoint.x;
    CGFloat yDistance = endPoint.y - startPoint.y;
    CGRect rect = CGRectZero;
    if (endPoint.x < startPoint.x) {
        rect.origin.x = startPoint.x + xDistance;
        rect.size.width = FABS(xDistance);
    } else {
        rect.origin.x = startPoint.x;
        rect.size.width = xDistance;
    }
    
    if (endPoint.y < startPoint.y) {
        rect.origin.y = startPoint.y + yDistance;
        rect.size.height = FABS(yDistance);
    } else {
        rect.origin.y = startPoint.y;
        rect.size.height = yDistance;
    }
    
    return rect;
}

CGRect SSRectMakeWithAspectRatioInsideRect(CGRect aspectRatio, CGRect boundingRect, SSRectResizingMethod resizingMethod) {
    if (CGRectIsEmpty(aspectRatio)) {
        return CGRectZero;
    }
    
    if (CGRectEqualToRect(aspectRatio, boundingRect)) {
        return aspectRatio;
    }
    
    CGFloat sourceWidth = aspectRatio.size.width;
    CGFloat sourceHeight = aspectRatio.size.height;
    CGFloat targetWidth = boundingRect.size.width;
    CGFloat targetHeight = boundingRect.size.height;
    CGFloat sourceRatio = sourceWidth / sourceHeight;
    CGFloat targetRatio = targetWidth / targetHeight;
    
    BOOL scaleWidth = (sourceRatio <= targetRatio);
    scaleWidth = (resizingMethod != SSRectResizingMethodScale) ? scaleWidth : !scaleWidth;
    
    CGFloat scalingFactor, scaledWidth, scaledHeight;
    if (scaleWidth) {
        scalingFactor = (CGFloat)1.0/sourceRatio;
        scaledWidth = targetWidth;
        scaledHeight = targetWidth * scalingFactor;
    } else {
        scalingFactor = sourceRatio;
        scaledWidth = targetHeight * scalingFactor;
        scaledHeight = targetHeight;
    }
    
    CGFloat scaleFactor = scaledHeight / sourceHeight;
    CGFloat w = targetWidth, h = targetHeight;
    CGFloat x = 0.0, y = 0.0;
    switch (resizingMethod) {
        case SSRectResizingMethodScale: {
            x = CGRectGetMidX(boundingRect) - (scaledWidth * (CGFloat)0.5);
            y = CGRectGetMidY(boundingRect) - (scaledHeight * (CGFloat)0.5);
            w = scaledWidth;
            h = scaledHeight;
        }
            break;
        case SSRectResizingMethodCropStart: {
            if (scaleWidth) {
                x = 0.0;
                y = 0.0;
            } else {
                x = (scaledWidth - targetWidth)/scaleFactor;
                y = ((scaledHeight - targetHeight) * (CGFloat)0.5)/scaleFactor;
            }
            w = targetWidth / scaleFactor;
            h = targetHeight / scaleFactor;
        }
            break;
        case SSRectResizingMethodCrop: {
            x = ((scaledWidth - targetWidth) * (CGFloat)0.5)/scaleFactor;
            y = ((scaledHeight - targetHeight) * (CGFloat)0.5)/scaleFactor;
            w = targetWidth / scaleFactor;
            h = targetHeight / scaleFactor;
        }
            break;
        case SSRectResizingMethodCropEnd: {
            if (scaleWidth) {
                x = ((scaledWidth - targetWidth) * (CGFloat)0.5)/scaleFactor;
                y = (scaledHeight - targetHeight)/scaleFactor;
            } else {
                x = 0.0;
                y = ((scaledHeight - targetHeight) * (CGFloat)0.5)/scaleFactor;
            }
            w = targetWidth / scaleFactor;
            h = targetHeight / scaleFactor;
        }
            break;
        case SSRectResizingMethodCropTopLeft: {
             x = y = 0.0;
        }
            break;
        case SSRectResizingMethodCropTopCenter: {
            x = (sourceWidth - targetWidth) * (CGFloat)0.5;
            y = 0.0;
        }
            break;
        case SSRectResizingMethodCropTopRight: {
            x = sourceWidth - targetWidth;
            y = 0.0;
        }
            break;
        case SSRectResizingMethodCropBottomLeft: {
            x = 0.0;
            y = sourceHeight - targetHeight;
        }
            break;
        case SSRectResizingMethodCropBottomCenter: {
            x = (sourceWidth - targetWidth) * (CGFloat)0.5;
            y = sourceHeight - targetHeight;
        }
            break;
        case SSRectResizingMethodCropBottomRight: {
            x = sourceWidth - targetWidth;
            y = sourceHeight - targetHeight;
        }
            break;
        case SSRectResizingMethodCropCenterLeft:
            x = 0.0;
            y = (sourceHeight - targetHeight) * (CGFloat)0.5;
            break;
        case SSRectResizingMethodCropCenterRight: {
            x = sourceWidth - targetWidth;
            y = (sourceHeight - targetHeight) * (CGFloat)0.5;
        }
            break;
        case SSRectResizingMethodCropCenter: {
            x = (sourceWidth - targetWidth) * (CGFloat)0.5;
            y = (sourceHeight - targetHeight) * (CGFloat)0.5;
        }
            break;
    }
    
    return CGRectIntegral((CGRect){.origin.x = x, .origin.y = y, .size = {w, h}});
}

CGFloat SSRectGetResizeScaleFactor(CGRect sourceRect, CGRect destinationRect) {
    CGFloat sourceWidth = sourceRect.size.width;
    CGFloat sourceHeight = sourceRect.size.height;
    CGFloat targetWidth = destinationRect.size.width;
    CGFloat targetHeight = destinationRect.size.height;
    CGFloat sourceRatio = sourceWidth / sourceHeight;
    CGFloat targetRatio = targetWidth / targetHeight;
    CGFloat scaledHeight;
    if (sourceRatio > targetRatio) {
        scaledHeight = targetWidth * ((CGFloat)1.0/sourceRatio);
    } else {
        scaledHeight = targetHeight;
    }
    return scaledHeight / sourceHeight;
}

void SSRectDivideEqually(CGRect rect, CGRectEdge edge, NSUInteger count, CGRect *buffer) {
	BOOL vertical = (edge == CGRectMinXEdge || edge == CGRectMaxXEdge);
	CGFloat size = (vertical ? CGRectGetWidth(rect) : CGRectGetHeight(rect))/count;
	CGRect remainder;
	CGRectDivide(rect, buffer, &remainder, size, edge);
	NSUInteger index;
	for (index = 1; index < count; index++) {
        buffer[index] = CGRectOffset(buffer[index-1], (vertical * size), (!vertical * size));
    }
}

void SSRectGetDrawingPointsForAngle(CGRect rect, CGFloat angle, CGPoint *startPoint, CGPoint *endPoint) {
    if (angle == 0) {
        *startPoint = CGPointMake(CGRectGetMinX(rect), CGRectGetMinY(rect)); //right of rect
        *endPoint = CGPointMake(CGRectGetMaxX(rect),CGRectGetMinY(rect)); //left of rect
  	} else if (angle == 90) {
        *startPoint = CGPointMake(CGRectGetMinX(rect), CGRectGetMinY(rect)); //bottom of rect
        *endPoint = CGPointMake(CGRectGetMinX(rect), CGRectGetMaxY(rect)); //top of rect
  	} else {
        CGFloat x,y;
        CGFloat sina, cosa, tana;
        CGFloat length;
        CGFloat deltaX, deltaY;
        CGFloat radians = RADIANS(angle); //convert the angle to radians
        if (FABS(TAN(radians)) <= 1) { //for range [-45,45], [135,225]
            x = CGRectGetWidth(rect);
            y = CGRectGetHeight(rect);
            
            sina = SIN(radians);
            cosa = COS(radians);
            tana = TAN(radians);
            
            length = x/FABS(cosa)+(y-x*FABS(tana))*FABS(sina);
            
            deltaX = length*cosa/(CGFloat)2.0;
            deltaY = length*sina/(CGFloat)2.0;
		} else { //for range [45,135], [225,315]
            static CGFloat radians90 = RADIANS(90);
            
            x = CGRectGetHeight(rect);
            y = CGRectGetWidth(rect);
            
            sina = SIN(radians - radians90);
            cosa = COS(radians - radians90);
            tana = TAN(radians - radians90);
            
            length = x/FABS(cosa)+(y-x*FABS(tana))*FABS(sina);
            
            deltaX =-length*sina/(CGFloat)2.0;
            deltaY = length*cosa/(CGFloat)2.0;
		}
        
        *startPoint = CGPointMake(CGRectGetMidX(rect)-deltaX, CGRectGetMidY(rect)-deltaY);
        *endPoint = CGPointMake(CGRectGetMidX(rect)+deltaX, CGRectGetMidY(rect)+deltaY);
	}
}

CGPoint SSRectGetPointAtPosition(CGRect rect, SSRectPosition position, CGSize offset) {
    CGPoint point = CGPointZero;
    switch (position) {
        case SSRectPositionLeft:
            point = CGPointMake(CGRectGetMinX(rect), CGRectGetMidY(rect));
            break;
        case SSRectPositionBottom:
            point = CGPointMake(CGRectGetMidX(rect), CGRectGetMinY(rect));
            break;
        case SSRectPositionRight:
            point = CGPointMake(CGRectGetMaxX(rect), CGRectGetMidY(rect));
            break;
        case SSRectPositionTop:
            point = CGPointMake(CGRectGetMidX(rect), CGRectGetMaxY(rect));
            break;
        case SSRectPositionRightTop:
            point = CGPointMake(CGRectGetMaxX(rect), CGRectGetMaxY(rect) - offset.height);
            break;
        case SSRectPositionBottomRight:
            point = CGPointMake(CGRectGetMaxX(rect) - offset.width, CGRectGetMinY(rect));
            break;
        case SSRectPositionLeftTop:
            point = CGPointMake(CGRectGetMinX(rect), CGRectGetMaxY(rect) - offset.height);
            break;
        case SSRectPositionTopRight:
            point = CGPointMake(CGRectGetMaxX(rect) - offset.width, CGRectGetMaxY(rect));
            break;
        case SSRectPositionLeftBottom:
            point = CGPointMake(CGRectGetMinX(rect), CGRectGetMinY(rect) + offset.height);
            break;
        case SSRectPositionBottomLeft:
            point = CGPointMake(CGRectGetMinX(rect) + offset.width, CGRectGetMinY(rect));
            break;
        case SSRectPositionRightBottom:
            point = CGPointMake(CGRectGetMaxX(rect), CGRectGetMinY(rect) + offset.height);
            break;
        case SSRectPositionTopLeft:
            point = CGPointMake(CGRectGetMinX(rect) + offset.width, CGRectGetMaxY(rect));
            break;
        case SSRectPositionCenter:
            point = CGPointMake(CGRectGetMidX(rect), CGRectGetMidY(rect));
            break;
    }
	return point;
}

SSRectPosition SSRectGetInversePosition(SSRectPosition position, bool byEdge) {
    SSRectPosition inversePosition = position;
    switch (position) {
        case SSRectPositionLeft:
            inversePosition = SSRectPositionRight;
            break;
        case SSRectPositionBottom:
            inversePosition = SSRectPositionTop;
            break;
        case SSRectPositionRight:
            inversePosition = SSRectPositionLeft;
            break;
        case SSRectPositionTop:
            inversePosition = SSRectPositionBottom;
            break;
        case SSRectPositionRightTop:
            inversePosition = byEdge ? SSRectPositionLeftTop : SSRectPositionLeftBottom;
            break;
        case SSRectPositionBottomRight:
            inversePosition = byEdge ? SSRectPositionTopRight : SSRectPositionBottomLeft;
            break;
        case SSRectPositionLeftTop:
            inversePosition = byEdge ? SSRectPositionRightTop : SSRectPositionRightBottom;
            break;
        case SSRectPositionTopRight:
            inversePosition = byEdge ? SSRectPositionBottomRight : SSRectPositionTopLeft;
            break;
        case SSRectPositionLeftBottom:
            inversePosition = byEdge ? SSRectPositionRightBottom : SSRectPositionRightTop;
            break;
        case SSRectPositionBottomLeft:
            inversePosition = byEdge ? SSRectPositionTopLeft : SSRectPositionBottomRight;
            break;
        case SSRectPositionRightBottom:
            inversePosition = byEdge ? SSRectPositionLeftBottom : SSRectPositionLeftTop;
            break;
        case SSRectPositionTopLeft:
            inversePosition = byEdge ? SSRectPositionBottomLeft : SSRectPositionTopRight;
            break;
        case SSRectPositionCenter:
            break;
    }
    return inversePosition;
}

CGRectEdge SSRectGetInverseEdge(CGRectEdge edge) {
    return (CGRectEdge)SSRectGetInversePosition((SSRectPosition)edge, true);
}

CGRect SSRectGetDestinationRectForEdge(CGRect rect, CGRectEdge edge) {
    CGRect destinationRect = rect;
    switch (edge) {
        case CGRectMinXEdge:
            destinationRect.origin.x -= destinationRect.size.width;
            break;
        case CGRectMinYEdge:
            destinationRect.origin.y -= destinationRect.size.height;
            break;
        case CGRectMaxXEdge:
            destinationRect.origin.x += destinationRect.size.width;
            break;
        case CGRectMaxYEdge:
            destinationRect.origin.y += destinationRect.size.height;
            break;
    }
    return CGRectIntegral(destinationRect);
}

CGRect SSRectMakeWithSize(CGSize size) {
    return (CGRect){.origin.x = 0.0, .origin.y = 0.0, .size.width = size.width, .size.height = size.height};
}

CGFloat SSPointGetDistanceToPoint(CGPoint point, CGPoint otherPoint) {
    return SQRT(POW(otherPoint.x - point.x, 2.0) + POW(otherPoint.y - point.y, 2.0));
}

CGPoint SSPointGetMiddleToPoint(CGPoint point, CGPoint otherPoint) {
	return (CGPoint){(point.x + otherPoint.x)/2.0, (point.y + otherPoint.y)/2.0};
}

CGFloat SSPointGetAngleToPoint(CGPoint point, CGPoint otherPoint) {
	return FABS(TAN(otherPoint.y - point.y/otherPoint.x - point.x));
}

CGRect SSRectMakeWithWidthAndHeight(CGFloat width, CGFloat height) {
    return (CGRect){.origin.x = 0.0, .origin.y = 0.0, .size.width = width, .size.height = height};
}

CGRect SSRectMakeSquare(CGFloat squareSize) {
    return (CGRect){.origin.x = 0.0, .origin.y = 0.0, .size.width = squareSize, .size.height = squareSize};
}

CGRect SSRectMakeWithPoint(CGPoint point) {
    return (CGRect){.origin.x = point.x, .origin.y = point.y, .size.width = 0.0, .size.height = 0.0};
}

CGRect SSRectMakeSquareAtPoint(CGPoint point, CGFloat squareSize) {
    return (CGRect){.origin.x = point.x, .origin.y = point.y, .size.width = squareSize, .size.height = squareSize};
}

CGSize SSSizeMakeSquare(CGFloat squareSize) {
    return (CGSize){.width = squareSize, .height = squareSize};
}

CGSize SSSizeIntegral(CGSize size) {
    return (CGSize){.width = FLOOR(size.width), .height = FLOOR(size.height)};
}

bool SSSizeIsEmpty(CGSize size) {
    return CGRectIsEmpty((CGRect){.origin.x = 0.0, .origin.y = 0.0, .size.width = size.width, .size.height = size.height});
}

bool SSSizeIsSquare(CGSize size) {
    return size.width == size.height;
}

bool SSSizeIsPortrait(CGSize size) {
    return isless(size.width, size.height);
}

bool SSSizeIsLandscape(CGSize size) {
    return isgreater(size.width, size.height);
}

bool SSSizeIsGreaterThanSize(CGSize size1, CGSize size2) {
    return (bool)(SSSizeCompare(size1, size2) == NSOrderedAscending);
}

bool SSSizeIsLessThanSize(CGSize size1, CGSize size2) {
    return (bool)(SSSizeCompare(size1, size2) == NSOrderedDescending);
}

SSSizeShape SSSizeGetShape(CGSize size) {
    if (SSSizeIsPortrait(size)) {
        return SSSizeShapePortrait;
    }
    if (SSSizeIsLandscape(size)) {
        return SSSizeShapeLandscape;
    }
    return SSSizeShapeSquare;
}

CGPoint SSRectGetCenterPoint(CGRect rect) {
    return CGPointMake(CGRectGetMidX(rect), CGRectGetMidY(rect));
}

CGRect SSSizeCenteredAroundPoint(CGSize size, CGPoint point) {
    return (CGRect){.origin.x = point.x - (size.width*(CGFloat)0.5), .origin.y = point.y - (size.height*(CGFloat)0.5), .size.width = size.width, .size.height = size.height};
}

CGRect SSRectCenteredSize(CGRect rect, CGSize size) {
    return SSSizeCenteredAroundPoint(size, SSRectGetCenterPoint(rect));
}

CGRect SSRectCenteredSquare(CGRect rect, CGFloat squareSize) {
    return SSSizeCenteredAroundPoint(SSSizeMakeSquare(squareSize), SSRectGetCenterPoint(rect));
}

CGRect SSRectCenteredAroundPoint(CGRect rect, CGPoint point) {
    return SSSizeCenteredAroundPoint(rect.size, point);
}

CGRect SSRectCenteredRect(CGRect rect, CGRect bounds) {
    return SSSizeCenteredAroundPoint(bounds.size, SSRectGetCenterPoint(rect));
}

NSComparisonResult SSSizeCompare(CGSize size1, CGSize size2) {
    if (CGSizeEqualToSize(size1, size2)) {
        return NSOrderedSame;
    }
    
	NSInteger a = (NSInteger) FLOOR(size1.width * size1.height);
	NSInteger b = (NSInteger) FLOOR(size2.width * size2.height);
    if (a == b) {
        return NSOrderedSame;
    } else if (a > b) {
        return NSOrderedAscending;
    }
	return NSOrderedDescending;
}

CGRect SSRectScale(CGRect rect, CGFloat factor) {
    if (factor == 1.0) {
        return rect;
    }
    return SSRectMakeWithAspectRatioInsideRect(rect, (CGRect){.origin.x = rect.origin.x, .origin.y = rect.origin.y, .size.width = (rect.size.width*factor), .size.height = (rect.size.height*factor)}, SSRectResizingMethodScale);
}

CGSize SSSizeMakeWithAspectRatioInsideSize(CGSize aspectRatio, CGSize boundingSize, SSRectResizingMethod resizingMethod) {
    return SSRectMakeWithAspectRatioInsideRect(SSRectMakeWithSize(aspectRatio), SSRectMakeWithSize(boundingSize), resizingMethod).size;
}

CGFloat SSSizeGetResizeScaleFactor(CGSize sourceSize, CGSize destinationSize) {
    return SSRectGetResizeScaleFactor(SSRectMakeWithSize(sourceSize), SSRectMakeWithSize(destinationSize));
}

CGSize SSSizeScale(CGSize size, CGFloat factor) {
    if (factor == 1.0) {
        return size;
    }
    return SSRectScale(SSRectMakeWithSize(size), factor).size;
}

CGPoint SSPointFromString(NSString *string) {
#if TARGET_OS_IPHONE
    return CGPointFromString(string);
#else
    return NSPointFromString(string);
#endif
}

NSString *SSStringFromPoint(CGPoint point) {
#if TARGET_OS_IPHONE
    return NSStringFromCGPoint(point);
#else
    return NSStringFromPoint(point);
#endif
}

CGRect SSRectFromString(NSString *string) {
#if TARGET_OS_IPHONE
    return CGRectFromString(string);
#else
    return NSRectFromString(string);
#endif
}

NSString *SSStringFromRect(CGRect rect) {
#if TARGET_OS_IPHONE
    return NSStringFromCGRect(rect);
#else
    return NSStringFromRect(rect);
#endif
}

CGSize SSSizeFromString(NSString *string) {
#if TARGET_OS_IPHONE
    return CGSizeFromString(string);
#else
    return NSSizeFromString(string);
#endif
}

NSString *SSStringFromSize(CGSize size) {
#if TARGET_OS_IPHONE
    return NSStringFromCGSize(size);
#else
    return NSStringFromSize(size);
#endif
}

