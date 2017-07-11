;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname idade-media) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define-struct pessoa (nome ano pai mae))

;; Um Parente é:
;; 1. empty;
;; 2. (make-pessoa n a p m), onde:
;; n: String (nome da pessoa)
;; a: Número (ano de nascimento da pessoa)
;; p: Parente (pai desta pessoa)
;; m: Parente (mãe desta pessoa)

(define Carl (make-pessoa "Carl" 1926 empty empty))
(define Bettina (make-pessoa "Bettina" 1926 empty empty))
(define Addam (make-pessoa "Addam" 1950 Carl Bettina))
(define Dave (make-pessoa "Dave" 1955 Carl Bettina))
(define Eva (make-pessoa "Eva" 1965 Carl Bettina))
(define Fred (make-pessoa "Fred" 1966 empty empty))
(define Gustav (make-pessoa "Gustav" 1988 Fred Eva))

;; calcula-idade: Número -> Número
;; Dado o ano de nascimento de uma pessoa, retorna a sua idade
;; Exemplo: (calcula-idade 2000) 17
(define (calcula-idade a)
  (- 2017 a))
(check-expect (calcula-idade 2000) 17)

;; calcula-soma-idades: Parente -> Número
;; Dado um parente, calcula a soma das idades de todos os seus parentes, incluindo
;; ele próprio
;; Exemplo: (calcula-soma-idades empty) 0
;; Exemplo: (calcula-soma-idades Carl) 91
;; Exemplo: (calcula-soma-idades Addam) 249
(define (calcula-soma-idades p)
  (cond
    [(empty? p) 0]
    [else (+ (calcula-idade (pessoa-ano p))
             (calcula-soma-idades (pessoa-pai p))
             (calcula-soma-idades (pessoa-mae p)) ) ]))
(check-expect (calcula-soma-idades empty) 0)
(check-expect (calcula-soma-idades Carl) 91)
(check-expect (calcula-soma-idades Addam) 249)

;; total-parentes: Parente -> Número
;; Dado um parente, retorna o total de parentes presente na árvore que se inicia
;; com ele
;; Exemplo: (total-parentes empty) 0
;; Exemplo: (total-parentes Carl) 1
;; Exemplo: (total-parentes Gustav) 5
(define (total-parentes p)
  (cond
    [(empty? p) 0]
    [else (+ 1 (total-parentes (pessoa-pai p))
               (total-parentes (pessoa-mae p)) ) ]))
(check-expect (total-parentes empty) 0)
(check-expect (total-parentes Carl) 1)
(check-expect (total-parentes Gustav) 5)


;; idade-media: Parente -> Número
;; Dado um parente, produz a idade média de seus parentes na árvore, incluindo
;; ele próprio
;; Exemplo: (idade-media empty) 0
;; Exemplo: (idade-media Carl) 91
;; Exemplo: (idade-media Addam) 83
(define (idade-media p)
  (cond
    [(empty? p) 0]
    [else (/ (calcula-soma-idades p)
             (total-parentes p) ) ]))
(check-expect (idade-media empty) 0)
(check-expect (idade-media Carl) 91)
(check-expect (idade-media Addam) 83)
