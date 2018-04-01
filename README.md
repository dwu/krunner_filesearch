# Baloo File Search KRunner

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
