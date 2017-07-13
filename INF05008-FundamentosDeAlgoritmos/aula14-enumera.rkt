;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname enumera) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (menosUm n)
  (- n 1))


;; enumera: Natural -> Lista-de-Número
;; Dado um número natural, retorna uma lista com a enumeração de todos os naturais
;; começando dele e indo até zero (inclusive).
;; Exemplo: (enumera 0) (cons 0 empty)
;; Exemplo: (enumera 5) (cons 5 (cons 4 (cons 3 (cons 2 (cons 1 (cons 0 empty))))))
;; Exemplo: (enumera 11) (list 11 10 9 8 7 6 5 4 3 2 1 0)
(define (enumera n)
  (cond
    [(< n 1) (cons 0 empty)]
    [else (cons n (enumera (menosUm n)))]))
(check-expect (enumera 0) (cons 0 empty))
(check-expect (enumera 5) (cons 5 (cons 4 (cons 3 (cons 2 (cons 1 (cons 0 empty)))))))
(check-expect (enumera 11) (list 11 10 9 8 7 6 5 4 3 2 1 0))
