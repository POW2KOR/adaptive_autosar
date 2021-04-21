# Configuration file format for the Measurement daemon

This document describes the configuration file format for the Measurement daemon.


## Configuration file location and naming convention

All configuration files should be stored in a single directory. The Measurement daemon should parse all files in this
directory and extract the configuration parameters from them. Each configuration file represents a single process under
observation.

Files should be named as `<PROCESS NAME>.ini`, where `<PROCESS NAME>` is the name of the executable file under
observation.


## Configuration file format

Measurement configuration for an executable file is stored in `.ini` configuration file format. Detailed description of
configuration parameters is below.

Each configuration file should contain the `COMMON` section containing parser-related parameters, and other sections
named as variables under observation.


### Common section description

The `COMMON` section should contain the following parameters:
* `version`: version of the configuration layout used in `<MAJOR>.<MINOR>` format


### Variables sections description

Each section is responsible for a single variable. If it is needed to
read data from a pointer, or read a complex structure, containing a pointer to another object, then more than one
memory read operations are required, and they should be described as two different variables in the configuration file.

A variable-related configuration section should contain the following parameters:
* `address`: address of the variable under observation in the target process.
* `size`: size of the variable under observation in bytes.
* `indirectionLevel`: Amount of indirect reads which are required to access the variable. For instance, if reading of a
static variable is needed, the indirection level is 0, because the variable's address contains the value itself. If
reading of data should be made from a pointer, then indirection level is 1, because it is needed to read the address
stored in the pointer, and then use this address to read the variable.
* `offset`: offset of the variable under observation against the `address` parameter. Should be a single variable or a
list of variables with length of `indirectionLevel` + 1.


## Examples

Here is an example of a C source file, containing different variables, and an example of a configuration file for the
Measurement daemon.


### Excerpt of source code

```c
static uint8_t var_u8;
uint16_t var_u16;

char var_c_string[] = "Hello world";

int32_t** var_pp_int32;

#pragma pack(push,1)
struct sample_st {
    int16_t field_a;
    char* field_b;
    float field_c;
};
#pragma pack(pop)

struct sample_st var_sample_st;
```

For better understanding please note that here we refer 64-bit architecture. In case 32-bit architecture is used,
pointer sizes (as well as sizes of structures that contain pointers) must be adjusted accordingly.


### Sample configuration file

Please refer all the code sections as if they were combined into a single file. In this example they are separated for
reader's convenience.

```
[COMMON]
version=0.1
```

This is the common section, which keeps the configuration format version.

```
[var_u8]
address=0x11111100
size=1
indirectionLevel=0
offset=0
```

This section describes how to read the `var_u8` variable. Here we mention it's `address` obtained from the binary,
`size` is `1` because `sizeof(uint8_t) == 1`, the `indirectionLevel` is `0` because we read just a variable, and
`offset` is `0` because variable's data is located directly at the given address.

```
[var_u16]
address=0x11111200
size=2
indirectionLevel=0
offset=0
```

This section describes how to read the `var_u16` variable. Here we mention it's `address` obtained from the binary,
`size` is `2` because `sizeof(int16_t) == 1`, the `indirectionLevel` is `0` because we read just a variable, and
`offset` is `0` because variable's data is located directly at the given address.

```
[var_c_string]
address=0x11111300
size=12
indirectionLevel=1
offset=0:0
```

This section describes how to read the `var_c_string` variable. Here we mention it's `address` obtained from the binary,
`size` is `12` because the length of the string is 12 (including the null-terminator at the end). The `indirectionLevel`
is `1` because `var_c_string` is actually a pointer, and what we have is `address` of this pointer in memory. So it is
needed to read `ptr_t` bytes (platform- and architecture-dependent) from the given address, interpret these bytes as
another address and then read 12 bytes (the actual string length + null-terminator) from there. The `offset` is `0:0`
because both times we don't need to add any offsets to the addresses.

```
[var_pp_int32]
address=0x11111400
size=4
indirectionLevel=2
offset=0:0:0
```

This section describes how to read the `var_pp_int32` variable. Here we mention it's `address` obtained from the binary,
`size` is `4` because `sizeof(int32_t) == 4`. The `indirectionLevel` is `2` because we need to access the pointer to a
pointer and make 2 address reads in order to finally access the data. Offsets are all zeros, because we get addresses
without any need to modify them.

```
[var_sample_st]
address=0x11111500
size=14
indirectionLevel=0
offset=0
```

This section describes how to read the `var_sample_st` variable. The important thing here is that we read the raw
structure data, and here we have no way to access data pointed by fields in the structure. So, `address` is obtained
from the binary, `size` is `14` in this example because the structure in the sample is packed and it's `sizeof` is 14.
The `indirectionLevel` is `0` because we read raw structure bytes, and `offset` is `0` for the same reason.

```
[var_sample_st_char_array]
address=0x11111500
size=30
indirectionLevel=1
offset=2:0
```

This section describes how to read data pointed by a a field in the `var_sample_st` variable. The procedure s similar
to how pointers are handled, the only difference is that it is needed to know the length of the pointed data, and the
offset of the pointer in the given structure. So, in this example `address` is actually the address of the
`var_sample_st` variable. `offset` is offset of the `field_b` field in this structure which is 2 (it is equal to the
value of macro `offsetof(sample_st, field_b`), and offset from the address stored in the `field_b` field which is 0, so
finally it is `2:0`. The `size` parameter is `30` because the target `char` array is assumed to have the length of 30,
and the `indirectionLevel` is `1` because `field_b` is a pointer.

```
[var_sample_st_float]
address=0x11111500
size=4
indirectionLevel=0
offset=10
```

This section describes how to read a single field in a structure. Here the `field_c` from `sample_st` structure is read.
The `address` is the address of the `var_sample_st` variable which contains the whole structure. The `offset` parameter
is `10` because `offsetof(struct_st, field_c)` is 10, `size` is `4` because `sizeof(float)` is 4, and `indirectionLevel`
is `0` because no pointer dereferencing is required.
