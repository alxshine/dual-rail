(TeX-add-style-hook
 "presentation"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("beamer" "11pt" "t" "usepdftitle=false" "aspectratio=169")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("hf-tikz" "norndcorners" "customcolors")))
   (add-to-list 'LaTeX-verbatim-environments-local "semiverbatim")
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (TeX-run-style-hooks
    "latex2e"
    "beamer"
    "beamer11"
    "tikz"
    "adjustbox"
    "bm"
    "amsmath"
    "listings"
    "hf-tikz"
    "graphicx")
   (TeX-add-symbols
    '("btrans" 6)
    '("binp" 5)
    '("trans" 2)
    '("hex" 1)
    '("blfootnote" 1)
    "bsep"
    "borr"
    "band"
    "bxor"
    "bror"
    "blsl"
    "vq"
    "addlegendimage")
   (LaTeX-add-environments
    '("customlegend" LaTeX-env-args ["argument"] 0)))
 :latex)

