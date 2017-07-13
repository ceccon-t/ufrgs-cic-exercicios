;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname maior) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define L1 (list 1 5 4 9 2))
(define L2 (list 8 7 1 5 3))
(define L3 (list 4 5 3 2 7))
(define L4 (list 1))

;; maior: Lista-de-Numero -> Numero
;; Retorna o maior numero de uma lista NÃO VAZIA
;; Exemplo: (maior L1) 9
;; Exemplo: (maior L2) 8
;; Exemplo: (maior L3) 7
;; Exemplo: (maior L4) 1
(define (maior ldn)
  (cond
    [(empty? (rest ldn)) (first ldn)]
    [else (local ((define M (maior (rest ldn))))
                 (cond
                   [(> (first ldn) M) (first ldn)]
                   [else M]))]))
(check-expect (maior L1) 9)
(check-expect (maior L2) 8)
(check-expect (maior L3) 7)
(check-expect (maior L4) 1)
