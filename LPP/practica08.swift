import Swift;
import Foundation;

// Francisco Javier Pérez Martínez

// Experimento 1

let variable: Float = 4
print("Experimento 1:", variable)

// Experimento 2

let etiqueta = "El ancho es "
let ancho = 94
//let anchoEtiqueta = etiqueta + ancho

print("Experimento 2: El operador + no se puede aplicar a operandos de tipo String e Int.")

// Experimento 3

let manzanas = 3
let naranjas = 5
let resumenManzanas = "Tengo \(manzanas) manzanas."
let resumenFrutas = "Tengo \(manzanas + naranjas) frutas."

let nombre = "Juan"
let calculoFloat = "El arbol mide \(5.4 * 2.3) metros"
let sa = "Hola \(nombre), ¿qué tal?"

print("Experimento 3:", calculoFloat, "|", sa)

var listaCompra = ["huevos", "agua", "tomates", "pan"]
listaCompra[1] = "botella de agua"
//print(listaCompra)

var trabajos = [
    "Malcolm": "Capitán",
    "Kaylee": "Mecánico",
]
trabajos["Jayne"] = "Relaciones públicas"
//print(trabajos)

let arrayVacio = [String]()
let diccionarioVacio = [String: Float]()

listaCompra = []
trabajos = [:]

let http404Error = (404, "Not Found")

let (statusCode, statusMensaje) = http404Error
let (soloStatusCode, _) = http404Error

// print("El código de estado es \(http404Error.0)")
// print("Código \(http404Error.1)")

let puntuacionesIndividuales = [75, 43, 103, 87, 12]
var puntuacionEquipo = 0
for puntuacion in puntuacionesIndividuales {
    if puntuacion > 50 {
        puntuacionEquipo += 3
    } else {
        puntuacionEquipo += 1
    }
}
// print(puntuacionEquipo)


// Experimento 4

var cadenaOpcional: String? = "Hola"
// print(cadenaOpcional == nil)

var nombreOpcional: String?
var saludo = "Hola!"
if let nombre = nombreOpcional {
    saludo = "Hola, \(nombre)"
}
else if nombreOpcional == nil {
    saludo = "Buenas tardes"
}
print("Experimento 4:", saludo)

let nombrePila: String? = nil
let nombreCompleto: String = "John Appleseed"
let saludoInformal = "¿Qué tal, \(nombrePila ?? nombreCompleto)?"

// print(saludoInformal)

// Experimento 5

// Intenta eliminar el caso por defecto. ¿Qué error obtienes?
print("Experimento 5: El switch debe ser exhaustivo por lo que debemos añadir default para que funcione correctamente.")


// Experimento 6: Añade otra variable para seguir qué clase de número es el mayor.

let numerosInteresantes = [
    "Primos" : [2, 3, 5, 7, 11, 13],
    "Fibonacci" : [1, 1, 2, 3, 5, 8],
    "Cuadrados" : [1, 4, 9, 16, 25],
]
var mayor = 0
var claseMayor : String = ""

for (clase, numeros) in numerosInteresantes {
    for num in numeros {
        if num > mayor {
            mayor = num
            claseMayor = clase
        }
    }
}
let exp6 = (claseMayor, mayor)
print("Experimento 6:", exp6)

var n = 2
while n < 100 {
    n *= 2
}
// print(n)

var m = 2
repeat {
    m *=  2
} while m < 100

// print(m)

var total = 0
for i in 0..<4 {
    total += i
}
// print(total) -> 6

var res = 0
for i in 0...4 {
    res += i
}
// print(res) -> 10

// Experimento 7: Elimina el parámetro día. Añade un parámetro para incluir la comida de hoy en el saludo.

func saluda(nombre: String, comida: String) -> String {
    return "Hola \(nombre), hoy comemos \(comida)."
}
print("Experimento 7:", saluda(nombre: "Bob", comida: "pizza"))

func saluda(_ nombre: String, el dia: String) -> String {
    return "Hola \(nombre), hoy es \(dia)."
}
// print (saluda("Juan", el: "Martes"))

func calculaEstadisticas(puntuaciones: [Int]) -> 
                        (min: Int, max: Int, sum: Int) {
    var min = puntuaciones[0]
    var max = puntuaciones[0]
    var sum = 0

    for puntuacion in puntuaciones {
        if puntuacion > max {
            max = puntuacion
        } else if puntuacion < min {
            min = puntuacion
        }
        sum += puntuacion
    }

    return (min, max, sum)
}
let estadisticas = calculaEstadisticas(puntuaciones: [5, 3, 100, 3, 9])
// print(estadisticas.sum)
// print(estadisticas.2)

func suma(numeros: Int...) -> Int {
    var suma = 0
    for num in numeros {
        suma += num
    }
    return suma
}
// print(suma())
// print(suma(numeros: 42, 597, 12))

// Experimento 8

