;;; $DOOMDIR/config.el -*- lexical-binding: t; -*-

;; Place your private configuration here! Remember, you do not need to run 'doom
;; sync' after modifying this file!


;; Some functionality uses this to identify you, e.g. GPG configuration, email
;; clients, file templates and snippets.
(setq user-full-name "Andrew Liddll"
      user-mail-address "aliddell0423@gmail.com")

;; Doom exposes five (optional) variables for controlling fonts in Doom. Here
;; are the three important ones:
;;
;; + `doom-font'
;; + `doom-variable-pitch-font'
;; + `doom-big-font' -- used for `doom-big-font-mode'; use this for
;;   presentations or streaming.
;;
;; They all accept either a font-spec, font string ("Input Mono-12"), or xlfd
;; font string. You generally only need these two:
;; (setq doom-font (font-spec :family "monospace" :size 12 :weight 'semi-light)
;;       doom-variable-pitch-font (font-spec :family "sans" :size 13))

;; There are two ways to load a theme. Both assume the theme is installed and
;; available. You can either set `doom-theme' or manually load a theme with the
;; `load-theme' function. This is the default:
(setq doom-theme 'doom-sourcerer)

;; If you use `org' and don't want your org files in the default location below,
;; change `org-directory'. It must be set before org loads!
(setq org-directory "~/org/")

;; This determines the style of line numbers in effect. If set to `nil', line
;; numbers are disabled. For relative line numbers, set this to `relative'.
(setq display-line-numbers-type t)


;; Here are some additional functions/macros that could help you configure Doom:
;;
;; - `load!' for loading external *.el files relative to this one
;; - `use-package!' for configuring packages
;; - `after!' for running code after a package has loaded
;; - `add-load-path!' for adding directories to the `load-path', relative to
;;   this file. Emacs searches the `load-path' when you load packages with
;;   `require' or `use-package'.
;; - `map!' for binding new keys
;;
;; To get information about any of these functions/macros, move the cursor over
;; the highlighted symbol at press 'K' (non-evil users must press 'C-c c k').
;; This will open documentation for it, including demos of how they are used.
;;
;; You can also try 'gd' (or 'C-c c d') to jump to their definition and see how
;; they are implemented.



;; ==============EMAIL================

(add-to-list 'load-path "/usr/local/share/emacs/site-lisp/mu4e")
;;(require 'smtpmail)
(setq user-mail-address "mreggsaladsandvitch@gmail.com"
      user-full-name  "Andrew Liddell"
      ;; I have my mbsyncrc in a different folder on my system, to keep it separate from the
      ;; mbsyncrc available publicly in my dotfiles. You MUST edit the following line.
      ;; Be sure that the following command is: "mbsync -c ~/.config/mu4e/mbsyncrc -a"
      mu4e-get-mail-command "sync-mail"
      mu4e-update-interval  300
      mu4e-main-buffer-hide-personal-addresses t
      message-send-mail-function 'smtpmail-send-it
      starttls-use-gnutls t
      smtpmail-starttls-credentials '(("smtp.gmail.com" 587 nil nil))
      mu4e-sent-folder "/mreggsaladsandvitch/[Gmail]/Sent Mail"
      mu4e-drafts-folder "/mreggsaladsandvitch/Drafts"
      mu4e-trash-folder "/mreggsaladsandvitch/Trash"
      mu4e-maildir-shortcuts
      '(("/mreggsaladsandvitch/Inbox"      . ?i)
        ("/mreggsaladsandvitch/[Gmail]/Sent Mail" . ?s)
        ("/mreggsaladsandvitch/Drafts"     . ?d)
        ("/mreggsaladsandvitch/Trash"      . ?t)))

;; ==============SEND-EMAIL================
 (defvar my-mu4e-account-alist
   '(("mreggsaladsandvitch"
      (mu4e-sent-folder "/mreggsaladsandvitch/[Gmail]/Sent Mail")
      (mu4e-drafts-folder "/mreggsaladsandvitch/Drafts")
      (mu4e-trash-folder "/mreggsaladsandvitch/Trash")
      (mu4e-compose-signature
        (concat
          "Andrew Liddell\n"
          "mreggsaladsandvitch@gmail.com\n"))
      (user-mail-address "mreggsaladsandvitch@gmail.com")
      (smtpmail-default-smtp-server "smtp.gmail.com")
      (smtpmail-smtp-server "smtp.gmail.com")
      (smtpmail-smtp-user "mreggsaladsandvitch@gmail.com")
      (smtpmail-stream-type starttls)
      (smtpmail-smtp-service 587))
     ("aliddell"
      (mu4e-sent-folder "/aliddell/[Gmail]/Sent Mail")
      (mu4e-drafts-folder "/aliddell/Drafts")
      (mu4e-trash-folder "/aliddell/Trash")
      (mu4e-compose-signature
        (concat
          "Andrew Liddell\n"
          "aliddell0423@gmail.com\n"))
      (user-mail-address "aliddell0423@gmail.com")
      (smtpmail-default-smtp-server "smtp.gmail.com")
      (smtpmail-smtp-server "smtp.gmail.com")
      (smtpmail-smtp-user "aliddell0423@gmail.com")
      (smtpmail-stream-type starttls)
      (smtpmail-smtp-service 587))
     ("ajl496"
      (mu4e-sent-folder "/ajl496/Sent")
      (mu4e-drafts-folder "/ajl496/Drafts")
      (mu4e-trash-folder "/ajl496/Trash")
      (mu4e-compose-signature
        (concat
          "Andrew Liddell\n"
          "ajl496@nau.edu\n"))
      (user-mail-address "ajl496@nau.edu")
      (smtpmail-default-smtp-server "smtp.gmail.com")
      (smtpmail-smtp-server "smtp.gmail.com")
      (smtpmail-smtp-user "ajl496@nau.edu")
      (smtpmail-stream-type starttls)
      (smtpmail-smtp-service 587))))


(defun my-mu4e-set-account ()
  "Set the account for composing a message."
  (let* ((account
          (if mu4e-compose-parent-message
              (let ((maildir (mu4e-message-field mu4e-compose-parent-message :maildir)))
                (string-match "/\\(.*?\\)/" maildir)
                (match-string 1 maildir))
            (completing-read (format "Compose with account: (%s) "
                                     (mapconcat #'(lambda (var) (car var))
                                                my-mu4e-account-alist "/"))
                             (mapcar #'(lambda (var) (car var)) my-mu4e-account-alist)
                             nil t nil nil (caar my-mu4e-account-alist))))
         (account-vars (cdr (assoc account my-mu4e-account-alist))))
    (if account-vars
        (mapc #'(lambda (var)
                  (set (car var) (cadr var)))
              account-vars)
      (error "No email account found"))))

(add-hook 'mu4e-compose-pre-hook 'my-mu4e-set-account)

;; ==============EMOJIS================
(use-package emojify
  :hook (after-init . global-emojify-mode))

;; ==============RSS-FEED================
(use-package! elfeed-goodies)
(elfeed-goodies/setup)
(setq elfeed-goodies/entry-pane-size 0.8)
(add-hook 'elfeed-show-mode-hook 'visual-line-mode)
(evil-define-key 'normal elfeed-show-mode-map
  (kbd "J") 'elfeed-goodies/split-show-next
  (kbd "K") 'elfeed-goodies/split-show-prev)
(evil-define-key 'normal elfeed-search-mode-map
  (kbd "J") 'elfeed-goodies/split-show-next
  (kbd "K") 'elfeed-goodies/split-show-prev)
(setq elfeed-feeds (quote
                    (("https://rss.app/feeds/zWzYghLTUTgY2ONO.xml" instagram darkirongains)
                     ("https://distrowatch.com/news/dwd.xml" distrowatch linux))))
