/* Daniel Sohn & Richard Guo
*	dsohn3, rguo7
*	dsohn3@jhu.edu, rguo7@jhu.edu
*	601.220
*	10/16/17
*	MIDTERM PROJECT
*/

#ifndef PPM_IO_H
#define PPM_IO_H

#include <stdio.h>
#include <stdlib.h>
#include "menuUtil.h"
#include "ppmIO.h"
#include "structHeader.h"

/**
* Outputs an error message
* @param fp file pointer.
* @param fileName Name of the file trying to be opened.
* @return void
*/
void error();

/**
* Checks the current line to see if there is a comment
* @param fp File to be checked for comments
* @return void
*/
void checkComment(FILE *fp);

/**
* Reads image file into an image struct
* @fileName name of file to read
* @return A pointer to loaded image
*/
Image* readImage(char* fileName);

/**
* Saves an image to a ppm file
* @param filename name of desired file
* @param image pointer to image to be saved
* @return void
*/
void saveImage(char* filename, Image* image);

#endif
