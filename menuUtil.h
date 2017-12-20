/* Daniel Sohn & Richard Guo
*	dsohn3, rguo7
*	dsohn3@jhu.edu, rguo7@jhu.edu
*	601.220
*	10/16/17
*	MIDTERM PROJECT
*/
#ifndef MENU_UTIL_H
#define MENU_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmIO.h"
#include "structHeader.h"
#include "imageManip.h"

/**
 * Function to print menu errors.
 */
void menuError();

/**
 * Function to remove line from ppm file.
 */
void removeLine();

/**
 * Function to check whether crop corners are valid.
 *
 * @param img Image being cropped
 * @param uc upper column coordinate
 * @param ur upper row coordinate
 * @param lc lower column coordinate
 * @param lr lower row coordinate
 */
int checkCropCorners(Image* img, int uc, int ur, int lc, int lr);

/**
 * Function to print menu options
 */
void printMenu();

/**
 * Function to run program
 */
void runProgram();

#endif
