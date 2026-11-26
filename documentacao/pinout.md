# Pinout da V5

| Componente | Pino do componente | Arduino Uno | Observações |
| :--- | :--- | :--- | :--- |
| Teclado 4×4 | Linhas 1–4 | D9, D8, D7, D6 | Varredura matricial |
| Teclado 4×4 | Colunas 1–4 | D5, D4, D3, D2 | INPUT_PULLUP |
| Sensor PIR | OUT | D10 | HIGH indica movimento |
| Sensor PIR | VCC / GND | 5V / GND | Alimentação |
| Botão da porta | Contato / retorno | D12 / GND | LOW quando pressionado |
| Botão do vidro | Contato / retorno | D11 / GND | LOW quando pressionado |
| LED vermelho | Ânodo / cátodo | D13 / GND | Resistor de 220 Ω em série |
| Servo motor | Sinal | A0 | 0° destravado; 90° travado |
| Servo motor | VCC / GND | 5V / GND | Fonte externa de 5V se necessário, com GND comum |
| Buzzer piezo | Positivo / negativo | A1 / GND | tone() |
| LCD I2C | SDA | A4 | Dados |
| LCD I2C | SCL | A5 | Clock |
| LCD I2C | VCC / GND | 5V / GND | Alimentação |
