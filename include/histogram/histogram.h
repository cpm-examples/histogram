#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <stdint.h>


/**
 * @brief Equalize the histogram of the specified ppm image
 * 
 * @param filename the name of the ppm image
 */
void histogram_equalize(const char *filename);


#endif	// HISTOGRAM_H
