;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname Lab02_2017-04-27) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;; Definição de dados

(define-struct carro-passeio (cor tipo possui-airbag num-vendidos))
;; Um elemento carro-passeio de Carro-Passeio é uma estrutura
;; (make-carro-passeio c t pa nv)
;; onde:
;; c: String, é a cor do carro
;; t: String, é o tipo do carro
;; pa: Booleano, true se o carro possui airbag, false se não possui
;; nv: Número, número de unidades já vendidas

(define CP1 (make-carro-passeio "Cinza" "sedan" true 50))
(define CP2 (make-carro-passeio "Ciano" "sedan" false 30))
(define CP3 (make-carro-passeio "Azul" "hatch" false 30))


(define-struct carro-utilitario (cor num-assentos tracao4rodas num-vendidos))
;; Um elemento carro-utilitario de Carro-Utilitario é uma estrutura
;; (make-carro-utilitario c na tr nv)
;; onde:
;; c: String, é a cor do carro
;; na: Número, número de assentos do carro
;; tr: Booleano, true se o carro possui tração nas 4 rodas, false se não possui
;; nv: Número, número de unidades já vendidas

(define UT1 (make-carro-utilitario "Vermelho" 4 true 100))
(define UT2 (make-carro-utilitario "Amarelo" 5 false 200))


(define-struct caminhao (cor total-carga volume-carga num-vendidos))
;; Um elemento caminhao de Caminhão é uma estrutura
;; (make-caminhao c tc vc nv)
;; onde:
;; c: String, é a cor do caminhão
;; tc: Número, peso total em toneladas que o caminhão pode transportar
;; vc: Número, volume total de espaço para cargas em m³
;; nv: Número, número de unidades já vendidas

(define C1 (make-caminhao "Preto" 16 50 150))
(define C2 (make-caminhao "Branco" 20 55 250))

;; Um elemento veículo de Veículo é:
;; 1. ou um elemento de Carro-Passeio
;; 2. ou um elemento de Carro-Utilitario
;; 3. ou um elemento de Caminhao

(define-struct montadora (total-a-ser-enviado vendidos-passeio vendidos-utilitario vendidos-caminhao))
;; Um elemento montadora de Montadora é uma estrutura
;; (make-montadora t vp vu vc)
;; onde:
;; t: Número, é o número total de veículos a serem enviados para as revendedoras
;; vp: Número, é o número de carros de passeio já vendidos
;; vu: Número, é o número de carros utilitários já vendidos
;; vc: Número, é o número de caminhões já vendidos

(define M (make-montadora 500 0 0 0))


;; tipo-e-cor: Veículo -> String
;; Dado um veículo, retornar uma string contendo seu tipo e sua cor no formato "Tipo: XXXX , Cor: XXXX"
;; Exemplo: (tipo-e-cor CP1) "Tipo: Carro de passeio , Cor: Cinza"
;; Exemplo: (tipo-e-cor UT1) "Tipo: Carro utilitário , Cor: Vermelho"
;; Exemplo: (tipo-e-cor C1) "Tipo: Caminhão , Cor: Preto"
(define (tipo-e-cor veiculo)
  (cond
    [(carro-passeio? veiculo) (string-append "Tipo: Carro de passeio , Cor: " (carro-passeio-cor veiculo))]
    [(carro-utilitario? veiculo) (string-append "Tipo: Carro utilitário, Cor: " (carro-utilitario-cor veiculo))]
    [(caminhao? veiculo) (string-append "Tipo: Caminhão , Cor: " (caminhao-cor veiculo))]))
(check-expect (tipo-e-cor CP1) "Tipo: Carro de passeio , Cor: Cinza")
(check-expect (tipo-e-cor UT1) "Tipo: Carro utilitário, Cor: Vermelho")
(check-expect (tipo-e-cor C1) "Tipo: Caminhão , Cor: Preto")

