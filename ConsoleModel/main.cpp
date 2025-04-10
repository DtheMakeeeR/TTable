#include "Model.h"
#include <ctime>
int main()
{
    srand(time(NULL));
    Model m;
    m.CheckSorts(1000, 1000);
}
