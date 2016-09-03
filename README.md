# Jogo da Velha
Jogo da velha multiplayer desenvolvido em C++.

## Projetos
### Common
Contém componentes comuns e genéricos a todos os projetos. Estão presentes classes de Erro, Console, Socket e outros.

### Game
Implementação geral do Jogo da Velha a ser controlado externamente por outros métodos através de comandos (funções).

### Cliente
Jogador a se conectar com o servidor e participar da partida. É a interface entre o usuário e a comunicação com o servidor.

### Servidor
Servidor controlador do jogo. Nele se conectam clientes que participarão da partida e irão competir entre si.