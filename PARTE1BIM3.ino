/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM / EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Ayuda practica 3 - matriz led
   Dev: Profe. Alejandro Lopez Navas
   Fecha: 09 de julio.
   link de la simulacion: 
   Link para animaciones led: https://www.riyas.org/2013/12/online-led-matrix-font-generator-with.html
*/

//Librerias
#include <LedControl.h>         //Libreria que me permita usar el IC MAX7219 (matriz led)

//Directivas de preprocesador
#define din_matrix        3     //pin3 del arduino conectado al pin DIN de la matriz led
#define cs_matrix         2     //pin2 del arduino conectado al pin CS de la matriz led
#define clk_matrix        4     //pin4 del arduino conectado al pin CLK de la matriz led
#define pot_pin           A0    //pin A0 del arduino conectado al potenciómetro

//Constructores
//Voy a controlar con el objeto PacmanMatrix un arreglo de 1 matriz led
LedControl PacmanMatrix = LedControl(din_matrix, clk_matrix, cs_matrix, 1);

//Variables
//Array que contiene los valores binarios para representar un pacman con la boca abierta y cerrada
byte pacman_boca_abierta[8] = {
  B00111000,
  B01000100,
  B10001000,
  B10010000,
  B10001000,
  B01000100,
  B00111000,
  B00000000
};

byte pacman_boca_cerrada[8] = {
  B00111000,
  B01000100,
  B10000010,
  B10011110,
  B10000010,
  B01000100,
  B00111000,
  B00000000
};

unsigned long update_delay = 850; // Espacio entre animaciones.

//Configuraciones
void setup() {
  Serial.begin(9600); //Inicio la comunicacion serial a 9600 baudios.
  PacmanMatrix.shutdown(0, false);    //Encendiendo mi matriz led. 
  PacmanMatrix.setIntensity(0, 15);    //Configuro el brillo de la matriz led a la mitad (este valor puede ser desde el 0 al 30)
  PacmanMatrix.clearDisplay(0);        //Limpio la pantalla de alguna animacion.
  Serial.println("Uso de la matriz led");
}

//Funciones para imprimir las animaciones
void print_pacman_open() {
  for (int i = 0; i < 8; i++) {
    PacmanMatrix.setRow(0, i, pacman_boca_abierta[i]);
  }
}

void print_pacman_close() {
  for (int i = 0; i < 8; i++) {
    PacmanMatrix.setRow(0, i, pacman_boca_cerrada[i]);
  }
}

//Ciclo infinito
void loop() {
  int pot_value = analogRead(pot_pin); // Leer el valor del potenciómetro
  update_delay = map(pot_value, 0, 1023, 100, 2000); // Mapear el valor del potenciómetro a un rango de 100 a 2000 ms

  print_pacman_open();
  delay(update_delay);
  print_pacman_close();
  delay(update_delay);
}
