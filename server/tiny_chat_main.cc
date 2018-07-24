//
// Created by Sunshine on 2018/7/18.
//
#include <iostream>

#include "context/main_context.h"


int main(int argc, char* argv[]) {

    context::MainContext* main_context =
            context::MainContext::Create();

    main_context->Initialize();

    main_context->Run();

    main_context->Shutdown();

    return 0;


}

