/*  Controlador de velocidad  */
/*  Cálculo velocidad y controlador de velocidad */
int aux_vel = 0;


double w_der;


double w_izq;

/* PID velocidad discreto*/
double Kp_der = 1.3714;
double Ki_der = 10.5241 * 0.01;

double Kp_izq = 1.3695;
double Ki_izq = 10.514 * 0.01;

double u_ant_der = 0.0;
double u_act_der = 0.0;
double u_ant_izq = 0.0;
double u_act_izq = 0.0;
/*
double x_ant_der = 0.0;
double x_ant_izq = 0.0;

double error_der = 0.0;
double error_izq = 0.0;
*/
double Gv_der = 1000.0/110.1;
double Gv_izq = 1000.0/104.1;

void velocidad(double r_izq, double r_der)
{ 
  pos_der = encoder_der.read()*2*PI/118;
  pos_izq = encoder_izq.read()*2*PI/118;
    
  if (aux_vel== 5)
  {  
    aux_vel = 0;
    
    w_der = (pos_der - pos_anterior_der)/(5*h); 
    double estimated_w_der = kf_der.updateEstimate(w_der);

    w_izq = (pos_izq - pos_anterior_izq)/(5*h); 
    double estimated_w_izq = kf_izq.updateEstimate(w_izq);
        
    pos_anterior_der = pos_der;
    pos_anterior_izq = pos_izq;

    /*  Control velocidad */
    error_der = r_der  - estimated_w_der;
    error_izq = r_izq  - estimated_w_izq;
    
    x_act_der = (Kp_der - Ki_der)/Kp_der * x_ant_der - (Ki_der/(Kp_der * Kp_der))*u_ant_der;
    x_act_izq = (Kp_izq - Ki_izq)/Kp_izq * x_ant_izq - (Ki_izq/(Kp_izq * Kp_izq))*u_ant_izq;


    u_act_der = Kp_der *(error_der - x_act_der);
    u_act_izq = Kp_izq *(error_izq - x_act_izq);

    if (u_act_der > 440.32)
    {
      u_act_der = 440.32;
    }

    else if (u_act_der < -440.32)
    {
      u_act_der = -440.32;
    }

    if (u_act_izq > 440.32)
    {
      u_act_izq = 440.32;
    }

    else if (u_act_izq < -440.32)
    {
      u_act_izq = -440.32;
    }

    u_ant_der = u_act_der;
    x_ant_der = x_act_der;

    u_ant_izq = u_act_izq;
    x_ant_izq = x_act_izq;
    
    motor(u_act_izq * Gv_izq,  u_act_der * Gv_der);
    
    /*    ----------    */
    /*
    Serial.print(T2);
    Serial.print(' '); 
    Serial.print(Vel);
    Serial.print(' '); 
    Serial.printf("%lf",pos_der);
    Serial.print(' '); 
    Serial.printf("%lf",pos_anterior_der);
    Serial.print(' '); 
    Serial.printf("%lf",r_der);
    Serial.print(' ');
    Serial.printf("%lf", w_der);
    Serial.print(' ');
    Serial.printf("%lf", estimated_w_der);
    Serial.print(' '); 
    Serial.printf("%lf",r_izq);
    Serial.print(' '); 
    Serial.printf("%lf", w_izq);
    Serial.print(' ');
    Serial.printf("%lf", estimated_w_izq);
    Serial.println();
    */
     /*    ----------    */

  }  
  aux_vel = aux_vel + 1;
}


