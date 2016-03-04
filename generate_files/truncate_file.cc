#include <unistd.h>
#include <sys/types.h>

int truncate(const char *path, off_t length);
int main()
{
    truncate("/home/pi/random.img", 1024*1024*1536);
    return 0;
}
