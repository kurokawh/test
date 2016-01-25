;; setting of psvn
;; delay load until start using psvn function.
(when (executable-find "svn")
  (setq svn-status-verbose nil)
  (autoload 'svn-status "psvn" "Run `svn status'." t))

;; setting of Egg (git front-end)
(when (executable-find "git")
  (require 'egg nil t))
