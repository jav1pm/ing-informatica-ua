# hada-p1

**P1 ¿Qué rama se ha subido exactamente?**

    La rama master.
    
**P2 ¿Qué pasa al utilizar la opción Comparar con la versión no modificada?**

    Nos muestra las lineas modificadas en nuestro código.
    
 **P3 ¿Y ahora ves algún cambio en el repositorio remoto? ¿Por qué?**
 
    Si nos dirigimos a la clase "HadaP1.cs" de nuestro repositorio remoto vemos como los comentarios escritos en los metodos 
    no se han subido al repositorio remoto.
    
 **P4 ¿Qué significa Confirmar > “Confirmar por etapas” y cuál sería el comando git equivalente?**
 
    Guardar los cambios realizados en nuestro repositorio. En git, su comando equivalente es git add + git commit.
  
 **P5 ¿Qué significa Confirmar > “Confirmar por etapas e insertar” y cuál sería el comando git equivalente?**
 
    Hacemos exactamente lo mismo que en la pregunta anterior pero ahora las modificaciones locales se envian al repositorio remoto.
    En git, su comando equivalente es git add + git commit + git push -u origin master.
 
 **P6 ¿Qué significa Confirmar > “Confirmar por etapas y sincronizar” cuál sería el comando git equivalente?** 
    
    Con esta opción, además de realizar lo anterior, permitimos sincronizar el repositorio local con el remoto.
    En git, su comando equivalente es git pull.

**P7 ¿Cuál es la diferencia entre pulsar Sincronizar o Extraer? ¿Cuáles serían los comandos git equivalentes?**

    La diferencia está en que Extraer es actualizar solo el repositorio local y Sincronizar actualiza el local y el remoto.
    En git, sus comandos serian =>
    Para Sincronizar: git push y git pull
    Para Extraer: git push

**P8 ¿Qué significa Ramas > "Fusionar mediante combinación" y cuál sería el comando git equivalente?**

    Significa que podemos unificar las ramas pero no perdemos el historial. En git, el comando equivalente es git merge. 

**P9 ¿Qué significa Confirmar > "Fusionar mediante cambio de base" cuál sería el comando git equivalente?**

    Unificar las ramas pero perdiendo el historial de los commit. En git, el comando equivalente es git rebase.



Preguntas Práctica 1a: Uso de git

```
    - P1: La opción -n en el comando revert significa que solamente hace el revert y no realiza automáticamente el commit.

    - P2: Si usamos el comando $git reset --hard, lo que hacemos es destruir el último commit completamente como si no hubiera existido.

    - P3: El revert vuelve al estado anterior utilizando los commits que has utilizado y el reset deshace los cambios desde la última confirmación.

    - P4: Cuando haces un rebase, lo que hacemos es como cambiar de rama (checkout). Por otro lado, cuando hacemos un merge de una rama en la tuya, lo que haces es juntar el historial de ambas (todos los commits).
```    
