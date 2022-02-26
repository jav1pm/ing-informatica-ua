;; Francisco Javier Perez Martinez

#lang racket
(require rackunit)

;;
;; Ejercicio 1
;;

;; a)

(define (binario-a-decimal b3 b2 b1 b0)
  (+ (* b3 (expt 2 3)) (* b2 (expt 2 2)) (* b1 (expt 2 1)) (* b0 (expt 2 0))))

(check-equal? (binario-a-decimal 1 1 1 1) 15)
(check-equal? (binario-a-decimal 0 1 1 0) 6)
(check-equal? (binario-a-decimal 0 0 1 0) 2)

;; b)

(define (binario-a-hexadecimal b3 b2 b1 b0)
  (cond((equal? (binario-a-decimal b3 b2 b1 b0) 10) #\A)
       ((equal? (binario-a-decimal b3 b2 b1 b0) 11) #\B)
       ((equal? (binario-a-decimal b3 b2 b1 b0) 12) #\C)
       ((equal? (binario-a-decimal b3 b2 b1 b0) 13) #\D)
       ((equal? (binario-a-decimal b3 b2 b1 b0) 14) #\E)
       ((equal? (binario-a-decimal b3 b2 b1 b0) 15) #\F)
       (else (integer->char (+ 48 (binario-a-decimal b3 b2 b1 b0))))))

(check-equal? (binario-a-hexadecimal 1 1 1 1) #\F) ; ⇒ #\F
(check-equal? (binario-a-hexadecimal 0 1 1 0) #\6) ; ⇒ #\6
(check-equal? (binario-a-hexadecimal 1 0 1 0) #\A) ; ⇒ #\A


;;
;; Ejercicio 2
;;

;; versión 1

(define (menor-de-tres n1 n2 n3)
  (if (and (< n1 n2) (< n1 n3))
      n1
      (if (and (< n2 n1) (< n2 n3))
          n2
          n3)))

(check-equal? (menor-de-tres 2 8 1) 1) ;; ⇒ 1

;; versión 2

;; Función auxiliar
(define (menor x y)
  (if (< x y)
      x
      y))

(define (menor-de-tres-v2 n1 n2 n3)
  (menor (menor n1 n2) n3))

(check-equal? (menor-de-tres-v2 3 0 3) 0) ;; ⇒ 0

;;
;; Ejercicio 3
;;

;; a) evaluar -> (f (g (+ 2 1)) (+ 1 1))

;; Aplicativo

;; (f (g (+ 2 1)) (+ 1 1))
;; (f (g 3)) (+ 1 1))
;; (f (cons 2 3) ( + 1 1))
;; (f (cons 2 . 3) (+ 1 1))
;; (f (2 . 3) 2)
;; (cons (2 . 3) 2) => ((2 . 3) . 2)

;; Normal

;; (f (g (+ 2 1)) (+ 1 1))
;; (cons (g (+ 2 1)) (+ 1 1))
;; (cons (cons 2 (+ 2 1)) (+ 1 1))
;; (cons (cons 2 3) (+ 1 1))
;; (cons (2 . 3) (+ 1 1))
;; (cons (2 . 3) 2) => ((2 . 3) . 2)

;; b) evaluar -> (g 0 (f 10))

;; Aplicativo

;; (g 0 (f 10))
;; (g 0 (/ 10 0) => division by zero

;; Normal

;; (if (= 0 0) 0 (f 10))
;; (if #t 0 (f 10))
;; 0

;;
;; Ejercicio 4
;;

(define (suma-pareja p)
  (+ (car p) (cdr p)))

(define (tirada-ganadora t1 t2)
  (if (< (abs(- (suma-pareja t1) 7)) (abs(- (suma-pareja t2) 7)))
      1
      (if (> (abs(- (suma-pareja t1) 7)) (abs(- (suma-pareja t2) 7)))
          2
          0)))

(check-equal? (tirada-ganadora (cons 1 3) (cons 1 6)) 2) ; ⇒ 2
(check-equal? (tirada-ganadora (cons 1 5) (cons 2 2)) 1) ; ⇒ 1
(check-equal? (tirada-ganadora (cons 6 2) (cons 3 3)) 0) ; ⇒ 0

;;
;; Ejercicio 5
;;
              
(define tres-de-oros '3O)
(define as-de-copas 'AC)
(define caballo-de-espadas 'CE)

(define (obten-palo char)
  (cond((equal? char #\O) 'Oros)
       ((equal? char #\E) 'Espadas)
       ((equal? char #\C) 'Copas)
       (else 'Bastos)))

(define (obten-valor char)
  (cond((equal? char #\A) 1)
       ((equal? char #\S) 10)
       ((equal? char #\C) 11)
       ((equal? char #\R) 12)
       (else (- (char->integer char) (char->integer #\0)))))

(check-equal? (obten-palo #\O) 'Oros) ; ⇒ Oros
(check-equal? (obten-palo #\E) 'Espadas); ⇒ Espadas
(check-equal? (obten-valor #\3) 3); ⇒ 3
(check-equal? (obten-valor #\S) 10); ⇒ 10

(define (carta simbolo)
  (cons (obten-valor (string-ref (symbol->string simbolo) 0))
        (obten-palo (string-ref (symbol->string simbolo) 1))))

(check-equal? (carta tres-de-oros) '(3 . Oros))
(check-equal? (carta as-de-copas) '(1 . Copas))
(check-equal? (carta caballo-de-espadas) '(11 . Espadas))
(check-equal? (carta 'RB) '(12 . Bastos))

;;
;; Ejercicio 6
;;

(define epsilon 0.0001)

(define (iguales-reales? x y)
    (< (abs (- x y)) epsilon))

;; Funcion auxiliar: obtener la distancia entre 2 puntos.
(define (distancia c1 c2)
  (sqrt (+ (expt (- (car c1) (car c2)) 2)
           (expt (- (cdr c1) (cdr c2)) 2))))

;; Funcion auxiliar: obtener tipo de triangulo por distancias
(define (tipo-triangulo-distancia c1 c2 c3)
  (cond((and (iguales-reales? c1 c2) (iguales-reales? c1 c3)) "equilatero")
       ((or (iguales-reales? c1 c2) (iguales-reales? c1 c3) (iguales-reales? c2 c3)) "isósceles")
       (else "escaleno")))

(define (tipo-triangulo c1 c2 c3)
  (tipo-triangulo-distancia (distancia c1 c2) (distancia c1 c3) (distancia c2 c3)))

(check-equal? (tipo-triangulo (cons 1 1) (cons 1 6) (cons 6 1)) "isósceles")
(check-equal? (tipo-triangulo (cons -2 3) (cons 2 6) (cons 5 3)) "escaleno")
(check-equal? (tipo-triangulo (cons -3 0) (cons 3 0) (cons 0 5.1961)) "equilatero")
