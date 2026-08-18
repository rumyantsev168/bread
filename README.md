# bread

**Bread** (stands for *byte read*) is a simple CLI tool, that can print a given file in bytes!

## Build

To get the executable file, use the build script or check the Releases tab for latest release.

## Usage

Run `bread --help`. You will see this message:

```txt
Usage: bread <filename> [--base=N] [--bytes_per_line=N] [--bytes_count_max=N] [--verbose=T/F]
Options:
  --base               How to represent the bytes. Default is 16. Possible values are:
                         2 - binary    8 - octal   10 - decimal    16 - hexadecimal
  --bytes_per_line     How many bytes should each output line display. Default is 32.
  --bytes_count_max    If specified, outputs first N bytes of a given file. Default is none.
  --verbose            Whether to print file name and total printed bytes count. Default is true.
```

The command options are:

1. `--base`\
    Can be one of `2`, `8`, `10` or `16`. Each byte will be printed in the specified base.
2. `--bytes_per_line`\
    Must be a number. Defines how many bytes should one output line contain. Default is 32.
3. `--bytes_count_max`\
    Must be a number. Limits the output to the first N bytes of the file. If not specified, the entire file is printed.
4. `--verbose`\
    True by default or if set to one of `true`/`t`/`yes`/`y`. Otherwise false.\
    If `true`: Prints a header showing the filename and whether it's printing all bytes or a specific count, plus a footer with the total byte count.\
    If `false`: Outputs only the hex-like values without additional text.

## Examples

Print the first 16 bytes of a binary file in hexadecimal.

```sh
bread file.bin --bytes_count_max=16
```

Print a file in binary format with 8 bytes per line.

```sh
bread data.bin --base=2 --bytes_per_line=8 --verbose=false
```

Write the hexadecimal bytes of a file into another file.

```sh
bread file.dat --verbose=false > content.txt
```
