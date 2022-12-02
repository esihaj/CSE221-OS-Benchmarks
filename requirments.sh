#!/bin/bash
sudo apt update
sudo apt install -y htop git curl cpufrequtils curl g++ gcc tuned
sudo service tuned start
sudo service tuned status
sudo tuned-adm profile latency-performance
cpufreq-info | head -n 10
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

#taskset -c 5
