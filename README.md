kompilator za paskal

-prevodi paskal kod na odgovarajuci LLVM IR kod

-radjen na clang-3.8:

	sudo apt-get install clang-3.8
	sudo ln -s /usr/bin/clang++-3.8 /usr/bin/clang++
	
-podrzava rad sa izrazima (sabiranje, oduzimanje, mnozenje, dijeljenje - div, modul, manje, vece) u broju sa pokretnim zarezom - real

-takodje su podrzana grananja if... then... , kao i if... then... else...

-podrzane su i pretlje oblika: while... do...

-napomena: kljucne rijeci su uvijek mala slova, zbog jednostavnosti leksera

-u datoteci se nalaze i test primjeri kojima se testira tacnost izvrsavanja:
	-test_izrazi.pass
	-test_if_then.pass
	-test_while_do.pass - napomena: linkovati sa -lm, jer koristi mod operator
	-test_kombinovano.pass
	
-kompilacija:
	make
	./pascal < test_kombinovano.pass 2>rez.ll
	llc rez.ll
	gcc rez.s
	./a.out
	
-kompilacija, malo kraci nacin:
	make
	./pascal < test_kombinovano.pass 2>rez.ll
	clang rez.ll
	./a.out
ovaj nacin podrazumijeva sledece preimenovanje:
	sudo ln -s /usr/bin/clang-3.8 /usr/bin/clang