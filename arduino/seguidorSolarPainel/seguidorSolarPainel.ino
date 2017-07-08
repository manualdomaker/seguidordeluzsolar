/*
Seguidor de Luz Solar para painel solar
Mais tutoriais no blog: http://makerbrasiltv.wordpress.com
Gotou? Tem algum projeto que tenha o interesse em compartilhar para todos?
Entre em nosso blog e envie uma mensagem com assunto, Projeto para todos.
Curta nosso canal do youtube para nos ajudar a mudar a educacao do Brasil, para melhor.
Faça sua parte :-)
*/


#include <Servo.h>
Servo horizontal;    // horizontal servo
int servoh = 90;     // stand horizontal servo

Servo vertical;      // vertical servo 
int servov = 90;     // stand vertical servo

// LDR pin connections
//  name  = analogpin;
int ldrlt = 2;       //LDR baixo esquerda
int ldrrt = 3;       //LDR baixo direita
int ldrld = 0;       //LDR topo esquerda
int ldrrd = 1;       //LDR topo direita

void setup()
{
  Serial.begin(9600);
  horizontal.attach(3); 
  vertical.attach(4);
}

void loop() 
{
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt

  int dtime = analogRead(4)/20;  
  int tol = analogRead(5)/4;
  
  int avt = (lt + rt) / 2;    // valor do topo
  int avd = (ld + rd) / 2;    // valor de baixo
  int avl = (lt + ld) / 2;    // valor da esquerda
  int avr = (rt + rd) / 2;    // valor da direita
  int dvert = avt - avd;      // verifica a diferenca do topo e de baixo
  int dhoriz = avl - avr;     // verifica a diferenca da esquerda e da direita
    
  if (-1*tol > dvert || dvert > tol) // verifica a diferenca e a tolerancia se nao muda o angulo vertical 
  {
     if (avt > avd)
  {
     servov = --servov;
     if (servov > 180) 
     { 
        servov = 180;
     }
  }
  else if (avt < avd)
  {
    servov= ++servov;
    if (servov < 0)
  {
    servov = 0;
  }
  }
  vertical.write(servov);
  }

  //verifica adiferenca e a tolerancia senao muda o angulo horizontal
  if (-1*tol > dhoriz || dhoriz > tol)  
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < 0)
    {
    servoh = 0;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > 180)
     {
     servoh = 180;
     }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }
   delay(dtime); 
}
