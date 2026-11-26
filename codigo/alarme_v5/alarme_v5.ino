#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);
Servo trava;
const int LED = 13, PORTA = 12, VIDRO = 11, PIR = 10;
const int BUZZER = A1, SERVO = A0;
const byte linhas[4] = {9, 8, 7, 6};
const byte colunas[4] = {5, 4, 3, 2};
char teclas[4][4] = {
  {'1','2','3','A'}, {'4','5','6','B'},
  {'7','8','9','C'}, {'*','0',35,'D'}
};
bool armado = false, disparado = false, armando = false;
int etapa = 0, erros = 0, digitos = 0;
char entrada[7];
char ultimaTecla = 0;
unsigned long inicio, inicioArmar, inicioBloqueio, ultimaAuth;
bool bloqueado = false;
int ultimoSegundo = -1;
const char* causa = "";
int portaBruta = HIGH, vidroBruto = HIGH;
int portaEstavel = HIGH, vidroEstavel = HIGH;
unsigned long mudouPorta = 0, mudouVidro = 0;

char lerTeclado() {
  for (int i = 0; 4 > i; i++) {
    pinMode(linhas[i], OUTPUT);
    digitalWrite(linhas[i], LOW);
    for (int j = 0; 4 > j; j++) {
      if (digitalRead(colunas[j]) == LOW) {
        pinMode(linhas[i], INPUT);
        return teclas[i][j];
      }
    }
    pinMode(linhas[i], INPUT);
  }
  return 0;
}

void tela(const char* primeira, const char* segunda) {
  lcd.clear();
  lcd.print(primeira);
  lcd.setCursor(0, 1);
  lcd.print(segunda);
}

void telaNormal() {
  if (disparado) tela("ALARME DISPARADO", causa);
  else if (armado) tela("ALARME ARMADO", "D: desarmar");
  else tela("DESARMADO", "A: armar");
}

void telaSenha() {
  tela(etapa == 1 ? "Codigo mestre:" : "Senha:", "");
  for (int i = 0; digitos > i; i++) lcd.print('*');
}

unsigned long hashEntrada() {
  unsigned long h = 5381;
  const char* sal = etapa == 1 ? "CAR-M:" : "CAR-P:";
  for (int i = 0; 6 > i; i++) h = h * 33UL + sal[i];
  for (int i = 0; digitos > i; i++) h = h * 33UL + entrada[i];
  return h & 0xFFFFFFFFUL;
}

void dispararAlarme(const char* motivo) {
  disparado = true;
  causa = motivo;
  tone(BUZZER, 1200);
  Serial.println("ALARME DISPARADO");
  Serial.println(motivo);
  if (etapa == 0 && !bloqueado) telaNormal();
}

void desarmarAlarme() {
  armado = false;
  disparado = false;
  etapa = 0;
  digitos = 0;
  erros = 0;
  bloqueado = false;
  trava.write(0);
  noTone(BUZZER);
  digitalWrite(LED, LOW);
  telaNormal();
  Serial.println("Alarme desarmado");
}

void falha() {
  erros++;
  etapa = 0;
  digitos = 0;
  Serial.println("Credencial incorreta");
  if (erros >= 3) {
    bloqueado = true;
    inicioBloqueio = millis();
    ultimoSegundo = -1;
    Serial.println("Bloqueado por 30 segundos");
  } else {
    tela("CODIGO ERRADO", "D: tentar de novo");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(PORTA, INPUT_PULLUP);
  pinMode(VIDRO, INPUT_PULLUP);
  pinMode(PIR, INPUT);
  for (int i = 0; 4 > i; i++) {
    pinMode(linhas[i], INPUT);
    pinMode(colunas[i], INPUT_PULLUP);
  }
  trava.attach(SERVO);
  trava.write(0);
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  inicio = millis();
  tela("DESARMADO", "A: armar");
  Serial.println("Sistema iniciado");
}

void loop() {
  unsigned long agora = millis();
  int p = digitalRead(PORTA), v = digitalRead(VIDRO);
  if (p != portaBruta) { portaBruta = p; mudouPorta = agora; }
  if (v != vidroBruto) { vidroBruto = v; mudouVidro = agora; }
  if (agora - mudouPorta >= 40) portaEstavel = portaBruta;
  if (agora - mudouVidro >= 40) vidroEstavel = vidroBruto;

  if (armando) {
    unsigned long passou = agora - inicioArmar;
    if (passou >= 5000) {
      armando = false;
      armado = true;
      trava.write(90);
      telaNormal();
      Serial.println("Alarme armado");
    } else {
      int segundo = (5000 - passou + 999) / 1000;
      if (segundo != ultimoSegundo) {
        ultimoSegundo = segundo;
        tela("ARMANDO...", "Saida: ");
        lcd.print(segundo);
        lcd.print("s");
      }
    }
  }

  if (armado && !disparado) {
    if (portaEstavel == LOW) dispararAlarme("PORTA ABERTA");
    else if (vidroEstavel == LOW) dispararAlarme("VIDRO VIOLADO");
    else if (agora - inicio >= 5000 && digitalRead(PIR) == HIGH) dispararAlarme("MOVIMENTO");
  }
  digitalWrite(LED, disparado && (agora / 300) % 2 == 0);

  if (bloqueado) {
    unsigned long passou = agora - inicioBloqueio;
    if (passou >= 30000) {
      bloqueado = false;
      erros = 0;
      telaNormal();
      Serial.println("Bloqueio encerrado");
    } else {
      int segundo = (30000 - passou + 999) / 1000;
      if (segundo != ultimoSegundo) {
        ultimoSegundo = segundo;
        tela(disparado ? "ALARME BLOQUEADO" : "BLOQUEADO", "Aguarde: ");
        lcd.print(segundo);
        lcd.print("s");
      }
    }
  }
  if (etapa != 0 && agora - ultimaAuth >= 20000) {
    etapa = 0;
    digitos = 0;
    telaNormal();
  }

  char tecla = lerTeclado();
  if (tecla != 0 && tecla != ultimaTecla && !bloqueado) {
    if (tecla == 'A' && !armado && !armando) {
      if (agora - inicio >= 5000) {
        armando = true;
        inicioArmar = agora;
        ultimoSegundo = -1;
      } else tela("AGUARDE PIR", "Tente A em 5s");
    } else if (armado && tecla == 'D') {
      etapa = 1;
      digitos = 0;
      ultimaAuth = agora;
      telaSenha();
    } else if (etapa != 0) {
      ultimaAuth = agora;
      if (tecla == '*') {
        if (digitos > 0) digitos--;
        telaSenha();
      } else if (tecla >= '0' && '9' >= tecla) {
        if ((etapa == 1 ? 6 : 4) > digitos) {
          entrada[digitos++] = tecla;
          telaSenha();
        } else falha();
      } else if (tecla == 35) {
        if (etapa == 1 && digitos == 6 && hashEntrada() == 0xC30CDA64UL) {
          etapa = 2;
          digitos = 0;
          telaSenha();
          Serial.println("Codigo mestre aceito");
        } else if (etapa == 2 && digitos == 4 && hashEntrada() == 0xCBEF63BCUL) {
          desarmarAlarme();
        } else falha();
      }
    }
  }
  ultimaTecla = tecla;
  delay(30);
}
