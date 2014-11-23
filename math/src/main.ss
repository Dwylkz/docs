#!/usr/bin/petite --script

(define make-matrix
  (lambda (n m)
    (let ([data (vector-map (lambda (x) (make-vector m)) (make-vector n))])
      (lambda (msg)
        (case msg
          [n n]
          [m m]
          [self->string
            (lambda ()
              (do [(i 0 (+ i 1)) (res "" res)]
                [(= i n) res] 
                (set! res
                  (string-append
                    res
                    (do [(j 0 (+ j 1)) (res "" res)]
                      [(= j m) (string-append res "\n")]
                      (set! res
                        (string-append
                          res
                          (format "~a " (vector-ref (vector-ref data i) j)))))))))]
          [self->echelon
            (lambda ()
              (do [(i 0 (+ i 1))]
                [(= i n) '()] 
                (do [(j 0 (+ j 1))]
                  [(= j m) '()])))]
          [ref (lambda (i j) (vector-ref (vector-ref data i) j))]
          [set! (lambda (i j v) (vector-set! (vector-ref data i) j v))]
          [else (assertion-violation 'matrix "invalid method" msg)])))))

(define m (make-matrix 2 2))
((m 'set!) 1 1 2)

(define-syntax def
  (syntax-rules
    ()
    [(_ v) (begin
             (define v 'a))]))

(def fuck)

(write fuck)
(newline)

; (display ((m 'self->echelon)))
(display((m 'self->string)))
