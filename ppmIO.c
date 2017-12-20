/* Daniel Sohn & Richard Guo
* dsohn3, rguo7
* dsohn3@jhu.edu, rguo7@jhu.edu
* 601.220
* 10/16/17
* MIDTERM PROJECT
*/
//TODO: Check right color or else throw out image
//TODO: check if file exists I ran on bad name by accident and got seg fault
//TODO: are u getting rid of comments?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmIO.h"
#include "structHeader.h"
#define MAX_WORD 255

/**
* Outputs an error message
* @param fp file pointer.
* @param fileName Name of the file trying to be opened.
* @return void
*/
void error(FILE *fp, char* fileName) {
    printf("Error:ppmIO - failed to open \"%s\" for reading\n", fileName);
    ///clolse file if pointer isn't NULL
    if (fp != NULL) {
      fclose(fp);
    }
}

/**
* Checks the current line to see if there is a comment
* @param fp File to be checked for comments
* @return void
*/
void checkComments(FILE *fp) {
  char check = getc(fp);
  
  while(check == '#') {
    while (getc(fp) != '\n');
    check = getc(fp);
  }
  
  ungetc(check, fp);
}


/**
* Reads image file into an image struct
* @fileName name of file to read
* @return A pointer to loaded image
*/
Image* readImage(char* fileName) {
  //Open file stream
  FILE *fp = NULL;
  fp = fopen(fileName, "r");

  if(fp == NULL) {
    error(fp, fileName);
    return NULL;
  }
  //Pointer to opened image
  Image* image = malloc(sizeof(Image));
  //Checks to see if right filetype
  printf("Reading from %s...\n", fileName);

  char fileType[MAX_WORD];

  checkComments(fp);

  //If can't obtain file type, show error.
  if (fscanf(fp, "%s \n", fileType) == 0) {
    error(fp,fileName);
    return NULL;
  }
  //If wrong filetype, show error.
  if (strcmp(fileType, "P6") != 0) {
    error(fp,fileName);
    return NULL;
  }

  //Moves fscanf pointer past comments
  checkComments(fp);

  //A pointer that points to an individual pixel
  char* onePixel = malloc(sizeof(char) * 3);
  //Finds image data
  fscanf(fp, "%u %u \n", &(image->cols), &(image->rows));

  checkComments(fp);

  fscanf(fp, "%u \n", &(image->color));

  //Pointer that will point to a collection of all the pixels
  Pixel* pixelData = malloc(image->cols * image->rows * sizeof(Pixel));

  int ctr = 0;
  //gets all pixels in image
  for (unsigned int i = 0; i < image->rows; i++) {
    for (unsigned int j = 0; j < image->cols; j++) {
      fread(onePixel, 1, 3, fp);

      (pixelData + ctr)->r = *(onePixel);
      (pixelData + ctr)->g = *(onePixel + 1);
      (pixelData + ctr)->b = *(onePixel + 2);
      ctr ++;
    }
  }
  //Sets the data pointer for image
  image->data = pixelData;
  //free the temp pixel pointer used
  free(onePixel);
  fclose(fp);
  return image;
}

/**
* Saves an image to a ppm file
* @param filename name of desired file
* @param image pointer to image to be saved
* @return void
*/
void saveImage(char* filename, Image* image) {

  FILE* fp = fopen(filename, "wb");

  printf("Writing to \"%s\"...\n", filename);

  //if no image loaded, show error
  if (image == NULL) {
    printf("Error:ppmIO - failed to write image to \"%s\"\n", filename);
    return;
  }
  //adds comment to image
  fprintf(fp, "P6\n#Made in my project \n%d %d\n%d\n", image->cols, image->rows, image->color);
  //write image
  fwrite(image->data, 3 * image->cols, image->rows, fp);
  fclose(fp);
}
