#include "histogram/histogram.h"

#include "ppm/ppm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


struct rgb {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

static void print_hist(int *histogram) {
    for(int i = 0; i < 255; i++) {
        printf("%d: ", i);
        for(int j = 0; j < histogram[i]; j += 40) {
            printf("#");
        }
        printf("\n");
    }
}

void histogram_equalize(const char *filename) {

    FILE *original_image = fopen(filename, "rb");
    int cmax = ppm_get_max_color_value(filename) + 1;   // number of colors
    int pmax = 0;                                       // number of pixels
    int histogram[256] = {0};
    int HS = 0;                 // values from the histogram pile up here
    int HM = 0;                 // average value of histogram
    int Lc;                     // left part of the interval
    int Rc;                     // right part of the interval
    int r = 0;                  // shows how many times HS > HM
    uint8_t N[256] = {0};       // the new colors for the equalized histogram
    int eq_hist[256] = {0};


    // 1. Fill the histogram
    fseek(original_image, 16, SEEK_SET);
    for(struct rgb c; fread(&c, 3, 1, original_image) == 1; ) {
        pmax++;     // count each pixel
        histogram[c.red]++;
    }
    if(ferror(original_image)) {
        puts("Error occurred!");
    }
    HM = pmax / cmax;   // calculate the average value of the histogram
    //print_hist(histogram);

    // 2. Equalize the histogram
    for(int c = 0; c < cmax; c++) {
        Lc = r;
        HS += histogram[c];
        r = HS / HM;
        Rc = r;
        N[c] = (Lc + Rc) / 2;   // calculate what the new color will be
        eq_hist[N[c]] = histogram[c];
    }
    //print_hist(eq_hist);

    // 3. Create the new image
    FILE *equalized_image = fopen("equalized.ppm", "wb+");
    rewind(original_image);

    // Copy the original image into a new file
    int c;
    while ((c = getc(original_image)) != EOF) {
        putc(c, equalized_image);
    }

    // Change all the colors the the newly calculated ones
    fseek(original_image, 16, SEEK_SET);
    fseek(equalized_image, 16, SEEK_SET);
    for(struct rgb c; fread(&c, 3, 1, original_image) == 1; ) {
        // create the new color for the current pixel
        struct rgb new_color = { N[c.red], N[c.green], N[c.blue] };
        fwrite(&new_color, sizeof(struct rgb), 1, equalized_image);
    }

    fclose(original_image);
    fclose(equalized_image);
}
