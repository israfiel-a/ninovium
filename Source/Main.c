#include <Engine/Engine.h>
#include <ErrorHandling/ErrorID.h>
int main(void)
{
    Ni_StartEngine("Generic RPG", (ni_init_args_t){true});

    Ni_RunEngine();

    Ni_TerminateEngine();
    return 0;
}
