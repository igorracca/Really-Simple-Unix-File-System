# Really-Simple-Unix-File-System

# Projeto Final: Sistemas de Arquivos

**1 Objetivo** 

Entender mais a fundo a construção de software básico, construindo um sis-
tema de arquivos elementar a partir de um dispositivo de disco genérico.

**2 Visão Geral**

Um sistema de arquivos transforma um dispositivo de disco que armazena se-
tores de dados em uma abstração de mais alto nível: arquivos. Um dispositivo
de disco permite apenas guardar e recuperar setores com um número fixo de
bytes. Cabe ao programador do sistema de arquivos organizar estes setores,
de forma a dividi-los entre todos os dados a serem armazenados, alocá-los
ou desalocá-los a medida que os dados crescem ou diminuem, gerenciar o
espaço livre, etc. Arquivos, por outro lado contém uma sequência contínua
de bytes com tamanho variável. O programador de aplicação não se preocupa
com como estes dados são guardados, como o arquivo cresce ou diminui, em
quais setores estão os dados, etc. Arquivos são localizados por nome, e a sua
enumeração, criação e remoção são tarefas bem simples.
Neste projeto nós iremos construir um sistema de arquivos sobre um dis-
positivo de disco simulado, para prover os serviços necessários ao funciona-
mento de um interpretador de comandos elementar. Uma visão esquemática
é a seguinte:

Neste diagrama, cada camada é implementada utilizando apenas as fun-
ções fornecidas pela camada inferior. A implementação do dispositivo de
disco e do interpretador de comandos, além da especificação do sistema de
arquivos, serão fornecidos pelo professor.Figura 1: Visão Geral da Arquitetura de Software

**3 Tarefas**

Neste projeto a sua tarefa é implementar as funções usadas pelo interpreta-
dor de comandos usando como base as funções fornecidas pelo dispositivo
de disco. O código fonte fornecido já está estruturado com implementações
vazias destas funções, falta completar a sua implementação. O sistema de ar-
quivos implementado deve seguir a especificação contida neste documento,
em especial as simplificações e limitações dadas para tornar a tarefa mais sim-
ples.
