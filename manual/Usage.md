## Usage
ULIS can be used in a variety of ways, ranging from very easy to quite difficult to grasp when performance matters and asynchronous operations and multithreading are introduced.  
Here is a sample of an easy use of ULIS if performance is not critical:

```cpp
//////////////////////////////////////////////////////
// Easy In Order MonoThread Scheduling
#include <ULIS3>

int main() {
    using namespace ::ul3;
    FContext ctx;

    FVec2i size( 1024, 1024 );
    FRasterImage2D drawing( size );
    FRasterImage2D overlay( size );
    FGPUTexture2D texture( size );

    ctx.Fill( drawing, FColor::RGB( 255, 0, 0 ) );
    ctx.Fill( overlay, FColor::RGB( 0, 0, 255 ) );
    ctx.AlphaBlendAA( overlay, drawing, overlay.Rect(), FVec2f( 0, 0 ), Blend_Normal, 1.f );
    ctx.UploadToGPU( drawing, texture );

    return  0;
}
```

Now here is a sample of asynchronous multithreaded operations when performance matters:
```cpp
//////////////////////////////////////////////////////
// Advanced Out Of Order Multithreaded Scheduling
#include <ULIS3>

int main() {
    using namespace ::ul3;

    FThreadPool pool( FThreadPool::MaxWorkers() - 1 );
    FCommandQueue queue( thread_pool );
    tFormat documentFormat = Format_RGBA8;
    FContext ctx( documentFormat, command_queue, Ctx_PrefetchDispatch, SelectPerf_SSE );

    FHostDeviceInfo info = FHostDeviceInfo::Detect();

    FSchedulerPolicy cacheEfficientPolicy( Run_Multi, Schedule_Chunks, ItemSize_ChunkLength, info.CacheLineSize_L1 );
    FSchedulerPolicy scanLinePolicy( Run_Multi, Schedule_Scanlines )
    FSchedulerPolicy monoPolicy( Run_Mono );

    FVec2ui16 size( 1024, 1024 );
    FRasterImage2D drawing( documentFormat, size );
    FRasterImage2D overlay( documentFormat, size );
    FGPUTexture2D texture( documentFormat, size );

    FTaskEvent evt_fill_drawing = ctx.Fill( drawing, FColor::FromHex( 0xF00 ), cacheEfficientPolicy );
    FTaskEvent evt_fill_overlay = ctx.Fill( overlay, FColor::FromHex( 0xBA2 ), cacheEfficientPolicy, &evt_fill_drawing );

    FTaskEvent evt_blend = ctx.AlphaBlendAA( overlay, drawing, overlay.Rect(), FVec2f( 0, 0 ), Blend_Normal, 1.f, scanLinePolicy );
    ctx.Fence();

    ctx.UploadToGPU( drawing, texture, monoPolicy, &evt_blend );
    ctx.Flush();

    return  0;
}
```
