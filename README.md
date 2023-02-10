# Histogram

A C library for working with `ppm` image histograms

## Installation

```sh
cpm install histogram
```

```cmake
add_subdirectory(lib/histogram)

target_include_directories(<target>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/lib/histogram/include
)

target_link_libraries(<target>
	PRIVATE
		histogram
)
```

## Example usage

```c
// main.cpp

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
```
