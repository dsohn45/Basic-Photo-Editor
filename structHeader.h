/* Daniel Sohn & Richard Guo
*	dsohn3, rguo7
*	dsohn3@jhu.edu, rguo7@jhu.edu
*	601.220
*	10/16/17
*	MIDTERM PROJECT
*/
#ifndef STRUCT_HEADER_H
#define STRUCT_HEADER_H

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Pixel;

typedef struct {
  Pixel* data;
  unsigned int rows;
  unsigned int cols;
  unsigned int color;
} Image;


#endif
