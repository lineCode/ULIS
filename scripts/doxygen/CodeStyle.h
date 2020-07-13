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
// Fully qualified explicit names with hardcore DLL safety
int main()
{
    ul3::FThreadPool* threadPool = XCreateThreadPool();
    ul3::FHostDeviceInfo* host = XCreateHostDeviceInfo();
    host->Detect();
    ul3::uint32 perfIntent = ::ul3::ePerf::kUseMultithreading | ul3::ePerf::kUseSSE42;
    ul3::FBlock* drawing = XCreateBlock( 64, 64, ul3::eFormat::kRGBA8 );
    ul3::FBlock* overlay = XCreateBlock( 64, 64, ul3::eFormat::kRGBA8 );
    ul3::FColor* red = XCreateColor();
    red->SetRGB( 255, 0, 0 )
    ul3::FColor* blue = XCreateColor();
    red->SetRGB( 0, 0, 255 )
    ul3::Fill( threadPool, ul3::eFlow::kBlocking, host, perfIntent, drawing, red );
    ul3::Fill( threadPool, ul3::eFlow::kBlocking, host, perfIntent, overlay, blue );
    ul3::AlphaBlend( threadPool, ul3::eFlow::kBlocking, host, perfIntent, overlay, drawing, overlay->Rect(), ul3::FVec2F( 0, 0 ), ::ul3::eAntialiasing::kOn, ul3::eBlendingMode::kNormal, 1.f );

    return  0;
}

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
// Fully qualified explicit names with hardcore DLL safety and std-like snake case
int main()
{
    ul3::thread::thread_pool* thread_pool = ul3::thread::create_thread_pool();
    ul3::hardware::host_device_info* host = ul3::hardware::create_host_device_info();
    host->detect();
    ul3::uint32 perf_intent = ::ul3::performances::use_multithreading | ul3::performances::use_sse42;
    ul3::image::block* overlay = ul3::image::create_block( 64, 64, ul3::image::format::RGBA8 );
    ul3::image::block* drawing = ul3::image::create_block( 64, 64, ul3::image::format::RGBA8 );
    ul3::image::color* red = ul3::image::format::create_color();
    red->set_rgb( 255, 0, 0 )
    ul3::image::color* blue = ul3::image::format::create_color();
    blue->set_rgb( 0, 0, 255 )
    ul3::functions::clearfill::fill( thread_pool, ul3::flow::blocking, host, perf_intent, drawing, red );
    ul3::functions::clearfill::fill( thread_pool, ul3::flow::blocking, host, perf_intent, overlay, blue );
    ul3::functions::blend::alpha_blend( thread_pool, ul3::flow::blocking, host, perf_intent, overlay, drawing, overlay->rect(), ul3::math::vec2< float >( 0, 0 ), ul3::image::antialiasing::on, ul3::image::blend_mode::normal, 1.f );

    ul3::image::delete_block( drawing );
    ul3::image::delete_block( overlay );
    ul3::image::delete_color( red );
    ul3::image::delete_color( blue );
    ul3::hardware::delete_host_device_info( host );
    ul3::thread::delete_thread_pool( thread_pool );

    return  0;
}


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
    ul3::FThreadPool threadPool;
    ul3::FHostDeviceInfo host = ul3::FHostDeviceInfo::Detect();
    ul3::uint32 perfIntent = ul3::PERF_MT | ul3::PERF_SSE42;
    ul3::Block drawing( 64, 64, ul3::FORMAT_RGBA8 );
    ul3::Block overlay( 64, 64, ul3::FORMAT_RGBA8 );
    ul3::Fill( threadPool, ul3::FLOW_BLOCKING, host, perfIntennt, drawing, ul3::Color::RGB( 255, 0, 0 ) );
    ul3::Fill( threadPool, ul3::FLOW_BLOCKING, host, perfIntennt, overlay, ul3::Color::RGB( 0, 0, 255 ) );
    ul3::AlphaBlendAA( threadPool, ul3::FLOW_BLOCKING, host, overlay, drawing, overlay.Rect(), ul3::Vec2F( 0, 0 ), ul3::BM_NORMAL, 1.f );

    return  0;
}

pros:
    No prefix for classes or enums
    Feels easy to write

cons:
    All caps enum values

//////////////////////////////////////////////////////
// Potential Goal
#include <ULIS3>
using namespace ::ul3;

int main() {
    ThreadPool pool;
    CommandQueue queue( thread_pool );
    PainterContext painter( Format_RGBA8, command_queue );
    painter.PreDispatch();
    RasterImage drawing( 64, 64, Format_RGBA8 );
    RasterImage overlay( 64, 64, Format_RGBA8 );
    painter.DirectFill( drawing, Color::RGB( 0XFF0000 ) );
    painter.DirectFill( overlay, Color::RGB( 0X0000FF ) );
    painter.EnqueueAlphaBlendAA( overlay, drawing, overlay.Rect(), UVec2F( 0, 0 ), Blend_Normal, 1.f );
    painter.Flush();

    return  0;
}

//////////////////////////////////////////////////////
// Target API, snake_case, std-like, no prefix
#include <ulis3>

int main() {
    ul3::thread_pool;
    ul3::command_queue queue( thread_pool );
    ul3::painter_context painter( ul3::format::rgba8, command_queue );
    painter.dispatch();
    ul3::raster_image drawing( 64, 64, ul3::format::rgba8 );
    ul3::raster_image overlay( 64, 64, ul3::format::rgba8 );
    painter.direct_fill( drawing, ul3::color::rgb( 0XFF0000 ) );
    painter.direct_fill( overlay, ul3::color::rgb( 0X0000FF ) );
    painter.enqueue_alpha_blend_aa( overlay, drawing, overlay.rect(), ul3::vec2f( 0, 0 ), ul3::blend::normal, 1.f );
    painter.flush();

    return  0;
}


//////////////////////////////////////////////////////
// Potential Goal
#include <ULIS3>

int main() {
    using namespace ul3;
    FPainterContext painter( Format_RGBA8 );
    FImage drawing( 64, 64, Format_RGBA8 );
    FImage overlay( 64, 64, Format_RGBA8 );
    painter.Fill( drawing, FColor::RGB( 0XFF0000 ) );
    painter.Fill( overlay, FColor::RGB( 0X0000FF ) );
    painter.AlphaBlendAA( overlay, drawing, overlay.Rect(), FVec2f( 0, 0 ), Blend_Normal, 1.f );

    return  0;
}