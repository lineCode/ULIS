//! [FRasterImage2D on stack]
    { // Begin local scope
        FRasterImage2D image( 64, 64, eFormat::Format_RGBA8 );
        // Work with your image.
    } // End local scope, image is destroyed and so is the underlying data.
//! [FRasterImage2D on stack]

//! [FRasterImage2D on heap]
    FRasterImage2D* image = new FRasterImage2D( 64, 64, eFormat::Format_RGBA8 );
    // Work with your image.
    delete  image;
//! [FRasterImage2D on heap]

//! [FRasterImage2D X Version]
    FRasterImage2D* image = FRasterImage2D::XMake( 64, 64, eFormat::Format_RGBA8 );
    // Work with your image.
    FRasterImage2D::XDelete( image );
//! [FRasterImage2D X Version]
