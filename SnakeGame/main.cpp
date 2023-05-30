#include "Application.h"

Application application;

int main()
{
    _wsetlocale(LC_ALL, L"korean");

    application.Initialize();
    application.Run();
    application.Release();

    return 0;
}

