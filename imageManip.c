/* Daniel Sohn & Richard Guo
* dsohn3, rguo7
* dsohn3@jhu.edu, rguo7@jhu.edu
* 601.220
* 10/16/17
* MIDTERM PROJECT
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imageManip.h"
#define MAX_UCHAR 255 //magic number :O
#define PI 3.14159

void swapColor(Image* img) {
  int rows = (int)img->rows;
  int cols = (int)img->cols;
  unsigned char temp;
  Pixel* pix = img->data;
  for (int i = 0; i < rows*cols; i++) {
    temp = pix->r;
    pix->r = pix->g;
    pix->g = pix->b;
    pix->b = temp;
    // go to next pixel
    pix++;
  }
}

void brighten(Image* img, double amt) {
  int rows = (int)img->rows;
  int cols = (int)img->cols;
  Pixel* pix = img->data;
  for (int i = 0; i < rows*cols; i++) {
    pix->r = changeColor(pix->r, amt);
    pix->g = changeColor(pix->g, amt);
    pix->b = changeColor(pix->b, amt);
    // go to next pixel
    pix++;
  }
}

unsigned char changeColor(unsigned char rgb, double amt) {
  double sum = rgb + amt;
  return clamp(sum);
}

unsigned char clamp(double value) {
  if (value > MAX_UCHAR) return (unsigned char) MAX_UCHAR;
  else if (value < 0) return (unsigned char) 0;
  else return (unsigned char) value;
}

void grayscale(Image* img) {
  int rows = (int)img->rows;
  int cols = (int)img->cols;
  Pixel* pix = img->data;
  for (int i = 0; i < rows*cols; i++) {
    int intensity = (int)(.3*(pix->r) + .59*(pix->g) + .11*(pix->b));
    pix->r = intensity;
    pix->g = intensity;
    pix->b = intensity;
    // go to next pixel
    pix++;
  }
}

unsigned char contrastColor(unsigned char rgb, double amt) {
  double contrast_color = (((double) rgb) - 127.5) / (MAX_UCHAR);
  contrast_color *= amt;
  // revert back to 0-255 range
  contrast_color *= MAX_UCHAR;
  contrast_color += 127.5;
  return clamp(contrast_color);
}

void contrast(Image* img, double amt) {
  int rows = (int)img->rows;
  int cols = (int)img->cols;
  Pixel* pix = img->data;
  for (int i = 0; i < rows*cols; i++) {
    pix->r = contrastColor(pix->r, amt);
    pix->g = contrastColor(pix->g, amt);
    pix->b = contrastColor(pix->b, amt);
    // go to next pixel
    pix++;
  }
}
//TODO: menu input for crop
void crop(Image* img, int uc, int ur, int bc, int br) {
  int x_difference = bc - uc;
  int y_difference = br - ur;

  Pixel* cropped_pix = malloc(sizeof(Pixel)*x_difference*y_difference);
  Pixel* cropped_start = cropped_pix;

  Pixel* orig = img->data;
  int start_index = img->cols*(ur) + (uc);
  orig += start_index;
  for(int i = 0; i < y_difference; i++) {
    for (int j = 0; j < x_difference; j++) {
      cropped_pix->r = orig->r;
      cropped_pix->b = orig->b;
      cropped_pix->g = orig->g;
      cropped_pix++;
      orig++;
    }
    orig += (img->cols - x_difference);
  }
  free(img->data);

  img->data = cropped_start;
  img->rows = y_difference;
  img->cols = x_difference;
}

double sq(double x) {return (x * x);} //pow function?

void gaussian(double* gauss, int N, double sigma) {
  double sum = 0;
  int ctr = 0;
  int mid = N / 2;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      *(gauss + ctr) =  (1.0 / (2.0 * PI * sq(sigma))) * exp( -(sq(mid - j) + sq(mid - i)) / (2 * sq(sigma)));
      sum += *(gauss + ctr);
      ctr++;
    }
  }
}

void blur(Image* img, double sigma) {
  int N = sigma * 5;
  N = N * 2 + 1;
  int mid = N / 2;

  Pixel* toMask = malloc(sizeof(Pixel) * N * N);
  double* gauss = malloc(sizeof(double) * N * N);
  Pixel blank;
  blank.r = 0;
  blank.g = 0;
  blank.b = 0;



  gaussian(gauss, N, sigma);

  for (unsigned int i = 0; i < img->rows; i++) {
    for (unsigned int j = 0; j < img->cols; j++) {
      double sum = 0;

      int ctr = 0;

      int startCol = j - mid;
      int startRow = i - mid;

      for (int k = 0; k < N; k++) {
        for (int l = 0; l < N; l++) {
          if (startCol + l < 0 || startCol + l >= (int) img->cols || startRow + k < 0 || startRow + k >= (int) img->rows) {
            *(toMask + ctr) = blank;
          } else {
            *(toMask + ctr) = *(img->data + ((startRow + k) * img->cols) + l + startCol);
            sum += (double) *(gauss + ctr);
          }
          ctr++;
        }
      }

      double red = 0;
      double green = 0;
      double blue = 0;

      ctr = 0;
      for (int x = 0; x < N * N; x++) {
        red += (double) ((toMask + ctr)->r * *(gauss + ctr));
        blue += (double) ((toMask + ctr)->b * *(gauss + ctr));
        green += (double) ((toMask + ctr)->g * *(gauss + ctr));
        ctr++;
      }

      (img->data + i * img->cols + j)->r = red / sum;
      (img->data + i * img->cols + j)->g = green / sum;
      (img->data + i * img->cols + j)->b = blue / sum;

    }
  }

  free(gauss);
  free(toMask);
}

void copy(Image* source, Image* dest) {
  dest->rows = source->rows;
  dest->cols = source->cols;
  dest->color = source->color;

  Pixel* pixelData = malloc(source->cols * source->rows * sizeof(Pixel));

  for (unsigned int i = 0; i < source->cols * source->rows; i++) {
    *(pixelData + i) = *((source->data) + i);
  }

  dest->data = pixelData;

}

void sharpen(Image* img, double sigma, double strength) {

  Image* blurred = malloc(sizeof(Image));

  copy(img, blurred);

  blur(blurred, sigma);

  for (unsigned int i = 0; i < img->cols * img->rows; i++) {
    double blue = 0;
    double red = 0;
    double green = 0;

    red = (double) ((img->data) + i)->r - (double) ((blurred->data) + i)->r;
    blue = (double) ((img->data) + i)->b - (double) ((blurred->data) + i)->b;
    green = (double) ((img->data) + i)->g - (double) ((blurred->data) + i)->g;

    ((img->data + i))->r = clamp(red * strength + ((img->data + i))->r);
    ((img->data + i))->g = clamp(green * strength + ((img->data + i))->g);
    ((img->data + i))->b = clamp(blue * strength + ((img->data + i))->b);
  }

  free(blurred->data);
  free(blurred);
}

double gradientX(Pixel* pix) {
  double left_i = (pix - 1)->r;
  double right_i = (pix + 1)->r;
  return (right_i - left_i)/2;
}

double gradientY(Pixel* pix, unsigned int cols) {
  double up_i = (pix - cols)->r;
  double down_i = (pix + cols)->r;
  return (up_i - down_i)/2;
}

double magGradient(double gradientX, double gradientY) {
  return sqrt(pow(gradientX, 2) + pow(gradientY, 2));
}

void edgeDetect(Image* img, double sigma, double threshold) {
  grayscale(img);
  blur(img, sigma);

  //TODO: just copy over pixels instead
  Image* origImage = malloc(sizeof(Image));
  copy(img, origImage);

  Pixel* pix = img->data;
  Pixel* origPix = origImage->data;

  pix += img->cols; //correct start index
  origPix += img->cols;

  for (int i = 0; i < (int)img->rows - 2; i++) {
    for (int j = 0; j < (int)img->cols - 2; j++) {
      double gradX = gradientX(origPix);
      double gradY = gradientY(origPix, img->cols);
      double mag = magGradient(gradX, gradY);
      if (mag > threshold) {
        pix->r = 0;
        pix->b = 0;
        pix->g = 0;
      } else {
        pix->r = 255;
        pix->b = 255;
        pix->g = 255;
      }
      pix++;
      origPix++;
    }
    pix+=2;
    origPix+=2;
  }

  free(origImage->data);
  origImage->data = NULL;
  free(origImage);
  origImage = NULL;
}
