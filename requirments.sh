#!/bin/bash
sudo apt update
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
sudo apt install -y htop git curl cpufrequtils curl g++ gcc