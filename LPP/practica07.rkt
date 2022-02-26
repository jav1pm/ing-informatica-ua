;; Francisco Javier Perez Martinez

#lang racket
(require rackunit)

;--------------------------------------;
; Implementación FOS exist? y for-all? ;
;--------------------------------------;

(define (exists? predicado lista)
  (and (not (null? lista))
       (or (predicado (car lista))
           (exists? predicado (cdr lista)))))

(define (for-all? predicado lista)
  (or (null? lista)
      (and (predicado (car lista))
           (for-all? predicado (cdr lista)))))

;---------------------------------------;
; Barrera de abstracción arbol genérico ;
;---------------------------------------;

(define (dato-arbol arbol) 
    (car arbol))

(define (hijos-arbol arbol) 
    (cdr arbol))

(define (hoja-arbol? arbol) 
   (null? (hijos-arbol arbol)))

(define (construye-arbol dato lista-arboles)
   (cons dato lista-arboles))

;--------------------------------------;
; Barrera de abstracción arbol binario ;
;--------------------------------------;

(define (dato-arbolb arbol)
   (car arbol))

(define (hijo-izq-arbolb arbol)
   (cadr arbol))

(define (hijo-der-arbolb arbol)
   (caddr arbol))

(define arbolb-vacio '())

(define (vacio-arbolb? arbol)
   (equal? arbol arbolb-vacio))

(define (hoja-arbolb? arbol)
   (and (vacio-arbolb? (hijo-izq-arbolb arbol))
        (vacio-arbolb? (hijo-der-arbolb arbol))))

(define (construye-arbolb dato hijo-izq hijo-der)
    (list dato hijo-izq hijo-der))

;;
;; Ejercicio 1
;;

;; a.1)

(define arbol '(15 (4 (2) (3)) (8 (6)) (12 (9) (10) (11))))
(check-equal? (dato-arbol (cadr (hijos-arbol (caddr (hijos-arbol arbol))))) 10)

;; a.2)

(define (suma-datos-arbol arbol)
    (+ (dato-arbol arbol)
       (suma-datos-bosque (hijos-arbol arbol))))

(define (suma-datos-bosque bosque)
    (if (null? bosque)
        0
        (+ (suma-datos-arbol (car bosque)) 
           (suma-datos-bosque (cdr bosque)))))

;; (suma-datos-bosque (hijos-arbol arbol)) => 65
;; 1. (suma-datos-arbol (car bosque)) => 9
;; 2. Primera llamada recursiva de suma-datos-bosque => 56

;; a.3)

(define (suma-datos-arbol-fos arbol)
   (foldr + (dato-arbol arbol) 
       (map suma-datos-arbol-fos (hijos-arbol arbol))))

;; 1. ¿Qué devuelve la invocación a map dentro de la función? => '(9 14 42)

;; 2. ¿Qué invocaciones se realizan a la función + durante la ejecución de foldr
;;    sobre la lista devuelta por la invocación a map? Enuméralas en orden,
;;    indicando sus parámetros y el valor devuelto en cada una de ellas.

;; 1º invocación = 15 + 42
;; 2º invocación = 57 + 14
;; 3º invocación = 71 + 9

;; b.1)

(define arbolb '(40
                 (23
                  (5 () ())
                  (32 (29 () ()) ()))
                 (45 () (56 () ()))))

(check-equal? (dato-arbolb (hijo-izq-arbolb (hijo-der-arbolb (hijo-izq-arbolb arbolb)))) 29)

;;
;; Ejercicio 2
;;

;; a)

(define (to-string-arbol arbol)
  (string-append (symbol->string (dato-arbol arbol))
                 (to-string-bosque (hijos-arbol arbol))))

(define (to-string-bosque bosque)
  (if (null? bosque)
      ""
      (string-append (to-string-arbol (car bosque))
                     (to-string-bosque (cdr bosque)))))

