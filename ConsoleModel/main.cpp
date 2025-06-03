#include "Model.h"
#include <ctime>
int main()
{
    srand(time(NULL));
    Model m(100);
    m.Run();
}
