#include "histogram/histogram.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    if(argc < 2) {
        puts("Invalid ppm image!");
        return EXIT_FAILURE;
    }

    histogram_equalize(argv[1]);
  
	return EXIT_SUCCESS;
}
