#import "GPUImagePicture.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@implementation GPUImagePicture

#pragma mark -
#pragma mark Initialization and teardown

- (id)initWithURL:(NSURL *)url;
{
    NSData *imageData = [[NSData alloc] initWithContentsOfURL:url];
    
    if (!(self = [self initWithData:imageData]))
    {
        return nil;
    }
    
    return self;
}

- (id)initWithData:(NSData *)imageData;
{
    UIImage *inputImage = [[UIImage alloc] initWithData:imageData];
    
    if (!(self = [self initWithImage:inputImage]))
    {
		return nil;
    }
    
    return self;
}

- (id)initWithImage:(UIImage *)newImageSource;
{
    if (!(self = [self initWithImage:newImageSource smoothlyScaleOutput:NO]))
    {
		return nil;
    }
    
    return self;
}

- (id)initWithCGImage:(CGImageRef)newImageSource;
{
    if (!(self = [self initWithCGImage:newImageSource smoothlyScaleOutput:NO]))
    {
		return nil;
    }
    return self;
}

- (id)initWithImage:(UIImage *)newImageSource smoothlyScaleOutput:(BOOL)smoothlyScaleOutput;
{
    return [self initWithCGImage:[newImageSource CGImage] smoothlyScaleOutput:smoothlyScaleOutput];
}

- (id)initWithCGImage:(CGImageRef)newImageSource smoothlyScaleOutput:(BOOL)smoothlyScaleOutput;
{
    return [self initWithCGImage:newImageSource smoothlyScaleOutput:smoothlyScaleOutput removePremultiplication:NO flipped:NO];
}

- (id)initWithImage:(UIImage *)newImageSource removePremultiplication:(BOOL)removePremultiplication;
{
    return [self initWithCGImage:[newImageSource CGImage] smoothlyScaleOutput:NO removePremultiplication:removePremultiplication flipped:NO];
}

- (id)initWithCGImage:(CGImageRef)newImageSource removePremultiplication:(BOOL)removePremultiplication;
{
    return [self initWithCGImage:newImageSource smoothlyScaleOutput:NO removePremultiplication:removePremultiplication flipped:NO];
}

- (id)initWithImage:(UIImage *)newImageSource smoothlyScaleOutput:(BOOL)smoothlyScaleOutput removePremultiplication:(BOOL)removePremultiplication flipped:(BOOL)flipped;
{
    return [self initWithCGImage:[newImageSource CGImage] smoothlyScaleOutput:smoothlyScaleOutput removePremultiplication:removePremultiplication flipped:flipped];
}

