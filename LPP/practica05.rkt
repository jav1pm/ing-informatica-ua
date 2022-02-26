;; Francisco Javier Perez Martinez

#lang racket
(require rackunit)
(require graphics/turtles)

;;
;; Ejercicio 1
;;

;; a)

(define (concat-iter lista res)
  (if (null? lista)
      res
      (concat-iter (cdr lista) (string-append res (car lista)))))

(define (concat lista)
  (concat-iter lista ""))

(check-equal? (concat  '("hola" "y" "adiós")) "holayadiós")
(check-equal? (concat-iter '("hola" "y" "adiós") "") "holayadiós")

;; b)

(define (min-max-pareja dato p1)
  (cons (min dato (car p1))
        (max dato (cdr p1))))

(define (min-max-iter lista res)
  (if (null? lista)
      res
      (min-max-iter (cdr lista) (min-max-pareja (car lista) res))))

(define (min-max lista)
  (min-max-iter (cdr lista) (cons (car lista) (car lista))))

(check-equal? (min-max '(2 5 9 12 5 0 4)) '(0 . 12)) ; ⇒ (0 . 12)
(check-equal? (min-max-iter '(5 9 12 5 0 4) (cons 2 2)) '(0 . 12)) ; ⇒ (0 . 12)


;;
;; Ejercicio 2
;;

;; a)

(define (expande-pareja-iter pareja res)
  (if (= (cdr pareja) 0)
      res
      (expande-pareja-iter (cons (car pareja) (- (cdr pareja) 1)) (cons (car pareja) res))))

(define (expande-pareja pareja)
  (expande-pareja-iter pareja '()))

(define (expande-parejas-iter lista res)
  (if (null? lista)
      res
      (expande-parejas-iter (cdr lista) (append res (expande-pareja (car lista))))))

(define (expande-parejas . lista)
  (expande-parejas-iter lista '()))

;; b)

(define (rotar k lista)
  (if (= k 0)
      lista
      (rotar (- k 1) (append (cdr lista) (list (car lista))))))

(check-equal? (rotar 4 '(a b c d e f g)) '(e f g a b c d)) ; ⇒ (e f g a b c d)

;;
;; Ejercicio 3
;;

;; a)

(define (mi-foldl funcion res lista)
  (if (null? lista)
      res
      (mi-foldl funcion (funcion (car lista) res) (cdr lista))))

(check-equal? (mi-foldl string-append "****" '("hola" "que" "tal")) "talquehola****")
(check-equal? (mi-foldl cons '() '(1 2 3 4)) '(4 3 2 1))

;; b)

(define (prefijo-lista? lista1 lista2)
  (if (null? lista1)
      #t
      (and (equal? (car lista1) (car lista2)) (prefijo-lista? (cdr lista1) (cdr lista2)))))

(check-true (prefijo-lista? '(a b c) '(a b c d e)))
(check-false (prefijo-lista? '(b c) '(a b c d e)))

;;
;; Ejercicio 4
;;

(define (crea-diccionario)
  (mcons '*diccionario* '()))

(define (busca key dic)
  (cond
    ((null? dic) #f)
    ((equal? key (mcar (mcar dic)))
     (mcar dic))
    (else (busca key (mcdr dic)))))

(define (get key dic)
  (define record (busca key (mcdr dic)))
  (if (not record)
      #f
      (mcdr record)))

(define (put key value dic)
  (define record (busca key (mcdr dic)))
  (if (not record)
      (set-mcdr! dic
                (mcons (mcons key value)
                      (mcdr dic)))
      (set-mcdr! record value))
  value)

(define (pascal-memo fila col dic)
  (cond ((= col 0) 1)
        ((= col fila) 1)
        ((not (equal? (get (cons fila col) dic) #f)) (get (cons fila col) dic))
        (else (put (cons fila col) (+ (pascal-memo (- fila 1) (- col 1) dic)
                                      (pascal-memo (- fila 1) col dic)) dic))))

(define diccionario (crea-diccionario))
(check-equal? (pascal-memo 8 4 diccionario) 70)
(check-equal? (pascal-memo 40 20 diccionario) 137846528820)


;;
;; Ejercicio 5
;;

;; a)

(define (koch nivel trazo)
  (if (= nivel 0)
      (draw trazo)
      (begin
        (koch (- nivel 1) (/ trazo 3))
        (turn 60)
        (koch (- nivel 1) (/ trazo 3))
        (turn -120)
        (koch (- nivel 1) (/ trazo 3))
        (turn 60)
        (koch (- nivel 1) (/ trazo 3)))))

;; b)

(define (copo-nieve nivel trazo)
  (begin
    (koch nivel trazo)
    (turn -120)
    (koch nivel trazo)
    (turn -120)
    (koch nivel trazo)))

;;
;; Ejercicio 6
;;

(define (cuadrado tam)
  (begin
    (draw tam)
    (turn 90)
    (draw tam)
    (turn 90)
    (draw tam)
    (turn 90)
    (draw tam)
    (turn 90)))

(define (alfombra-sierpinski tam)
  (if (> tam 10)
      (begin
        (alfombra-sierpinski (/ tam 3))
        (move (/ tam 3))
        (alfombra-sierpinski (/ tam 3))
        (move (/ tam 3))
        (alfombra-sierpinski (/ tam 3))
        (turn 90) (move (/ tam 3)) (turn -90)
        (alfombra-sierpinski (/ tam 3))
        (turn 90) (move (/ tam 3)) (turn -90)
        (alfombra-sierpinski (/ tam 3))
        (turn 180) (move (/ tam 3)) (turn -180)
        (alfombra-sierpinski (/ tam 3))
        (turn 180) (move (/ tam 3)) (turn -180)
        (alfombra-sierpinski (/ tam 3))
        (turn -90) (move (/ tam 3)) (turn 90)
        (alfombra-sierpinski (/ tam 3))
        (turn -90) (move (/ tam 3)) (turn 90))
      (cuadrado tam)))