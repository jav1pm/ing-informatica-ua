print("¡Hola, soy Minibot!")
print("¿Quieres escanear la habitación?")

while True:
    res = input()

    if (res == "y" or res == "Y"):
        print("Introduce la primera medida del láser (arriba): ")
        medida1 = input()
        print("Introduce la segunda medida del láser (abajo): ")
        medida2 = input()
        print("Introduce la tercera medida del láser (derecha): ")
        medida3 = input()
        print("Introduce la cuarta medida del láser (izquierda): ")
        medida4 = input()

        largo = int(medida1) + int(medida2)
        print("El largo del robot es de", largo)

        ancho = int(medida3) + int(medida4)
        print("El ancho del robot es de", ancho)

        superficie = largo * ancho
        print("La superficie total del robot es de", superficie)
        print("Posición del robot (X,Y) = (", medida4, ",", medida2, ")")
        break

    elif (res == "n" or res == "N"):
        print("¡Minibot se despide! - Fin del programa")
        break

    else:
        print("No te he entendido, vuelve a introducir una respuesta válida (y/Y o n/N): ")
