# Enderman-CG-OPENGL
Enderman (Minecraft) feito em opengl com C++ 

  O trabalho tem como objetivo o desenvolvimento do personagem em 3d 
Enderman do jogo Minecraft, utilizando o opengl, o personagem contara com 
articulações e movimentos.
  Para o desenvolvimento do personagem foi utilizado como base o código
da mão disponibilizado pelo professor, para isso foi definido como cabeça do 
personagem o dedão da mão e para os outros membros como pernas e braços foi 
utilizado os outros dedos, a palma da mão foi convertida no tronco do 
personagem.
  Foi utilizado a biblioteca SOIL.h para adição de textura ao projeto, foi 
utilizado GL_QUADS para adição da textura, ao todo foram utilizadas 3 texturas 
no personagem sendo as 3 do rosto com variações.

![image](https://user-images.githubusercontent.com/57024499/183314040-e68adfbd-ceb4-4910-ad15-47f6d8b159b0.png)
  
  As texturas do rosto são trocadas para fazer uma animação de olho 
piscado, foi utilizado a função glutTimerFunc para disparar essa mudança em 10 
segundos.

  ![image](https://user-images.githubusercontent.com/57024499/183314059-943d44b0-b79b-452d-bded-4e294bd137b9.png)

  O desenvolvimento do personagem tem o intuito de deixar o mais parecido 
com o original encontrado no jogo, alem de adicionar algumas movimentações ao 
personagem.
  ![image](https://user-images.githubusercontent.com/57024499/183314073-8cfa46f9-ad06-4abc-b79b-39b0c6d83ea0.png)
  As animações que foram criadas para o projeto foram as de dança, andar e 
tchau, para criação da dança foi usado como referência o jogo Fortnite e suas 
animações, a animação de tchau é a movimentação do seu abraço acenando para 
a tela, já a movimentação de andar é a junção da movimentação dos braços e 
pernas do personagem.
  O trabalho possui também outros tipos de movimento como a 
movimentação de cada membro do personagem e rotação do personagem na tela 
permitindo visualizar de qualquer angulo.
  ![image](https://user-images.githubusercontent.com/57024499/183314091-f655b975-9b6b-4c13-9e38-498f5af15946.png)
  Com isso, pudesse visualizar que o desenvolvimento do personagem em 3d 
foi realizada com sucesso, permitindo que o personagem faça movimentos como 
tchau, dançar e andar alem dos movimentos de cada membro e a rotação do 
personagem em todos os eixos
