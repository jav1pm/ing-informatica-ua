;; Francisco Javier Perez Martinez

#lang racket
(require rackunit)

;;
;; Ejercicio 1
;;

;; a.1)

(define (menor x y)
  (if (< x y)
      x
      y))

(define (minimo lista)
  (if (null? (cdr lista))
      (car lista)
      (menor (car lista) (minimo (cdr lista)))))

(check-equal? (minimo '(1 8 6 4 3)) 1) ; ⇒ 1
(check-equal? (minimo '(1 -1 3 -6 4)) -6); ⇒ -6

;; a.2) (minimo '(1 8 6 4 3)) ; ⇒ 1

;; ¿Qué lista se pasa como parámetro a la primera llamada recursiva a la función?
;;
;; '(8 6 4 3)
;;
;; ¿Qué devuelve esa llamada recursiva?
;;
;; 3
;;
;; ¿Con qué argumentos se llama a la función menor que devuelve el resultado final?
;;
;; (menor 1 3)

;; b)

(define (concatena lista-chars)
  (if (null? lista-chars)
      ""
      (string-append (string (car lista-chars)) (concatena (cdr lista-chars)))))

(check-equal? (concatena '(#\H #\o #\l #\a)) "Hola") ; ⇒ "Hola"
(check-equal? (concatena '(#\S #\c #\h #\e #\m #\e #\space #\m #\o #\l #\a)) "Scheme mola") ; ⇒ "Scheme mola"

;; c)

(define (contiene-lista? lista dato)
  (if (null? lista)
      #f
      (or (equal? (car lista) dato) (contiene-lista? (cdr lista) dato))))

(check-false (contiene-lista? '() 'a))
(check-false (contiene-lista? '(3 "adios" #\C) 'a))
(check-true (contiene-lista? '("hola" 1 'a) 1))

(define (contiene? cadena char)
  (contiene-lista? (string->list cadena) char))

(check-equal? (contiene? "Hola" #\o) #t) ; ⇒ #t
(check-equal? (contiene? "Esto es una frase" #\space) #t) ; ⇒ #t
(check-equal? (contiene? "Hola" #\h) #f) ; ⇒ #f

;;
;; Ejercicio 2
;;

;; a)

(define (binario-a-decimal lista-bits)
  (if (null? lista-bits)
      0
      (+ (* (car lista-bits) (expt 2 (- (length lista-bits) 1))) (binario-a-decimal (cdr lista-bits)))))

(check-equal? (binario-a-decimal '(1 1 1 1)) 15) ; ⇒ 15
(check-equal? (binario-a-decimal '(1 1 0)) 6) ; ⇒ 6
(check-equal? (binario-a-decimal '(1 0)) 2) ; ⇒ 2

;; b)

(define (ordenada-creciente? lista-nums)
  (or (null? (cdr lista-nums))
      (and (< (car lista-nums) (cadr lista-nums)) (ordenada-creciente? (cdr lista-nums)))))

;;
;; Ejercicio 3
;;

;; a.1)
(define p1 (list (cons 1 2) (list 3 4)))

;; a.2)
(check-equal? (cdar p1) 2)
(check-equal? (cadadr p1) 4)

;; b.1)
(define p2 (cons (list (cons 7 (cons 8 9)) (list 1 2)  3) (cons 10 11)))

;; b.2)
(check-equal? (cddaar p2) 9)
(check-equal? (cadadr (car p2)) 2)

;;
;; Ejercicio 4
;;

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

(define (carta simbolo)
  (cons (obten-valor (string-ref (symbol->string simbolo) 0))
        (obten-palo (string-ref (symbol->string simbolo) 1))))

(define cartas1 '(3O 5E AC 2B 5O 5C 4B))
(define cartas2 '(CE AO 3B AC 2E SC 4C))

(define (suma-n-primeras-cartas lista n)
  (if (or (null? lista) (= n 0))
      0
      (+ (car (carta (car lista))) (suma-n-primeras-cartas (cdr lista) (- n 1)))))


(define (blackjack cartas1 n1 cartas2 n2)
  (cond((and (> (suma-n-primeras-cartas cartas1 n1) 21) (> (suma-n-primeras-cartas cartas2 n2) 21) -1))
       ((> (suma-n-primeras-cartas cartas1 n1) 21) 2)
       ((> (suma-n-primeras-cartas cartas2 n2) 21) 1)
       ((> (suma-n-primeras-cartas cartas1 n1) (suma-n-primeras-cartas cartas2 n2)) 1)
       ((< (suma-n-primeras-cartas cartas1 n1) (suma-n-primeras-cartas cartas2 n2)) 2)
       (else 0)))

(check-equal? (blackjack cartas1 5 cartas2 4) 0) ; ⇒ 0
(check-equal? (blackjack cartas1 5 cartas2 3) 1) ; ⇒ 1
(check-equal? (blackjack cartas1 3 cartas2 4) 2); ⇒ 2
(check-equal? (blackjack cartas1 7 cartas2 6) -1); ⇒ -1
(check-equal? (blackjack cartas1 7 cartas2 3) 2); ⇒ 2
(check-equal? (blackjack cartas1 3 cartas2 7) 1); ⇒ 1

;;
;; Ejercicio 5
;;

;; a)

(define (suma-izq pareja n)
  (cons (+ (car pareja) n) (cdr pareja)))

(define (suma-der pareja n)
  (cons (car pareja) (+ (cdr pareja) n)))

(check-equal? (suma-izq (cons 10 20) 3) (cons 13 20))  ; ⇒ (13 . 20)
(check-equal? (suma-der (cons 10 20) 5) (cons 10 25)) ; ⇒ (10 . 25)

;; b)

(define (suma-impares-pares lista-num)
  (cond((null? lista-num) (cons 0 0))
       ((odd? (car lista-num)) (suma-izq (suma-impares-pares (cdr lista-num)) (car lista-num)))
       (else (suma-der (suma-impares-pares (cdr lista-num)) (car lista-num)))))

(check-equal? (suma-impares-pares '(3 2 1 4 8 7 6 5)) (cons 16 20)) ; ⇒ (16 . 20)
(check-equal? (suma-impares-pares '(3 1 5)) (cons 9 0)) ; ⇒ (9 . 0)

;;
;; Ejercicio 6
;;

(define (cadena-mayor lista)
  (cond((null? lista)(cons "" 0))
       ((> (string-length (car lista)) (cdr (cadena-mayor (cdr lista))))
                          (cons (car lista) (string-length (car lista))))
       (else (cadena-mayor (cdr lista)))))

(check-equal? (cadena-mayor '("vamos" "a" "obtener" "la" "cadena" "mayor")) (cons "obtener" 7)) ; ⇒  ("obtener" . 7)
(check-equal? (cadena-mayor '("prueba" "con" "maximo" "igual")) (cons "maximo" 6)) ; ⇒ ("maximo" . 6)
(check-equal? (cadena-mayor '()) (cons "" 0)) ; ⇒ ("" . 0)




