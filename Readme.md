# Introdução

Este documento servirá de “manual de uso” das ferramentas de Romhacking utilizadas no projeto de tradução do jogo “Panzer Bandit”, da plataforma Sony Playstation, desenvolvido pela empresa *Fill in Café.*



## Ferramentas utilizadas

Para realizarmos todo o processo de extração, edição e reinserção dos textos no jogo do Panzer Bandit, utilizaremos as seguintes ferramentas:

·     CDMage, disponível em https://www.romhacking.net/utilities/1435/

·     kisindat_reimporter (incluída neste repositório)

·     Inserter_panzer (incluída neste repositório)



## CDMage

Ferramenta exclusiva para jogos de Playstation, que neste projeto será utilizada para visualizar, extrair e reinserir containers de dados binários existentes na primeira camada da imagem iso do jogo. No nosso caso, o arquivo container que será usado para edição dos textos e outros “*resources*” do jogo Panzer Bandit será o KISINDAT.NCB.



## kisindat_reimporter

Ferramenta de extração e reinserção de “sub arquivos” existentes dentro do Container principal “KISINDAT.NCB”.  A ferramenta foi desenvolvida pelo Romhacker Mumm-ra em linguagem Python e pode ser executada via linha de comando acessando-se o arquivo “Extrair.bat” da pasta “/kisindat_reimporter” ou o arquivo “Reimportar.bat” da mesma pasta.



## Inserter_panzer

Ferramenta feita por mim (Kuroi) utilizada para reinserir os textos traduzidos nos “sub arquivos” gerados pela ferramenta “kisindat_reimporter”. A ferramenta foi toda desenvolvida em linguagem C e seu código fonte também está disponível neste repositório. Para utilizá-la, basta executar o arquivo “Inserter_panzer.exe” da página inicial do repositório, ou utilizar o arquivo .bat “Executar.bat”, que executa a ferramenta “Inserter_panzer” em conjunto com a ferramenta “kisindat_reimporter”, já copiando também todos os resources editados separadamente.



# Estrutura de pastas

O projeto de tradução do Panzer Bandit possui uma estrutura de pastas bem definida para que os tipos diferentes de “resources” fiquem mais organizados, portanto, temos as seguintes pastas:



## Arquivos Profile

A pasta “Arquivos Profile” carrega nela todos os sub arquivos referentes aos gráficos da abertura do jogo, que demonstram a história de cada personagem da trama. Os mesmos podem ser abertos em ferramentas de edição de imagem de formato TIM do Playstation e exportados para PNG, para que possam ser editados no Photoshop ou afins antes da reinserção no Container via “kisindat_reimporter”.

Atentar para quando for editar os arquivos PSD que estão dentro da pasta "\Profile\PSDs", salvar os arquivos usando o "Salvar como" simples do Photoshop e cortar todos os arquivos em dois pedaços de 256X240 em png simples, antes de reinserir nos arquivos binários.



## Binarios

A pasta “Binarios” agrega todos os sub arquivos que contém textos do jogo. Portanto, a ferramenta “Inserter_panzer” atuará diretamente usando esses 14 arquivos binários como referência.



## Binarios_orig

Assim como a pasta “Binarios”, a pasta “Binarios_orig” guardam todos os sub arquivos que contém textos, porém já editados e traduzidos.



## Ponteiros

A pasta “Ponteiros” possui as referências de ponteiros “hardcoded” do jogo. Dentro dela estão todos os parâmetros que dizem onde se encontram os ponteiros de cada arquivo binário de texto do jogo.

 

## scripts_originais

Assim como o nome já diz, esta pasta serve para guardar todos os arquivos de texto referentes aos Scripts originais (em japonês) de texto do jogo, porém, como não desenvolvemos nenhuma ferramenta de Dumper neste projeto, a pasta está vazia.

 

## scripts_traduzidos

A pasta “scripts_traduzidos” possui todos os textos traduzidos do japonês para o Português Brasileiro em formato texto. Os arquivos estão formatados especificamente em codificação ANSI para serem lidos pela ferramenta “Inserter_panzer”, que medirá os seus tamanhos e posteriormente os reinserirá no arquivo binário correspondente ao bloco de texto em específico.

 

