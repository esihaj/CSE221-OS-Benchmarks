#!/bin/bash
set -e

GREEN='\033[1;32m\n\n\n'
NC='\033[0m' # No Color
CURRENT_DIR=$(pwd)
echo -e "${GREEN}current dir: $CURRENT_DIR ${NC}"

sudo apt update
sudo apt install -y htop git curl cpufrequtils wget curl g++ gcc tuned msr-tools zlib1g-dev cmake
echo -e "${GREEN}setting up Hdr Histograms${NC}"
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
echo "${GREEN}if it is empty run `LD_LIBRARY_PATH=/usr/local/lib`${NC}"


echo -e "${GREEN}setting up C++ Boost library${NC}"
cd $CURRENT_DIR
cd ../
wget "https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.gz"
tar -xf boost_1_80_0.tar.gz


cd $CURRENT_DIR
#disable hyperthreading
echo -n "${GREEN}hyper threading:${NC}"
sudo echo off > /sys/devices/system/cpu/smt/control
cat /sys/devices/system/cpu/smt/active
echo -e "${GREEN} tuned latency-performance profile${NC}"
#https://github.com/redhat-performance/tuned/
sudo service tuned start
sudo service tuned status
sudo tuned-adm profile latency-performance
sudo modprobe msr
echo -e "${GREEN}disable turbo boost${NC}"
sudo ./turbo-boost.sh disable
cpufreq-info | head -n 10



echo -e "${GREEN} zsh${NC}"

sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

#taskset -c 5
#https://www.glennklockwood.com/hpc-howtos/process-affinity.html#31-the-linux-portable-way-taskset