- (id)initWithCGImage:(CGImageRef)newImageSource smoothlyScaleOutput:(BOOL)smoothlyScaleOutput removePremultiplication:(BOOL)removePremultiplication flipped:(BOOL)flipped;
{
    if (!(self = [super init]))
    {
		return nil;
    }
    
    _hasProcessedImage = NO;
    _shouldSmoothlyScaleOutput = smoothlyScaleOutput;

    // TODO: Dispatch this whole thing asynchronously to move image loading off main thread
    CGFloat widthOfImage = CGImageGetWidth(newImageSource);
    CGFloat heightOfImage = CGImageGetHeight(newImageSource);

    // If passed an empty image reference, CGContextDrawImage will fail in future versions of the SDK.
    NSAssert( widthOfImage > 0 && heightOfImage > 0, @"Passed image must not be empty - it should be at least 1px tall and wide");
    
    _pixelSizeOfImage = CGSizeMake(widthOfImage, heightOfImage);
    CGSize pixelSizeToUseForTexture = _pixelSizeOfImage;
    
    BOOL shouldRedrawUsingCoreGraphics = NO;
    
    // For now, deal with images larger than the maximum texture size by resizing to be within that limit
    CGSize scaledImageSizeToFitOnGPU = [self sizeThatFitsWithinATextureForSize:_pixelSizeOfImage];
    if (!CGSizeEqualToSize(scaledImageSizeToFitOnGPU, _pixelSizeOfImage))
    {
        _pixelSizeOfImage = scaledImageSizeToFitOnGPU;
        pixelSizeToUseForTexture = _pixelSizeOfImage;
        shouldRedrawUsingCoreGraphics = YES;
    }
    
    if (self.shouldSmoothlyScaleOutput)
    {
        // In order to use mipmaps, you need to provide power-of-two textures, so convert to the next largest power of two and stretch to fill
        CGFloat powerClosestToWidth = ceil(log2(_pixelSizeOfImage.width));
        CGFloat powerClosestToHeight = ceil(log2(_pixelSizeOfImage.height));
        
        pixelSizeToUseForTexture = CGSizeMake(pow(2.0, powerClosestToWidth), pow(2.0, powerClosestToHeight));
        
        shouldRedrawUsingCoreGraphics = YES;
    }
    
    if (flipped)
    {
        shouldRedrawUsingCoreGraphics = YES;
    }
    
    GLubyte *imageData = NULL;
    CFDataRef dataFromImageDataProvider = NULL;
    GLenum format = GL_BGRA;
    BOOL isLitteEndian = YES;
    BOOL alphaFirst = NO;
    BOOL premultiplied = NO;
	
    if (!shouldRedrawUsingCoreGraphics) {
        /* Check that the memory layout is compatible with GL, as we cannot use glPixelStore to
         * tell GL about the memory layout with GLES.
         */
        if (CGImageGetBytesPerRow(newImageSource) != CGImageGetWidth(newImageSource) * 4 ||
            CGImageGetBitsPerPixel(newImageSource) != 32 ||
            CGImageGetBitsPerComponent(newImageSource) != 8)
        {
            shouldRedrawUsingCoreGraphics = YES;
        } else {
            /* Check that the bitmap pixel format is compatible with GL */
            CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(newImageSource);
            if ((bitmapInfo & kCGBitmapFloatComponents) != 0) {
                /* We don't support float components for use directly in GL */
                shouldRedrawUsingCoreGraphics = YES;
            } else {
                CGBitmapInfo byteOrderInfo = bitmapInfo & kCGBitmapByteOrderMask;
                if (byteOrderInfo == kCGBitmapByteOrder32Little) {
                    /* Little endian, for alpha-first we can use this bitmap directly in GL */
                    CGImageAlphaInfo alphaInfo = bitmapInfo & kCGBitmapAlphaInfoMask;
                    if (alphaInfo != kCGImageAlphaPremultipliedFirst && alphaInfo != kCGImageAlphaFirst &&
                        alphaInfo != kCGImageAlphaNoneSkipFirst) {
                        shouldRedrawUsingCoreGraphics = YES;
                    }
                } else if (byteOrderInfo == kCGBitmapByteOrderDefault || byteOrderInfo == kCGBitmapByteOrder32Big) {
					isLitteEndian = NO;
                    /* Big endian, for alpha-last we can use this bitmap directly in GL */
                    CGImageAlphaInfo alphaInfo = bitmapInfo & kCGBitmapAlphaInfoMask;
                    if (alphaInfo != kCGImageAlphaPremultipliedLast && alphaInfo != kCGImageAlphaLast &&
                        alphaInfo != kCGImageAlphaNoneSkipLast) {
                        shouldRedrawUsingCoreGraphics = YES;
                    } else {
                        /* Can access directly using GL_RGBA pixel format */
						premultiplied = alphaInfo == kCGImageAlphaPremultipliedLast || alphaInfo == kCGImageAlphaPremultipliedLast;
						alphaFirst = alphaInfo == kCGImageAlphaFirst || alphaInfo == kCGImageAlphaPremultipliedFirst;
						format = GL_RGBA;
                    }
                }
            }
        }
    }
    
    //    CFAbsoluteTime elapsedTime, startTime = CFAbsoluteTimeGetCurrent();
    
    if (shouldRedrawUsingCoreGraphics)
    {
        // For resized or incompatible image: redraw
        imageData = (GLubyte *) calloc(1, (int)pixelSizeToUseForTexture.width * (int)pixelSizeToUseForTexture.height * 4);
        
        CGColorSpaceRef genericRGBColorspace = CGColorSpaceCreateDeviceRGB();
        
        CGContextRef imageContext = CGBitmapContextCreate(imageData, (size_t)pixelSizeToUseForTexture.width, (size_t)pixelSizeToUseForTexture.height, 8, (size_t)pixelSizeToUseForTexture.width * 4, genericRGBColorspace,  kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
        if (flipped)
        {
            CGContextTranslateCTM (imageContext, 0, pixelSizeToUseForTexture.height);
            CGContextScaleCTM (imageContext, 1.0, -1.0);
        }
        //        CGContextSetBlendMode(imageContext, kCGBlendModeCopy); // From Technical Q&A QA1708: http://developer.apple.com/library/ios/#qa/qa1708/_index.html
        CGContextDrawImage(imageContext, CGRectMake(0.0, 0.0, pixelSizeToUseForTexture.width, pixelSizeToUseForTexture.height), newImageSource);
        CGContextRelease(imageContext);
        CGColorSpaceRelease(genericRGBColorspace);
		isLitteEndian = YES;
		alphaFirst = YES;
		premultiplied = YES;
    }
    else
    {
        // Access the raw image bytes directly
        dataFromImageDataProvider = CGDataProviderCopyData(CGImageGetDataProvider(newImageSource));
        imageData = (GLubyte *)CFDataGetBytePtr(dataFromImageDataProvider);
    }
	
	if (removePremultiplication && premultiplied) {
		NSUInteger	totalNumberOfPixels = round(pixelSizeToUseForTexture.width * pixelSizeToUseForTexture.height);
		uint32_t	*pixelP = (uint32_t *)imageData;
		uint32_t	pixel;
		CGFloat		srcR, srcG, srcB, srcA;

		for (NSUInteger idx=0; idx<totalNumberOfPixels; idx++, pixelP++) {
			pixel = isLitteEndian ? CFSwapInt32LittleToHost(*pixelP) : CFSwapInt32BigToHost(*pixelP);

			if (alphaFirst) {
				srcA = (CGFloat)((pixel & 0xff000000) >> 24) / 255.0f;
			}
			else {
				srcA = (CGFloat)(pixel & 0x000000ff) / 255.0f;
				pixel >>= 8;
			}

			srcR = (CGFloat)((pixel & 0x00ff0000) >> 16) / 255.0f;
			srcG = (CGFloat)((pixel & 0x0000ff00) >> 8) / 255.0f;
			srcB = (CGFloat)(pixel & 0x000000ff) / 255.0f;
			
			srcR /= srcA; srcG /= srcA; srcB /= srcA;
			
			pixel = (uint32_t)(srcR * 255.0) << 16;
			pixel |= (uint32_t)(srcG * 255.0) << 8;
			pixel |= (uint32_t)(srcB * 255.0);

			if (alphaFirst) {
				pixel |= (uint32_t)(srcA * 255.0) << 24;
			}
			else {
				pixel <<= 8;
				pixel |= (uint32_t)(srcA * 255.0);
			}
			*pixelP = isLitteEndian ? CFSwapInt32HostToLittle(pixel) : CFSwapInt32HostToBig(pixel);
		}
	}
    
    _shouldRedrawUsingCoreGraphics = shouldRedrawUsingCoreGraphics;
    _data = imageData;
    _dataProvider = dataFromImageDataProvider;
    
    return self;
}

- (CGSize)sizeThatFitsWithinATextureForSize:(CGSize)inputSize;
{
    const GLint maxTextureSize = 4086;
    if ( (inputSize.width < maxTextureSize) && (inputSize.height < maxTextureSize) )
    {
        return inputSize;
    }
    
    CGSize adjustedSize;
    if (inputSize.width > inputSize.height)
    {
        adjustedSize.width = (CGFloat)maxTextureSize;
        adjustedSize.height = ((CGFloat)maxTextureSize / inputSize.width) * inputSize.height;
    }
    else
    {
        adjustedSize.height = (CGFloat)maxTextureSize;
        adjustedSize.width = ((CGFloat)maxTextureSize / inputSize.height) * inputSize.width;
    }
    
    return adjustedSize;
}

- (void)dealloc
{
    if (_shouldRedrawUsingCoreGraphics)
    {
        if (_data)
        {
            free(_data);
        }
    }
    else
    {
        if (_dataProvider)
        {
            CFRelease(_dataProvider);
        }
    }
}

@end
