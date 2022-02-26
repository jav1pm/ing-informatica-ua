import Swift;
import Foundation;

// Francisco Javier Pérez Martínez

// Ejercicio 1

// a)

func prefijos(prefijo: String, palabras: [String]) -> [Bool] {
    if(palabras.isEmpty) {
        return []
    }
    else{
        let primero = palabras[0]
        let resto = Array(palabras.dropFirst())
        return [primero.starts(with: prefijo)] + prefijos(prefijo: prefijo, palabras: resto)
    }
}

let array = ["anterior", "antígona", "antena"]
let prefijo = "ante"
print("\n******\n1a) Función prefijos(prefijo:palabras:)\n******")
print(prefijos(prefijo: prefijo, palabras: array))
// Imprime: [true, false, true]

// b)

func mayorImparPar(num: Int, pareja: (Int, Int)) -> (Int, Int) {
    if (num % 2 != 0) {
        return (max(pareja.0, num), pareja.1)
    }
    else {
        return (pareja.0, max(pareja.1, num))
    }
}

func parejaMayorParImpar(numeros: [Int]) -> (Int, Int) {

    if(numeros.isEmpty) {
        return (0, 0)
    }
    else {
        let primero = numeros[0]
        let resto = Array(numeros.dropFirst())
        
        // Llamada recursiva que devuelve la pareja con el mayorImpar y el mayorPar
        let parejaResto = parejaMayorParImpar(numeros: resto)
        return mayorImparPar(num: primero, pareja: parejaResto)
    }
}

let numeros = [10, 201, 12, 103, 204, 2]
print("\n******\n1b) Función parejaMayorParImpar(numeros:)\n******")
print(parejaMayorParImpar(numeros: numeros))
// Imprime: (201, 204)

// Ejercicio 2

// a)

func compruebaParejas(_ numeros: [Int], funcion: (Int) -> Int) -> [(Int, Int)] {
    
    if(numeros.count <= 1) {
        return []
    }
    else {
        let primero = numeros[0]
        let resto = Array(numeros.dropFirst())
        let segundo = numeros[1]

        if(funcion(primero) == segundo){
            return [(primero, segundo)] + compruebaParejas(resto, funcion: funcion)
        }
        else {
            return compruebaParejas(resto, funcion: funcion)
        }
    }
}

func cuadrado(x: Int) -> Int {
   return x * x
}
print("\n******\n2a) Función compruebaParejas(_:funcion:)\n******")
print(compruebaParejas([2, 4, 16, 5, 10, 100, 105], funcion: cuadrado))
// Imprime [(2,4), (4,16), (10,100)]

// b)

func coinciden(parejas: [(Int, Int)], funcion: (Int) -> Int) -> [Bool] {

    if(parejas.isEmpty) {
        return []
    }
    else {
        let primero = parejas[0]
        let resto = Array(parejas.dropFirst())

        if(funcion(primero.0) == primero.1){
            return [true] + coinciden(parejas: resto, funcion: funcion)
        }
        else {
            return [false] + coinciden(parejas: resto, funcion: funcion)
        }
    }
}

let array2 = [(2,4), (4,14), (4,16), (5,25), (10,100)]
print("\n******\n2b) Función coinciden(parejas:funcion:)\n******")
print(coinciden(parejas: array2, funcion: cuadrado))

// Ejercicio 3

enum Movimiento {
    case deposito(Double)
    case cargoRecibo(String, Double)
    case cajero(Double)
}

func calculaMovimientos(movimiento: Movimiento, total: (Double, [String])) -> (Double, [String]){

    switch movimiento {
    case let .deposito(cantidad):
        return (total.0 + cantidad, total.1)
    case let .cargoRecibo(compraEn, cantidad):
        return (total.0 - cantidad, [compraEn] + total.1)
    case let .cajero(cantidad):
        return (total.0 - cantidad, total.1) 
    }
}

func aplica(movimientos: [Movimiento]) -> (Double, [String]) {

    if(movimientos.isEmpty) {
        return (0, [])
    }
    else {
        let primero = movimientos[0]
        let resto = Array(movimientos.dropFirst())

        let restoCalculado = aplica(movimientos: resto)
        return calculaMovimientos(movimiento: primero, total: restoCalculado)
    }
}

let movimientos: [Movimiento] = [.deposito(830.0), .cargoRecibo("Gimnasio", 45.0), .deposito(400.0), .cajero(100.0), .cargoRecibo("Fnac", 38.70)]
print("\n******\n3) Función aplica(movimientos:)\n******")
print(aplica(movimientos: movimientos))
//Imprime (1046.3, ["Gimnasio", "Fnac"])

// Ejercicio 4

indirect enum ArbolBinario {
    case vacio
    case nodo(Int, ArbolBinario, ArbolBinario)
}

let arbol: ArbolBinario = .nodo(8, 
                                .nodo(2, .vacio, .vacio), 
                                .nodo(12, .vacio, .vacio))

func suma(arbolb: ArbolBinario) -> Int {

    switch arbolb {
    case .vacio:
        return 0
    case let .nodo(dato, iz, de):
        return dato + suma(arbolb: iz) + suma(arbolb: de)
    }
}

print("\n******\n4) Función suma(arbolb:)\n******")
print(suma(arbolb: arbol))
// Imprime: 22

// Ejercicio 5

indirect enum Arbol {

    case nodo(Int, [Arbol])
}

/*
Definimos el árbol

    10
   / | \
  3  5  8
  |
  1

*/

let arbol1 = Arbol.nodo(1, [])
let arbol3 = Arbol.nodo(3, [arbol1])
let arbol5 = Arbol.nodo(5, [])
let arbol8 = Arbol.nodo(8, [])
let arbol10 = Arbol.nodo(10, [arbol3, arbol5, arbol8])


func suma(arbol: Arbol, cumplen: (Int)-> Bool) -> Int {
    switch arbol {
    case let .nodo(dato, hijos):
        if cumplen(dato) {
            return dato + suma(bosque: hijos, cumplen: cumplen)
        }
        else {
            return suma(bosque: hijos, cumplen: cumplen)
        }
    }
}

func suma(bosque: [Arbol], cumplen: (Int) -> Bool) -> Int {
    
    if bosque.isEmpty {
        return 0
    }
    else {
        let primero = bosque[0]
        let resto = Array(bosque.dropFirst())
        return suma(arbol: primero, cumplen: cumplen) + suma(bosque: resto, cumplen: cumplen)
    }
}


func esPar(x: Int) -> Bool {
    return x % 2 == 0
}

print("\n******\n5) Función suma(arbol:cumplen:)\n******")
print("La suma del árbol es: \(suma(arbol: arbol10, cumplen: esPar))")
// Imprime: La suma del árbol genérico es: 18