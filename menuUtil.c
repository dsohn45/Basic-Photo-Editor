/* Daniel Sohn & Richard Guo
* dsohn3, rguo7
* dsohn3@jhu.edu, rguo7@jhu.edu
* 601.220
* 10/16/17
* MIDTERM PROJECT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menuUtil.h"
#include "ppmIO.h"
#include "structHeader.h"
#include "imageManip.h"

#define MAX_WORD 255

void printMenu() {
 printf(
  "Main menu:\n"
  "      r <filename> - read image from <filename>\n"
  "      w <filename> - write image to <filename>\n"
  "      s - swap color channels\n"
  "      br <amt> - change brightness (up or down) by the given amount\n"
  "      c <x1> <y1> <x2> <y2> - crop image to the box with the given corners\n"
  "      g - convert to grayscale\n"
  "      cn <amt> - change contrast (up or down) by the given amount\n"
  "      bl <sigma> - Gaussian blur with the given radius (sigma)\n"
  "      sh <sigma> <amt> - sharpen by given amount (intensity), with radius (sigma)\n"
  "      e <sigma> <threshold> - detect edges with intensity gradient greater than the given threshold\n"
  "      q - quit\n"
  "Enter choice: ");
 return;
}

void menuError() {printf("Error: bad menu option\n");}


void removeLine() {
  char choice = 'a';

  while(choice != '\n') {
    scanf("%c", &choice);
  }
}

int checkCropCorners(Image* img, int uc, int ur, int lc, int lr) {
  if (lr <= uc) return 0;
  if (lr <= ur) return 0;
  if (uc < 0) return 0;
  if (ur < 0) return 0;
  if (lc > (int)img->cols) return 0;
  if (lr > (int)img->rows) return 0;
  return 1;
}

void runProgram() {

  char choice[MAX_WORD];
  char input[MAX_WORD];
  Image* image = NULL;

  printMenu();

  while(scanf("%s", choice) == 1) {

    if (!strcmp(choice, "q")) {
      if (image != NULL) {
        free(image->data);
        free(image);
      }
      printf("Goodbye!\n");
      return;
    }

    else if (!strcmp(choice, "r")) {
      scanf("%s", input);
      Image* temp;
      temp = readImage(input);
      if (temp != NULL) {
        image = temp;
      } 
    }

    else if (!strcmp(choice, "w")) {
      if (scanf("%s", input) == 1) {
        saveImage(input, image);
      }
    }

    else if (!strcmp(choice, "s")) {
      if (image != NULL) {
        printf("Swapping color channels...\n");
        swapColor(image);
      } else {
        menuError();
      }
    }

    else if (!strcmp(choice, "br")) {
      double amt = 0.0;
      if(scanf("%lf", &amt) == 1 && image != NULL) {
        printf("Adjusting brightness by %d...\n", (int) amt);
        brighten(image, amt);
      } else {
        menuError();
      }
    }

    else if (!strcmp(choice, "g")) {
      if (image != NULL) {
        printf("Converting to grayscale...\n");
        grayscale(image);
      } else {
        menuError();
      }
    }

    else if (!strcmp(choice, "cn")) {
      double amt = 0.0;
      if(scanf("%lf", &amt) == 1 && image != NULL) {
        printf("Adjusting contrast by %1.2f...\n", amt);
        contrast(image, amt);
      } else {
        menuError();
      }
    }

    else if (!strcmp(choice, "c")) {
      int uc = 0;
      int ur = 0;
      int lc = 0;
      int lr = 0;
      //TODO: check that bounds r ok
      if (scanf("%d %d %d %d", &uc, &ur, &lc, &lr) == 4 && image != NULL \
      && checkCropCorners(image, uc, ur, lc, lr)) {
        printf("Cropping region from (%d, %d) to (%d, %d)...\n", uc, ur, lc, lr);
        crop(image, uc, ur, lc, lr);
      } else {
        menuError();
      }
    }

    else if (!strcmp(choice, "bl")) {
      double sigma;
      if (scanf("%lf", &sigma) == 1 && image != NULL) {
        printf("Applying blur filter, sigma %1.2f\n",sigma);
        blur(image, sigma);
      } else {
        menuError();
      }
    }

    else if (!strcmp(choice, "sh")) {
      double sigma;
      double strength;
      if (scanf("%lf %lf", &sigma, &strength) == 2 && image != NULL) {
        printf("Applying sharpen filter, sigma %1.2f, intensity %1.2f\n", sigma, strength);
        sharpen(image, sigma, strength);
      } else {
        menuError();
      }
    }

    else if (!strcmp(choice, "e")) {
      double sigma;
      double threshold;
      if (scanf("%lf %lf", &sigma, &threshold) == 2 && image != NULL) {
        printf("Doing edge detection with sigma %1.2f and threshold %1.2f...\n", sigma, threshold);
        edgeDetect(image, sigma, threshold);
      } else {
        menuError();
      }
    }

    else {
      menuError();
    }

    removeLine();
    printMenu();

  }

}