func media(numeros: Double...) -> Double {
    var total = 0.0

    for num in numeros {
        total += num
    }

    let tam = Double(numeros.count) // tamaño del array
    let media = total / tam
    return media
}
print("Experimento 8:", media(numeros: 10, 30, 20))

func devuelveQuince() -> Int {
    var y = 10
    func suma() {
        y += 5
    }
    suma()
    return y
}
// print(devuelveQuince())

func construyeIncrementador() -> ((Int) -> Int) {
    func sumaUno(numero: Int) -> Int {
        return 1 + numero
    }
    return sumaUno
}
var incrementa = construyeIncrementador()
// print(incrementa(7))

func devuelveSuma() -> (() -> Int) {
    var y = 10;
    func suma() -> Int {
        y += 5;
        return y
    }
    return suma
}

let f = devuelveSuma()
// print(f())
// print(f())

func cumpleCondicion(lista: [Int], condicion: (Int) -> Bool) -> Bool {
    for item in lista {
        if condicion(item) {
            return true
        }
    }
    return false
}
func menorQueDiez(numero: Int) -> Bool {
    return numero < 10
}
var numeros = [20, 19, 7, 12]
// print(cumpleCondicion(lista: numeros, condicion: menorQueDiez))

// Experimento 9

let devuelveCero = numeros.map({
    (numero: Int) -> Int in
    if (numero % 2 != 0){
        return 0
    }
    else {
        let resultado = 3 * numero
        return resultado
    }
})
print("Experimento 9:", devuelveCero)

let numerosMapeados = numeros.map({ numero in 3 * numero })
// print(numerosMapeados)

let numerosOrdenados = numeros.sorted { $0 > $1 }
// print(numerosOrdenados)

// Experimento 10

class Figura {
    var numeroDeLados = 0
    public var coordenadaX = 0;

    func descripcionSencilla() -> String {
        return "Una figura con \(numeroDeLados) lados."
    }

    func devolverCoordenadaX(_ coordenadaX: Int) -> String {
        return "La coordenada devuelta es: \(coordenadaX)."
    }
}

var figura = Figura()
figura.numeroDeLados = 7
var descripcionFigura = figura.descripcionSencilla()
let coord = figura.devolverCoordenadaX(5)
print("Experimento 10:", coord)

class FiguraConNombre {
    var numeroDeLados: Int = 0
    var nombre: String

    init(nombre: String) {
        self.nombre = nombre
    }

    func descripcionSencilla() -> String {
        return "Una figura con \(numeroDeLados) lados."
    }
}

class Cuadrado: FiguraConNombre {
    var longitudLado: Double

    init(longitudLado: Double, nombre: String) {
        self.longitudLado = longitudLado
        super.init(nombre: nombre)
        numeroDeLados = 4
    }

    func area() ->  Double {
        return longitudLado * longitudLado
    }

    override func descripcionSencilla() -> String {
        return "Un cuadrado con lados de longitud \(longitudLado)."
    }
}
let test = Cuadrado(longitudLado: 5.2, nombre: "Mi cuadrado de prueba")
// print(test.area())
// print(test.descripcionSencilla())

// Expermiento 11

class Circulo: FiguraConNombre {
    var radio: Double

    init(radio: Double, nombre: String){
        self.radio = radio
        super.init(nombre: nombre)
        numeroDeLados = 4
    }

    func area() -> Double {
        return Double.pi * radio * radio;
    }

    override func descripcionSencilla() -> String {
        return "El area del círculo es \(area())."
    }
}

let testCirculo = Circulo(radio: 6.50, nombre: "Mi circulo de prueba")
print("Experimento 11:", testCirculo.descripcionSencilla())

// getter y setter

class TrianguloEquilatero: FiguraConNombre {
    var longitudLado: Double = 0.0

    init(longitudLado: Double, nombre: String) {
        self.longitudLado = longitudLado
        super.init(nombre: nombre)
        numeroDeLados = 3
    }

    var perimetro: Double {
        get {
            return 3.0 * longitudLado
        }
        set {
            longitudLado = newValue / 3.0
        }
    }

    override func descripcionSencilla() -> String {
        return "Un triangulo equilátero con lados de longitud \(longitudLado)."
    }
}
var triangulo = TrianguloEquilatero(longitudLado: 3.1, nombre: "un triángulo")
// print(triangulo.perimetro)
triangulo.perimetro = 9.9
// print(triangulo.longitudLado)

// Enumeraciones y estructuras

enum Valor: Int {
    case uno = 1
    case dos, tres, cuatro, cinco, seis, siete, ocho, nueve, diez
    case sota, caballo, rey
    func descripcionSencilla() -> String {
        switch self {
        case .uno:
            return "as"
        case .sota:
            return "sota"
        case .caballo:
            return "caballo"
        case .rey:
            return "rey"
        default:
            return String(self.rawValue)
        }
    }
}
let carta = Valor.uno
let valorBrutoCarta = carta.rawValue
