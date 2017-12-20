/* Daniel Sohn & Richard Guo
*	dsohn3, rguo7
*	dsohn3@jhu.edu, rguo7@jhu.edu
*	601.220
*	10/16/17
*	MIDTERM PROJECT
*/
#ifndef IMAGE_MANIP_H
#define IMAGE_MANIP_H

#include "structHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Swaps color channels by 1
 *
 * @param img Image object
 */
void swapColor(Image* img);

/**
 * Brightens color channels by amount
 *
 * @param img Image object
 * @param amt double of amount being brightened or darkened
 */
void brighten(Image* img, double amt);

/**
 * Changes color of pixel by an amount
 *
 * @param rgb original pixel value
 * @param amt amount pixel is being changed by
 */
unsigned char changeColor(unsigned char rgb, double amt);

/**
 * Clamps pixel to range of 0 and 255
 *
 * @param value double being clamped
 */
unsigned char clamp(double value);

/**
 * Makes image grayscale
 *
 * @param img Image object
 */
void grayscale(Image* img);

/**
 * Increases contrast in image by amount
 *
 * @param img Image object
 * @param amt amount of contrast being applied
 */
void contrast(Image* img, double amt);

/**
 * Increases contrast of pixel value by amount
 *
 * @param rgb original pixel value
 * @param amt amount being increased
 */
unsigned char contrastColor(unsigned char rgb, double amt);

/**
 * Crops image by coordinates
 *
 * @param img Image object
 * @param img Image being cropped
 * @param uc upper column coordinate
 * @param ur upper row coordinate
 * @param lc lower column coordinate
 * @param lr lower row coordinate
 */
void crop(Image* img, int uc, int ur, int bc, int br);

/**
 * Squares value
 *
 * @param x double being squared
 */
double sq(double x);

/**
 * Calculates gaussian kernel of certain size based on sigma
 *
 * @param gauss kernel
 * @param N NxN size of kernel
 * @param sigma std dev of kernel
 */
void gaussian(double* gauss, int N, double sigma);

/**
 * Blurs image
 *
 * @param img Image object
 * @param sigma amount being blurred by
 */
void blur(Image* img, double sigma);

/**
 * Creates a copy of image
 *
 * @param source original image
 * @param dest array image is being copied to
 */
void copy(Image* source, Image* dest);

/**
 * Sharpens image
 *
 * @param img Image object
 * @param sigma std dev of blur kernel
 * @param strength amount being sharpened by
 */
void sharpen(Image* img, double sigma, double strength);

/**
 * Calculates gradient of pixel based on x direction
 *
 * @param pix pixel whose gradient is being calculated
 */
double gradientX(Pixel* pix);

/**
 * Calculates gradient of pixel based on y direction
 *
 * @param pix pixel whose gradient is being calculated
 */
double gradientY(Pixel* pix, unsigned int cols);

/**
 * Calculates magnitude of gradient
 *
 * @param gradientX gradient of pixel in x direction
 * @param gradientY gradient of pixel in y direction
 */
double magGradient(double gradientX, double gradientY);

/**
 * Detects edges in an image
 *
 * @param sigma amount image is being blurred
 * @param cutoff value to decide if pixel is edge or not
 */
void edgeDetect(Image* img, double sigma, double threshold);

#endif
