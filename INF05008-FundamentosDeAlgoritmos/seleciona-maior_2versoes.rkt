;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname seleciona-maior_2versoes) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;; DEFINIÇÃO DE DADOS
(define L1 (list 1 3 5 9 7 2))
(define L2 (list 1))
(define L3 (list 8 4 3 5))
(define L4 (list 5 3 9))


;; 1a versão

;; seleciona-maior: Lista-de-Número Número -> Número
;; Dada uma lista de números, retorna o maior número presente nela
;; usando um parâmetro como variável
;; Exemplo: (seleciona-maior empty 1) 1
;; Exemplo: (seleciona-maior (rest L1) (first L1)) 9
;; Exemplo: (seleciona-maior (rest L3) (first L3)) 8
;; Exemplo: (seleciona-maior (rest L4) (first L4)) 9
(define (seleciona-maior ldn n)
  (cond
    [(empty? ldn) n]
    [else (cond
            [(> (first ldn) n) (seleciona-maior (rest ldn) (first ldn))]
            [else (seleciona-maior (rest ldn) n)])]))
(check-expect (seleciona-maior empty 1) 1)
(check-expect (seleciona-maior (rest L1) (first L1)) 9)
(check-expect (seleciona-maior (rest L3) (first L3)) 8)
(check-expect (seleciona-maior (rest L4) (first L4)) 9)

;; 2a versão

;; maior: Número Número -> Número
;; Dados dois números, retorna o maior entre eles, ou o próprio caso sejam iguais
;; Exemplo: (maior 4 5) 5
;; Exemplo: (maior 8 3) 8
;; Exemplo: (maior 2 2) 2
(define (maior a b)
  (cond
    [(> a b) a]
    [else b]))
(check-expect (maior 4 5) 5)
(check-expect (maior 8 3) 8)
(check-expect (maior 2 2) 2)

;; menor: Número Número -> Número
;; Dados dois números, retorna o menor entre eles, ou o próprio caso sejam iguais
;; Exemplo: (menor 4 5) 4
;; Exemplo: (menor 8 3) 3
;; Exemplo: (menor 2 2) 2
(define (menor a b)
  (cond
    [(< a b) a]
    [else b]))
(check-expect (menor 4 5) 4)
(check-expect (menor 8 3) 3)
(check-expect (menor 2 2) 2)

;; Versao alternativa de 'seleciona-maior', parametrizada com funcao de ordem

;; seleciona-elemento: Lista-de-Número Número (Número Número -> Número) -> Número
;; Dada uma lista e uma função de ordem, retorna o elemento mais relevante na lista
;; de acordo com a função, usando um parâmetro como variável
;; Exemplo: (seleciona-elemento empty 1 maior) 1
;; Exemplo: (seleciona-elemento (rest L1) (first L1) maior) 9
;; Exemplo: (seleciona-elemento (rest L3) (first L3) maior) 8
;; Exemplo: (seleciona-elemento (rest L4) (first L4) maior) 9
;; Exemplo: (seleciona-elemento empty 1 menor) 1
;; Exemplo: (seleciona-elemento (rest L1) (first L1) menor) 1
;; Exemplo: (seleciona-elemento (rest L3) (first L3) menor) 3
;; Exemplo: (seleciona-elemento (rest L4) (first L4) menor) 3
(define (seleciona-elemento ldn n op)
  (cond
    [(empty? ldn) n]
    [else (seleciona-elemento (rest ldn) (op (first ldn) n) op )]))

(check-expect (seleciona-elemento empty 1 maior) 1)
(check-expect (seleciona-elemento (rest L1) (first L1) maior) 9)
(check-expect (seleciona-elemento (rest L3) (first L3) maior) 8)
(check-expect (seleciona-elemento (rest L4) (first L4) maior) 9)
(check-expect (seleciona-elemento empty 1 menor) 1)
(check-expect (seleciona-elemento (rest L1) (first L1) menor) 1)
(check-expect (seleciona-elemento (rest L3) (first L3) menor) 3)
(check-expect (seleciona-elemento (rest L4) (first L4) menor) 3)
