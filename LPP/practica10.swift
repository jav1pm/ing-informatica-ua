import Swift;
import Foundation;

// Francisco Javier Pérez Martínez

// Ejercicio 1

// a)

func maxOpt(_ x: Int?, _ y: Int?) -> Int? {
    
    if x == nil {
        return y
    }
    else if y == nil {
        return x
    }
    else {
        return max(x!, y!)
    }
}

let res1 = maxOpt(nil, nil) 
let res2 = maxOpt(10, nil)
let res3 = maxOpt(-10, 30)
print("\n******\n1a) Función maxOpt(x,y)\n******")
print("res1 = \(String(describing: res1))")
print("res2 = \(String(describing: res2))")
print("res3 = \(String(describing: res3))")
// Imprime:
// res1 = nil
// res2 = Optional(10)
// res3 = Optional(30)

// b1)

func mayorImparPar2(num: Int, pareja: (Int?, Int?)) -> (Int?, Int?) {
    if (num % 2 != 0) {
        return (maxOpt(pareja.0, num), pareja.1)
    }
    else {
        return (pareja.0, maxOpt(pareja.1, num))
    }
}

func parejaMayorParImpar2(numeros: [Int]) -> (Int?, Int?) {

    if(numeros.isEmpty) {
        return (nil, nil)
    }
    else {
        let primero = numeros[0]
        let resto = Array(numeros.dropFirst())
        
        let parejaResto = parejaMayorParImpar2(numeros: resto)
        return mayorImparPar2(num: primero, pareja: parejaResto)
    }
}

let numeros = [15, 202, 12, 100, 204, 2]
print("\n******\n1b1) Función parejaMayorParImpar2(numeros:)\n******")
print(parejaMayorParImpar2(numeros: numeros))
// Imprime:
// parejaMayorParImpar2(numeros: [15, 202, 12, 100, 204, 2])
// (Optional(15), Optional(204))

// b2)

func sumaMaxParesImpares(numeros: [Int]) -> Int {

    let pareja = parejaMayorParImpar2(numeros: numeros)

    if let dato1 = pareja.0, let dato2 = pareja.1 {
        return dato1 + dato2
    }
    else if let dato1 = pareja.0 {
        return dato1
    }
    else if let dato2 = pareja.1 {
        return dato2
    }
    else {
        return 0
    }
}

let numeros2 = [-10, 202, 12, 100, 204, 2]
let emptyNumeros = [Int]()


print("\n******\n1b2) Función sumaMaxParesImpares(numeros: \(numeros2))\n******")
print(sumaMaxParesImpares(numeros: numeros2))
print(sumaMaxParesImpares(numeros: emptyNumeros))
// Imprime:
// sumaMaxParesImpares(numeros: [-10, 202, 12, 100, 204, 2])
// 204

// b3)



// Ejercicio 2

// a.1)

let nums = [1,2,3,4,5,6,7,8,9,10]
let result2a1 = nums.filter{$0 % 3 == 0}.count

print("\n******\n2a1) Devuelve la cantidad de nº divisibles por 3: \(result2a1)\n******")

// a.2)

let nums2 = [1,2,3,4,5,6,7,8,9,10]
let result2a2 = nums2.map{$0+100}.filter{$0 % 5 == 0}.reduce(0,+)

print("\n******\n2a2) Devuelve la suma de todos los nº incrementados por 100 que sean divisibles por 5: \(result2a2)\n******")

// a.3)

let cadenas = ["En", "un", "lugar", "de", "La", "Mancha"]
let result2a3 = cadenas.sorted{$0.count < $1.count}.map{$0.count}

print("\n******\n2a3) Devuelve un array con el tamaño de los strings ordenados de menor a mayor: \(result2a3)\n******")

// a.4)

let cadenas2 = ["En", "un", "lugar", "de", "La", "Mancha"]
let result2a4 = cadenas2.reduce([]) {
    (res: [(String, Int)], c: String) -> [(String, Int)] in
        res + [(c, c.count)]}.sorted(by: {$0.1 < $1.1})

print("\n******\n2a4) Devuelve un array de parejas (string, longitud) ordenadas de menor a mayor por el tamaño del string: \(result2a4)\n******")

// b.1)

func f(nums: [Int], n: Int) -> Int {
    return nums.filter{$0 == n}.count
}

