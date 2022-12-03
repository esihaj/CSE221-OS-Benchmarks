#!/bin/bash
sudo apt update
sudo apt install -y htop git curl cpufrequtils wget curl g++ gcc tuned msr-tools zlib1g-dev cmake



echo "setting up Hdr Histograms"
cd ../
wget "https://github.com/HdrHistogram/HdrHistogram_c/archive/refs/tags/0.11.6.zip"
unzip 0.11.6.zip
cd HdrHistogram_c-0.11.6
mkdir build && cd build
cmake ..
make -j20
sudo make install
sudo ldconfig #https://stackoverflow.com/a/42047062/730033
echo "LD_LIBRARY_PATH: ["
echo $LD_LIBRARY_PATH
echo "]"
echo "if it is empty run `LD_LIBRARY_PATH=/usr/local/lib`"


#https://github.com/redhat-performance/tuned/
sudo service tuned start
sudo service tuned status
sudo tuned-adm profile latency-performance
sudo modprobe msr
sudo ./turbo-boost.sh disable
cpufreq-info | head -n 10





sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

#taskset -c 5
#https://www.glennklockwood.com/hpc-howtos/process-affinity.html#31-the-linux-portable-way-taskset
