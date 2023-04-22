OBJETIVO DO PROJETO:
O que  deve ser implementado:

Desenvolva um jogo  de adivinhação onde vamos utilizar um microcontrolador, dois displays e  4 botões.

Serão conectados ao mesmo microcontrolador os 2 displays e os 4 botões.

Cada participante  do jogo  utiliza 2 botões e um display.

Um participante configura um número para ser adivinhado no seu display  e o outro participante  tenta acertar o número escolhendo  com os seus botões e display.

A cada jogada as do participante se alterna (configura ou adivinha).

Será necessário utilizar a mesma interface SPI para acionar os dois displays. Para tanto será necessário  criar sinais de chip select para cada um dos displays . Para isso pode-se  alterar o driver  user_5110,  adicionando um parâmetro nas funções para indicar qual dos displays devem ser  ativados. A outra opção é  manter a implementação do driver original e  controlar o sinal de chip select para cada display de forma manual antes de chamar as funções do driver.

OBS: Projeto foi implementado utilizando interfaces SPI diferentes. Para isso, foram necessárias alterações nas libs.