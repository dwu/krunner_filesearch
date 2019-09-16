# Baloo File Search KRunner

## Install dependencies (example: Kubuntu)

```bash
sudo apt install cmake extra-cmake-modules libkf5runner-dev libkf5kio-dev baloo-kf5-dev
```

## Build instructions

```bash
mkdir build
cd build

cmake ../${_srcname}-${pkgver} \
    -DCMAKE_INSTALL_PREFIX=$(kf5-config --prefix) \
    -DQT_PLUGIN_INSTALL_DIR=$(kf5-config --qt-plugins) \
    -DCMAKE_BUILD_TYPE=Release

make
make install
```
