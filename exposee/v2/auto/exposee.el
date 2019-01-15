(TeX-add-style-hook
 "exposee"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("geometry" "a4paper") ("fontenc" "T1")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
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
    "sec:related-work"
    "sec:conclusion-schedule")
   (LaTeX-add-bibliographies
    "sources.bib"))
 :latex)

