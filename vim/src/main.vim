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

let xs = [1, 2, 3]
echo xs
unlet xs
