//Apply train for one neurone with two inputs

#include <stdio.h>
#include <stdlib.h>
#include "work.h"
#include "sortie_cible.h"
#include "optimation_tools.h"
#include "fct_activation_derivation.h"
#include "lib.h"
#include "Save.h"
#include "description.h"
#include "train.h"
#include <time.h>

int main() {
    srand(time(NULL));
    train_single_neuron_network("‪C:\Users\Amna\Downloads\dataset.xlsx");
    return 0;
}
