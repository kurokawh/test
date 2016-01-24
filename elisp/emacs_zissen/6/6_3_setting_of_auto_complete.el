;; settings of auto-complete
(when (require 'auto-complete-config nil t)
  (add-to-list 'ac-dictionary-directories
	       "~/.emacs.d/elisp/ac-dict")
  (setq ac-auto-show-menu nil) ; disable auto show menu
;  (define-key ac-mode-map (kbd "M-/") 'auto-complete) ; (override default completion)
  (define-key ac-mode-map (kbd "M-?") 'auto-complete) ; S-M-/ pops up candidates
  (ac-config-default))


