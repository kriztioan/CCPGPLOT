# CCPGPLOT Demo

## Description

`CCPGPLOT` is a C++ library build around [PGPLOT](https://sites.astro.caltech.edu/~tjp/pgplot/) for use with interactive devices. The library supports `zoom`, `plot`-switching, and saving to `Postscript`. `demo` is a program for showing how to use `CCPGPLOT` in new code and demonstrate (some of) its capabilities.

## Usage

The `CCPGPLOT` demo program is created by invoking `make`.

```shell
make
```

This will result in a binary called `demo` that can be invoked with:"

```shell
./demo
```

## Keys

`CCPGPLOT` recognizes the following keys:

| key | function |
----|------------|
|`+`|increase window size|
|`-`|decrease window size|
|`.`|next plot, loops around|
|`,`|previous plot, loops around|
|`A`|set cursor position, move and press `A` again to zoom|
|`D`|restore zoom level|
|`q`|quit|
|`s`|save current plot to Postscript|
|`X`|next plot, exits after last|

The `left`, `middle`, and `right` mouse buttons are mapped to `A`, `D`, and `X`, respectively.

## Notes

1. To build `demo` using `make`, `libccpgplot.a` needs to be present in the demo parent directory.
2. `demo` uses the default `/XWINDOW`-device.

## BSD-3 License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
