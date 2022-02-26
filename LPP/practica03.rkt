;; Francisco Javier Perez Martinez

#lang racket
(require rackunit)

;;
;; Ejercicio 1
;;

;; a)

(define (es-prefijo? pal1 pal2)
  (if (< (string-length pal2) (string-length pal1))
      #f
      (equal? pal1 (substring pal2 0 (string-length pal1)))))

(check-equal? (es-prefijo? "ante" "anterior") #t) ; ⇒ #t
(check-equal? (es-prefijo? "sub" "antena") #f) ; ⇒ f

(define (contiene-prefijo prefijo lista-pal)
  (if (null? (cdr lista-pal))
      (list (es-prefijo? prefijo (car lista-pal)))
      (cons (es-prefijo? prefijo (car lista-pal)) (contiene-prefijo prefijo (cdr lista-pal)))))

(check-equal? (contiene-prefijo "ante" '("anterior" "antígona" "antena" "anatema")) '(#t #f #t #f)) ; ⇒ (#t #f #t #f)

;; b)

(define (inserta-pos dato pos lista)
  (if (= pos 0)
      (cons dato lista)
      (cons (car lista) (inserta-pos dato (- pos 1) (cdr lista)))))

(check-equal? (inserta-pos 'b 2 '(a a a a)) '(a a b a a)) ; ⇒ '(a a b a a)
(check-equal? (inserta-pos 'b 0 '(a a a a)) '(b a a a a)) ; ⇒ '(b a a a a)

;; c)

(define (inserta-ordenada n lista-ordenada)
  (cond((< n (car lista-ordenada)) (cons n lista-ordenada))
       ((null? (cdr lista-ordenada)) (append lista-ordenada (list n)))
       (else (cons (car lista-ordenada) (inserta-ordenada n (cdr lista-ordenada))))))

(check-equal? (inserta-ordenada 10 '(-8 2 3 11 20)) '(-8 2 3 10 11 20)) ; ⇒ (-8 2 3 10 11 20)

(define (ordena lista)
  (if (null? (cdr lista))
      lista
      (inserta-ordenada (car lista) (ordena (cdr lista)))))

(check-equal? (ordena '(2 -1 100 4 -6)) '(-6 -1 2 4 100)) ; ⇒ (-6 -1 2 4 100)

;;
;; Ejercicio 2
;;

;; a)

(define (expande-pareja pareja)
  (if (equal? 0 (cdr pareja))
      '()
      (cons (car pareja) (expande-pareja (cons (car pareja) (- (cdr pareja) 1))))))

(check-equal? (expande-pareja (cons #t 4)) '(#t #t #t #t))
(check-equal? (expande-pareja (cons '3 0)) '())

(define (expande-lista lista-parejas)
  (if (null? lista-parejas)
      '()
      (append (expande-pareja (car lista-parejas)) (expande-lista (cdr lista-parejas)))))

(define (expande-parejas . pareja_n)
  (expande-lista pareja_n))

(check-equal? (expande-parejas '(#t . 3) '("LPP" . 2) '(b . 4)) '(#t #t #t "LPP" "LPP" b b b b)) ; ⇒ (#t #t #t "LPP" "LPP" b b b b)

;; b)

(define (expande2 lista)
  (cond((null? lista) '())
       ((integer? (car lista)) (append (expande-pareja (cons (cadr lista) (car lista))) (expande2 (cddr lista))))
       (else (append (list (car lista)) (expande2 (cdr lista))))))

(check-equal? (expande2 '(4 clase ua 3 lpp aulario)) '(clase clase clase clase ua lpp lpp lpp aulario))
(check-equal? (expande2 '(clase 5 ua 3 lpp aulario)) '(clase ua ua ua ua ua lpp lpp lpp aulario))

;;
;; Ejercicio 3
;;

;; a)


;; b)

(define (first-elem elem lista)
  (if (null? (cdr lista))
      (list (cons elem (car lista)))
      (cons (cons elem (car lista)) (first-elem elem (cdr lista)))))

(check-equal? (first-elem 1 '(1 2 3)) '((1 . 1) (1 . 2) (1 . 3)))
      
      

(define (producto-cartesiano lista1 lista2)
  (if (null? (cdr lista1))
      (first-elem (car lista1) lista2)
      (append (first-elem (car lista1) lista2) (producto-cartesiano (cdr lista1) lista2))))

(check-equal? (producto-cartesiano '(1 2) '(1 2 3)) '((1 . 1) (1 . 2) (1 . 3) (2 . 1) (2 . 2) (2 . 3)))
; ⇒ ((1 . 1) (1 . 2) (1 . 3) (2 . 1) (2 . 2) (2 . 3))


;;
;; Ejercicio 4
;;

;; a)

;; ((lambda (x) (* x x)) 3) ; ⇒ 9
;; ((lambda () (+ 6 4))) ; ⇒ 10
;; ((lambda (x y) (* x (+ 2 y))) (+ 2 3) 4) ; ⇒ 30
;; ((lambda (x y) (* x (+ 2 x))) 5) ; ⇒ #<procedure>: arity mismatch --> falta 1 argumento


(define f (lambda (a b) (string-append "***" a b "***")))
(define g f)
;; (procedure? g) ; ⇒ #t
;; (g "Hola" "Adios") ; ⇒ "***HolaAdios***"

;; b)

(define suma-3
  (lambda (x) (+ x 3)))

(check-equal? (suma-3 3) 6)

(define factorial
  (lambda (x)
    (if (= x 0)
        1
        (* x (factorial (- x 1))))))

(check-equal? (factorial 5) 120)

;; c)

(define (doble x)
   (* 2 x))

(define (foo f g x y)
   (f (g x) y))

(define (bar f p x y)
   (if (and (p x) (p y))
       (f x y)
       'error))

;; (foo + 10 doble 15) ⇒ error, g espera un procedure.

;; (foo doble + 10 15) ⇒ error, f recibe 2 parametros y solo debe recibir 1.

;; (foo + doble 10 15) ⇒ 35

;; (foo string-append (lambda (x) (string-append "***" x)) "Hola" "Adios") ⇒ "***HolaAdios"

;; (bar doble number? 10 15) ⇒ error, f esta recibiendo 2 parametros.

;; (bar string-append string? "Hola" "Adios") ⇒ "HolaAdios"

;; (bar + number? "Hola" 5) ⇒ error

;;
;; Ejercicio 5
;;

;; a)

(define (unir-pareja pareja)
  (string->symbol (string (cdr pareja) (car pareja))))

(check-equal? (unir-pareja (cons #\u2660 #\A)) 'A♠)

(define (crea-baraja lista-parejas)
  (if (null? (cdr lista-parejas))
      (list (unir-pareja (car lista-parejas)))
      (cons (unir-pareja (car lista-parejas)) (crea-baraja (cdr lista-parejas)))))

(check-equal? (crea-baraja '((#\u2660 . #\A) (#\u2663 . #\2) (#\u2665 . #\3) (#\u2666 . #\R))) '(A♠ 2♣ 3♥ R♦)); ⇒ (A♠ 2♣ 3♥ R♦)

;; b)

(define palos '(#\u2660 #\u2663 #\u2665 #\u2666))
(define valores '(#\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9 #\0 #\J #\Q #\K #\A))

(define (baraja-poker)
  (crea-baraja (producto-cartesiano palos valores)))

;; c)

(define (mezcla lista)
  (if (null? lista)
      '()
      (inserta-pos (car lista) (random 0 (length lista)) (mezcla (cdr lista)))))


;;
;; Ejercicio 6
;;

(define (check-tam? simbolo num)
  (= (string-length (symbol->string simbolo)) num))

(check-true (check-tam? 'este 4))
(check-false (check-tam? 'un 6))


(define (filtra-simbolos lista-simbolos lista-num)
  (cond((null? lista-simbolos) '())
       ((check-tam? (car lista-simbolos) (car lista-num))
                    (cons (cons (car lista-simbolos) (car lista-num)) (filtra-simbolos (cdr lista-simbolos) (cdr lista-num))))
       (else (filtra-simbolos (cdr lista-simbolos) (cdr lista-num)))))

(check-equal? (filtra-simbolos '(este es un ejercicio de examen) '(2 1 2 9 1 6)) '((un . 2) (ejercicio . 9) (examen . 6))) ; ⇒ ((un . 2) (ejercicio . 9) (examen . 6))



