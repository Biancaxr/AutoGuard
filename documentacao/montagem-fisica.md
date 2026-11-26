# Montagem e gravação física

1. Desconecte a alimentação e faça as ligações conforme [pinout](pinout.md).
2. Utilize resistor de 220 Ω em série com o LED e terra comum. Use alimentação de 5 V adequada para o servo; se externa, una os GNDs.
3. Abra `codigo/alarme_v5/alarme_v5.ino` no Arduino IDE. Instale Servo e Adafruit LiquidCrystal pelo gerenciador de bibliotecas.
4. Confirme o modelo do LCD. O código usa Adafruit_LiquidCrystal lcd(0); módulos PCF8574 podem requerer biblioteca e endereço diferentes. Não altere a V5 de simulação: faça uma cópia para adaptar ao hardware.
5. Verifique o tempo de estabilização do PIR real e adapte os dois limites de 5000 ms associados ao aquecimento, mantendo os 5000 ms da contagem de saída.
6. Selecione Arduino Uno e a porta serial, compile e envie. Abra o Monitor Serial a 9600 baud.
7. Execute o [roteiro de testes](testes.md) e fotografe a montagem.

Não conecte o protótipo diretamente ao sistema elétrico automotivo. Procedimento ainda não validado em placa física.
