;; set English font
;; set ascii font to Menlo.
;; :height is  font size.
(set-face-attribute 'default nil
		    :family "Menlo"
		    :height 120)


;; set Japanese font
;; set ヒラノギ明朝
(set-fontset-font
 nil 'japanese-jisx0208
 ;; in english
 ;; (font-spec :family "Hiragino Mincho Pro")
 (font-spec :family "ヒラノギ明朝 Pro"))

;; 漢字以外の全角文字のフォントを設定する
;; 日本語の設定をしたあとに、ひらがな・カタカナだけ別のフォントで上書き設定する
;; set to MotoyaCedar
;; U+3000-303F  CJK記号、句読点
;; U+3040-309F  ひらがな
;; U+30A0-30FF  カタカナ
(set-fontset-font
 nil '(#x3040 . #x30ff)
 (font-spec :family "NfMotoyaCedar"))


;; フォントの横幅を調節する
(setq face-font-rescale-alist
      '((".*Menlo.*" . 1.0)
	(".*Hiragino_Mincho_Pro.*" . 1.2)
	(".*nfmotoyacedar-bold.*" . 1.2)
	(".*nfmotoyacedar-medium.*" . 1.2)
	("-cdac$" . 1.3)))


