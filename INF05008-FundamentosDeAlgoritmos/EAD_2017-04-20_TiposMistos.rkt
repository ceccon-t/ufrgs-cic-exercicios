;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname EAD-TiposMistos) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;; Definição de dados:

(define-struct cubo (lado))
;; Um elemento cubo de Cubo é uma estrutura
;; (make-cubo lado)
;; onde:
;; lado: Número, é o comprimento do lado do cubo

(define-struct prisma (altura largura profundidade))
;; Um elemento prisma de Prisma é uma estrutura
;; (make-prisma altura largura profundidade)
;; onde:
;; altura: Número, é a altura do prisma
;; largura: Número, é a largura do prisma
;; profundidade: Número, é a profundidade do prisma

(define-struct esfera (raio))
;; Um elemento esfera de Esfera é uma estrutura
;; (make-esfera raio)
;; onde:
;; raio: Número, é o raio da esfera

;; Um elemento forma3D de Forma3D é:
;; 1. ou um elemento de Cubo
;; 2. ou um elemento de Prisma
;; 3. ou um elemento de Esfera


;; volume: Forma3D -> Número
;; Calcular o volume de uma determinada Forma3D com a fórmula correta
;; Exemplo: (volume (make-cubo 2)) 8
;; Exemplo: (volume (make-prisma 2 5 3) 30
;; Exemplo: (volume (make-esfera 3) 12.56
(define (volume forma)
  (cond
    [(cubo? forma) (expt (cubo-lado forma) 3)]
    [(prisma? forma) (* (prisma-altura forma) (prisma-largura forma) (prisma-profundidade forma))]
    [(esfera? forma) (/ (* 4 3.14 (expt (esfera-raio forma) 3)) 3)]
    ) )
(check-expect (volume (make-cubo 2)) 8)
(check-expect (volume (make-prisma 2 5 3)) 30)
(check-expect (volume (make-esfera 3)) 113.04)


;; mesma-forma3D?: Forma3D Forma3D -> Booleano
;; Verifica se duas formas são do mesmo tipo e possuem mesmas dimensões
;; Exemplo: (mesma-forma3D? (make-cubo 3) (make-esfera 3)) false
;; Exemplo: (mesma-forma3D? (make-esfera 3) (make-esfera 4)) false
;; Exemplo: (mesma-forma3D? (make-cubo 5) (make-prisma 5 5 5)) false
;; Exemplo: (mesma-forma3D? (make-cubo 2) (make-cubo 2)) true
(define (mesma-forma3D? forma1 forma2)
  (cond
    [(and (cubo? forma1) (cubo? forma2)) (= (cubo-lado forma1) (cubo-lado forma2))]
    [(and (esfera? forma1) (esfera? forma2)) (= (esfera-raio forma1) (esfera-raio forma2))]
    [(and (prisma? forma1) (prisma? forma2)) (and (= (prisma-altura forma1) (prisma-altura forma2))
                                             (= (prisma-largura forma1) (prisma-largura forma2))
                                             (= (prisma-profundidade forma1) (prisma-profundidade forma2)))]
    [else false]) )
(check-expect (mesma-forma3D? (make-cubo 3) (make-esfera 3)) false)
(check-expect (mesma-forma3D? (make-esfera 5) (make-prisma 5 5 5)) false)
(check-expect (mesma-forma3D? (make-cubo 2) (make-cubo 2)) true)
(check-expect (mesma-forma3D? (make-cubo 4) (make-cubo 2)) false)
(check-expect (mesma-forma3D? (make-esfera 5) (make-esfera 5)) true)
(check-expect (mesma-forma3D? (make-esfera 3) (make-esfera 4)) false)
(check-expect (mesma-forma3D? (make-prisma 1 2 5) (make-prisma 1 2 5)) true)
(check-expect (mesma-forma3D? (make-prisma 9 2 5) (make-prisma 1 2 5)) false)
(check-expect (mesma-forma3D? (make-prisma 1 2 10) (make-prisma 1 4 5)) false)
