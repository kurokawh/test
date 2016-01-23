;; add user-emacs-directory definition
;; if the Emacs version is earlier than 23
;; because those versions does not define
;; user-emacs-directory by default.
(when (> emacs-major-version 23)
  (defvar user-emacs-directory "~/.emacs.d"))

;; define add-to-load-path function which
;; adds directories recursively
(defun add-to-load-path (&rest paths)
  (let (path)
    (dolist (path paths paths)
      (let ((default-directory
	      (expand-file-name (concat user-emacs-directory path))))
	(add-to-list 'load-path default-directory)
	(if (fboundp 'normal-top-level-add-subdirs-to-load-path)
	    (normal-top-level-add-subdirs-to-load-path))))))

;; usage
;; this adds all of ~/.emacs.d/{site-lisp,elpa,auto-install} recursively.
(add-to-load-path "site-lisp" "elpa" "auto-install")