(define (to-string-arbol-fos arbol)
  (foldr string-append ""
         (cons (symbol->string (dato-arbol arbol))
         (map to-string-arbol-fos (hijos-arbol arbol)))))

;; b)

(define (veces-arbol dato arbol)
  (if (equal? dato (dato-arbol arbol))
      (+ 1 (veces-bosque dato (hijos-arbol arbol)))
      (veces-bosque dato (hijos-arbol arbol))))

(define (veces-bosque dato bosque)
  (if (null? bosque)
      0
      (+ (veces-arbol dato (car bosque))
           (veces-bosque dato (cdr bosque)))))

(define (veces-arbol-fos dato arbol)
  (foldr + (if (equal? dato (dato-arbol arbol)) 1 0)
         (map (lambda(x) (veces-arbol-fos dato x)) (hijos-arbol arbol))))

;;
;; Ejercicio 3
;;

;; a)

(define arbol1 '(10 (2) (12 (4) (2)) (10 (5))))
(define arbol2 '(10 (2) (12 (4) (2)) (10 (6))))

(define (hojas-cumplen pred arbol)
  (if (and (hoja-arbol? arbol) (pred (dato-arbol arbol)))
      (list (dato-arbol arbol))
      (hojas-cumplen-bosque pred (hijos-arbol arbol))))

(define (hojas-cumplen-bosque pred bosque)
  (if (null? bosque)
      '()
      (append (hojas-cumplen pred (car bosque))
            (hojas-cumplen-bosque pred (cdr bosque)))))

(define (hojas-cumplen-fos pred arbol)
  (if (and (hoja-arbol? arbol) (pred (dato-arbol arbol)))
      (list (dato-arbol arbol))
      (foldr append '()
             (map (lambda(x) (hojas-cumplen-fos pred x)) (hijos-arbol arbol)))))

(check-equal? (hojas-cumplen-fos even? arbol1) '(2 4 2))

;; b)

(define (todas-hojas-cumplen? pred arbol)
  (if (hoja-arbol? arbol)
      (pred (dato-arbol arbol))
      (todas-hojas-cumplen-bosque? pred (hijos-arbol arbol))))

(define (todas-hojas-cumplen-bosque? pred bosque)
  (or (null? bosque)
      (and (todas-hojas-cumplen? pred (car bosque))
           (todas-hojas-cumplen-bosque? pred (cdr bosque)))))

(define (todas-hojas-cumplen-fos? pred arbol)
  (if (hoja-arbol? arbol)
      (pred (dato-arbol arbol))
      (for-all? (lambda(x)
                  (todas-hojas-cumplen-fos? pred x)) (hijos-arbol arbol))))

(check-true (todas-hojas-cumplen-fos? even? arbol2))


;;
;; Ejercicio 4
;;

;; a)

(define (suma-raices-hijos arbol)
  (foldr + 0 (map dato-arbol (hijos-arbol arbol))))

(define arbol3 '(20 (2) (8 (4) (2)) (9 (5))))
;(suma-raices-hijos arbol3) ; ⇒ 19
;(suma-raices-hijos (cadr (hijos-arbol arbol3))) ; ⇒ 6

;; b)

(define (raices-mayores-arbol? arbol)
  (and (> (dato-arbol arbol) (suma-raices-hijos arbol))
         (raices-mayores-bosque? (hijos-arbol arbol))))

(define (raices-mayores-bosque? bosque)
  (or (null? bosque)
      (and (raices-mayores-arbol? (car bosque))
          (raices-mayores-bosque? (cdr bosque)))))

;(raices-mayores-arbol? arbol3) ; ⇒ #t
;(raices-mayores-arbol? '(20 (2) (8 (4) (5)) (9 (5)))) ; ⇒ #f

(define (raices-mayores-fos? arbol)
  (and (> (dato-arbol arbol) (suma-raices-hijos arbol))
       (for-all? raices-mayores-fos? (hijos-arbol arbol))))

;(raices-mayores-fos? arbol3) ; ⇒ #t
;(raices-mayores-fos? '(20 (2) (8 (4) (5)) (9 (5)))) ; ⇒ #f

;; c)

(define (comprueba-raices-arbol arbol)
  (construye-arbol (if (> (dato-arbol arbol) (suma-raices-hijos arbol)) 1 0)
                   (comprueba-raices-bosque (hijos-arbol arbol))))

(define (comprueba-raices-bosque bosque)
  (if (null? bosque)
      '()
      (cons (comprueba-raices-arbol (car bosque))
            (comprueba-raices-bosque (cdr bosque)))))

;(comprueba-raices-arbol arbol3) ; ⇒ (1 (1) (1 (1) (1)) (1 (1)))
;(comprueba-raices-arbol '(20 (2) (8 (4) (5)) (9 (5)))) 
; ⇒ (1 (1) (0 (1) (1)) (1 (1)))

(define (comprueba-raices-arbol-fos arbol)
  (construye-arbol (if (> (dato-arbol arbol) (suma-raices-hijos arbol)) 1 0)
                   (foldr cons '() (map comprueba-raices-arbol-fos (hijos-arbol arbol)))))

;(comprueba-raices-arbol-fos arbol3) ; ⇒ (1 (1) (1 (1) (1)) (1 (1)))
;(comprueba-raices-arbol-fos '(20 (2) (8 (4) (5)) (9 (5)))) 
; ⇒ (1 (1) (0 (1) (1)) (1 (1)))

;;
;; Ejercicio 5
;;

(define arbol_ej5 '(a
                    (a (a) (b))
                    (b (a) (c))
                    (c)))
                      
(define (es-camino? lista arbol)
  (and (equal? (car lista) (dato-arbol arbol))
       (es-camino-bosque? (cdr lista) (hijos-arbol arbol))))

(define (es-camino-bosque? lista bosque)
  (cond ((and (null? lista) (null? bosque)) #t)
        ((or (null? lista) (null? bosque)) #f)
        (else (or (es-camino? lista (car bosque))
                   (es-camino-bosque? lista (cdr bosque))))))

(define (es-camino?-fos lista arbol)
  (and (equal? (car lista) (dato-arbol arbol))
       (or (and (null? (cdr lista)) (hoja-arbol? arbol))
           (exists? (lambda (subarbol)
                      (es-camino?-fos (cdr lista) subarbol))
                    (hijos-arbol arbol)))))

;(es-camino? '(a b a) arbol_ej5) ; ⇒ #t
;(es-camino? '(a b) arbol_ej5) ; ⇒ #f
;(es-camino? '(a b a b) arbol_ej5) ; ⇒ #f

;; b)

(define arbol_5b '(1 (2 (3 (4) (2)) (5)) (6 (7))))

(define (nodos-nivel nivel arbol)
  (if (= nivel 0)
      (list (dato-arbol arbol))
      (nodos-nivel-bosque (- nivel 1) (hijos-arbol arbol))))

(define (nodos-nivel-bosque nivel bosque)
  (if (null? bosque)
      '()
      (append (nodos-nivel nivel (car bosque))
            (nodos-nivel-bosque nivel (cdr bosque)))))

;(nodos-nivel 0 arbol_5b) ; ⇒ '(1)
;(nodos-nivel 1 arbol_5b) ; ⇒ '(2 6)
;(nodos-nivel 2 arbol_5b) ; ⇒ '(3 5 7)
;(nodos-nivel 3 arbol_5b) ; ⇒ '(4 2)

(define (nodos-nivel-fos nivel arbol)
  (if (= nivel 0)
      (list (dato-arbol arbol))
      (foldr append '()
             (map (lambda(x) (nodos-nivel-fos (- nivel 1) x)) (hijos-arbol arbol)))))

;(nodos-nivel-fos 0 arbol_5b) ; ⇒ '(1)
;(nodos-nivel-fos 1 arbol_5b) ; ⇒ '(2 6)
;(nodos-nivel-fos 2 arbol_5b) ; ⇒ '(3 5 7)
;(nodos-nivel-fos 3 arbol_5b) ; ⇒ '(4 2)

;;
;; Ejercicio 6
;;

;; a)

(define arbolb1 '(20 (13 (2 () ())
                         (18 () ()))
                     (40 (25 () () )
                         (43 () ()))))
(define arbolb2 '(20 (13 (2 () ())
                         (22 () ()))
                     (40 (25 () () )
                         (43 () ()))))

(define (ordenado-entre? arbolb min max)
  (if (vacio-arbolb? arbolb)
      #t
      (and (<= (dato-arbolb arbolb) max)
           (>= (dato-arbolb arbolb) min)
           (ordenado-entre? (hijo-izq-arbolb arbolb) min (dato-arbolb arbolb))
           (ordenado-entre? (hijo-der-arbolb arbolb) (dato-arbolb arbolb) max))))

;(ordenado-entre? arbolb1 0 50) ; ⇒ #t
;(ordenado-entre? arbolb2 0 50) ; ⇒ #f
;(ordenado-entre? arbolb1 0 30) ; ⇒ #f

;; b)

(define (ordenado-menor? arbolb max)
  (if (vacio-arbolb? arbolb)
      #t
      (and (<= (dato-arbolb arbolb) max)
           (ordenado-menor? (hijo-izq-arbolb arbolb) (dato-arbolb arbolb))
           (ordenado-entre? (hijo-der-arbolb arbolb) (dato-arbolb arbolb) max))))

(define (ordenado-mayor? arbolb min)
  (if (vacio-arbolb? arbolb)
      #t
      (and (>= (dato-arbolb arbolb) min)
           (ordenado-entre? (hijo-izq-arbolb arbolb) min (dato-arbolb arbolb))
           (ordenado-mayor? (hijo-der-arbolb arbolb) (dato-arbolb arbolb)))))

;(ordenado-menor? arbolb1 50) ; ⇒ #t
;(ordenado-menor? arbolb1 40) ; ⇒ #f
;(ordenado-menor? arbolb2 50) ; ⇒ #f
;(ordenado-mayor? arbolb1 0)  ; ⇒ #t
;(ordenado-mayor? arbolb1 20) ; ⇒ #f
;(ordenado-mayor? arbolb2 0) ; ⇒ #f

;; c)

(define (ordenado? arbolb)
  (if (vacio-arbolb? arbolb)
      #t
      (and (ordenado-menor? (hijo-izq-arbolb arbolb) (dato-arbolb arbolb))
           (ordenado-mayor? (hijo-der-arbolb arbolb) (dato-arbolb arbolb)))))

;(ordenado? arbolb1) ; ⇒ #t
;(ordenado? arbolb2) ; ⇒ #f

;;
;; Ejercicio 7
;;

(define b-tree '(9 (5 (3 (1 () ())
                          (4 () ()))
                       (7 () ()))
                    (15 (13 (10 () ())
                            (14 () ()))
                        (20 ()
                            (23 () ())))))

(define (camino-b-tree b-tree camino)
  (cond ((or (null? camino) (vacio-arbolb? arbolb))'())
        ((equal? (car camino) '<) (camino-b-tree (hijo-izq-arbolb b-tree) (cdr camino)))
        ((equal? (car camino) '>) (camino-b-tree (hijo-der-arbolb b-tree) (cdr camino)))
        (else (cons (dato-arbolb b-tree) (camino-b-tree b-tree (cdr camino))))))

;(camino-b-tree b-tree '(= < < = > =)) ; ⇒ '(9 3 4)
;(camino-b-tree b-tree '(> = < < =)) ; ⇒ '(15 10)