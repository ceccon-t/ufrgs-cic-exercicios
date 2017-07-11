;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname pesquisa-contato) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define-struct contato (registro numero nome esq dir))
;; Um elemento contato do conjunto Contato é uma estrutura
;; (make-contato r num n e d), onde:
;; r: Número, o registro do contato
;; num: Número, o telefone do contato
;; n: String, o nome do contato
;; e: Nó-Contato
;; d: Nó-Contato
;; onde e contém todos os contatos cujo número de registro é menor do que esse contato
;; e d contém todos os contatos cujo número de registro é maior do que esse contato

;; Um elemento nó-contato do conjunto Nó-Contato é:
;; 1. empty
;; 2. Contato

(define C1 (make-contato 6162 33154252 "Joana" empty empty))
(define C2 (make-contato 4111 33151515 "João" empty empty))
(define C3 (make-contato 5110 31325450 "Carlos" C2 C1))
(define C4 (make-contato 2100 31541654 "Maria" empty empty))
(define C5 (make-contato 3030 30215121 "Cássio" C4 C3))


(define-struct info (nome numero))
;; Um elemento info do conjunto Info é uma estrutura:
;; (make-info n num), onde:
;; n: String, o nome de uma pessoa
;; num: Número, o número de telefone dessa pessoa
(define I1 (make-info "Joana" 33154252))
(define I4 (make-info "Maria" 31541654))
(define I5 (make-info "Cássio" 30215121))

;; Um elemento infooufalse de InfoOuFalse é:
;; ou Info
;; ou Booleano (false)


;; pesquisa-contato: Nó-Contato Número -> InfoOuFalse
;; Dada uma ABP de contatos e o número do registro de um contato, retorna o nome
;; e o número de telefone desse contato caso ele esteja na árvore e false caso
;; não esteja
;; Exemplo: (pesquisa-contato empty) false
;; Exemplo: (pesquisa-contato C5 3030) I5
;; Exemplo: (pesquisa-contato C5 6162) I1
;; Exemplo: (pesquisa-contato C5 2100) I4
;; Exemplo: (pesquisa-contato C5 7070) false
(define (pesquisa-contato adc r)
  (cond
    [(empty? adc) false]
    [(= r (contato-registro adc)) (make-info (contato-nome adc) (contato-numero adc) )]
    [(< r (contato-registro adc)) (pesquisa-contato (contato-esq adc) r)]
    [else (pesquisa-contato (contato-dir adc) r) ]))
(check-expect (pesquisa-contato empty 3030) false)
(check-expect (pesquisa-contato C5 3030) I5)
(check-expect (pesquisa-contato C5 6162) I1)
(check-expect (pesquisa-contato C5 2100) I4)
(check-expect (pesquisa-contato C5 7070) false)
