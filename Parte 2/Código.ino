//Rocío Gómez
//Link al arduino https://www.tinkercad.com/things/4V3IpgrkTf7-segunda-parte-arduino/editel?sharecode=_P_RaZtPehFyl-r7bR4qIpv5Ga5wqvJ5VrdzujCquEE

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
#define SLIDER 13
//Se declaran las variables que se van a 
//utilizar para controlar el comportamiento del contador y 
//la detección de presion de botones
int contador = 0;
int suma = 1;
int resta = 1;
int suma_anterior = 0;
int resta_anterior = 0;
int contador_primos = 3;


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
  
  
  pinMode(SLIDER,INPUT_PULLUP);
  Serial.begin(9600);
}
//LOOP

void loop()
{ 
  if(digitalRead(SLIDER) == 0) 
   //Slider indica que mientras esté en 0, hace el contador normal
    
  {
    int pressed = keypressed();
    if (pressed == SUMA_PULSADOR)
    {
      
      contador++;
      if (contador > 99)
      {
        contador = 0; 
      }
    }
    else if (pressed == RESTA_PULSADOR)
    {
      
      contador--;
      if (contador < 1)
      {
        contador = 99;
      }
    }

    imprimirContador(contador);
  }
  else
    //Sino, hace el número primo
  { 
    int pressed = keypressed();
    if (pressed == SUMA_PULSADOR)
    {
//El while, verifica si el contador_primos utiliza la función bool primo
     //para encontrar al número primo. Luego se utiliza el imprimirContador
      //para mostrarlo en el display.
      contador_primos++;
      while (!primo(contador_primos))
      { 
        contador_primos++;
      }
      imprimirContador(contador_primos);
    }
    else if (pressed == RESTA_PULSADOR)
    {
      contador_primos--;
      while (!primo(contador_primos))
      { 
        contador_primos--;
      }
      imprimirContador(contador_primos);
    }
  }
}
//Función para detectar cuando es un número primo
bool primo(int digito) {
  //Si el dígito es menor o igual a 1, se retorna falso
  //Cualquier numero menor o igual a 1 no es primo.
  if (digito <= 1) {
    return false;
  }
  //Si el valor de digito es divisible por i sin dejar resto
  //devuelve falso, ya que no es un número primo.
  for (int i = 2; i * i <= digito; i++) {
    if (digito % i == 0) {
      return false;
    }
  }
  return true;//Cuando ya encuentra un número primo.
}



//FUNCIONES
//Pulsación de botones
int keypressed(void)
{
  //Almacena suma y resta
  suma = digitalRead(SUMA_PULSADOR);
  resta = digitalRead(RESTA_PULSADOR);
  
  
  if (suma == 1)
  {
 	suma_anterior = 1;  
  }
  if (resta == 1)
  {
 	resta_anterior = 1;  
  }
  //Se verifica el estado de os botones.
  
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
  //Si verifica si pasó a estar presionado,
  return 0;
  //No fue presionado
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
