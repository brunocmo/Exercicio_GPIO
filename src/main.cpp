#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

bool acabando[30];

int pwmLedLigar(int led, int frequenciaLed ) {

  int frequenciaTotal{frequenciaLed+1};

  std::cout << "ligando led..." << led << '\n';
  for(int i{0}; i<frequenciaTotal; ++i) {
    softPwmWrite(led, i);
    std::cout << "valor led: " << i << '\n';
    delay(250);
  }

}

int pwmLedDesligado(int led, int frequenciaLed ) {

  int frequenciaTotal{frequenciaLed+1};

  std::cout << "desligando led ..." << led << '\n';
  for(int j{frequenciaTotal}; j>0; --j) {
    softPwmWrite(led,j);
    std::cout << "valor led: " << j << '\n';

    delay(250);
  }

}

int pwmLed( int frequeciaLed ) {

  pwmLedLigar( 6, frequeciaLed ); 
  pid_t process = fork();


  if (process == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (process > 0 ) {
    pwmLedDesligado( 6, frequeciaLed);
  } else {
    pwmLedLigar(10, frequeciaLed);
    pwmLedDesligado( 10, frequeciaLed);
  }

}

int main() {

  int ledVermelho{6};
  int ledAmarelo{10};
  int frequencia{60};

  wiringPiSetup () ;
  softPwmCreate (ledAmarelo, 0, frequencia) ;
  softPwmCreate (ledVermelho, 0, frequencia) ;

  pwmLed( frequencia);

  // pinMode (ledVermelho, OUTPUT) ;
  // for (;;)
  // {
  //   digitalWrite (ledVermelho, HIGH) ; 
  //     std::cout << "Ligado" << '\n';
  //     delay (500) ;
  //   digitalWrite (ledVermelho,  LOW) ; 
  //     std::cout << "Desligado" << '\n';
  //     delay (500) ;
  // }

  return 0;
}
