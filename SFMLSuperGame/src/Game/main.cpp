#include "../Core/Program.h"

int main() {
    Program* program = new Program(false); 
    if(program != nullptr) {
        delete program;
        program = nullptr;
    }
    return 0;
}