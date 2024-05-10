#ifndef NEURONE_FCT_ACTIVATION_DERIVATION_H
#define NEURONE_FCT_ACTIVATION_DERIVATION_H
#include "lib.h"

double derivative_sigmoid(double x) {
    return sigmoid(x) * (1 - sigmoid(x));
}

#endif
