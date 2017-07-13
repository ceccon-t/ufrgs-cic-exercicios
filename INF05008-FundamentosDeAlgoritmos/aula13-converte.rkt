;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname converte) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;; DEFINIÇÃO DE DADOS
(define LDN1 (cons 1 (cons 5 (cons 3 empty))))
(define LDN2 (list 5 2 6 2))

;; converte: Lista-De-Número -> Número
;; Dada uma lista de dígitos entre 0 e 9, retorna uma representação decimal
;; de um número construído considerando-se o primeiro dígito da lista como
;; o menos significativo, o segundo como o segundo menos significativo, etc.
;; Exemplo: (converte empty) 0
;; Exemplo: (converte LDN1)  351
;; Exemplo: (converte LDN2)  2625
(define (converte ldn)
  (cond
    [(empty? ldn) 0]
    [else (+ (first ldn) (* 10 (converte (rest ldn))))]))
(check-expect (converte empty) 0)
(check-expect (converte LDN1)  351)
(check-expect (converte LDN2)  2625)
