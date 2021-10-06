### EXPORTS ###
set fish_greeting
set TERM "st"
set EDITOR "emacsclient -t -a ''"
set VISUAL "emacsclient -c -a emacs"

# MANPAGER
set -x MANPAGER "sh -c 'col -bx | bat -l man -p'"

# VI MODE
function fish_user_key_bindings
    fish_vi_key_bindings
end
# VI MODE /

# NAVIGATION ALIAS
alias ..='cd ..'
alias ...='cd ../..'
alias .3='cd ../../..'
alias .4='cd ../../../..'
alias .5='cd ../../../../..'

# Functions needed for !! and !$
function __history_previous_command
  switch (commandline -t)
  case "!"
    commandline -t $history[1]; commandline -f repaint
  case "*"
    commandline -i !
  end
end

function __history_previous_command_arguments
  switch (commandline -t)
  case "!"
    commandline -t ""
    commandline -f history-token-search-backward
  case "*"
    commandline -i '$'
  end
end
# The bindings for !! and !$
if [ $fish_key_bindings = fish_vi_key_bindings ];
  bind -Minsert ! __history_previous_command
  bind -Minsert '$' __history_previous_command_arguments
else
  bind ! __history_previous_command
  bind '$' __history_previous_command_arguments
end

# Function for creating a backup file
# ex: backup file.txt
# result: copies file as file.txt.bak
function backup --argument filename
    cp $filename $filename.bak
end

# Function for copying files and directories, even recursively.
# ex: copy DIRNAME LOCATIONS
# result: copies the directory and all of its contents.
function copy
    set count (count $argv | tr -d \n)
    if test "$count" = 2; and test -d "$argv[1]"
	set from (echo $argv[1] | trim-right /)
	set to (echo $argv[2])
        command cp -r $from $to
    else
        command cp $argv
    end
end

# Starship init
starship init fish | source

# PATHS
fish_add_path /home/andrew/.scripts/
fish_add_path /home/andrew/.mega/usr/bin/
fish_add_path /home/andrew/voidrice/.local/bin/statusbar/
fish_add_path /home/andrew/.emacs.d/bin/
