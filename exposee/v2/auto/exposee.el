(TeX-add-style-hook
 "exposee"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("geometry" "a4paper") ("fontenc" "T1")))
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "geometry"
    "cleveref"
    "tikz"
    "caption"
    "subcaption"
    "sansmathfonts"
    "fontenc")
   (TeX-add-symbols
    "qemu"
    "dual"
    "llvm"
    "lc")
   (LaTeX-add-labels
    "sec:background"
    "fig:llvm"
    "sec:methodology"
    "sec:related-work"
    "sec:difficulties")
   (LaTeX-add-bibliographies
    "sources.bib"))
 :latex)

