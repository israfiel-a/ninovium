#include <Engine/Engine.h>
int main(void)
{
    Ni_StartEngine("Generic RPG", NULL);

    Ni_RunEngine();

    Ni_TerminateEngine();
    return 0;
}
