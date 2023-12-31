// Rocío Gómez
//Link al arduino:
//https://www.tinkercad.com/things/df2fIFHAack-primera-parte/editel?sharecode=_2tCSoK-26oWPHVYkRN4ZvY2Dq9JVb-CqAMrX8DW3Dkk

// C++ code
//Se definen las entradas a utilizar
#define a 10
#define b 11
#define f 9
#define g 8
#define e 7
#define d 6
#define c 5
#define unidad A4
#define decena A5
#define ALLOF 0
#define RESTA_PULSADOR 2
#define SUMA_PULSADOR 3
#define REINICIO_PULSADOR 4


//Se declaran las variables que se van a 
//utilizar para controlar el comportamiento del contador y 
//la detección de presion de botones
int contador = 0;
int suma = 1;
int resta = 1;
int reinicio = 1;
int suma_anterior = 0;
int reinicio_anterior = 0;
int resta_anterior = 0;

void setup(){
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(decena,OUTPUT);
  pinMode(unidad, OUTPUT);
  pinMode(RESTA_PULSADOR,INPUT_PULLUP);
  pinMode(SUMA_PULSADOR,INPUT_PULLUP);
  pinMode(REINICIO_PULSADOR,INPUT_PULLUP);
  Serial.begin(9600);
}
//LOOP

void loop()
{ //Se llama a la función keypressed para verificar si se presionó un botón.
  int pressed = keypressed();
  if(pressed == SUMA_PULSADOR)
  {
   contador++;
   if (contador > 99)
    {
     contador = 0; 
    }
    
  }
   if(pressed == RESTA_PULSADOR)
   {
     contador--;
     if (contador < 1)
     {
       contador = 99;
     }
   }
   if(pressed == REINICIO_PULSADOR)
   {
 	contador = 0;
   }
  

imprimirContador(contador);//Se usa para mostrar el valor actual del contador
}




//FUNCIONES
//Pulsación de botones
int keypressed(void)
{
  
  suma = digitalRead(SUMA_PULSADOR);
  resta = digitalRead(RESTA_PULSADOR);
  reinicio = digitalRead(REINICIO_PULSADOR);	

  if (suma == 1)
  {
 	suma_anterior = 1;  
  }
  if (resta == 1)
  {
 	resta_anterior = 1;  
  }
  if (reinicio == 1)
  {
 	reinicio_anterior = 1;  
  }
  if(suma == 0 & suma != suma_anterior)
  {
  	suma_anterior = suma;
    return SUMA_PULSADOR;
  }
  if(resta == 0 & resta != resta_anterior)
  {
  	resta_anterior = resta;
    return RESTA_PULSADOR;
  }
  if(reinicio == 0 & reinicio != reinicio_anterior)
  {
  	reinicio_anterior = reinicio;
    return REINICIO_PULSADOR;
  }
  return 0;
}

//Se controla el display de 7 segmentos       
void mostrarDigito(int digito){

    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);


  if(digito == 0){
        digitalWrite(a,HIGH);
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,HIGH);
        digitalWrite(e,HIGH);
        digitalWrite(f,HIGH);

  }else if(digito == 1){

        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);

  }else if(digito == 2){
          digitalWrite(a,HIGH);
        digitalWrite(b,HIGH);
        digitalWrite(d,HIGH);
        digitalWrite(e,HIGH);
        digitalWrite(g,HIGH);
  }else if(digito == 3){
          digitalWrite(a,HIGH);
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,HIGH);
        digitalWrite(g,HIGH);
  }else if(digito == 4){
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(f,HIGH);
        digitalWrite(g,HIGH);
  }else if(digito == 5){
        //a,c,d,f,g
          digitalWrite(a,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,HIGH);
        digitalWrite(f,HIGH);
        digitalWrite(g,HIGH);
  }else if(digito == 6){
        //a,c,d,e,f,g
          digitalWrite(a,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,HIGH);
        digitalWrite(e,HIGH);
        digitalWrite(f,HIGH);
        digitalWrite(g,HIGH);
  }else if(digito == 7){
        //a,b,c
          digitalWrite(a,HIGH);
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
  }else if(digito == 8){
        //a,b,c,d,e,f,g
          digitalWrite(a,HIGH);
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,HIGH);
        digitalWrite(e,HIGH);
        digitalWrite(f,HIGH);
        digitalWrite(g,HIGH);
  }else if(digito == 9){
        //a,c,d,e,f,g
          digitalWrite(a,HIGH);
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,HIGH);
        digitalWrite(f,HIGH);
        digitalWrite(g,HIGH);

  }
}
//Función que controla cuál de los dos dígitos debe estar encendido
void prenderDigito(int digito){
  if(digito == decena){
    digitalWrite(unidad,HIGH);
  	digitalWrite(decena,LOW);
    delay(10);
}
  else if(digito == unidad){
    digitalWrite(unidad,LOW);
  	digitalWrite(decena,HIGH);
    delay(10);
  }
   else{
    digitalWrite(unidad,HIGH);
  	digitalWrite(decena,HIGH);
}

}
//Muestra un número de dos digitos en un display.
void imprimirContador (int contador){
 
  prenderDigito(ALLOF);//APAGA LAS DOS
  mostrarDigito(contador/10);//78 / 10 = 7.8. 
  //Calcula el dígito de las decenas dividiendo el contador por 10
  prenderDigito(decena);//Se asegura que el dígito de las decenas se encienda en el display
  prenderDigito(ALLOF);
  mostrarDigito(contador - (int(contador/10)*10)); //78 - (int(contador/10)*10) 
  //Calcula el dígito de las unidades tomando el valor del contador y restando el valor del dígito de las decenas
  prenderDigito(unidad);//Lo mismo, solo que prende la unidad.
}
