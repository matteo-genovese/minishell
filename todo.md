# TODO

## Tasks

- [x] parser token wrapper

## FIX

- [x] here doc 				Edofo
- [x] fix split sui pipe e sulle redirect	Starry
- [x] esecuzione builtin 			Federico
fixare attesa cat (?)
- [x] fixa echo				Matteo
- [x] redirect file descriptor esplicito
- [x] free if execve error correctly free command**
- [x] errore echo
```sh
echo "|"
# non printa
```
- [x] se scrivo "ciao | " returna un errore su ciao ma resta in attesa
- [x] devo fare exit 2 volte per uscire da minishell
- [x] se scrivo "ls > > file" dovrebbe dare: "bash: syntax error near unexpected token `>'" 
invece mi crea due file ( un file ">" vuoto e un file "file" con il risultato del ls)
- [x] errore redirect
```sh
cat < nofile(non esiste) > file2
# -> errore sbagliato
```
- [x] se scrivo "ls | | grep test" non ricevo errore
- [x] se scrivo "ls | exit" mi dice "double free or corruption (out)"
comportamento corretto:
"e3r3p1% bash
 edforte@e3r3p1:~/Desktop$ ls | exit
 edforte@e3r3p1:~/Desktop$ exit
 exit
 e3r3p1%"
- [x] se scrivo "echo $USER$HOME" mi stampa: "SER$HOME" invece bash "edforte/nfs/homes/edforte"
- [x] se scrivo "echo $NONEXIST" ottengo "ONEXIST" mentre dovrei ottenere linea vuota
- [x] "export " -> segfault
- [x] export -> error
```sh
"export """
# ritorna
declare -x LANGUAGE=en_US:en
declare -x USER=edforte
declare -x LC_TIME=en_US.UTF-8
declare -x XDG_SESSION_TYPE=x11
declare -x SHLVL=3
declare -x HOME=/nfs/homes/edforte
declare -x OLDPWD=/nfs/homes/edforte/Desktop/minishell
declare -x DESKTOP_SESSION=ubuntu
declare -x GTK_MODULES=gail:atk-bridge
declare -x XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
declare -x LC_MONETARY=en_US.UTF-8
declare -x SYSTEMD_EXEC_PID=20572
declare -x DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/101040/bus
declare -x COLORTERM=truecolor
declare -x LIBVIRT_DEFAULT_URI=qemu:///system
declare -x GTK_IM_MODULE=ibus
declare -x LOGNAME=edforte
declare -x _=/nfs/homes/edforte/Desktop/minishell/./minishell
declare -x XDG_SESSION_CLASS=user
declare -x TERM=xterm-256color
declare -x GNOME_DESKTOP_SESSION_ID=this-is-deprecated
declare -x PATH=/nfs/homes/edforte/bin:/nfs/homes/edforte/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/nfs/homes/edforte/.dotnet/tools
declare -x SESSION_MANAGER=local/e3r3p1.42roma.it:@/tmp/.ICE-unix/20549,unix/e3r3p1.42roma.it:/tmp/.ICE-unix/20549
declare -x GDM_LANG=en
declare -x GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/4bfb1a7a_f0b1_4e0c_ade6_d8ff09c36d98
declare -x XDG_MENU_PREFIX=gnome-
declare -x XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
declare -x XDG_RUNTIME_DIR=/run/user/101040
declare -x LC_ADDRESS=en_US.UTF-8
declare -x DISPLAY=:0
declare -x LANG=en_US.UTF-8
declare -x XDG_CURRENT_DESKTOP=Unity
declare -x DOTNET_BUNDLE_EXTRACT_BASE_DIR=/nfs/homes/edforte/.cache/dotnet_bundle_extract
declare -x LC_TELEPHONE=en_US.UTF-8
declare -x XDG_SESSION_DESKTOP=ubuntu
declare -x XMODIFIERS=@im=ibus
declare -x GNOME_TERMINAL_SERVICE=:1.95
declare -x XAUTHORITY=/nfs/homes/edforte/.Xauthority
declare -x SSH_AUTH_SOCK=/run/user/101040/keyring/ssh
declare -x XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/edforte
declare -x SSH_AGENT_LAUNCHER=gnome-keyring
declare -x KRB5CCNAME=FILE:/tmp/krb5cc_101040_jJeETs
declare -x SHELL=/bin/zsh
declare -x LC_NAME=en_US.UTF-8
declare -x QT_ACCESSIBILITY=1
declare -x GDMSESSION=ubuntu
declare -x DOCKER_HOST=unix:///run/user/101040/docker.sock
declare -x LC_MEASUREMENT=en_US.UTF-8
declare -x LC_IDENTIFICATION=en_US.UTF-8
declare -x GPG_AGENT_INFO=/run/user/101040/gnupg/S.gpg-agent:0:1
declare -x QT_IM_MODULE=ibus
declare -x PWD=/nfs/homes/edforte/Desktop/minishell
declare -x XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
declare -x XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/nfs/homes/edforte/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop
declare -x LC_NUMERIC=en_US.UTF-8
declare -x LC_PAPER=en_US.UTF-8
declare -x VTE_VERSION=6800
declare -x CHROME_DESKTOP=code-url-handler.desktop
declare -x ORIGINAL_XDG_CURRENT_DESKTOP=ubuntu:GNOME
declare -x GDK_BACKEND=x11
declare -x TERM_PROGRAM=vscode
declare -x TERM_PROGRAM_VERSION=1.91.1
declare -x GIT_ASKPASS=/usr/share/code/resources/app/extensions/git/dist/askpass.sh
declare -x VSCODE_GIT_ASKPASS_NODE=/usr/share/code/code
declare -x VSCODE_GIT_ASKPASS_EXTRA_ARGS=
declare -x VSCODE_GIT_ASKPASS_MAIN=/usr/share/code/resources/app/extensions/git/dist/askpass-main.js
declare -x VSCODE_GIT_IPC_HANDLE=/run/user/101040/vscode-git-f5c0b39b3b.sock
declare -x VSCODE_INJECTION=1
declare -x ZDOTDIR=/nfs/homes/edforte
declare -x USER_ZDOTDIR=/nfs/homes/edforte
# return corretto
bash: export: `': not a valid identifier
```
- [x] se scrivo ```"echo ciao >>>>>> file"``` lo esegue senza problemi
- [x] errore sbagliato
```sh
;;;;;
# ritorna
minishell: ;;;;; command not found...
# return corretto
bash: syntax error near unexpected token `;;'

NON DOVENDO GESTIRE ';' STICAZZI FORTISSIMI, VA BENE QUESTO COME ERRORE
```
- [x] errore sbagliato pipe redirect
```sh
echo ciao | > file/.txt
# -> minishell: >: command not found
# return corretto
bash: file/.txt: No such file or directory
```

- [ ] null pointer errore sopra
```sh
Invalid read of size 1
==12872==    at 0x406691: ft_strncmp (ft_strncmp.c:19)
==12872==    by 0x405AC5: is_builtin (fork_processes.c:20)
==12872==    by 0x4048BB: invalid_command (execute_command.c:45)
==12872==    by 0x4060B9: command_error_handler (fork_processes.c:154)
==12872==    by 0x405E3E: child_process (fork_processes.c:91)
==12872==    by 0x404A31: execute_command (execute_command.c:84)
==12872==    by 0x401E8A: main (main.c:277)
==12872==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
```
- [ ] seg fault
```sh
echo dasdśd"asdas's""""da'sadsadsada"sadaasdasd'as
```
