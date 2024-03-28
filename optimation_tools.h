#ifndef OPTIMATION_TOOLS_H_
#define OPTIMATION_TOOLS_H_

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<lib.h>
/*la fonction de la calcule de la perte */
float calcule_perte(float y_true,float y_pred)
{
 // calcule loss
 if (y_pred<1 && y_pred_>0 )
 {
  float loss = -(y_true*log(y_pred)+(1-y_true)*log(1-y_pred));
  return loss;
  }
}

/*calcule du perte à l'aide de la fonction sigmoid*/
float calcule_loss_sig(float *y_true, float *y_pred, int nb_input){

 double loss = 0;
 for(int i =0 ; i<nb_input;i++){
    loss+=calcule_perte(y_true[i],sigmoid(y_pred[i]));
 }
 return loss/nb_input;
}



#endif // OPTIMATION_TOOLS_H_
