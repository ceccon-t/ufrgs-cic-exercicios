;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname Lab01_2017-04-13) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;; imposto-sobre-salario: Numero -> Numero
;; Dado um salario bruto, retorna a quantia de imposto devida 
;; Exemplo: (imposto-sobre-salario 10) 0
;; Exemplo: (imposto-sobre-salario 240) 0
;; Exemplo: (imposto-sobre-salario 241) 36.15
;; Exemplo: (imposto-sobre-salario 480) 72
;; Exemplo: (imposto-sobre-salario 481) 134.68
;; Exemplo: (imposto-sobre-salario 500) 140
(define (imposto-sobre-salario salario)
  (cond
    [(<= salario 240) 0]
    [(<= salario 480) (* salario 0.15)]
    [else (* salario 0.28)]
  )
)
(check-expect (imposto-sobre-salario 10) 0)
(check-expect (imposto-sobre-salario 240) 0)
(check-expect (imposto-sobre-salario 241) 36.15)
(check-expect (imposto-sobre-salario 480) 72)
(check-expect (imposto-sobre-salario 481) 134.68)
(check-expect (imposto-sobre-salario 500) 140)

;; salario-bruto: Numero -> Numero
;; Dado o numero de horas trabalhadas, retorna o valor do salario bruto (considerando que a hora vale R$ 15.00
;; Exemplo: (salario-bruto 100) 1500
(define (salario-bruto horas-trabalhadas)
  (* horas-trabalhadas 15)
)
(check-expect (salario-bruto 1) 15)
(check-expect (salario-bruto 88) 1320)
(check-expect (salario-bruto 100) 1500)

;; calcular-salario-liquido: Numero -> Numero
;; A partir de um determinado numero de horas trabalhadas, calcula o salario liquido (salario bruto - imposto)
;; Exemplo: (calcular-salario-liquido 1) 15
;; Exemplo: (calcular-salario-liquido 16) 240
;; Exemplo: (calcular-salario-liquido 17) 216.75
;; Exemplo: (calcular-salario-liquido 32) 408
;; Exemplo: (calcular-salario-liquido 33) 356.4
(define (calcular-salario-liquido horas-trabalhadas)
  (- (salario-bruto horas-trabalhadas)
     (imposto-sobre-salario (salario-bruto horas-trabalhadas))
  )
)
(check-expect (calcular-salario-liquido 1) 15)
(check-expect (calcular-salario-liquido 16) 240)
(check-expect (calcular-salario-liquido 17) 216.75)
(check-expect (calcular-salario-liquido 32) 408)
(check-expect (calcular-salario-liquido 33) 356.4)


;; testa-cores: String String String String -> Symbol
;; Recebe o nome de duas cores ordenadas e duas tentativas de adivinhações e informa qual o grau de acerto das adivinhações
;; Exemplo: (testa-cores "verde" "vermelho" "verde" "vermelho") 'Exato!
;; Exemplo: (testa-cores "verde" "vermelho" "azul" "vermelho") 'UmaPosiçãoCorreta
;; Exemplo: (testa-cores "verde" "vermelho" "vermelho" "azul") 'UmaCorCorreta
;; Exemplo: (testa-cores "verde" "vermelho" "azul" "amarelo") 'TudoErrado!
(define (testa-cores p1 p2 c1 c2)
  (cond
    [(and (string=? p1 c1) (string=? p2 c2)) 'Exato!]
    [(or (string=? p1 c1) (string=? p2 c2)) 'UmaPosiçãoCorreta]
    [(or (or (string=? c1 p1) (string=? c1 p2)) (or (string=? c2 p1) (string=? c2 p2))) 'UmaCorCorreta]
    [else 'TudoErrado!]
  )
)
(check-expect (testa-cores "verde" "vermelho" "verde" "vermelho") 'Exato!)
(check-expect (testa-cores "verde" "vermelho" "azul" "vermelho") 'UmaPosiçãoCorreta)
(check-expect (testa-cores "verde" "vermelho" "vermelho" "azul") 'UmaCorCorreta)
(check-expect (testa-cores "verde" "vermelho" "azul" "amarelo") 'TudoErrado!)

;; calcular-pos-final-robo: Numero Symbol Numero -> Numero
;; Dada uma posicao atual, uma direcao de movimento e o numero de passos a executar,
;; calcular posicao final do robo caso todos os passos sejam executados (sem considerar limitacao de movimentos)
;; Exemplo: (calcular-pos-final-robo 1 'D 1) 2
;; Exemplo: (calcular-pos-final-robo 1 'D 60) 61
;; Exemplo: (calcular-pos-final-robo 10 'E 1) 9
;; Exemplo: (calcular-pos-final-robo 10 'E 11) -1 
(define (calcular-pos-final-robo pos-atual sentido num-passos)
  (cond
    [(symbol=? sentido 'D) (+ pos-atual num-passos)]
    [(symbol=? sentido 'E) (- pos-atual num-passos)]
  )
)
(check-expect (calcular-pos-final-robo 1 'D 1) 2)
(check-expect (calcular-pos-final-robo 1 'D 60) 61)
(check-expect (calcular-pos-final-robo 10 'E 1) 9)
(check-expect (calcular-pos-final-robo 10 'E 11) -1)


;; mover-robo: Numero Symbol Numero -> Numero
;; Dada uma posicao atual, uma direcao de movimento e o numero de passos a executar,
;; calcular posicao final do robo em uma reta com 50 posicoes (nao extrapolando)
;; Exemplo: (mover-robo 1 'D 1) 2
;; Exemplo: (mover-robo 1 'D 51) 50
;; Exemplo: (mover-robo 10 'E 1) 9
;; Exemplo: (mover-robo 10 'E 11) 1
(define (mover-robo pos-atual sentido num-passos)
  (cond
    [(> (calcular-pos-final-robo pos-atual sentido num-passos) 50) 50]
    [(< (calcular-pos-final-robo pos-atual sentido num-passos) 1) 1]
    [else (calcular-pos-final-robo pos-atual sentido num-passos)]
  )
)
(check-expect (mover-robo 1 'D 1) 2)
(check-expect (mover-robo 1 'D 51) 50)
(check-expect (mover-robo 10 'E 1) 9)
(check-expect (mover-robo 10 'E 11) 1)