##  Staff

Esta pasta possui os arquivos referentes aos gráficos de “Staff” que desenvolveu o jogo original, assim como também os créditos do pessoal que contribuiu para a tradução do mesmo. Dentro dela há um arquivo binário base que contém a imagem TIM original do Staff, um arquivo .psd editável no Photoshop, que permite a edição dos dados de saída e um arquivo de imagem de extensão .png que permite a reinserção dos gráficos editados no arquivo binário utilizando-se de alguma ferramenta de edição de gráficos TIM para Playstation.

 

## Arquivo Blocos_Panzer.txt

O arquivo “Blocos_Panzer.txt” possui todos os parâmetros de começo e fim dos textos nos arquivos binários que possuem texto do jogo. Servirá somente como referência para o Inserter, na hora de reinserir os textos traduzidos.



# Extração do Container KISINDAT.NCB

Agora que já foram apresentadas as ferramentas e toda a estrutura de pastas do repositório, partiremos para o processo de utilização das ferramentas propriamente ditas.

A primeira etapa do processo de tradução dos textos do Panzer Bandit consiste na extração do container principal, “KISINDAT.NCB” de dentro da iso do jogo. Para isso utilizaremos a tool CDMage.



**Passo 1:** Abertura da iso traduzida para o português

Uma vez baixada a versão traduzida da iso do Panzer Bandit, abra-a utilizando o menu “File/Open” do CDMage, conforme imagem abaixo:

