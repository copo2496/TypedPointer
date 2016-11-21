# TypedPointer

In 64bit Linux, the pointer type (void *) only actually uses 48 bits, leaving the left most 16 bits as 0's. Some valuable data can be stored in these 16 bits, so this repo is mostly just my playing around with the possibilities of that. y