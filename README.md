SAM-Bip
===

*Forked from [vidarh/SAM](https://github.com/vidarh/SAM).*

Bip?
---
See [this playlist](https://youtube.com/playlist?list=PLQHoGwsHiDYOrRAveweKuqMpATbGx7dnq).

Changes
---
Changes from the original are:
- Removed debug code
- Removed setting of variables
- Forced requiring libsdl
- Hard-set variables:
```c
unsigned char speed = 62;
unsigned char pitch = 32;
unsigned char mouth = 216;
unsigned char throat = 216;
```
- Output binary is `sam-bip`
- Make target is `build`
- Removed `package` make target

License
---
This code is not released under any licence, following the precedent of the original.
