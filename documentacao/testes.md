# Roteiro e registro de testes

Abra o Monitor Serial a 9600 baud. Execute cada teste na simulação e repita na placa física. Registre o resultado observado e anexe evidências em `imagens/`.

| Teste | Procedimento e resultado esperado | Simulação | Placa física |
|---|---|---|---|
| Diagnóstico integrado | Teclado, LCD, servo, buzzer, LED e sensores respondem | Sucesso relatado | Pendente |
| Inicialização V5 | Compilar e iniciar sem erro | Sucesso relatado | Pendente |
| Armar | Após aquecimento, A; aguardar 5 s; servo em 90° | Pendente | Pendente |
| Porta | Com alarme armado, pressionar botão D12; sirene, LED e PORTA ABERTA | Pendente | Pendente |
| Vidro | Desarmar, rearmar e pressionar botão D11; VIDRO VIOLADO | Pendente | Pendente |
| PIR | Desarmar, rearmar e simular movimento; MOVIMENTO | Pendente | Pendente |
| Autenticação | D, 246810#, 1234#; sirene para e servo retorna a 0° | Pendente | Pendente |
| Senha incorreta | D, 246810#, 0000#; proteção permanece ativa | Pendente | Pendente |
| Anti-Brute Force | D, 000000# três vezes; bloqueio de 30 s | Pendente | Pendente |
| Vigilância no bloqueio | Acionar sensor durante bloqueio; sirene e LED ativos | Pendente | Pendente |
| Recuperação | Após 30 s, autenticar corretamente | Pendente | Pendente |
| Expiração | Iniciar autenticação e aguardar 20 s sem digitar | Pendente | Pendente |

Os resultados relatados não equivalem a validação independente. A montagem física e os testes de segurança da V5 ainda não foram confirmados.
