## ethminer-nr

What is ethminer-nr? 

This is Nerd Ralph's fork of Genoil's ethminer.  I contributed code to Genoil's miner, and after he stopped maintaining it I started my own fork.  I am not supporting CUDA or Windows, so while they may continue to work, I only test on Linux with OpenCL (AMD).

### Usage

ethminer is a command line program. This means you launch it either from a Windows command prompt or Linux console, or create shortcuts to predefined command lines using a Linux Bash script or Windows batch/cmd file.
for a full list of available command, please run 

```
ethminer --help
```

### F.A.Q

4. Can I still mine ETH with my 2GB GPU?
Not since the ethereum DAG exceeded 2GB.  Other ethash coins with a smaller
DAG like expanse can still be mined.

5. Can I buy a private kernel from you that hashes faster?
No, but I will consider custom development opportunities.


### Building on Windows

- download or clone this repository
- download and install Visual Studio 12 2013 and CMake
- run [getstuff.bat](extdep/getstuff.bat) in [cpp-ethereum/extdep](extdep) 
- open a command prompt and navigate to cpp-ethereum directory

``` 
mkdir build 
cd build
cmake -DBUNDLE=cudaminer -G "Visual Studio 12 2013 Win64" ..
```

- if you don't want/need CUDA support, use "miner" instead of "cudaminer". This will only compile OpenCL support
- to speed up compilation a bit, you can add -DCOMPUTE=xx , where x is your CUDA GPU Compute version * 10. i.e -DCOMPUTE=52 for a GTX970.  
- you may disable stratum support by adding -DETH_STRATUM=0
- When CMake completes without errors, opn ethereum.sln created in the build directory in Visual Studio
- Set "ethminer" as startup project by right-clicking on it in the project pane
- Build. Run

### Building on Ubuntu

Ubuntu 14.04. OpenCL only (for AMD cards)

```bash
sudo apt-get install software-properties-common -y 
sudo add-apt-repository -y ppa:ethereum/ethereum
sudo apt-get update
sudo apt-get install git cmake libleveldb-dev libjsoncpp-dev libboost-all-dev ocl-icd-libopencl1 opencl-headers build-essential -y
git clone https://github.com/Genoil/cpp-ethereum/
cd cpp-ethereum/
mkdir build
cd build
cmake -DBUNDLE=miner ..
make
```

You can then find the executable in the ethminer subfolder

Ubuntu 14.04. OpenCL + CUDA (for NVIDIA cards)

```bash
wget http://developer.download.nvidia.com/compute/cuda/repos/ubuntu1404/x86_64/cuda-repo-ubuntu1404_7.5-18_amd64.deb
sudo dpkg -i cuda-repo-ubuntu1404_7.5-18_amd64.deb
sudo apt-get -y install software-properties-common
sudo add-apt-repository -y ppa:ethereum/ethereum
sudo apt-get update
sudo apt-get install git cmake libleveldb-dev libjsoncpp-dev libjson-rpc-cpp-dev libboost-all-dev libgmp-dev libreadline-dev libcurl4-gnutls-dev ocl-icd-libopencl1 opencl-headers mesa-common-dev libmicrohttpd-dev build-essential cuda -y
git clone https://github.com/Genoil/cpp-ethereum/
cd cpp-ethereum/
mkdir build
cd build
cmake -DBUNDLE=cudaminer ..
make
```

You can then find the executable in the ethminer subfolder
