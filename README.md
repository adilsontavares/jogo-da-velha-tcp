# Jogo da Velha
Jogo da velha multiplayer desenvolvido em C++.

## Projetos
### Common
Cont�m componentes comuns e gen�ricos a todos os projetos. Est�o presentes classes de Erro, Console, Socket e outros.

### Game
Implementa��o geral do Jogo da Velha a ser controlado externamente por outros m�todos atrav�s de comandos (fun��es).

### Cliente
Jogador a se conectar com o servidor e participar da partida. � a interface entre o usu�rio e a comunica��o com o servidor.

### Servidor
Servidor controlador do jogo. Nele se conectam clientes que participar�o da partida e ir�o competir entre si.