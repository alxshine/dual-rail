(TeX-add-style-hook
 "exposee"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("geometry" "a4paper")))
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "geometry"
    "cleveref"
    "tikz"
    "caption"
    "subcaption")
   (TeX-add-symbols
    "qemu")
   (LaTeX-add-labels
    "sec:background"
    "sec:related-work"
    "sec:intended-methodology")
   (LaTeX-add-bibliographies
    "sources.bib"))
 :latex)

