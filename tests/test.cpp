// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         test.cpp
* @author       Clement Berthaud
* @brief        Test application for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS2>
//#include <CL/cl.hpp>
//#include <vectorclass.h>
using namespace ::ul2;

int
main()
{
    FColor rgb8( ULIS2_FORMAT_RGB8, { 255, 0, 0 } );
    FColor bgr8( ULIS2_FORMAT_BGR8 );
    FColor GreyA16( ULIS2_FORMAT_GA16 );
    FColor HSVA8( ULIS2_FORMAT_HSVA8 );
    FColor HSLF( ULIS2_FORMAT_HSLF );
    FColor CMYA8( ULIS2_FORMAT_CMYA8 );
    FColor CMYK8( ULIS2_FORMAT_CMYK8 );
    FColor LabD( ULIS2_FORMAT_LabD );
    Conv( rgb8, bgr8 );
    Conv( rgb8, GreyA16 );
    Conv( rgb8, HSVA8 );
    Conv( rgb8, HSLF );
    Conv( rgb8, CMYA8 );
    Conv( rgb8, CMYK8 );
    Conv( rgb8, LabD );
    std::cout << "____________________________" << std::endl;
    std::cout << "rgb8:" << std::endl;
    std::cout << (int)rgb8.R8() << std::endl;
    std::cout << (int)rgb8.G8() << std::endl;
    std::cout << (int)rgb8.B8() << std::endl;
    std::cout << "____________________________" << std::endl;
    std::cout << "bgr8:" << std::endl;
    std::cout << (int)bgr8.R8() << std::endl;
    std::cout << (int)bgr8.G8() << std::endl;
    std::cout << (int)bgr8.B8() << std::endl;
    std::cout << "____________________________" << std::endl;
    std::cout << "GreyA16:" << std::endl;
    std::cout << (int)GreyA16.Grey16() << std::endl;
    std::cout << (int)GreyA16.A16() << std::endl;
    std::cout << "____________________________" << std::endl;
    std::cout << "HSVA8:" << std::endl;
    std::cout << (int)HSVA8.Hue8() << std::endl;
    std::cout << (int)HSVA8.Saturation8() << std::endl;
    std::cout << (int)HSVA8.Value8() << std::endl;
    std::cout << (int)HSVA8.A8() << std::endl;
    std::cout << "____________________________" << std::endl;
    std::cout << "HSLF:" << std::endl;
    std::cout << (float)HSLF.HueF() << std::endl;
    std::cout << (float)HSLF.SaturationF() << std::endl;
    std::cout << (float)HSLF.LightnessF() << std::endl;
    std::cout << "____________________________" << std::endl;
    std::cout << "CMYA8:" << std::endl;
    std::cout << (int)CMYA8.Cyan8() << std::endl;
    std::cout << (int)CMYA8.Magenta8() << std::endl;
    std::cout << (int)CMYA8.Yellow8() << std::endl;
    std::cout << (int)CMYA8.A8() << std::endl;
    std::cout << "____________________________" << std::endl;
    std::cout << "CMYK8:" << std::endl;
    std::cout << (int)CMYK8.Cyan8() << std::endl;
    std::cout << (int)CMYK8.Magenta8() << std::endl;
    std::cout << (int)CMYK8.Yellow8() << std::endl;
    std::cout << (int)CMYK8.Key8() << std::endl;
    std::cout << "____________________________" << std::endl;
    std::cout << "LabD:" << std::endl;
    std::cout << (double)LabD.LD() << std::endl;
    std::cout << (double)LabD.aD() << std::endl;
    std::cout << (double)LabD.bD() << std::endl;

    /*
    FBlock blockA( 256, 256, ULIS2_FORMAT_ARGB8 );
    FBlock blockB( 256, 256, ULIS2_FORMAT_ARGB8 );
    FThreadPool pool;
    FPerf       perf( Perf_Lowest );
    Blend( &pool, ULIS2_BLOCKING, &blockA, &blockB, glm::vec2( 0 ), BM_HUE, AM_NORMAL, 1.f, perf, ULIS2_CALL_CB );
    */

    /*
    // OpenCL
    //get all platforms (drivers)
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if(all_platforms.size()==0){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

     //get default device of the default platform
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Device default_device=all_devices[0];
    std::cout<< "Num devices: "<<all_devices.size()<<"\n";
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";

    cl::Context context({default_device});
    cl::Program::Sources sources;

    // kernel calculates for each element C=A+B
    std::string kernel_code =
            "   void kernel simple_add(global const int* A, global const int* B, global int* C){    "
            "       C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                    "
            "   }                                                                                   ";
    sources.push_back({kernel_code.c_str(),kernel_code.length()});

    cl::Program program(context,sources);
    if(program.build({default_device})!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
    }

    // create buffers on the device
    cl::Buffer buffer_A( context,CL_MEM_READ_WRITE,sizeof(int)*10 );
    cl::Buffer buffer_B( context,CL_MEM_READ_WRITE,sizeof(int)*10 );
    cl::Buffer buffer_C( context,CL_MEM_READ_WRITE,sizeof(int)*10 );

    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

    //create queue to which we will push commands for the device.
    cl::CommandQueue queue(context,default_device);
    //write arrays A and B to the device
    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*10,A);
    queue.enqueueWriteBuffer(buffer_B,CL_TRUE,0,sizeof(int)*10,B);

    cl::make_kernel< cl::Buffer, cl::Buffer, cl::Buffer > simple_add( cl::Kernel( program, "simple_add" ) );
    cl::EnqueueArgs eargs(queue, cl::NullRange, cl::NDRange(10), cl::NullRange);
    simple_add(eargs, buffer_A, buffer_B, buffer_C).wait();

    int C[10];
    //read result C from the device to array C
    queue.enqueueReadBuffer(buffer_C,CL_TRUE,0,sizeof(int)*10,C);

    std::cout<<" result: \n";
    for(int i=0;i<10;i++){
        std::cout<<C[i]<< " " << std::endl;
    }

    cl_int err;
    cl::size_t< 3 > origin;
    cl::size_t< 3 > region;
    region[0] = 256;
    region[1] = 256;
    cl::Image2D resource( context, CL_MEM_USE_HOST_PTR, { CL_RGBA, CL_FLOAT }, 256, 256, 0, block.DataPtr(), &err );
    std::cout << err << std::endl;
    std::cout << resource.getInfo< CL_MEM_SIZE >( &err ) << std::endl;
    std::cout << err << std::endl;
    auto _dummy = 0;
    */
    return  0;
}

