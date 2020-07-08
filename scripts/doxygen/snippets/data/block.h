//! [FBlock on stack]
    { // Begin local scope
        ::ul3::FBlock image( 64, 64, FMT_RGBA8 );
        // Work with your image.
    } // End local scope, image is destroyed and so is the underlying data.
//! [FBlock on stack]

//! [FBlock on heap]
    ::ul3::FBlock* image = new ::ul3::FBlock( 64, 64, FMT_RGBA8 );
    // Work with your image.
    delete  image;
//! [FBlock on heap]

//! [FBlock X Version]
    ::ul3::FBlock* image = ::ul3::FBlock::XMake( 64, 64, FMT_RGBA8 );
    // Work with your image.
    ::ul3::FBlock::XDelete( image );
//! [FBlock X Version]
