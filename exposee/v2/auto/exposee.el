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
    "tikz"
    "caption"
    "subcaption"
    "hyperref"
    "cleveref"
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
    "sec:qemu"
    "sec:methodology"
    "fig:byte"
    "fig:bit"
    "fig:schemes"
    "sec:difficulties"
    "sec:related-work")
   (LaTeX-add-bibliographies
    "sources.bib"))
 :latex)

