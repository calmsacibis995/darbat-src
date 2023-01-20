# $Id: Makefile,v 1.10 2005/02/14 03:44:55 ikuz Exp $
HOMEDISY   = /home/disy
BibDir     = "${HOMEDISY}/lib/BibTeX"
LaTeXEnv   = TEXINPUTS=".:${HOMEDISY}/lib/TeX:${HOMEDISY}/lib/ps:${TEXINPUTS}:"
BibTexEnv  = BIBINPUTS=".:${BibDir}:${BIBINPUTS}:"

LaTeX      = ${LaTeXEnv} latex
BibTeX     = ${BibTexEnv} bibtex
Dvi2Ps    = ${LaTeXEnv} dvips -t a4 -Pwww
Ps2Pdf	   = ps2pdf
Fig2Eps    = fig2dev -L eps
Eps2Pdf	   = epstopdf
mv	   = mv
awk	   = awk

# Allow modifications of the above...
-include Makefile.local


# CONFIGURATION OPTIONS
# =====================

# Write the tex file name here
Target = paper
# or
Target = magpie

# List figures generated from .fig sources in the converted form that is
# sourced into LaTeX: either name1.pstex name1.pstex_t name2.pstex name2.pstex_t
# or name1.eps name2.eps ...  Mixtures are fine.
FigFiles = fig/magpie-overview.eps

# Any other stuff that may be needed

# END CONFIGURATION OPTIONS


# Don't force a printer on people, use your own PRINTER environment!
#PRINTER = early@score
LPR = lpr

all: ${Target}.pdf ${Target}.ps ${Target}.dvi ${Target}.bbl

pdf: ${Target}.pdf

view: ${Target}.ps
	gv ${Target}.ps &

print: ${Target}.ps
	${LPR} -P${PRINTER} $<

clean:
	rm -f *.aux *.toc *.bbl *.blg *.dvi *.log *.pstex* *.eps *.cb *.brf *.out

realclean: clean
	rm -f *~ *.ps *.pdf *.tgz

tar:	realclean
	( p=`pwd` && d=`basename "$$p"` && cd .. && \
	  tar cfz $$d.tgz $$d && \
	  mv $$d.tgz $$d )

${Target}.toc: Makefile ${Target}.tex ${FigFiles}

%.pstex_t: %.pstex
	${Fig2Dev} -L pstex_t -p $< $(patsubst %.pstex,%.fig,$<) $@

%.pstex: %.fig
	${Fig2Dev} -L pstex $< $@

%.pdf: %.eps
	${Eps2Pdf} $<

%.eps: %.fig
	${Fig2Eps} $< $@

%.ps.gz: %.ps
	gzip $@ > $<

%.ps: %.dvi
	${Dvi2Ps} $< -o $@

%.pdf: %.ps
	${Ps2Pdf} $<

%.dvi: %.toc
	${LaTeX} $(patsubst %.toc,%,$<)

%.toc: %.bbl
	${LaTeX} $(patsubst %.bbl,%,$<)

%.bbl: %.tex ${FigFiles} Makefile
	${LaTeX} $(patsubst %.tex,%,$<)
	${BibTeX} $(patsubst %.tex,%,$<)	
# 	Fix BibTeX-generated line breaks that \url doesn't handle correctly:
	${mv} $(patsubst %.tex,%,$<).bbl $(patsubst %.tex,%,$<).bbl~
	${awk} <$(patsubst %.tex,%,$<).bbl~ >$(patsubst %.tex,%,$<).bbl \
		'/%$$/{printf "%s", substr($$0,1,length()-1); next};{print}'
