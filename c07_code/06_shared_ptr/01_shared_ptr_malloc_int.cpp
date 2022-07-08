#include <cstdlib>
#include <memory>

using namespace std;

//#define MAIN_1

int* malloc_int(int value)
{
    int* p = (int*)malloc(sizeof(int));
    *p = value;
    return p;
}

#ifdef MAIN_1

int main()
{
    shared_ptr<int> myIntSmartPtr(malloc_int(42), free);

    return 0;
}

#endif