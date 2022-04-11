//Variáveis
int flagSys;
int valorDisp;
int estadoLed;
int filtroBt;
//Constantes
const int pinoBt                  = 5;  //pino conectado ao botão
const int pinoLed                 = 13; //pino conectado ao Led
const int pinoA                   = 12; //pino conectado ao pino A do display
const int pinoB                   = 11; //pino conectado ao pino B do display
const int pinoC                   = 10; //pino conectado ao pino C do display
const int pinoD                   = 9; //pino conectado ao pino D do display
const int pinoE                   = 8; //pino conectado ao pino E do display
const int pinoF                   = 7; //pino conectado ao pino F do display
const int pinoG                   = 6; //pino conectado ao pino G do display
const int tempoFiltragem_ms       = 300;//contador para filtro do botão
const int _1_ms                   = 1;  //multiplicador do filtro
const int on                      = 1;  //estado para indicar que o led esta ligado
const int off                     = 0;  //estado para indicar que o led esta desligado

void AcionaLed();
void AtualizaDisp();
void Show0();
void Show1();
void Show2();
void Show3();
void Show4();
void Show5();
void Show6();
void Show7();
void Show8();
void Show9();

void setup()
{    
    pinMode(pinoBt,INPUT);
    pinMode(pinoLed,OUTPUT);
    pinMode(pinoA,OUTPUT);
    pinMode(pinoB,OUTPUT);
    pinMode(pinoC,OUTPUT);
    pinMode(pinoD,OUTPUT);
    pinMode(pinoE,OUTPUT);
    pinMode(pinoF,OUTPUT);
    pinMode(pinoG,OUTPUT);
    digitalWrite(pinoLed,LOW);  //garantir que o pino do led vai começar em nível lógico 0
    flagSys = 0;
    estadoLed = off;
}

void loop()
{
    filtroBt = 0;
    while(digitalRead(pinoBt) == LOW && filtroBt < tempoFiltragem_ms)
    {
        delay(_1_ms);
        filtroBt++;
    }
    if(filtroBt == tempoFiltragem_ms)
    {
      
        if(flagSys == 0)
        {
            flagSys = 1;
        }  
    }
    else
    {
        if(flagSys == 1)
        {
            delay(50);
            valorDisp++;
            if(valorDisp == 10)
            {
                valorDisp = 0;
            }
            AtualizaDisp();
            if(digitalRead(pinoBt) == LOW)
            {
                AcionaLed();
                while(1);                             
            }                  
        }
    }
}

void AcionaLed()
{
    digitalWrite(pinoLed, HIGH);
    estadoLed = on;
}
  
void AtualizaDisp()
{
    if(valorDisp == 0)
    {
        Show0();
    }
    if(valorDisp == 1)
    {
        Show1();
    }
    if(valorDisp == 2)
    {
        Show2();        
    }
    if(valorDisp == 3)
    {
        Show3();
    }
    if(valorDisp == 4)
    {
        Show4();
    }
    if(valorDisp == 5)
    {
        Show5();
    }
    if(valorDisp == 6)
    {
        Show6();        
    }
    if(valorDisp == 7)
    {
        Show7();
    }
    if(valorDisp == 8)
    {
        Show8();
    }
    if(valorDisp == 9)
    {
        Show9();        
    }
}
void Show0()
{
    digitalWrite(pinoA, HIGH);
    digitalWrite(pinoB, HIGH);
    digitalWrite(pinoC, HIGH);
    digitalWrite(pinoD, HIGH);
    digitalWrite(pinoE, HIGH);
    digitalWrite(pinoF, LOW);
    digitalWrite(pinoG, HIGH);
}
void Show1()
{
    digitalWrite(pinoA, LOW);
    digitalWrite(pinoB, HIGH);
    digitalWrite(pinoC, HIGH);
    digitalWrite(pinoD, LOW);
    digitalWrite(pinoE, LOW);
    digitalWrite(pinoF, LOW);
    digitalWrite(pinoG, LOW);
}
void Show2()
{
    digitalWrite(pinoA, HIGH);
    digitalWrite(pinoB, HIGH);
    digitalWrite(pinoC, LOW);
    digitalWrite(pinoD, HIGH);
    digitalWrite(pinoE, HIGH);
    digitalWrite(pinoF, HIGH);
    digitalWrite(pinoG, LOW);
}
void Show3()
{
    digitalWrite(pinoA, HIGH);
    digitalWrite(pinoB, HIGH);
    digitalWrite(pinoC, HIGH);
    digitalWrite(pinoD, HIGH);
    digitalWrite(pinoE, LOW);
    digitalWrite(pinoF, HIGH);
    digitalWrite(pinoG, LOW);
}
void Show4()
{
    digitalWrite(pinoA, LOW);
    digitalWrite(pinoB, HIGH);
    digitalWrite(pinoC, HIGH);
    digitalWrite(pinoD, LOW);
    digitalWrite(pinoE, LOW);
    digitalWrite(pinoF, HIGH);
    digitalWrite(pinoG, HIGH);
}
void Show5()
{
    digitalWrite(pinoA, HIGH);
    digitalWrite(pinoB, LOW);
    digitalWrite(pinoC, HIGH);
    digitalWrite(pinoD, HIGH);
    digitalWrite(pinoE, LOW);
    digitalWrite(pinoF, HIGH);
    digitalWrite(pinoG, HIGH);
}
void Show6()
{
    digitalWrite(pinoA, HIGH);
    digitalWrite(pinoB, LOW);
    digitalWrite(pinoC, HIGH);
    digitalWrite(pinoD, HIGH);
    digitalWrite(pinoE, HIGH);
    digitalWrite(pinoF, HIGH);
    digitalWrite(pinoG, HIGH);
}
void Show7()
{
    digitalWrite(pinoA, HIGH);
    digitalWrite(pinoB, HIGH);
    digitalWrite(pinoC, HIGH);
    digitalWrite(pinoD, LOW);
    digitalWrite(pinoE, LOW);
    digitalWrite(pinoF, LOW);
    digitalWrite(pinoG, LOW);
}
void Show8()
{
    digitalWrite(pinoA, HIGH);
    digitalWrite(pinoB, HIGH);
    digitalWrite(pinoC, HIGH);
    digitalWrite(pinoD, HIGH);
    digitalWrite(pinoE, HIGH);
    digitalWrite(pinoF, HIGH);
    digitalWrite(pinoG, HIGH);
}
void Show9()
{
    digitalWrite(pinoA, HIGH);
    digitalWrite(pinoB, HIGH);
    digitalWrite(pinoC, HIGH);
    digitalWrite(pinoD, LOW);
    digitalWrite(pinoE, LOW);
    digitalWrite(pinoF, HIGH);
    digitalWrite(pinoG, HIGH);
}
