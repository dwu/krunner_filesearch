# Baloo File Search KRunner

## Install dependencies

- Kubuntu: `sudo apt install cmake extra-cmake-modules libkf5runner-dev libkf5kio-dev baloo-kf5-dev`
- Solus Plasma: `sudo eopkg it kio-devel baloo-devel krunner-devel cmake extra-cmake-modules ki18n-devel`

## Build instructions

```bash
mkdir build
cd build

cmake .. \
    -DCMAKE_INSTALL_PREFIX=$(kf5-config --prefix) \
    -DKDE_INSTALL_QTPLUGINDIR=$(kf5-config --qt-plugins) \
    -DCMAKE_BUILD_TYPE=Release

make
make install
```
