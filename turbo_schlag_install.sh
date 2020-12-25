# ==================== #
# TURBO SCHLAG INSTALL #
# for Lihowar          #
# ==================== #

# schlag access via:
# wget https://raw.githubusercontent.com/ludchieng/IMAC-Lihowar/main/turbo_schlag_install.sh && sh ./turbo_schlag_install.sh

# schlag install
sudo apt-get -y install g++ cmake \
libsdl2-dev libsdl2-mixer-dev \
libglu1-mesa-dev mesa-common-dev mesa-utils \
libglew-dev freeglut3-dev \
doxygen
cd IMAC-Lihowar
mkdir build
cd build
cmake ..
make

# schlag execute
cd bin
./lihowar config/fullscreen.json
