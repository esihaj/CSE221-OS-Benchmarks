#!/bin/bash
sudo apt update
sudo apt install -y htop git curl cpufrequtils curl g++ gcc
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
