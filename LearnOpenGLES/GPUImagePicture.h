#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@interface GPUImagePicture : NSObject

@property (nonatomic, assign, readonly) BOOL shouldRedrawUsingCoreGraphics;
@property (nonatomic, assign, readonly) BOOL shouldSmoothlyScaleOutput;
@property (nonatomic, assign, readonly) BOOL hasProcessedImage;
@property (nonatomic, assign, readonly) CGSize pixelSizeOfImage;
@property (nonatomic, assign, readonly) CFDataRef dataProvider;
@property (nonatomic, assign, readonly) unsigned char *data;

// Initialization and teardown
- (id)initWithURL:(NSURL *)url;
- (id)initWithImage:(UIImage *)newImageSource;
- (id)initWithCGImage:(CGImageRef)newImageSource;
- (id)initWithImage:(UIImage *)newImageSource smoothlyScaleOutput:(BOOL)smoothlyScaleOutput;
- (id)initWithCGImage:(CGImageRef)newImageSource smoothlyScaleOutput:(BOOL)smoothlyScaleOutput;
- (id)initWithImage:(UIImage *)newImageSource removePremultiplication:(BOOL)removePremultiplication;
- (id)initWithCGImage:(CGImageRef)newImageSource removePremultiplication:(BOOL)removePremultiplication;
- (id)initWithImage:(UIImage *)newImageSource smoothlyScaleOutput:(BOOL)smoothlyScaleOutput removePremultiplication:(BOOL)removePremultiplication flipped:(BOOL)flipped;
- (id)initWithCGImage:(CGImageRef)newImageSource smoothlyScaleOutput:(BOOL)smoothlyScaleOutput removePremultiplication:(BOOL)removePremultiplication flipped:(BOOL)flipped;

@end