print("\n******\n2b1) Devuelve cuantas veces aparece n (5) en el array:", f(nums: [1, 4, 5, 45, 6, 5, 2], n: 5))

// b.2)

func g(nums: [Int]) -> [Int] {
    return nums.reduce([], {
        (res: [Int], n: Int) -> [Int] in
            if !res.contains(n) {
                return res + [n]
            } else {
                return res
            }
    })
}

print("\n******\n2b2) Devuelve el mismo vector, eliminando los elementos repetidos:", g(nums: [1, 4, 5, 45, 6, 5, 2]))

// b.3)

func h(nums: [Int], n: Int) -> ([Int], [Int]) {
   return nums.reduce(([],[]), {
       (res: ([Int],[Int]), num: Int ) -> ([Int],[Int]) in
           if (num >= n) {
               return (res.0, res.1 + [num])
           } else {
               return ((res.0 + [num], res.1))
           }
   })
}

print("\n******\n2b3) Devuelve una pareja donde la parte izq es un array con los nº < n (5) y la parte der si son >=:", h(nums: [1, 4, 5, 45, 6, 5, 2], n: 5))

// c.1)

func suma(palabras: [String], contienen: Character) -> Int {
    return palabras.filter{$0.contains(contienen)}.reduce(0, {$0 + $1.count})
}

print("\n******\n2c1) Función suma(palabras:contienen:)\n******")
print(suma(palabras: ["hola", "buenas", "tardes"], contienen: "e"))

// c.2)

func sumaMenoresMayores(nums: [Int], pivote: Int) -> (Int, Int) {
    return nums.reduce((0,0), {
        if $1 >= pivote {
            return ($0.0, $0.1 + $1)
        }
        else {
            return ($0.0 + $1, $0.1)
        }
    })
}

print("\n******\n2c2) Función sumaMenoresMayores(nums:pivote:)\n******")
print(sumaMenoresMayores(nums: [1, 2, 5, 6, 20, 12], pivote: 10))

// d)

func bar(f: (Int) -> Int) {
  print(f(4))
}

func foo() -> (Int) -> Int {
  var x = 3
  return {
    x += $0 + 2
    return x
  }
}

var x = 5
let g = foo()
print("\n******\n2d) Ejercicio sobre variables capturadas por clausuras\n******")
bar(f: g)   // => 9
bar(f: g)   // => 15

// Ejercicio 3

indirect enum Arbol<T> {
    
    case nodo(T, [Arbol<T>])
}

let arbolInt: Arbol = .nodo(53, 
                            [.nodo(13, []), 
                             .nodo(32, []), 
                             .nodo(41, 
                                   [.nodo(36, []),
                                    .nodo(39, [])
                                   ])
                            ])
let arbolString: Arbol = .nodo("Zamora", 
                               [.nodo("Buendía", 
                                      [.nodo("Albeza", []), 
                                       .nodo("Berenguer", []), 
                                       .nodo("Bolardo", [])
                                      ]), 
                                .nodo("Galván", [])
                               ])

func toArray<T>(arbol: Arbol<T>) -> [T] {

    switch arbol {
        case let .nodo(raiz, hijos):
            return [raiz] + toArray(bosque: hijos)      
    }
}

func toArray<T>(bosque: [Arbol<T>]) -> [T] {
    
    if bosque.isEmpty {
        return []
    }
    else {
        let primero = bosque[0]
        let resto = Array(bosque.dropFirst())
        return toArray(arbol: primero) + toArray(bosque: resto)
    }
}

print("\n******\n3) Funcion toArray y toArrayFOS\n******")

print(toArray(arbol: arbolInt))
// Imprime: [53, 13, 32, 41, 36, 39]

func toArrayFOS<T>(arbol: Arbol<T>) -> [T] {

    switch arbol {
        case let .nodo(raiz, hijos):
            return hijos.map(toArrayFOS).reduce([raiz], +)
    }
}

print(toArrayFOS(arbol: arbolString))
// ["Zamora", "Buendía", "Albeza", "Berenguer", "Bolardo", "Galván"]

// Ejercicio 4

func imprimirListadoAlumnos(_ alumnos: [(String, Double, Double, Double, Int)]) {
    print("Alumno   Parcial1   Parcial2   Parcial3  Años")
    for alu in alumnos {
        alu.0.withCString {
            print(String(format:"%-10s %5.2f      %5.2f    %5.2f  %3d", $0, alu.1,alu.2,alu.3,alu.4))
        }
    }
}