![image-20240729001943486](https://i.imgur.com/7Kq5TrF.png)



Certifique-se também de abrir o arquivo .CUE referente à imagem gerada, para que os parâmetros de “Track 1” e “Track 2” também sejam exibidos pelo programa. Os dados que utilizaremos se encontram na Track 1.



**Passo 2:** Extração do KISINDAT.NCB

Uma vez dentro da iso, a seguinte tela será exibida, se selecionarmos a “Track 1” do jogo:

![image-20240729002023669](https://i.imgur.com/1WjIocb.png)



O objetivo principal nesta tela é extrair o Container “KISINDAT.NCB”, portanto devemos clicar com o botão direito em cima dele e escolher “Extract files...”:

![image-20240729002044222](https://i.imgur.com/UyuR93s.png)

Após isso, escolha uma pasta de saída na linha “Extract files to:” da próxima tela e clique em “Extract”:

![image-20240729002415692](https://i.imgur.com/wN2lyNV.png)

Pronto, Container extraído.



# Extração dos arquivos do Container

Uma vez com o Container KISINDAT.NCB extraído, agora podemos usar a ferramenta “kisindat_reimporter” do Mumm-ra para extrair todos os sub arquivos binários referentes aos “resources” do jogo. Para isso, vamos primeiro executar o arquivo .bat “Extrair.bat” da pasta “kisindat_reimporter”, que possui a seguinte sintaxe no seu comando:

python kisindat_extractor.py e SLPS_008.99 KISINDAT.NCB .\output2

Este comando executa a ferramenta passando como primeiro parâmetro o arquivo KISINDAT.NCB e como segundo parâmetro o endereço da saída, pasta “output2”. Após a extração, a pasta “output2” terá 198 arquivos, dentre eles, gráficos, textos e outros resources.

Obs: Se o comando não rodar, certifique-se que você tenha o Python instalado em sua máquina, para que possa executar comandos “python”.

 

# Tradução dos textos

Obviamente, este processo seria auto-explicativo, não fossem algumas “regras” que devem ser levadas em consideração na inserção dos textos nos arquivos. Vamos a elas.

O exemplo abaixo trata-se de um script do jogo Panzer Bandit em PT-BR:

![image-20240729002455772](https://i.imgur.com/jRvQvn1.png)

Repare que há um {0a} ao final de cada linha e que depois de cada bloco de texto (string) existe um número irregular de {00}. Isso significa que todas as Quebras de linha são feitas com o uso do Byte {0a} e que o Endstring é composto pelo {08} seguido de {00} suficientes para “preencher” os espaços vazios restantes na memória. 

Com isso em mente, podemos substituir o texto em português por qualquer outra língua latina simplesmente mantendo os Bytes de quebra de linha e fim de diálogo, mantendo também o tamanho de cada string e considerando o tamanho de 1 Byte para cada letra e 1 Byte para cada hexadecimal dentro de {}.



# Inserção dos textos nos arquivos binários

Como foi explicado anteriormente, a ferramenta “Inserter_panzer” utiliza como auxílio diversos arquivos e pastas, dentre eles o arquivo “Blocos_Panzer.txt”, a pasta “Binarios”, a pasta “Ponteiros” e a pasta “scripts_traduzidos”. Mas como os mesmos já estão configurados aqui no repositório, precisamos simplesmente rodar a ferramenta “Inserter_panzer.exe” para que possamos ver a seguinte tela:

![image-20240729002524282](https://i.imgur.com/YN07D2D.png)



Na tela acima, pressione 1 e pressione ENTER para ir para a tela seguinte:

![image-20240729002536486](https://i.imgur.com/BU4cyYF.png)



Se você pressionar do número 1 ao 15, poderá escolher um script em específico para reinserir. Porém, se pressionar o 0, irá inserir todos os scripts em todos os arquivos em sequência.

Independente da escolha do usuário, ao pressionar ENTER após o número desejado, o programa deve fazer uma checagem de tamanho em Bytes do arquivo traduzido e a ferramenta só fará a reinserção se o mesmo couber dentro do espaço disponível no arquivo binário.



 

# Remontagem do container

Uma vez que eu já tenha inserido todas as mudanças necessárias nos arquivos que compõem o Container, preciso voltar a montá-lo, para que possa compor um novo KISINDAT.NCB. Para isso voltaremos a usar a ferramenta do Mumm-ra, “kisindat_reimporter”.

Dentro da pasta do “kisindat_reimporter” existe mais um arquivo .bat chamado “Reimportar.bat”, que possui os seguintes comandos:

 

xcopy "..\Binarios\*.*" "output2\" /s /f /Y

xcopy "..\Arquivos_Profile\*.*" "output2\" /s /f /Y

xcopy "..\Staff\STAFF.SP" "output2\" /s /f /Y

python kisindat_extractor.py r SLPS_008.99 KISINDAT.NCB .\output2

pause

 

Os comandos acima fazem:

1-  Copiar o conteúdo da pasta “\Binarios” para dentro da pasta “\output2”

2-  Copiar o conteúdo da pasta “\Arquivos_Profile” para dentro da pasta “\output2”

3-  Copiar o arquivo “STAFF.SP” da pasta “\Staff” para dentro da pasta “\output2”

4-  Rodar a ferramenta kisindat_reimporter passando o arquivo SLPS_008.99 da iso original como primeiro parâmetro, o arquivo KISINSDAT.NCB com segundo parâmetro e a pasta de referência “\output2” como terceiro parâmetro

 

Após rodar o comando corretamente, um novo arquivo KISINDAT.NCB chamado  “KISINDAT.NCB_new” e um novo arquivo SLPS chamado “SLPS_008.99_new” serão criados. Container remontado.



# Reinserção do novo container KISINDAT.NCB na iso

Agora que já temos o novo container montado e configurado, basta reinseri-lo novamente na iso usando de novo a ferramenta CDMage.

**Passo 1:** Abrir a iso com o CDMage

![image-20240729002610334](https://i.imgur.com/f4SHucX.png)



**Passo 2:** Clicar com o botão direito no arquivo KISINDAT.NCB e escolher “Import File...”

![image-20240729002621789](https://i.imgur.com/yTdKvL4.png)



**Passo 3:** Encontrar o arquivo KISINDAT.NCB_new gerado anteriormente e importá-lo

 

**Passo 4:** Fazer o mesmo processo de importação para o arquivo SLPS_009.99_new



# Testar a tradução no emulador

Após todo o processo, basta agora só testar a tradução no emulador e ver se funcionou.