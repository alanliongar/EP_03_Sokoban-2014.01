# EP03_Sokoban - 05/07/2014

<html>
<body>
<center>
  <h2>MAC110 - Introdução à Computação
    <br>
    Prof. Dr. Paulo Miranda
    <br>
    Instituto de Matemática e Estatística (IME)
    <br>
    Universidade de São Paulo (USP)
    <br>
  </h2>
</center>

Sokoban (zelador do armazén) é um tipo de jogo de transporte e movimentação de caixas ou engradados
em um armazém. O objetivo é pegar e estocar os engradados em determinadas posições. Sokoban foi
criado em 1981 por Hiroyuki Imabayashi, e publicado em 1982 por Thinking Rabbit, uma emrpesa de
software localizada em Takarazuka.<br><br>
Regras:<br>
• Os únicos movimentos que o trabalhador pode realizar são andar e empurrar caixas que somente
se deslocam nos sentidos horizontal e vertical. Nenhuma caixa pode ser puxada, sendo assim,
quando são colocadas nos cantos do cenário não podem mais serem movidas.
• Apenas uma caixa pode ser movimentada por vez. Não é permitido empurrar duas ou mais caixas
juntas de uma só vez.<br>
• O jogador não poderá ocupar o mesmo lugar da caixa ou andar nos muros.<br>
• O jogo é finalizado quando as caixas são colocadas nas posições predeterminadas.<br>
Para melhor entender a dinâmica do jogo, nada melhor do que jogar a versão online disponível em: http://www.game-sokoban.com/<br><br>

Atividade:<br>
Faça um programa em C que implementa uma versão em modo texto no terminal do jogo Sokoban.
O seu programa deve ler uma fase do jogo (cenário/mapa do jogo) de um arquivo texto fornecido pelo
usuário, mostrar no terminal o cenário correspondente, solicitar a entrada de uma lista de comandos (string),
processar os comandos, guardar o histórico de movimentos realizados, permitir que movimentos sejam
desfeitos (undo), e finalizar o jogo com uma mensagem de vitória, quando as caixas forem colocadas nas
posições predeterminadas (locais de armazenamento).<br><br>
Os formatos de arquivo texto contendo os cenários serão os mesmos que são usados pelos sites:
http://www.game-sokoban.com/ e http://www.sokoban-online.de/<br>


<img src="https://github.com/user-attachments/assets/2da3f998-db6c-4935-821a-701d792d4d25" width="800"/>
Formato padrão:
O formato mais utilizado para representar os níveis Sokoban usa a seguinte tabela de codificação:


<img src="https://github.com/user-attachments/assets/4744295a-de2e-4cb9-afed-a841bb062892" width="800"/>



O nível mais simples possível corresponde a um arquivo texto com as seguintes linhas:<br><br>
<pre>
#####<br>
#@$.#<br>
#####<br><br></pre>
É importante que todo o nível seja cercado por muros.
Uma solução do jogo é representada pelo histórico de movimentos do jogador.<br>
O jogador pode mover-se para cima, baixo, esquerda ou direita. Cada movimento é representado por uma das seguintes letras: u, d, l, r (u = up, d = down, l = left, r = right).<br>
Letras maiúsculas são usadas no histórico para indicar que uma caixa foi empurrada pelo movimento do jogador. Essa informação é importante para permitir desfazer movimentos (operação de “undo”) sem ambiguidade.<br><br>
Exemplos de cenários com um possível histórico de solução:
<pre>
#######<br>
#     #<br>
# $+$ #<br>
#.*#*.#<br>
# $.$ #<br>
#     #<br>
#######<br>
</pre>
Solução: LulDrrurrdLrdddlluRdrUdlllluR<br><br>
<pre>
#####<br>
#   #<br>
#.*.###<br>
# *   #<br>
# $.**#<br>
#  $ ##<br>
# $ ##<br>
#@ ##<br>
####<br>
</pre>
Solução: uuuuuRldddrUUddlddrUrUdlruLdlUUU<br><br>
<pre>
####<br>
#  ####<br>
#  $  ###<br>
# $#$  .##<br>
#  $  ...#<br>
# $#$ ...#<br>
#  $  ####<br>
#@ ####<br>
####<br>
</pre>
Solução: uuurRRRRRlululLrrlrddudlllluuRlddrDuluurDlddrUrrrlllluurDldRRRRRurDldRluululLrrddllluluurDldddddrUUluudRRRRdrluRdrUllddlLrruulllldddrUUluRRRRRluulllDldRRRRurDldRluddlUdllluurrRRuulDullldrdrRurDldR<br><br>

