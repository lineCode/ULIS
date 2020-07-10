//////////////////////////////////////////////////////
// Current
int main()
{
    ul3::FBlock drawing( 64, 64, ULIS3_FORMAT_RGBA8 );
    ul3::FBlock overlay( 64, 64, ULIS3_FORMAT_RGBA8 );
    ul3::Fill( drawing, ul3::FColor::RGB( 255, 0, 0 ) );
    ul3::Fill( overlay, ul3::FColor::RGB( 0, 0, 255 ) );
    ul3::AlphaBlend( overlay, drawing, overlay.Rect(), ul3::FVec2F( 0, 0 ), ULIS3_AA, ul3::BM_NORMAL, 1.f );

    return  0;
}

pros:
    Follows UE4 coding style
    Easy enough

cons:
    Inconsistent mix of named literal values through macros mixed with all caps enums

//////////////////////////////////////////////////////
// Full
int main()
{
    ul3::FBlock drawing( 64, 64, ul3::eFormat::kRGBA8 );
    ul3::FBlock overlay( 64, 64, ul3::eFormat::kRGBA8 );
    ul3::Fill( drawing, ul3::FColor::RGB( 255, 0, 0 ) );
    ul3::Fill( overlay, ul3::FColor::RGB( 0, 0, 255 ) );
    ul3::AlphaBlendAA( overlay, drawing, overlay.Rect(), ul3::FVec2F( 0, 0 ), ul3::eBlendingMode::kNormal, 1.f );

    return  0;
}

pros:
    Follows UE4 coding style
    Fully qualified names

cons:
    Harder to write, long namespaces
    Feels more tedious


//////////////////////////////////////////////////////
// std-like
int main()
{
    ul3::block drawing( 64, 64, ul3::format::rgba8 );
    ul3::block overlay( 64, 64, ul3::format::rgba8 );
    ul3::function::fill( drawing, ul3::color::rgb( 255, 0, 0 ) );
    ul3::function::fill( overlay, ul3::color::rgb( 0, 0, 255 ) );
    ul3::function::alpha_blend_aa( overlay, drawing, overlay.rect(), ul3::math::vec2< float >( 0, 0 ), ul3::blend::mode::normal, 1.f );

    return  0;
}

pros:
    Follows standard library or boost coding style
    Fully qualified names

cons:
    No prefix for classes or enums
    Feels very long and tedious

//////////////////////////////////////////////////////
// Sweet
int main()
{
    ul3::FBlock drawing( 64, 64, ul3::Format_RGBA8 );
    ul3::FBlock overlay( 64, 64, ul3::Format_RGBA8 );
    ul3::Fill( drawing, ul3::FColor::RGB( 255, 0, 0 ) );
    ul3::Fill( overlay, ul3::FColor::RGB( 0, 0, 255 ) );
    ul3::AlphaBlendAA( overlay, drawing, overlay.Rect(), ul3::FVec2F( 0, 0 ), ul3::Blend_Normal, 1.f );

    return  0;
}

pros:
    Follows UE4 coding style
    Feels easy to write

cons:
    no prefix for enum values

//////////////////////////////////////////////////////
// Qt-Like
int main()
{
    UBlock drawing( 64, 64, ul3::Format_RGBA8 );
    UBlock overlay( 64, 64, ul3::Format_RGBA8 );
    UPainter painter( ul3::Format_RGBA8 );
    painter.Fill( drawing, UColor::RGB( 255, 0, 0 ) );
    painter.Fill( overlay, UColor::RGB( 255, 0, 0 ) );
    painter.AlphaBlendAA( overlay, drawing, overlay.Rect(), UPointF( 0, 0 ), ul3::Blend_Normal, 1.f );

    return  0;
}

pros:
    Follows Qt coding style
    Feels easy to write

cons:
    A bit convoluted ( no orphan functions in library scope )
    U prefix conflicts with UE4 coding style

//////////////////////////////////////////////////////
// C++ OpenCV-like
int main()
{
    ul3::Block drawing( 64, 64, ul3::FORMAT_RGBA8 );
    ul3::Block overlay( 64, 64, ul3::FORMAT_RGBA8 );
    ul3::Fill( drawing, ul3::Color::RGB( 255, 0, 0 ) );
    ul3::Fill( overlay, ul3::Color::RGB( 0, 0, 255 ) );
    ul3::AlphaBlendAA( overlay, drawing, overlay.Rect(), ul3::Vec2F( 0, 0 ), ul3::BM_NORMAL, 1.f );

    return  0;
}

pros:
    No prefix for classes or enums
    Feels easy to write

cons:
    All caps enum values

