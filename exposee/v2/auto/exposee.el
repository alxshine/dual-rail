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
    "subcaption"
    "arev")
   (TeX-add-symbols
    "qemu"
    "dual"
    "llvm")
   (LaTeX-add-labels
    "sec:background"
    "sec:methodology"
    "sec:related-work"
    "sec:difficulties")
   (LaTeX-add-bibliographies
    "sources.bib"))
 :latex)

