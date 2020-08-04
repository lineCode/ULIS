# Architecture
ULIS architecture and design principles, *Clément Berthaud*, 2020

## Introduction
The architecture of ULIS does not differ fundamentally from other existing traditional graphic libraries, however it pursues its own philosophy and design principles, which leads to its ease of use and efficiency. We discuss here what choices lead to the current design, and try to explain them. Other libraries are mentioned and sometimes compared with, with their respective drawbacks and advantages, assuming the usage context ULIS targets, which is explained in details later.

In ["An Image Processing Library in Modern C++"](https://hal.archives-ouvertes.fr/hal-02176414/document), *Michaël Roynard*, *Edwin Carlinet* and *Thierry Géraud* provide insight to achieve simplicity and efficiency with generic programming, in the context of an image processing library in modern C++. While I don't agree with everything stated here, and although this resource was encountered after the architecture of ULIS4+ was designed, I recommend reading it, since it is relevant to the topic, and it describes common pitfalls ULIS encountered in the early stages of its design. Some principles discussed in the paper will also be discussed here.

<!--
## Table of Contents
- [0](@ref 0)
    + [0.0](@ref 0.0)
    + [0.1](@ref 0.1)
    + [0.2](@ref 0.2)
- [1](@ref 1)
    + [1.1](@ref 1.1)
    + [1.2](@ref 1.2)
    + [1.3](@ref 1.3)
    + [1.4](@ref 1.4)
-->
