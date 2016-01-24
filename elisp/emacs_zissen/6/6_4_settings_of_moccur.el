;; setting of color_moccur
(when (require 'color-moccur nil t)
  ;; assign occur-by-moccur to M-o.
  (define-key global-map (kbd "M-o") 'occur-by-moccur)
  ;; AND search with space
  ;(setq moccur-split-word t)
  ;; ignore in directory search
  (add-to-list 'dmoccur-exclusion-mask "\\.DS_Store")
  (add-to-list 'dmoccur-exclusion-mask "^#.+#$")
  ;; use Migemo if it is available.
  (when (and (executable-find "cmigemo")
	     (require 'migemo nil t))
    (setq moccur-use-migemo t))
  ;; load moccur-edit as well.
  (require 'moccur-edit nil t))


;; settings of wgrep
(require 'wgrep nil t)
