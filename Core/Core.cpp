#include "Core.hpp"
#include <iostream>

namespace Csc {

void Greeter::SayHi() { Core::Hello(); }

namespace Core {

void Hello() { std::cout << "Hello From Core!" << std::endl; }

} // namespace Core

} // namespace Csc
