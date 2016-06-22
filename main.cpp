#include <iostream>

#include "json.hpp"
#include "communication.h"

using json = nlohmann::json;

using namespace std;

int main()
{
    Communication* c= new Communication();
    if(c->init())
        c->run();
    delete(c);


    return 0;
}

