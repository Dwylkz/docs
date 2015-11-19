'(display "hello sicp")
'(newline)

(define (ex1.5)
  (define (p) (p))
  (define (test x y)
    (if (= x 0)
      0
      y))
  (display (test 0 (p))))
'(ex1.5)

(define EPS 1e-5)
(define SQRT-TEST 0.0001000009)

(define (gen-iter good-enough? improve guess x)
  (if (good-enough? guess x)
    guess
    (gen-iter good-enough? improve (improve guess x) x)))

(define (sqrt-iter-g good-enough? guess x)
  (gen-iter good-enough? improve guess x))

(define (sqrt-iter guess x)
  (sqrt-iter-g good-enough? guess x))

(define (improve guess x)
  (average guess (/ x guess)))

(define (average x y)
  (/ (+ x y) 2))

(define (sqrt-diff guess x)
  (abs (- (square guess) x)))

(define (good-enough? guess x)
  (< (sqrt-diff guess x) EPS))

(define (square x)
  (* x x))

(define (sqrt x)
  (sqrt-iter 1.0 x))

(define (eg1.1.7)
  (display (sqrt SQRT-TEST))
  (display " ")
  (display (sqrt-diff (sqrt SQRT-TEST) SQRT-TEST))
  (newline))
'(eg1.1.7)

(define (ex1.6)
  (define (new-if predicate then-clause else-clause)
    (cond (predicate then-clause)
          (else else-clause)))
  (define (sqrt-iter guess x)
    (new-if (good-enough? guess x)
      guess
      (sqrt-iter (improve guess x)
                 x)))
  (define (sqrt x)
    (sqrt-iter 1.0 x))
  (display (sqrt 2))
  (newline))
'(ex1.6)

(define (ex1.7)
   (define (good-enough? guess x)
     (< (abs (- (improve guess x) guess)) EPS))
   (define (sqrt-iter guess x)
     (sqrt-iter-g good-enough? guess x))
   (define (sqrt x)
     (sqrt-iter 1.0 x))
   (display (sqrt SQRT-TEST))
   (display " ")
   (display (sqrt-diff (sqrt SQRT-TEST) SQRT-TEST))
   (newline))
'(eg1.1.7)
'(ex1.7)

(define (ex1.8)
  (display "ex1.8\n")
  (define (good-enough? guess x)
    (< (abs (- (* guess guess guess) x)) EPS))
  (define (improve guess x)
    (/ (+ (/ x (* guess guess)) (* 2 guess)) 3))
  (define (curt-iter guess x)
    (gen-iter good-enough? improve guess x))
  (define (curt x)
    (curt-iter 1.0 x))
  (display (curt 27)))
(ex1.8)
