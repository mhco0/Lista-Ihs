# Projeto
CinBomb

## Requerimentos
* Versão da Allegro 5.2 ou maior
* Versão do Cmake 3.6 ou maior
* Todos os requerimentos da Allegro lib
* Sistema POSIX

## Como rodar
Depois de instalado todos os requerimentos é necessário que a pasta esteja no seu Desktop junto com a pasta da allegro5.
Para instalar o driver é necessario que se vá na pasta `projeto_base_drivers` e rodar o script `lazy_shell.sh`, ele rodará o código
`app.c` que vai desligar as luzes da placa , escrever `1010` no display e tentar ler os switches. Instalado os drives , o projeto se 
encontra em `Game/CinBomb/src` , se tudo estiver sido feito com sucesso basta rodar make no terminal dessa pasta e um display será mostrado
com o jogo padrão Genius , para alterar os jogos basta ir no código da main e na linha 817 em `minigames* m = new genius();` trocar a classe 
de jogo que está sendo criada , exemplo: quero mudar para o jogo Cut Wire  então eu vou na linha 817 e escrevo `minigames* m = new cut_wire();`.

### Detalhe
O projeto se encontra em [](https://github.com/mhco0/Lista-ihs) . Basta entrar nesse link para mais detalhes
