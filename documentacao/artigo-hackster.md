# AutoGuard — Segurança automotiva além da chave

**Equipe:** Maria Bianca, Laura Júlia, Bruna Mylena e Maria Letícia.

## Resumo
Protótipo de alarme automotivo com Arduino Uno, três entradas de detecção, trava por servo e autenticação em duas etapas com bloqueio temporário contra tentativas repetidas.

## História do projeto
A proposta surgiu da necessidade de demonstrar como sistemas embarcados podem detectar acessos indevidos e proteger um veículo simulado. O AutoGuard combina botões que representam a porta e o vidro, um PIR que identifica movimento e um teclado para controlar a segurança. Quando ocorre uma violação, o sistema aciona uma sirene, pisca um LED e informa a causa no display.

## Componentes
Arduino Uno R3 (1), teclado 4×4 (1), botões (2), PIR (1), servo (1), LCD 16×2 I2C (1), buzzer piezo (1), LED (1), resistor 220 Ω (1), protoboard e jumpers.

## Construção e funcionamento
1. Conecte os componentes conforme o pinout do repositório.
2. Carregue o firmware V5 no Tinkercad; para a placa física, valide as bibliotecas, alimentação e tempo de estabilização do PIR.
3. Pressione A após o aquecimento. O sistema aguarda cinco segundos e trava a maquete.
4. Acione os sensores e observe os alertas sonoros e visuais.
5. Pressione D, digite 246810# e depois 1234# para desarmar.
6. Repita uma credencial incorreta três vezes para demonstrar o bloqueio de 30 segundos. Verifique que os sensores permanecem ativos.

## Segurança e algoritmo
O firmware emprega lógica de estados, temporização com millis(), debounce, autenticação sequencial e comparação de hashes DJB2 com sal fixo. O mecanismo tem finalidade didática: não constitui autenticação de dois fatores independentes, nem oferece segurança criptográfica comercial. A comunicação é local, sem conectividade de rede.

## Resultados e próximos passos
Os componentes funcionaram na simulação de diagnóstico e a V5 iniciou sem erro de compilação, conforme os testes relatados pela equipe. A validação completa da segurança e a montagem física ainda precisam ser registradas. Como evolução, podem ser incorporados sensores magnéticos reais, autenticação por fator físico e conectividade protegida.

## Código e esquemático
Repositório: https://github.com/Biancaxr/AutoGuard.
Anexar imagem do Tinkercad, firmware V5, fotos da montagem física e vídeo dos testes após realizá-los.
