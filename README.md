# KernelPanicHDMI
Repositorio com o código fonte do projeto final da disciplina PCS3732.

O projeto tem como objetivo a implementação de um _driver_ que permitirá a execução do jogo <a href="https://www.ponggame.org/">Pong</a> usando a saída HDMI da Raspberry Pi 0W. O grupo implementará o projeto através de uma aplicação _bare metal_ para o modelo citado de Raspberry Pi.

A documentação referente ao desenvolvimento do projeto se encontra na pasta `doc` no formato PDF.

## Dependências
As dependências usadas durante o desenvolvimento do projeto foram:
- Ferramentas binárias para o ARM, possibilitando realizar operações "cruzadas" para a arquitetura do processador da Raspberry
- Funções do _runtime_ do gcc, instaladas juntamente com o compilador cruzado

## Periféricos da Raspberry Pi
Para o desenvolvimento do projeto, utilizaram-se alguns periféricos da Raspberry Pi 0W. Os periféricos usados pelo grupo foram:
- _Mailbox 0_: Periférico responsável pela comunicação entre a CPU e GPU da placa. Utilizado para a alocação de um _frame buffer_, o que permite com que a própria CPU altere a saída HDMI
- Mini UART: Usado para a comunicação serial entre o computador em que serão feitas as ações do jogo e a placa
- _Core Timer_: _Timer_ utilizado para atualização periódica da interface

## Guia para desenvolvimento
O projeto se encontra estruturado da seguinte forma: Na raíz do diretório, existem alguns arquivos necessários para a geração dos arquivos executáveis e os arquivos de imagem finais, aqueles que são carregados na Raspberry, como o `linker.ld` e `Makefile`, além de possuir o arquivo `jtag.cfg` de configuração da interface J-Tag, útil para depuração do código.

Além disso, a pasta `build` concentra os arquivos objeto gerados no processo de compilação e usados na vinculação, enquanto a pasta `dir` contém o arquivo `kernel.img`, o qual será a nossa aplicação _bare metal_ a ser carregada na placa.

Por fim, os códigos fonte do projeto se encontram dentro da pasta `src`, especificamente, na pasta `pong`. Optou-se por uma estrutura de várias pastas dentro de `src` a fim de permitir uma maior flexibilidade na execução de testes durante o desenvolvimento, possibilitando testar funcionalidades específicas separadamente do projeto, em outras pastas dentro de `src`. Para isso, é preciso apenas alterar a linha 9 do `Makefile` e apontar para o projeto alvo desejado.

## Teste do projeto
Para validar a implementação do projeto, basta executar o comando `make`, na raíz do projeto, que o arquivo `kernel.img` será gerado na pasta `dir`, conforme explicado anteriormente. Feito isso, pode-se adicionar tal arquivo ao micro SD a ser carregado na Raspberry Pi. Juntamente com o arquivo `kernel.img`, o micro SD deve possuir os arquivos `bootcode.bin`, `start.elf` e `bcm2708-rpi-zero-w.dtb`, os quais se encontram disponíveis no repositório <a href="https://github.com/raspberrypi/rpi-firmware">rpi-firmware</a>.

Em seguida, deve-se fazer as conexões UART da placa com o computador em que serão realizadas as ações do jogo e a conexão da saída HDMI da placa em um monitor, por exemplo. Após ligar a Raspberry na fonte de alimentação, o jogo é iniciado e o seu estado pode ser acompanhado pelo monitor. 
