# Documentation Guidelines

Document every class and every fields of the public APIs. In short, everything in headers that are visible by consumers of the library, so all files under the include directory.  
Sometimes, comments are not that useful, for instance, take this example from the TVec2 class:

    /*! The x component of the 2D vector. */
    T x;
    /*! The y component of the 2D vector. */
    T y;

This looks a bit silly indeed, but members of other classes are not always that obvious, and it is more consistent to document everything.