Formato XSB (Run length encoding):<br><br>
O formato XSB com RLE (run-length-encoding), é mais compacto e eficiente em dispositivos móveis, além
de ser menor para enviar por SMS.<br><br>

Neste formato dígitos mostram quantos elementos do mesmo tipo estão a seguir.<br>
Por exemplo, o padrão de código #### pode ser escrito simplesmente como 4#<br>
Os cenários no formato XSB são fornecidos em uma única linha de texto, sendo a barra vertical “|” usada no lugar dos caracteres de quebra de linha, e os espaços em branco de piso são geralmente codificados usando hífens “-”.<br>
Por exemplo, o cenário abaixo:<br><br>
<pre>
#######
#.@ # #
#$* $ #
#   $ #
# ..  #
#  *  #
#######
</pre>
codificado em XSB com RLE fica: 7#|#.@-#-#|#$*-$-#|#3-$-#|#-..--#|#--*--#|7#<br><br>
Uma descrição detalhada dos formatos pode ser encontrada em:<br>
http://www.sokoban-online.de/help/sokoban/level-format.html<br><br>
Durante a leitura do arquivo de cenário, o seu programa deve selecionar o padrão de codificação de acordo com a extensão do arquivo: “.txt” para formato padrão e “.xsb” para codificação XSB com RLE.<br>

O seu programa deve implementar as seguintes funções:<br>

void LoadLevel(char map[LIM][LIM], int *m, int *n, char filename[]);<br>

Função que lê um cenário, no formato padrão, do arquivo filename na matriz map, e devolve em *m e *n o número de linhas e colunas do mapa, respectivamente.<br><br>
void LoadLevelXSB(char map[LIM][LIM], int *m, int *n, char filename[]);<br><br>
Função que lê um cenário, no formato XSB com RLE, do arquivo filename na matriz map, e devolve em *m e *n o número de linhas e colunas do mapa, respectivamente.<br><br>

void PrintLevel(char map[LIM][LIM], int m, int n);<br><br>
Função que imprime no terminal (saída padrão) o cenário no formato padrão. O cenário é dado pela matriz map com m linhas e n colunas.<br><br>
void GetPlayerPos(char map[LIM][LIM], int m, int n, int *i, int *j);<br><br>
Função que devolve em *i e *j as posições (linha e coluna) do jogador na matriz map.<br><br>
int Move(char *mov, char map[LIM][LIM], int m, int n);<br><br>
Função que realiza o movimento dado por *mov atualizando a matriz de estado do jogo, onde *mov pode assumir um dentre os seguintes valores: u, d, l, r.<br>
O valor de *mov deve ser alterado para letras maiúsculas quando uma caixa é empurrada pelo movimento.<br>
A função deve devolver verdadeiro quando o movimento é válido e falso no caso de movimento impossível (ex: empurrar duas ou mais caixas juntas de uma só vez).<br><br>
void Undo(char mov[MAXMOV], char map[LIM][LIM], int m, int n);<br><br>


Função que desfaz o último movimento presente no histórico de movimentos (string mov), atualizando a matriz de estado do jogo de modo correspondente. A string mov deve ser também atualizada, removendo o seu último caracter.<br><br>
int LevelComplete(char map[LIM][LIM], int m, int n);<br><br>
Função que verifica se todas caixas estão colocadas nas posições predeterminadas, indicando o fim do jogo. A função deve devolver verdadeiro (vitória do jogador) ou falso (jogo não encerrado).<br><br>

int IsValidLevel(char map[LIM][LIM], int m, int n);<br><br>

Função que testa se o cenário é um cenário válido. Todo cenário deve ter um único jogador, quantidade igual de caixas e locais de armazenamento, e pelo menos um lugar de armazenamento. A função deve devolver verdadeiro (cenário válido) ou falso (cenário inválido).<br>
OBS: Por propósitos de simplicidade, a parte de verificar se o cenário está cercado por muros é opcional.<br><br>

Exemplo de execução do programa:

<img src="https://github.com/user-attachments/assets/3baa9bbc-82e2-4892-9c99-cb4e34549917" width="500"/><br>

<img src="https://github.com/user-attachments/assets/61d6a9c7-8c6a-43a3-a3ed-03c9309cdab3" width="500"/><br>


