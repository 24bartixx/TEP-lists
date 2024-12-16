#include <iostream>
#include "UnitTests.h"
#include "CLI.h"

using namespace std;

int main()
{
    UnitTests::runAll();

    CLI cli;
    cli.simulateCLI();
}