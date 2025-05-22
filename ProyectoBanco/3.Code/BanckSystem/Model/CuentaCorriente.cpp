#include "CuentaCorriente.h"
using namespace std;

CuentaCorriente::CuentaCorriente() : Cuenta() {}

CuentaCorriente::CuentaCorriente(string num) : Cuenta(num, 0.0) {}
