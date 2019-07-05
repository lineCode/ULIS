/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <ULIS_CORE>
#include <thread>


int main()
{
    ::ULIS::IBlock* block = new ::ULIS::FBlockBGRA8( 64, 64 );
    int     num_threads = std::thread::hardware_concurrency();
    int     num_elements = block->BytesTotal();
    float   elements_per_thread = num_elements / (float)num_threads;
    std::cout << num_threads << std::endl;
    std::cout << num_elements << std::endl;
    std::cout << elements_per_thread << std::endl;

    return 0;
}

