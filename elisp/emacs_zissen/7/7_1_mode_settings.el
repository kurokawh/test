;; setting of yaml-mode
(when (require 'yaml-mode nil t)
  (add-to-list 'auto-mode-alist '("\\.yml$" . yaml-mode)))


;; ruby
(setq ruby-indent-level 3 ; default is 2
      ruby-deep-indent-paren-style nil ; arrange indent in return
      ;; use TAB character in ruby-mode
      ruby-indent-tabs-mode t) ; use TAB.
