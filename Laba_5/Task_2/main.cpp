#include "memory.h"
#include "memory_global_heap.h"
#include <cstring>
#include "../logger/logger.h"
#include "../logger/logger_concrete.h"
#include "../logger/logger_builder.h"
#include "../logger/logger_builder_concrete.h"
int main()
{
    logger_builder* builder = new logger_builder_concrete();
    
    logger *log = builder
        ->add_stream("log_allocate.txt", logger::severity::information)
        ->construct();

    memory *allocator = new memory_global_heap(log);

    int *a = reinterpret_cast <int*> (allocator->allocate(100));

    for (int i = 0; i < 25; i++)
    {
        a[i] = i;
    }

    char* str = reinterpret_cast<char*>(allocator->allocate(sizeof(char) * 10));
    strcpy(str, "123456789");

    allocator->deallocate(a);
    allocator->deallocate(str);

}