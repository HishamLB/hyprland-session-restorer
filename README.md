# My Project

This is a little project I'm working on to familiarize myself with shell and a bit of hyprland. NO guarantees this will work.
Hyprland does not have session restore built in as far as I know so I'm building one primarily using hyprctl clients. 
Parsing this seems a bit difficult especially with some applications. 
For example, when you save a libreoffice impress session it will show as class: libreoffice-impress in hyprctl clients. To launch libre office I have to pass hyprctl dispatch exec "libreoffice --impress". And so on.

TODO:
Figure out smarter parsing logic for special apps.
Comment out the code.
Clean up.
