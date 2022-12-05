#include <iostream>
#include "hdr.h"
using namespace std;

int main(int argc, char *argv[])
{
  vector<double> measurements = {11, 7, 7, 6, 6, 6, 6, 11, 9, 8, 6, 6, 7, 6, 7, 8, 7, 8, 6, 9, 6, 6, 7, 7, 7, 7, 6, 6, 7, 6, 7, 10, 6, 6, 6, 6, 6, 6, 8, 8, 6, 6, 10, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10, 6, 6, 6, 6, 7, 7, 7, 7, 6, 8, 7, 9, 7, 7, 6, 6, 7, 6, 7, 6, 6, 6, 8, 9, 6, 6, 6, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 6};
  print_hdr(measurements, "sample.hdr");
}
