all: main.bib main.tex
	pdflatex main
	bibtex main
	pdflatex main
	pdflatex main