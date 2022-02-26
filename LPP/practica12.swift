import Swift;
import Foundation;

// Francisco Javier Pérez Martínez

// Ejercicio 1

// a)

protocol A {
    var a: Int {get set}
    func foo(a: Int, b: Int) -> Int?
}

protocol B {
    mutating func bar()
}

struct MiStruct: A, B {
    var a = 10

    func foo(a: Int, b: Int) -> Int? {
        let res = a > 10 ? a: b
        return res
    }

    mutating func bar() {
        a += 1
    }
}

print(MiStruct())

var prueba = MiStruct()

var foo = prueba.foo(a: 1, b: 50)
print(foo!)
print(prueba.bar())  

struct Equipo : Equatable {
    let puntos: Int
    let nombre: String

    static func ==(primero: Equipo, segundo: Equipo) -> Bool {
        return primero.puntos == segundo.puntos && primero.nombre == segundo.nombre
    }
}



let equipo1 = Equipo(puntos: 10, nombre: "Hércules")
let equipo2 = Equipo(puntos: 8, nombre: "Villareal")
print(equipo1 == equipo2) // imprime false

// Ejercicio 3

protocol P {
   var p: Int { get }
}
class A1: P {
   var p = 0
   var a1 = 0
}
class A2: P {
   var p = 1
   var a2 = 0
}

var array: [P] = [A1(), A2()]
for i in array {

   // Código a completar
   if let a1 = i as? A1 {
       print("p: \(a1.p), a1: \(a1.a1)")
   }
   else if let a2 = i as? A2 {
       print("p: \(a2.p), a2: \(a2.a2)")
   }
}

// debe imprimir:
// debe imprimir:
// p: 0, a1: 0
// p: 1, a2: 0

// b)

protocol TieneVelocidad {
    func velocidadActual () -> Double
}

class Vehiculo {
    var velocidad = 0.0
    func velocidadActual() -> Double {
        return velocidad
    }
}

class Tren {
    static let velocidadEnMarcha = 300.0
    var pasajeros = 0
    var enMarcha = false
}

extension Vehiculo : TieneVelocidad {}
extension Tren : TieneVelocidad {
    func velocidadActual() -> Double {
        return enMarcha ? Tren.velocidadEnMarcha : 0.0
    }
}

//
// Código a completar
//

var vehiculo1 = Vehiculo()
var tren1 = Tren()
tren1.enMarcha = true

let transportes: [TieneVelocidad] = [vehiculo1, tren1]

for i in transportes {
    print(i.velocidadActual())
}

// Ejercicio 4

struct Timer {

    var segundos : Int

    mutating func paso() {
        if segundos > 0 {
            segundos -= 1
            Timer.pasosTotales += 1
        }
    }
    static var pasosTotales = 0

    static func + (timer1: Timer, timer2: Timer) -> Timer {
        return Timer(segundos: timer1.segundos + timer2.segundos)
    }
}

var t1 = Timer(segundos: 10)
var t2 = Timer(segundos: 5)

for _ in 0...4 {
    t1.paso()
}
for _ in 0...2 {
    t2.paso()
}

var t3 = t1 + t2

t3.paso()
print("Segundos del temporizador 1: \(t1.segundos)")
print("Segundos del temporizador 2: \(t2.segundos)")
print("Segundos del temporizador 3: \(t3.segundos)")
print("Pasos totales: \(Timer.pasosTotales)")
// Imprime:
// Segundos del temporizador 1: 5
// Segundos del temporizador 2: 2
// Segundos del temporizador 3: 6
// Pasos totales: 9