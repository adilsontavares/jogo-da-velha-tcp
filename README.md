# Comunica��o TCP
Projeto de comunica��o entre clientes e servidor, utilizando o protocolo TCP.

O cliente envia mensagens para o servidor, o qual transformar� em mai�sculo e retornar� para o cliente.

## Funcionamento
### Cliente
O cliente envia para o servidor as mensagens que o usu�rio inserir no terminal.

### Servidor
O objetivo do servidor � enviar novamente para o cliente todas as mensagens que recebeu. Por�m, a mensagem ser� retornada em mai�sculo.

### Exemplo
1. Usu�rio digitou "Hello world!"
2. Cliente enviou "Hello world!" para o servidor
3. Servidor alterou a mensagem para "HELLO WORLD!"
4. Servidor envia a nova mensagem para o cliente
5. O cliente mostra a mensagem na tela
