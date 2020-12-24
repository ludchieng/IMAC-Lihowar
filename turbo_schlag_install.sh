cd ~/Documents
sudo apt update

sudo apt install g++ git cmake \
libsdl2-dev libsdl-mixer2-dev \
libglu1-mesa-dev mesa-common-dev mesa-utils \
libglew-dev freeglut3-dev \
doxygen

git clone https://github.com/ludchieng/IMAC-Lihowar
cd IMAC-Lihowar
mkdir build
cd build
cmake ..
make
cd bin
./lihowar config/fullscreen.json
