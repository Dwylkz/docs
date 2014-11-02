#!/usr/bin/petite --script

(define e2.1.1
  (lambda ()
    (write (+ (* 1.2 (- 2 1/3)) -8.7))
    (newline)
    (write (+ (+ 2/3 4/9) (- 5/11 4/3)))
    (newline)
    (write (/ (+ 1 1) (+ 2 (/ 1 (+ 1 1/2)))))
    (newline)
    (write (* 1 (* -2 (* 3 (* -4 (* 5 (* -6 7)))))))
    (newline)))
; (e2.1.1)

(define e2.2.5
  (lambda ()
    (write (cons (cons 'a 'b) (cons (cons (cons 'c '()) (cons 'd '())) (cons '() '()))))))
; (e2.2.5)

(define e2.4.1
  (lambda ()

    (define a
      (lambda (a b)
        (let ([a (* 3 a)])
          (+ (- a b) (+ a b)))))
    (write (a 1 1))
    (newline)

    ; (define b
    ;   (lambda (a b c)
    ;     (let ([ls (list a b c)])
    ;       (cons (car ls) (cdr ls)))))
    ; (write (b 1 1 1))
    (newline)))
; (e2.4.1)

(define e2.5.2
  (lambda ()
    (define list
      (lambda x x))
    (write (list 1 2 3 4 5))
    (newline)

    (let ()
      (write "runned"))))
; (e2.5.2)

