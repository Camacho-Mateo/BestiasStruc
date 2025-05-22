template<typename T>
Nodo<T>* Buscador::buscarElemento(ListaDoble<T>& lista, const T& valor, bool (*comparar)(const T&, const T&)) {
    return lista.buscar(comparar, valor);
}

bool Buscador::compararPorCedula(const Persona& p, const Persona& valor) {
    return p.getCedula() == valor.getCedula();
}

bool Buscador::compararPorNumeroCuentaAhorro(const CuentaAhorro& c, const CuentaAhorro& valor) {
    return c.getNumeroCuenta() == valor.getNumeroCuenta();
}

bool Buscador::compararPorNumeroCuentaCorriente(const CuentaCorriente& c, const CuentaCorriente& valor) {
    return c.getNumeroCuenta() == valor.getNumeroCuenta();
}
