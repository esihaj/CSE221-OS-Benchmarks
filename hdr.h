#ifndef HDR_HIST_H
#define HDR_HIST_H
#include <vector>
#include <cstdio>
#include <iostream>
#include <hdr/hdr_histogram.h>

void print_hdr(std::vector<double> &measurements, std::string filename)
{
    struct hdr_histogram *histogram;

    // Initialise the histogram
    hdr_init(
        1,                   // Minimum value
        INT64_C(3600000000), // Maximum value
        3,                   // Number of significant figures
        &histogram);         // Pointer to initialise

    for (const auto m : measurements)
    {
        hdr_record_value(
            histogram,
            m);
    }

    FILE *output = fopen(filename.c_str(), "w+");
    if (output == NULL)
        std::cerr << "could not open output file to store Hdr Histogram [" << filename << "]\n";
    else
    {
        hdr_percentiles_print(histogram,
                              output,   // File to write to
                              5,        // Granularity of printed values
                              1.0,      // Multiplier for results
                              CLASSIC); // Format CLASSIC/CSV supported.
    }


    hdr_percentiles_print(histogram,
                          stdout,   // File to write to
                          5,        // Granularity of printed values
                          1.0,      // Multiplier for results
                          CLASSIC); // Format CLASSIC/CSV supported.
}

#endif