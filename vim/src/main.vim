" vim script is a piece of shit
" 1. complicate slient cast
" 2. fuckful let expression
" 3. stupid func .. endfunc wrap charactor
" 4. are you kidding me? a function must start with
" 	this piece of shit? capital? s:? w:? suck my dick
" 5. sb semi dynamic type
" 6. the sublist expression is all-close interval
" 7. xs[l:3] l:3 would compile as a variable!!!! shit
" 	you must use it like this xs[l :3]
" 8. you must unlet i in for-loop what a chaos var-scope

" let l = "string"
" echo l
" 
" let l = 44
" echo l
" 
" let l = 4.4
" echo l
" 
" let l = 4
" echo l
" 
" let l = "string"
" echo l
" 
" unlet l
" let l = [1, 2, 3]
" echo l
" 
" unlet l
" let l = {'a': 'a', 'b': 'b'}
" echo l

" unlet l
" 
" func! A()
" 	echo "hehe"
" 	return 0
" endfunc
" 
" let b:fn = function("A")
" echo b:fn() string(b:fn)
" 
" unlet b:fn

" let dict = {}
" func! dict.fuck(a, b) dict
" 	let self.val = 0
" endfunc
" call dict.fuck(1, [2, 1])
" echo dict
" 
" unlet dict

" let xs = [1, [2, 2, 2], 3]
" let xs += [[1, 23]]
" let l = 1
" echo xs[l :3]
" let ys = xs
" let ys = xs[:]
" let ys = copy(xs)
" let ys = deepcopy(xs)
" echo xs
" echo ys
" let xs[1][1] = "sb"
" echo xs
" echo ys
" echo ys is xs
" 
" unlet xs ys l

" echo 4 == "4"
" echo [4] == ["4"]

" let [a, b] = [1, 2]
" echo a b
" unlet a b

" let xs = [3, 2, 1, 2]
" echo xs
" call insert(xs, 'a')
" call insert(xs, 'a', 1)
" call add(xs, 'a')
" call add(xs, ['a'])
" call remove(xs, 1)
" call extend(xs, ['a'])
" let xs[1:2] = [3, 2]
" echo xs
" echo reverse(uniq(sort(xs)))
" unlet xs

" for i in [1, 2, 3]
" 	echo i
" endfor
" unlet i

" let i = 0
" while i < 100
" 	echo i
" 	let i += 1
" endwhile
" unlet i

" for [x, y; rest] in [[1, 2, 3], [1, 3], [3, 2]]
" 	echo x y rest
" endfor
" unlet x y rest

" delfunc Func
" func Func(a, b, c)
" 	return -1
" endfunc
" 
" let xs = [1, 2, 3]
" 
" let r = call("Func", xs)
" echo r
" unlet xs

" func! F()
" 	 let x = split("a b c a")
" 	 echo x 'len =' len(x)
" 	 echo 'max =' max(x)
" 	 echo 'min =' min(x)
" 	 let i = index(x, 'b')
" 	 echo i
" 	 echo 'a =' count(x, 'a')
" 	 echo join(x, ',')
" 	 let lines = getline(1, 10)
" 	 echo string(lines)
" 	let ys = [1, 2, 3]
" 	exe 'let sum = ' . join(ys, '+')
" 	echo sum
" 	 let s = string(ys)
" 	 echo s
" 	 call map(ys, '">>" . v:val')
" 	 echo ys
" 	 call append('^', x)
" endfunc

" func! F() 
" 	let dict = {'a': 'echo "haha"', 'b': 'echo lala'}
" 	exe dict.a
" 	for k in keys(dict)
" 		echo k
" 	endfor
" 	for k in values(dict)
" 		echo k
" 	endfor
" 	for i in items(dict)
" 		echo i
" 	endfor
" 	" echo filter(dict, 'v:val =~ "haha"')
" 	" call remove(dict, 'b')
" 	" echo dict
" 
" 	" func dict.len() dict
" 	" 	return len(self.a)+len(self.b)
" 	" endfunc
" 	" echo dict.len()
" 	echo max(dict)
" 	echo min(dict)
" 	echo has_key(dict, 'a')
" endfunc

func! F(lnum, ...)
	" echo 'a' ==? 'A'
	" echo 'a' ==# 'A'
	" echo 'a' <=? 'B'
	" echo 'a' <=# 'B'
	" echo 'aabb' =~ 'a*b*'
	" echo 'aabb' !~ 'a*b*'
	" let x = 'abcde'
	" echo x[2:3]
	" echo &cindent $PWD
	" echo @r
	" echo 'jude' a:lnum == 1
	" 			\? "top"
	" 			\: a:lnum == 1000
	" 			\? "last"
	" 			\: a:lnum
	" echo "foo\nbar" =~ "\n"
	" echo "foo\nbar" =~ "\\n"
	" echo getline(".")[col(".")-1]
	" echo 'abc' . 'abc'
	" let dict = {'one': 1, 2: 'two'}
	" echo printf('%.15e', atan(1))
	" echo "\X32"

	" for k in keys(a:)
	" 	echo k "=" a:[k]
	" endfor

	" echo argv()
	" echo bufname(1)
	" echo changenr()
	" echo complete_check()
	" echo cursor([1,1])
	" echo escape("abcd", "a")
	" echo feedkeys("abcd")
	" echo getcwd()
	" echo getfsize(bufname(1))
	" echo getreg()
	" echo printf("(%d, %d)", getwinposx(), getwinposy())
	" echo indent(getline('.'))
	" echo search("echo")
	" echo setline(211, 209)
	" echo wincol()
	" echo cindent('.')
	" echo getpos('.')
	" echo input("fuck>>")
	" echo inputsecret("fuck>>")
	echohl Title
	echo has("cindent")
	echo a:000
	echohl None
	" sleep 10
	let line = getpos('.')[1]
	echo line
	echo prevnonblank(line-1)
	echo indent(getpos('.')[1])
endfunc

call F(19, 1, 1, 1)
