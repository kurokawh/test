;; flymake setting for XML
(defun flymake-xml-init ()
  (list "xmllint" (list "--valid"
			(flymake-init-create-temp-buffer-copy
			 'flymake-create-temp-inplace))))


;; flymake setting for HTML
(defun flymake-html-init ()
  (list "tidy" (list (flymake-init-create-temp-buffer-copy
		      'flymake-create-temp-inplace))))
(add-to-list 'flymake-allowed-file-name-masks
	     '("\\.html\\'" flymake-html-init))
;; tidy error pattern
(add-to-list
 'flymake-err-line-patterns
 '("line \\([0-9]+\\) column \\([0-9]+\\) - \\(Warning\\|Error\\): \\(.*\\)"
   nil 1 2 4))


;; flymake setting for Ruby
(defun flymake-ruby-init ()
  (list "ruby" (list "-c" (flymake-init-create-temp-buffer-copy
			   'flymake-create-temp-inplace))))
(add-to-list 'flymake-allowed-file-name-masks
	     '("\\.rb\\'" flymake-ruby-init))
(add-to-list 'flymake-err-line-patterns
	     '("\\(.*\\):(\\([0-9]+\\)): \\(.*\\)" 1 2 nil 3))
