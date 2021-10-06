#
# ~/.bash_profile
#


[[ (fgconsole 2>/dev/null) == 1 ]] && exec startx -- vt1


[[ -f ~/.bashrc ]] && . ~/.bashrc
