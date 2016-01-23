;; read only on Mac.
(when (eq system-type 'darwin)
  ;; setting to tread files properly on mac.
  (require 'ucs-normalize)
  (setq file-name-coding-system 'utf-8-hfs)
  (setq local-coding-system 'utf-8-hfs))


;; disable tool-bar & scroll-bar except for terminal.
(when window-system
  ;; disable tool-bar
  (tool-bar-mode 0)
  ;; disable scroll-bar
  (scroll-bar-mode 0))

;; disable menu-bar except for CocoaEmacs.
(unless (eq window-system 'ns)
  ;; disable menu-bar
  (menu-bar-mode 0))


;; check emacs version
;; add user-emacs-directory only if version is less than 23
(when (> emacs-major-version 23)
  (defvar user-emacs-directory "~/.emacs.d"))

