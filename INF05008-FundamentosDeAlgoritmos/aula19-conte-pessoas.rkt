;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname conte-pessoas) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define-struct filho (pai mãe nome data olhos))
;; Um elemento filho do conjunto Filho é uma estrutura:
;; (make-filho p m n d o), onde
;; p e m: empty ou Filho, respectivamente, pai e mãe do filho
;; n e o são Símbolo, respectivamente, nome e cor dos olhos do
;; filho
;; d é Número, ano de nascimento do filho

;; Geração antiga :
( define Carl
( make-filho empty empty 'Carl 1926 'verdes ))
( define Bettina
( make-filho empty empty 'Bettina 1926 'verdes ))

;; Geração intermediária :
( define Addam
( make-filho Carl Bettina 'Addam 1950 'amarelos ))
( define Dave
( make-filho Carl Bettina 'Dave 1955 'pretos ))
( define Eva
( make-filho Carl Bettina 'Eva 1965 'azuis ))
( define Fred
( make-filho empty empty 'Fred 1966 'cor-de-rosa ))

;; Geração nova:
( define Gustav
( make-filho Fred Eva 'Gustav 1988 'castanhos ))


;; conte-pessoas: Filho -> Número
;; A partir de um nó de uma árvore genealógica, retorn o número de ancestrais
;; Exemplo: (conte-pessoas empty) 0
;; Exemplo: (conte-pessoas Carl) 1
;; Exemplo: (conte-pessoas Gustav) 5
(define (conte-pessoas f)
  (cond
    [(empty? f) 0]
    [else (+ 1 (conte-pessoas (filho-pai f)) (conte-pessoas (filho-mãe f)))]))
(check-expect (conte-pessoas empty) 0)
(check-expect (conte-pessoas Carl) 1)
(check-expect (conte-pessoas Gustav) 5)