;; altera-utilitario-com-tracao : Carro-Utilitario -> Carro-Utilitario
;; Dado um utilitário, se ele possui tração nas quatro rodas, remove um assento e muda sua cor para azul.
;; Exemplo: (altera-utilitario-com-tracao UT1) (make-carro-utilitario "Azul" 3 true 100)
;; Exemplo: (altera-utilitario-com-tracao UT2) UT2
(define (altera-utilitario-com-tracao veiculo)
  (make-carro-utilitario (cond [(carro-utilitario-tracao4rodas veiculo) "Azul"] [else (carro-utilitario-cor veiculo)])
                         (cond [(carro-utilitario-tracao4rodas veiculo) (- (carro-utilitario-num-assentos veiculo) 1)] [else (carro-utilitario-num-assentos veiculo)])
                         (carro-utilitario-tracao4rodas veiculo)
                         (carro-utilitario-num-vendidos veiculo)))
(check-expect (altera-utilitario-com-tracao UT1) (make-carro-utilitario "Azul" 3 true 100))
(check-expect (altera-utilitario-com-tracao UT2) UT2)

;; determina-informacoes: Veículo -> String
;; Recebe informações de um veículo e retorna uma String informando:
;; Se for um veículo de passeio e do tipo sedan, determina se ele possui ou não airbag
;; Se for um utilitário, determina se ele possui tração nas quatro rodas
;; Se for um caminhão, mostra o volume total de carga que ele pode transportar
;; Exemplo: (determina-informacoes CP1) "Possui airbag"
;; Exemplo: (determina-informacoes CP2) "Não possui airbag"
;; Exemplo: (determina-informacoes CP3) ""
;; Exemplo: (determina-informacoes UT1) "Possui tração nas quatro rodas"
;; Exemplo: (determina-informacoes UT2) "Não possui tração nas quatro rodas"
;; Exemplo: (determina-informacoes C1) "Volume total da carga: 50"
;; Exemplo: (determina-informacoes C2) "Volume total da carga: 55"
(define (determina-informacoes veiculo)
  (cond [(carro-passeio? veiculo) (cond [(string=? (carro-passeio-tipo veiculo) "sedan")
                                          (cond [(carro-passeio-possui-airbag veiculo) "Possui airbag"]
                                                [else "Não possui airbag"])]
                                        [else ""])]
        [(carro-utilitario? veiculo) (cond [(carro-utilitario-tracao4rodas veiculo) "Possui tração nas quatro rodas"]
                                           [else "Não possui tração nas quatro rodas"])]
        [(caminhao? veiculo) (string-append "Volume total da carga: " (number->string (caminhao-volume-carga veiculo)))]))
(check-expect (determina-informacoes CP1) "Possui airbag")
(check-expect (determina-informacoes CP2) "Não possui airbag")
(check-expect (determina-informacoes CP3) "")
(check-expect (determina-informacoes UT1) "Possui tração nas quatro rodas")
(check-expect (determina-informacoes UT2) "Não possui tração nas quatro rodas")
(check-expect (determina-informacoes C1) "Volume total da carga: 50")
(check-expect (determina-informacoes C2) "Volume total da carga: 55")




;; atualiza-passeios-vendidos: Número Montadora -> Montadora
;; Recebe o número de veículos de passeio vendidos no dia e retorna versão atualizada da montadora
;; Exemplo: (atualiza-passeios-vendidos 50 M) (make-montadora 500 50 0 0)
;; Exemplo: (atualiza-passeios-vendidos 0 M) (make-montadora 500 0 0 0)
(define (atualiza-passeios-vendidos num-vendidos montadora)
  (make-montadora (montadora-total-a-ser-enviado montadora)
                   (+ (montadora-vendidos-passeio montadora) num-vendidos)
                   (montadora-vendidos-utilitario montadora)
                   (montadora-vendidos-caminhao montadora)))
(check-expect (atualiza-passeios-vendidos 50 M) (make-montadora 500 50 0 0))
(check-expect (atualiza-passeios-vendidos 0 M) M)


