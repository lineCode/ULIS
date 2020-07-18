//! [Usage]
    FColor rgba_color( Format_RGBA8, { 255, 0, 0, 255 } ); // Red color in format RGBA8
    uint8 R8 = rgb_color.R8(); // Ok, legal
    float RF = rgb_color.RF(); // No, illegal: doesn't match the format type.

    FColor bgr_color( Format_BGR8, { 255, 0, 0 } ); // Blue color in format BGR8
    uint8 B8 = rgb_color.B8(); // Ok, cool.
    uint8 A8 = rgb_color.A8(); // Ok, safe to use even if the format doesn't have alpha, the value defaults to the type maximum.
    uint8 K = rgb_color.Key8(); // No, illegal: accessing through another model that has more samples lead to buffer out of bounds access.
    uint8 Hue = rgb_color.Hue8(); // Ok, legal because accessing through another model with the same number of components, but the resulting value is meaningless ( this is equivalent to R8 here ).
    uint8 Hue = rgb_color.LightnessF(); // No, illegal: bad type, and meaningless resulting value in non matching models.
//! [Usage]