typealias Evaluacion = [(String, Double, Double, Double, Int)]

func imprimirListadosNotas(_ alumnos: Evaluacion) {

    print("LISTADO ORIGINAL")
    imprimirListadoAlumnos(alumnos)

    print("\nLISTADO ORDENADO POR NOMBRE")
    let orderByName = alumnos.sorted() {$0 < $1}
    imprimirListadoAlumnos(orderByName)

    print("\nLISTADO ORDENADO POR PARCIAL 1")
    let orderByP1 = alumnos.sorted() {$0.1 < $1.1}
    imprimirListadoAlumnos(orderByP1)

    print("\nLISTADO ORDENADO POR PARCIAL 2")
    let orderByP2 = alumnos.sorted() {$0.2 > $1.2}
    imprimirListadoAlumnos(orderByP2)

    print("\nLISTADO ORDENADO POR PARCIAL 3 y AÑO")
    let orderByP3andYear = alumnos.sorted() {$0.3 < $0.1 && $0.4 < $1.4}
    imprimirListadoAlumnos(orderByP3andYear)

    print("\nLISTADO ORDENADO POR NOTA FINAL")
    let orderByNotaFinal = alumnos.sorted(by: {
        a1, a2 in
        let notaA1 = a1.1 * 0.34 + a1.2 * 0.33 + a1.3 * 0.33
        let notaA2 = a2.1 * 0.34 + a2.2 * 0.33 + a2.3 * 0.33

        return notaA1 < notaA2
    })
    imprimirListadoAlumnos(orderByNotaFinal)
}

let listaAlumnos = [("Pepe", 8.45, 3.75, 6.05, 1), 
                    ("Maria", 9.1, 7.5, 8.18, 1), 
                    ("Jose", 8.0, 6.65, 7.96, 1),
                    ("Carmen", 6.25, 1.2, 5.41, 2), 
                    ("Felipe", 5.65, 0.25, 3.16, 3), 
                    ("Carla", 6.25, 1.25, 4.23, 2), 
                    ("Luis", 6.75, 0.25, 4.63, 2), 
                    ("Loli", 3.0, 1.25, 2.19, 3)]

print("\n******\n4) Funcion imprimirListadosNotas(alumnos:)\n******")
imprimirListadosNotas(listaAlumnos)

// Ejercicio 5

// A)
print("\n******\n5A) Número de alumnos que han aprobado primer parcial y suspendido el segundo \n******")
print(listaAlumnos.filter {$0.1 >= 5 && $0.2 < 5}.count)

// B)
print("\n******\n5B) Alumnos que han aprobado la asignatura (tienen una nota final >= 5) \n******")


print(listaAlumnos.map{ (alumno) -> (String, Double) in
    let media = alumno.1 * 0.34 + alumno.2 * 0.33 + alumno.3 * 0.33
    return (alumno.0, media)
}.filter{$0.1 >= 5}.map{$0.0})

// C)
print("\n******\n5C) Nota media de todos los alumnos en forma de tupla (media_p1, media_p2, media_p3)\n******")

var tupla = listaAlumnos.reduce((0,0,0)) { 
    return ($0.0 + $1.1, $0.1 + $1.2, $0.2 + $1.3)
}
tupla = (tupla.0 / Double(listaAlumnos.count), tupla.1 / Double(listaAlumnos.count), tupla.2 / Double(listaAlumnos.count))
print(tupla)
// Resultado: (6.6812499999999995, 2.7624999999999997, 5.2262500000000003)

// Ejercicio 6

func construye(operador: Character) -> (Int, Int) -> Int {
    return {(op1: Int, op2: Int) -> Int in
        switch operador {
            case "+":
                return op1 + op2
            case "-":
                return op1 - op2
            case "*":
                return op1 * op2
            default:
                return op1 / op2
        }
    }
}

print("\n******\n6) Función construye(operador:)\n******")
var f = construye(operador: "+")
print(f(2,3))
// Imprime 5
f = construye(operador: "-")
print(f(2,3))
// Imprime -1
f = construye(operador: "*")
print(f(2,3))
// Imprime 6
f = construye(operador: "/")
print(f(6,2))
// Imprime 3