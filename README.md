# `write_kicad`

> [!WARNING]
> This is still in the early alpha stages, the
> KiCad files may be sub-optimal, or require an obscene number of devices.

`write_kicad` is a [Yosys] plugin to dump the netlist as a [KiCad] eeschema schematic file for physical layout. It was original bundled into the [discretize] project but is possibly useful in general so it was broken out into it's own repo.

## Configuring and Building

The following steps describe how to build discretize, it should be consistent for Linux, macOS, and Windows, but macOS and Windows remain untested.

**NOTE:** The minimum C++ standard to build discretize is C++17.

### Prerequisites

To build discretize, ensure you have the following build time dependencies:
 * git
 * meson
 * ninja
 * g++ >= 11 or clang++ >= 11
 * python >= 3.9
 * yosys >= 0.28


### Configuring

You can build discretize with the default options, all of which can be found in [`meson_options.txt`](meson_options.txt). You can change these by specifying `-D<OPTION_NAME>=<VALUE>` at initial meson invocation time, or with `meson configure` in the build directory post initial configure.

To change the install prefix, which is `/usr/local` by default ensure to pass `--prefix <PREFIX>` when running meson for the first time.

In either case, simply running `meson build` from the root of the repository will be sufficient and place all of the build files in the `build` subdirectory.

### Building

Once you have configured discretize appropriately, to simply build and install simply run the following:

```
$ ninja -C build
$ ninja -C build test # Optional: Run Tests
$ ninja -C build install
```

This will build and install discretize into the default prefix which is `/usr/local`, to change that see the configuration steps above.

### Notes to Package Maintainers

If you are building discretize for inclusion in a distributions package system then ensure to set `DESTDIR` prior to running meson install.

There is also a `bugreport_url` configuration option that is set to this repositories issues tracker by default, it is recommended to change it to your distributions bug tracking page.

## License

Discretize is licensed under the [BSD-3-Clause](https://spdx.org/licenses/BSD-3-Clause.html), the full text of which can be found in the [LICENSE](LICENSE) file.


[Yosys]: https://github.com/YosysHQ/yosys
[KiCad]: https://www.kicad.org/

[discretize]: https://github.com/lethalbit/discretize
