# Installing Nvidia Cuda Toolkit 10.0
[Step by step instruction: Source](https://www.pugetsystems.com/labs/hpc/How-To-Install-CUDA-10-together-with-9-2-on-Ubuntu-18-04-with-support-for-NVIDIA-20XX-Turing-GPUs-1236/)

- Install pre-requisites:
`sudo apt-get install build-essential dkms`
`sudo apt-get install freeglut3 freeglut3-dev libxi-dev libxmu-dev`

<br>

- Now download the required file according to your system configuration, `cuda_10.0.130_410.48_linux.run` from [Nvidia site](https://developer.nvidia.com/cuda-downloads)

<br>

**Mine is:**

| Device | Config |
| ------ | ----------- |
| GPU   | NVIDIA Corporation GM108M GeForce 940MX <br> (Test Command: lspci &#124; grep NVIDIA) |
| OS | Ubuntu 18.04 LTS |
| CPU    | Intel Corporation Xeon E3-1200 v6/7th Gen Core Processor <br> (Same `lspci` command can be used to list it) |

**So I chose:**


| Device | Config |
| ------ | ----------- |
| OS   | Linux |
| Architecture | x86_64 |
| Distribution    | Ubuntu |
| Version    | 18.04 |
| Installer Type    | runfile (local) |

<br>

- Assuming the file is in Downloads
`cd ~/Downloads`
`sudo sh cuda_10.0.130_410.48_linux.run`

<b>

- Reach the end of EULA and answer al the questions. (You can leave default value also)

**Logs after cuda installation:**

_\===========
= Summary =
===========_
_Driver:   Installed
Toolkit:  Installed in /usr/local/cuda-10.0
Samples:  Installed in /home/********

_Please make sure that
 \-   PATH includes /usr/local/cuda-10.0/bin
 \-   LD_LIBRARY_PATH includes /usr/local/cuda-10.0/lib64, or, add /usr/local/cuda-10.0/lib64 to /etc/ld.so.conf and run ldconfig as root_

_To uninstall the CUDA Toolkit, run the uninstall script in /usr/local/cuda-10.0/bin
To uninstall the NVIDIA Driver, run nvidia-uninstall_

_Please see CUDA_Installation_Guide_Linux.pdf in /usr/local/cuda-10.0/doc/pdf for detailed information on setting up CUDA._

- Default samples location:
`~/NVIDIA_CUDA-10.0_Samples`