(define e2.6
  (lambda ()
    (define compose
      (lambda (p1 p2)
        (lambda (x)
          (p1 (p2 x)))))

    (define cadr (compose car cdr))
    (define cddr (compose cdr cdr))
    (define caaar (compose car (compose car car)))

    (write (cadr '(a b c)))
    (newline)
    (write (cddr '(a b c)))
    (newline)
    (write (caaar '(((a b) b) c)))))
; (e2.6)

(define e2.7
  (lambda ()
    (define tree-copy-co
      (lambda (tree co)
        (if (not (pair? tree))
          (co tree)
          (tree-copy-co
              (car tree)
              (lambda (ltree)
                (tree-copy-co
                  (cdr tree)
                  (lambda (rtree)
                    (co (cons rtree ltree)))))))))
    (write (tree-copy-co '((a . b) . c) (lambda (x) x)))))
; (e2.7)

(define e2.8
  (lambda ()
    (define even?
      (lambda (n)
        (or (= n 0)
            (odd? (- n 1)))))

    (define odd?
      (lambda (n)
        (and (not (= n 0))
             (even? (- n 1)))))

    ; (define transpose
    ;   (lambda (ls)
    ;     (cond
    ;       [(null? ls) '()]
    ;       [(null? (cdr ls)) (car ls)]
    ;       [else (let ([ret (transpose (cdr ls))])
    ;               (cons (cons (caar ls) (car ret))
    ;                     (cons (cdar ls) (cdr ret))))])))

    (define transpose
      (lambda (ls)
        (cons (map car ls) (map cdr ls))))

    (write (even? 17))
    (newline)
    (write (odd? 17))
    (newline)
    (write (transpose '((a . 1) (b . 2) (c . 3))))))
; (e2.8)

(define e2.9
  (lambda ()
    (define make-queue
      (lambda ()
        (let ([end (cons 'ignored '())])
          (cons end end))))
    (define emptyq?
      (lambda (q)
        (eqv? (car q) (cdr q))))
    (define putq!
      (lambda (q v)
        (let ([end (cons 'ignored '())])
          (set-car! (cdr q) v)
          (set-cdr! (cdr q) end)
          (set-cdr! q end))))
    (define getq
      (lambda (q)
        (if (emptyq? q)
          (assertion-violation 'getq "empty list" q)
          (caar q))))
    (define delq!
      (lambda (q)
        (if (emptyq? q)
          (assertion-violation 'getq "empty list" q)
          (set-car! q (cdar q)))))
    (define myq (make-queue))

    (define make-counter
      (lambda (next step)
        (lambda ()
            (let ([v next])
              (set! next (+ next step))
              v))))

    (define a 1)
    (define counter (make-counter a -1))

    (define list?
      (lambda (ls)
        (define head ls)
        (define f
          (lambda (ls)
            (or (null? ls)
                (and (pair? ls)
                     (let ([next (cdr ls)])
                       (and (not (eq? head next))
                            (f next)))))))
        (f ls)))

    (define rl (cons 'a 'b))
    (set-cdr! rl rl)

    (write (list? rl))
    ; (write (list? '(a . b)))

    ; (write (counter))
    ; (newline)
    ; (write (counter))
    ; (newline)
    ; (write (counter))
    ; (newline)
    ; (write a)
    ; (newline)

    ; (write (emptyq? myq))
    ; (newline)
    ; (delq! myq)
    ; (getq myq)
    ; (putq! myq 'a)
    ; (putq! myq 'b)
    ; (write (emptyq? myq))
    ; (newline)
    ; (write (getq myq))
    ; (newline)
    ; (delq! myq)
    ; (write (getq myq))
    ; (newline)
    ; (delq! myq)
    ))
; (e2.9)

(define e3.1
  (lambda ()
    ; (let ([x (memv 'a ls)]) (and x (memv 'b x)))
    ; -> ((lambda (x) (and x (memv 'b x))) (memv 'a ls))
    ; -> ((lambda (x) (if x (and (memv 'b x)) #f)) (memv 'a ls))
    ; -> ((lambda (x) (if x (memv 'b x) #f)) (memv 'a ls))

    ; (or (memv x '(a b c)) (list x))
    ; -> (let ([v (memv x '(a b c))]) (if v v (or (list x))))
    ; -> ((lambda (v) (if v v (or (list x)))) (memv x '(a b c)))
    ; -> ((lambda (v) (if v v (list x))) (memv x '(a b c)))

    (define-syntax let*
      (syntax-rules
        ()
        [(_ () b1 b2 ...) (let () b1 b2 ...)]
        [(_ ((x1 e1) (x2 e2) ...) b1 b2 ...)
         (let ((x1 e1)) (let* ((x2 e2) ...) b1 b2 ...))]))

    (define-syntax when
      (syntax-rules
        ()
        [(_ t e1 e2 ...) (if t (begin e1 e2 ...) #f)]))

    (define-syntax unless
      (syntax-rules
        ()
        [(_ t e1 e2 ...) (if (not t) (begin e1 e2 ...) #f)]))

    (define get-count #f)
    (define fibonacci
      (let ([count 0])
        (set! get-count (lambda () count))
        (lambda (x)
          (set! count (+ count 1))
          (cond [(zero? x) 0]
                [(= x 1) 1]
                [else (+ (fibonacci (- x 1)) (fibonacci (- x 2)))]))))

    (define-syntax let
      (syntax-rules
        ()
        [(_ ([x e] ...) b1 b2 ...)
         ((lambda (x ...) b1 b2 ...) e ...)]
        [(_ f ([x e] ...) b1 b2 ...)
         (letrec ([f (lambda (x ...) b1 b2 ...)])
           (f e ...))]))

    (define-syntax or ; incorrect!
      (syntax-rules ()
                    [(_) #f]
                    [(_ e1 e2 ...)
                     (let ([t e1])
                       (if t t (or e2 ...)))]))

    (define factor
      (lambda (x)
        (let f ([x x] [i 2] [step 1])
          (let ([quotent (/ x i)])
            (cond [(> (* i i) x) (list x)]
                  [(integer? quotent) (cons i (f quotent i step))]
                  [else (f x (+ i step) 2)])))))

    (write (factor 16))

    ; (write (let f ([x 10000000])
    ;          (or (= x 0)
    ;              (let g ([x (- x 1)])
    ;                (and (not (= x 0))
    ;                     (f (- x 1)))))))
    ; 
    ; (write (fibonacci 100))
    ; (newline)
    ; (write (get-count))
    ; (write (even? 17))
    ; (write (let ([x 3])
    ;          (unless (= x 0) (set! x (+ x 1)))
    ;          (when (= x 4) (set! x (* x 2)))
    ;          x)) 
    ; (write (let* ([a 5] [b (+ a a)] [c (+ a b)])
    ;          (list a b c)))
    '()))
; (e3.1)

(define e3.3
  (lambda ()
    ; (let ([x (lambda (f i)
    ;            (write i)
    ;            (newline)
    ;            (f f (+ 1 i)))])
    ;   (x x 0))

    ; (let ([k.n (call/cc (lambda (k) (cons k 0)))])
    ;   (let ([k (car k.n)] [n (cdr k.n)])
    ;     (write n)
    ;     (newline)
    ;     (k (cons k (+ 1 n)))))
    
    ; (let ([k (call/cc (lambda (k) k))])
    ;   ((lambda (x) (write x))
    ;    (k 'a)))

    (define production
      (lambda (ls)
        (trace-let f ([ls ls] [prod 1])
          (cond [(null? ls) prod]
                [(zero? (car ls)) 0]
                [else (f (cdr ls) (* (car ls) prod))]))))
    (define make-queue
      (lambda ()
        (let ([end (cons 'ignored '())])
          (cons end end))))
    (define emptyq?
      (lambda (q)
        (eqv? (car q) (cdr q))))
    (define putq!
      (lambda (q v)
        (let ([end (cons 'ignored '())])
          (set-car! (cdr q) v)
          (set-cdr! (cdr q) end)
          (set-cdr! q end))))
    (define getq
      (lambda (q)
        (if (emptyq? q)
          (assertion-violation 'getq "empty list" q)
          (caar q))))
    (define delq!
      (lambda (q)
        (if (emptyq? q)
          (assertion-violation 'getq "empty list" q)
          (set-car! q (cdar q)))))
    
    (define lwp-list (make-queue))
    (define lwp
      (lambda (thunk)
        (putq! lwp-list thunk))) 
    (define start
      (lambda ()
        (let ([p (getq lwp-list)])
          (delq! lwp-list)
          (p))))
    (define start-lwp
      (lambda  ()
        (call/cc
          (lambda (k)
            (set! start-cc k)
            (start)))))
    (define pause
      (lambda ()
        (call/cc
          (lambda (k)
            (lwp (lambda () (k #f)))
            (start)))))
    (define quit
      (lambda (v)
        (if (emptyq? lwp-list)
          (start-cc v)
          (start))))

    (lwp (lambda () (let f () (pause) (display "h") (f))))
    (lwp (lambda () (let f () (pause) (display "e") (f))))
    (lwp (lambda () (let f () (pause) (display "y") (f))))
    (lwp (lambda () (let f () (pause) (display "!") (f))))
    (lwp (lambda ()
           (lwp (lambda () (let f () (pause) (display "b") (f))))
           (quit 0)))
    (lwp (lambda () (let f () (pause) (newline) (f))))
    (start-lwp)

    ; (production '(1 2 3 0 4 5))
    '()))
; (e3.3)

(define e3.4
  (lambda ()
    (define id (lambda (x) x))
    (define reciprocal
      (lambda (n succ fail)
        (if (zero? n)
          (fail)
          (/ 1 n))))

    (define retry #f)
    (define factorial
      (lambda (x)
        (let f ([x x] [k (lambda (x) x)])
          (if (= x 0)
            (begin (set! retry k) (k 1))
            (f (- x 1) (lambda (y) (k (* x y))))))))

    (define reciprocals
      (lambda (ls)
        (let ([break (lambda (x) x)])
          (let f ([ls ls] [k (lambda (x) x)])
            (cond [(null? ls) (k '())]
                  [(zero? (car ls)) (break "zero found")]
                  [else (f (cdr ls)
                           (lambda (y)
                             (k (cons (/ 1 (car ls)) y))))])))))

    ; (write (reciprocals '(2 1/3 5 1/4)))
    ; (newline)
    ; (write (reciprocals '(2 1/3 0 5 1/4)))
    ; (newline)
    ; (write(factorial 10))
    ; (newline)
    ; (write (retry 2))
    ; (newline)
    ; (display (reciprocal 0 id (lambda () "divided by zero")))
    '()))
; (e3.4)

(define e3.5
  (lambda ()
    (define calc #f)
    (let ()
      ; (define do-calc
      ;   (lambda (ek expr)
      ;     (cond
      ;       [(number? expr) expr]
      ;       [(and (list? expr) (= (length expr) 3))
      ;        (let ([op (car expr)] [args (cdr expr)])
      ;          (case op
      ;            [(add) (apply-op ek + args)]
      ;            [(sub) (apply-op ek - args)]
      ;            [(mul) (apply-op ek * args)]
      ;            [(div) (apply-op ek / args)]
      ;            [else (complain ek "invalid operator" op)]))]
      ;       [else (complain ek "invalid expression" expr)])))
      ; (define apply-op
      ;   (lambda (ek op args)
      ;     (op (do-calc ek (car args)) (do-calc ek (cadr args)))))

      ; (define complain
      ;   (lambda (ek msg expr)
      ;     (ek (list msg expr))))

      ; (define-syntax complain
      ;   (syntax-rules
      ;     ()
      ;     [(_ ek msg expr) (ek (list msg expr))]))

      ; (set! calc
      ;   (lambda (expr)
      ;     (call/cc
      ;       (lambda (ek)
      ;         (define do-calc
      ;           (lambda (expr)
      ;             (cond
      ;               [(number? expr) expr]
      ;               [(and (list? expr) (= (length expr) 3))
      ;                (let ([op (car expr)] [args (cdr expr)])
      ;                  (case op
      ;                    [(add) (apply-op + args)]
      ;                    [(sub) (apply-op - args)]
      ;                    [(mul) (apply-op * args)]
      ;                    [(div) (apply-op / args)]
      ;                    [else (complain "invalid operator" op)]))]
      ;               [else (complain "invalid expression" expr)])))
      ;         (define apply-op
      ;           (lambda (op args)
      ;             (op (do-calc (car args)) (do-calc (cadr args)))))
      ;         (define complain
      ;           (lambda (msg expr)
      ;             (ek (list msg expr))))
      ;         (do-calc expr)))))

      (define do-calc
        (lambda (expr)
          (cond
            [(number? expr) expr]
            [(list? expr)
             (let ([op (car expr)] [args (cdr expr)] [len (length expr)])
               (cond
                 [(= len 3) (case op
                              [(add) (apply-op + args)]
                              [(sub) (apply-op - args)]
                              [(mul) (apply-op * args)]
                              [(div) (apply-op / args)]
                              [else (complain  "invalid operator" op)])]
                 [(= len 2) (case op
                              [(minus) (- 0 (do-calc (car args)))]
                              [else (complain  "invalid operator" op)])]
                 [else (complain "invalid operand number" expr)]))]
            [else (complain  "invalid expression" expr)])))
      (define apply-op
        (lambda ( op args)
          (op (do-calc (car args)) (do-calc (cadr args)))))
      (define complain
        (lambda ( msg expr)
          (assertion-violation 'calc msg expr)))
      (set! calc do-calc)
      
      '())

    (write (calc '(minus (add 2 3))))
    (newline)
    (write (calc '(add (mul 3 2) -4)))
    (newline)
    (write (calc '(add (mul 3 2) (div 4))))
    (newline)
    '()))
; (e3.5)

(library
  (grades)
  (export gpa->grade gpa distribution histogram)
  (import (rnrs)) 

  (define in-range?
    (lambda (x n y)
      (and (>= n x) (< n y)))) 

  (define-syntax range-case 
    (syntax-rules (- else)
                  [(_ expr ((x - y) e1 e2 ...) ... [else ee1 ee2 ...])
                   (let ([tmp expr])
                     (cond
                       [(in-range? x tmp y) e1 e2 ...]
                       ...
                       [else ee1 ee2 ...]))]
                  [(_ expr ((x - y) e1 e2 ...) ...)
                   (let ([tmp expr])
                     (cond
                       [(in-range? x tmp y) e1 e2 ...]
                       ...))])) 

  (define letter->number
    (lambda (x)
      (case x
        [(a)  4.0]
        [(b)  3.0]
        [(c)  2.0]
        [(d)  1.0]
        [(f)  0.0]
        [else (assertion-violation 'grade "invalid letter grade" x)]))) 

  (define gpa->grade
    (lambda (x)
      (range-case x
                  [(0.0 - 0.5) 'f]
                  [(0.5 - 1.5) 'd]
                  [(1.5 - 2.5) 'c]
                  [(2.5 - 3.5) 'b]
                  [else 'a]))) 

  (define-syntax gpa
    (syntax-rules ()
                  [(_ g1 g2 ...)
                   (let ([ls (map letter->number
                                  (filter (lambda (x) (not (eq? 'x x)))
                                          '(g1 g2 ...)))])
                     (if (null? ls)
                       'x 
                       (/ (apply + ls) (length ls))))]))

  (define $distribution
    (lambda (ls)
      (define insert-ps
        (lambda (v ls)
          (if (null? ls)
            (assertion-violation
              'distribution
              "unrecognized grade letter" v)
            (let ([c (caar ls)] [g (cadar ls)])
              (if (eq? v g)
                (cons (list (+ 1 c) g) (cdr ls))
                (cons (car ls) (insert-ps v (cdr ls))))))))
      (let f ([ls ls] [d '((0 x) (0 a) (0 b) (0 c) (0 d) (0 f))])
        (if (null? ls)
          d
          (f (cdr ls) (insert-ps (car ls) d))))))

  (define-syntax distribution
    (syntax-rules
      () 
      [(_ g1 g2 ...)
       (cdr ($distribution '(g1 g2 ...)))]))
  
  (define print-pair
    (lambda (port c v)
      (define f
        (lambda (c)
          (if (zero? c)
            '()
            (begin
              (put-char port #\*)
              (f (- c 1))))))
      (put-datum port v)
      (put-string port ": ")
      (f c)
      (put-string port "\n")))
  (define histogram
    (lambda (port ls)
      (if (null? ls)
        '()
        (begin
          (print-pair port (caar ls) (cadar ls))
          (histogram port (cdr ls))))))
  )

(define e3.6
  (lambda ()
    (import (grades))
    (histogram (current-output-port)
               (distribution a b a c c c a f b a))
    (write (distribution a b a c c c a f b a))
    (newline)
    (write (gpa c a c b b))
    (newline)
    (write (gpa c a x c b b))
    (newline)
    (write (gpa x x x x x x))
    (newline)
    (write (gpa->grade 2.8))
    (newline)
    '()))
; (e3.6)

(define e4
  (lambda ()
    (define make-list
      (case-lambda
        [(n) (make-list n #f)]
        [(n x)
         (do ([n n (- n 1)] [ls '() (cons x ls)])
           ((zero? n) ls))]))

    (write (make-list 10 'a))
    ))
(e4)
