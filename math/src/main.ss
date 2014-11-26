#!/usr/bin/petite --script

(define make-matrix
  (lambda (m n)
    (do ([i 0 (+ i 1)]
         [mat (make-vector m 0) mat])
      [(= i n) mat]
      (vector-set! mat i (make-vector m 0)))))
(define matrix-rows
  (lambda (mat)
    (vector-length mat)))
(define matrix-columns
  (lambda (mat)
    (vector-length (vector-ref mat 0))))
(define matrix-ref
  (lambda (mat i j)
    (vector-ref (vector-ref mat i) j)))
(define matrix-set!
  (lambda (mat i j v)
    (vector-set! (vector-ref mat i) j v)))
(define vector-mul-by-scalar!
  (lambda (vec s)
    (do [(i 0 (+ i 1))]
      [(= i (vector-length vec)) vec]
      (vector-set! vec i (* (vector-ref vec i) s)))))
(define vector-add-by-scaled-vector!
  (lambda (lhs rhs scalar)
    (do [(i 0 (+ i 1))]
      [(= i (vector-length lhs)) lhs]
      (vector-set! lhs i (+ (vector-ref lhs i) (* (vector-ref rhs i) scalar))))))
(define matrix-swap-row!
  (lambda (mat i j)
    (let ([t (vector-ref mat i)])
      (vector-set! mat i (vector-ref mat j))
      (vector-set! mat j t))))

(define m (make-matrix 2 2))
(matrix-set! m 0 1 10)
(vector-mul-by-scalar! (vector-ref m 0) 100)
(vector-add-by-scaled-vector! (vector-ref m 1) (vector-ref m 0) 2)
(matrix-swap-row! m 0 1)
(display m)
