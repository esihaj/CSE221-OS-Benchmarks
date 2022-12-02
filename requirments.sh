#!/bin/bash
sudo apt update
sudo apt install -y htop git curl cpufrequtils curl g++ gcc tuned msr-tools
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
