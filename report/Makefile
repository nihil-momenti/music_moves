default:
	rst2latex.py report.rst | ./transform.rb | rubber-pipe --pdf > report.pdf
	open report.pdf

view:
	zsh -c 'view <( rst2latex.py report.rst | ./transform.rb )'
